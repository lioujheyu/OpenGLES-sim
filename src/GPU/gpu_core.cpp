/*
 * Copyright (c) 2013, Liou Jhe-Yu <lioujheyu@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 *	@file gpu_core.cpp
 *  @brief The GPU main loop function Implementation
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#include "gpu_core.h"
#include <stdio.h>

GPU_Core gpu;

void GPU_Core::Run()
{
    //clear frame buffer if needed
    if (clearStat) {
		ClearBuffer(clearMask);
		clearStat = false;
		return;
	}

	PassConfig2SubModule();

	InitPrimitiveAssembly();
	//Clear texture cache when new draw command is arrived.
	///@todo Judge if cleaning texture cache is required.
	for (int i=0; i<MAX_SHADER_CORE; i++)
		sCore[i].texUnit.ClearTexCache();

    //Main loop
    for (int vCnt=0; vCnt<vtxCount; vCnt++) {

		FetchVertexData(vCnt);

		//Vertex-based operation starts here
		///@todo Task scheduler for auto job dispatch
        VertexShaderEXE(0, &curVtx);

        PrimitiveAssembly();

        //Primitive-based operation starts here
        while (!primFIFO.empty()) {
			prim = primFIFO.front();

			if (prim.isGenerated == false) {
				Clipping();

				if (prim.iskilled) {
					primFIFO.pop();
					continue;
				}
			}

			PerspectiveDivision(&prim.v[0]);
			PerspectiveDivision(&prim.v[1]);
			PerspectiveDivision(&prim.v[2]);
			ViewPort(&prim.v[0]);
			ViewPort(&prim.v[1]);
			ViewPort(&prim.v[2]);

            TriangleSetup();
            Culling();

            if (prim.iskilled) {
				totalCulledPrimitive++;
				primFIFO.pop();
				continue;
            }

            //Fragment-based operation starts here
			for(int y=LY; y<=HY; y+=SPLIT_WIDTH) {
				for(int x=LX; x<=RX; x+=SPLIT_WIDTH) {
					PIXPRINTF("Recursive Entry:-------(%d,%d)-----\n",x,y);
					pixBufferP = 0;

					tileSplit(x,y,START_SPLIT_LEVEL);
					for (int i=0; i<pixBufferP/4; i++) {
						///@todo Task scheduler for auto job dispatch
						FragmentShaderEXE(1,
										  &pixBuffer[i*4  ],
										  &pixBuffer[i*4+1],
										  &pixBuffer[i*4+2],
										  &pixBuffer[i*4+3]);

						PerFragmentOp(pixBuffer[i*4  ]);
						PerFragmentOp(pixBuffer[i*4+1]);
						PerFragmentOp(pixBuffer[i*4+2]);
						PerFragmentOp(pixBuffer[i*4+3]);
					}
				}
			}

			primFIFO.pop();
        }
    }

    GPUPRINTF("Total processed vertex: %d\n",totalProcessingVtx);
    GPUPRINTF("Total processed Primitive: %d\n",totalProcessingPrimitive);
    GPUPRINTF("Total added primitives from clipping: %d\n",totalGeneratedPrimitive);
    GPUPRINTF("Total clipped primitives: %d\n",totalClippedPrimitive);
    GPUPRINTF("Total culled Primitive(Include completely outside the clip volume): %d\n",totalCulledPrimitive);
    GPUPRINTF("Tile Split Count: %d\n",tileSplitCnt);
    GPUPRINTF("Total processed pixel: %d\n",totalProcessingPix);
	GPUPRINTF("Ghost pixel: %d\n",totalGhostPix);
	GPUPRINTF("Normal/All processed pixel ratio: %f\n",
			  (float)(totalProcessingPix - totalGhostPix)/totalProcessingPix);
	GPUPRINTF("Final living pixel: %d\n\n",totalLivePix);

	GPUPRINTF("Texture memory access: %.2f MB (%d)\n",
			  (float)dram_64m.accessB/1024/1024,
			  dram_64m.accessB);
	GPUPRINTF("Texture memory access time: %.2f ms (%.2f ns)\n\n",
			  dram_64m.accessTime/1000/1000,
			  dram_64m.accessTime);

    GPUPRINTF("Texture cache hit: %d\n",sCore[1].texUnit.hit);
    GPUPRINTF("Texture cache miss: %d\n",sCore[1].texUnit.miss);
    GPUPRINTF("Texture cache miss rate: %f\n\n",
			   (float)sCore[1].texUnit.miss /
			   (sCore[1].texUnit.hit + sCore[1].texUnit.miss) );

	GPUPRINTF("VShader total executed instruction: %d\n",
			   sCore[0].totalInstructionCnt);
	GPUPRINTF("VShader total executed scale operation: %d\n",
			   sCore[0].totalScaleOperation);
	GPUPRINTF("Vertex Shader Usage: %f\n\n",
			   (float)(sCore[0].totalScaleOperation)/(sCore[0].totalInstructionCnt*4));

	GPUPRINTF("FShader total executed instruction: %d\n",
			   sCore[1].totalInstructionCnt);
	GPUPRINTF("FShader total executed scale operation: %d\n",
			   sCore[1].totalScaleOperation);
	GPUPRINTF("Fragment Shader Usage: %f\n",
			   (float)(sCore[1].totalScaleOperation)/(sCore[1].totalInstructionCnt*4));
	GPUPRINTF("==========================================================\n");

}

GPU_Core::GPU_Core() : sCore({&dram_64m, &dram_64m})
{
	//dram_128m("128MB", 0x8000000);

	for (int i=0; i<MAX_ATTRIBUTE_NUMBER; i++) {
		attrEnable[i] = false;
		varyEnable[i] = false;
	}

	depthRangeN = 0.0;
	depthRangeF = 1.0;
	viewPortLX = viewPortLY = 0.0;

	DepthRef = 255;
	depthTestMode = GL_LESS;
	depthTestEnable = false;
	blendEnable = false;

	totalProcessingPrimitive = totalProcessingPix = totalProcessingVtx =
		totalGhostPix = totalLivePix = totalCulledPrimitive =
		totalGeneratedPrimitive = 0;
	tileSplitCnt = 0;

#if defined(DEBUG) && defined(GPU_INFO) && defined(GPU_INFO_FILE)
	GPUINFOfp = fopen((std::string(GPU_INFO_FILE)+".txt").c_str(),"w");
#endif // GPU_INFO && GPU_INFO_FILE
#if defined(DEBUG) && defined(PIXEL_INFO) && defined(PIXEL_INFO_FILE)
	PIXELINFOfp = fopen((std::string(PIXEL_INFO_FILE)+".txt").c_str(),"w");
#endif // PIXEL_INFO && PIXEL_INFO_FILE
}

GPU_Core::~GPU_Core()
{
#if defined(DEBUG) && defined(GPU_INFO) && defined(GPU_INFO_FILE)
	fclose(GPUINFOfp);
#endif // GPU_INFO && GPU_INFO_FILE
#if defined(DEBUG) && defined(PIXEL_INFO) && defined(PIXEL_INFO_FILE)
	fclose(PIXELINFOfp);
#endif //PIXEL_INFO && PIXEL_INFO_FILE

#if defined(DEBUG) && defined(TEXEL_INFO) && defined(TEXEL_INFO_FILE)
	for (int i=0; i<MAX_SHADER_CORE; i++) {
		fclose(sCore[i].texUnit.TEXELINFOfp);
	}
#endif //TEXEL_INFO && TEXEL_INFO_FILE
}

void GPU_Core::FetchVertexData(uint32_t vCnt)
{
	uint32_t vIdx;

	//Get vertex index
	if (vtxInputMode == 0) //drawArray
		vIdx = vtxFirst + vCnt;
	else { //drawElements
		switch (vtxIndicesType) {
		case GL_UNSIGNED_BYTE:
			vIdx = *( (uint8_t*)vtxIndicesPointer + vCnt );
			break;
		case GL_UNSIGNED_SHORT:
			vIdx = *( (unsigned short*)vtxIndicesPointer + vCnt );
			break;
		case GL_UNSIGNED_INT:
			vIdx = *( (uint32_t*)vtxIndicesPointer + vCnt );
			break;
		}
	}

	//Fetch all data from a index-determined vertex
	for (int attrCnt=0; attrCnt<MAX_ATTRIBUTE_NUMBER; attrCnt++) {
		if (attrEnable[attrCnt]) {
			curVtx.attr[attrCnt].x =
				*( (float*)vtxPointer[attrCnt] + attrSize[attrCnt]*vIdx );
			curVtx.attr[attrCnt].y =
				*( (float*)vtxPointer[attrCnt] + attrSize[attrCnt]*vIdx + 1 );
			if (attrSize[attrCnt] > 2)
				curVtx.attr[attrCnt].z =
					*( (float*)vtxPointer[attrCnt] + attrSize[attrCnt]*vIdx + 2 );
			else
				curVtx.attr[attrCnt].z = 0.0;

			if (attrSize[attrCnt] > 3)
				curVtx.attr[attrCnt].w =
					*( (float*)vtxPointer[attrCnt] + attrSize[attrCnt]*vIdx + 3 );
			else
				curVtx.attr[attrCnt].w = 1.0;
		}
	}

//	printf("%f, %d \n", curVtx.attr[0].x, curVtx.attr[0].ix);
//	curVtx.attr[0].ix = 1;
//	printf("%f, %d \n", curVtx.attr[0].x, curVtx.attr[0].ix);

	curVtx.threadId = totalProcessingVtx++;
}

void GPU_Core::PassConfig2SubModule()
{
	int i,j;
	for (j=0; j<MAX_SHADER_CORE; j++) {
		for (i=0; i<MAX_TEXTURE_CONTEXT; i++) {
			sCore[j].texUnit.minFilter[i] = minFilter[i];
			sCore[j].texUnit.magFilter[i] = magFilter[i];
			sCore[j].texUnit.wrapS[i] = wrapS[i];
			sCore[j].texUnit.wrapT[i] = wrapT[i];
			sCore[j].texUnit.maxAnisoFilterRatio = maxAnisoFilterRatio;
			sCore[j].texUnit.tex2D[i] = tex2D[i];
			sCore[j].texUnit.texCubeNX[i] = texCubeNX[i];
			sCore[j].texUnit.texCubeNY[i] = texCubeNY[i];
			sCore[j].texUnit.texCubeNZ[i] = texCubeNZ[i];
			sCore[j].texUnit.texCubePX[i] = texCubePX[i];
			sCore[j].texUnit.texCubePY[i] = texCubePY[i];
			sCore[j].texUnit.texCubePZ[i] = texCubePZ[i];
		}
#if defined(DEBUG) && defined(TEXEL_INFO) && defined(TEXEL_INFO_FILE)
		sCore[j].texUnit.TEXELINFOfp =
			fopen((std::string(TEXEL_INFO_FILE)+'_'+std::to_string(j)+".txt").c_str(),"w");
#endif //TEXEL_INFO && TEXEL_INFO_FILE
	}
}
