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
	for (int i=0; i<MAX_SHADER_CORE; i++)
		sCore[i].texUnit.ClearTexCache();

    for (int vCnt=vtxFirst; vCnt<vtxCount; vCnt++) {

		//Each vertex will be injected into Geometry's curVtx here
        for (int attrCnt=0; attrCnt<MAX_ATTRIBUTE_NUMBER; attrCnt++) {
            if (attrEnable[attrCnt]) {
                curVtx.attr[attrCnt].x =
                    *( (float*)vtxPointer[attrCnt] + attrSize[attrCnt]*vCnt );
                curVtx.attr[attrCnt].y =
                    *( (float*)vtxPointer[attrCnt] + attrSize[attrCnt]*vCnt + 1 );
                if (attrSize[attrCnt] > 2)
                    curVtx.attr[attrCnt].z =
                        *( (float*)vtxPointer[attrCnt] + attrSize[attrCnt]*vCnt + 2 );
                else
                    curVtx.attr[attrCnt].z = 0.0;

                if (attrSize[attrCnt] > 3)
                    curVtx.attr[attrCnt].w =
                        *( (float*)vtxPointer[attrCnt] + attrSize[attrCnt]*vCnt + 3 );
                else
                    curVtx.attr[attrCnt].w = 1.0;
            }
        }

		//Vertex-based operation starts here
		///@todo Task scheduler for auto job dispatch
        VertexShaderEXE(0, &curVtx);
        PerspectiveDivision();
        ViewPort();
        PrimitiveAssembly();

        //Primitive-based operation starts here
        if (primitiveRdy) {
            TriangleSetup();

            //printf("Primitive %d drawing. ", totalPrimitive);
            //printf("Area: %f\n", fabs(constantC/2));

            //Fragment-based operation starts here
			for(int y=LY; y<=HY; y+=16) {
				for(int x=LX; x<=RX; x+=16) {
					PIXPRINTF("Recursive Entry:-------(%d,%d)-----\n",x,y);
					pixBufferP = 0;

					pixelSplit(x,y,3);
					for (int i=0; i<pixBufferP; i++) {
						///@todo Task scheduler for auto job dispatch
						FragmentShaderEXE(1,&pixBuffer[i]);
						PerFragmentOp(pixBuffer[i]);
					}
				}
			}

			primitiveRdy = false;
        }
    }

    GPUPRINTF("Vertex number: %d\n",totalVtx);
    GPUPRINTF("Primitive number: %d\n",totalPrimitive);
    GPUPRINTF("Pixel number: %d\n\n",totalPix);

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
	GPUPRINTF("Fragment Shader Usage: %f\n\n",
			   (float)(sCore[1].totalScaleOperation)/(sCore[1].totalInstructionCnt*4));

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

	totalPrimitive = totalPix = totalVtx = 0;

#ifdef GPU_INFO_FILE
	GPUINFOfp = fopen((std::string(GPU_INFO_FILE)+".txt").c_str(),"w");
#endif // GPU_INFO
#ifdef PIXEL_INFO_FILE
	PIXELINFOfp = fopen((std::string(PIXEL_INFO_FILE)+".txt").c_str(),"w");
#endif // PIXEL_INFO_FILE
}

GPU_Core::~GPU_Core()
{
#ifdef GPU_INFO_FILE
	fclose(GPUINFOfp);
#endif // GPU_INFO
#ifdef PIXEL_INFO_FILE
	fclose(PIXELINFOfp);
#endif // PIXEL_INFO_FILE

#ifdef TEXEL_INFO_FILE
	for (int i=0; i<MAX_SHADER_CORE; i++) {
		fclose(sCore[i].texUnit.TEXELINFOfp);
	}
#endif // TEXEL_INFO_FILE
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
			sCore[j].texUnit.texImage[i] = texImage[i];
		}
#ifdef TEXEL_INFO_FILE
		sCore[j].texUnit.TEXELINFOfp =
			fopen((std::string(TEXEL_INFO_FILE)+'_'+std::to_string(j)+".txt").c_str(),"w");
#endif // TEXEL_INFO_FILE
	}
}
