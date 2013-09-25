/**
 *	@file gpu_core.cpp
 *  @brief GPU Top module
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
		totalProcessingVtx++;

		//Vertex-based operation starts here
		///@todo Task scheduler for auto job dispatch
        VertexShaderEXE(0, &curVtx);
		curClipCoord = curVtx.attr[0];

        PerspectiveDivision();
        ViewPort();
        PrimitiveAssembly();

        //Primitive-based operation starts here
        while (!primStack.empty()) {
			prim = primStack.top();
			Clipping();

			if (prim.iskilled) {
				primStack.pop();
				continue;
            }

            TriangleSetup();
            Culling();

            if (prim.iskilled) {
				totalCulledPrimitive++;
				primStack.pop();
				continue;
            }

            //Fragment-based operation starts here
			for(int y=LY; y<=HY; y+=16) {
				for(int x=LX; x<=RX; x+=16) {
					PIXPRINTF("Recursive Entry:-------(%d,%d)-----\n",x,y);
					pixBufferP = 0;

					tileSplit(x,y,3);
					for (int i=0; i<pixBufferP/4; i++) {
						totalProcessingPix += 4;

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

			primStack.pop();
        }
    }

    GPUPRINTF("Total processed vertex: %d\n",totalProcessingVtx);
    GPUPRINTF("Total processed Primitive: %d\n",totalProcessingPrimitive);
    GPUPRINTF("Total culled Primitive: %d\n",totalCulledPrimitive);
    GPUPRINTF("Tile Split Count: %d\n",tileSplitCnt);
    GPUPRINTF("Total processed pixel: %d\n",totalProcessingPix);
	GPUPRINTF("Ghost pixel: %d\n",totalGhostPix);
	GPUPRINTF("Normal/All processed pixel ratio: %f\n",
			  (float)(totalProcessingPix - totalGhostPix)/totalProcessingPix);
	GPUPRINTF("Final living pixel: %d\n\n",totalLivePix);

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

GPU_Core::GPU_Core()
{
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
		totalGhostPix = totalLivePix = totalCulledPrimitive = 0;
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

void GPU_Core::FetchVertexData(unsigned int vCnt)
{
	unsigned int vIdx;

	//Get vertex index
	if (vtxInputMode == 0) //drawArray
		vIdx = vtxFirst + vCnt;
	else { //drawElements
		switch (vtxIndicesType) {
		case GL_UNSIGNED_BYTE:
			vIdx = *( (unsigned char*)vtxIndicesPointer + vCnt );
			break;
		case GL_UNSIGNED_SHORT:
			vIdx = *( (unsigned short*)vtxIndicesPointer + vCnt );
			break;
		case GL_UNSIGNED_INT:
			vIdx = *( (unsigned int*)vtxIndicesPointer + vCnt );
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
