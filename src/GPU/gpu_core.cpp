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
#ifdef GPU_INFO_FILE
	GPUINFOfp = fopen(GPU_INFO_FILE,"w");
#endif // GPU_INFO

#ifdef PIXEL_INFO_FILE
	PIXELINFOfp = fopen(PIXEL_INFO_FILE,"w");
#endif // PIXEL_INFO_FILE

#ifdef TEXEL_INFO_FILE
	TEXELINFOfp = fopen(TEXEL_INFO_FILE,"w");
#endif // TEXEL_INFO_FILE

    ///clear frame buffer if needed
    if (clearStat) {
		ClearBuffer(clearMask);
		clearStat = false;
		return;
	}

	sCore[0].instPool = VSinstPool;
	sCore[0].instCnt = VSinstCnt;
	sCore[0].uniformPool = uniformPool;
	sCore[0].shaderType= 0;
	sCore[1].instPool = FSinstPool;
	sCore[1].instCnt = FSinstCnt;
	sCore[1].uniformPool = uniformPool;
    sCore[1].shaderType = 1;

    //AlphaRef = 0;
	//DepthRef = 255;
	//AlphaTestMode = GL_ALWAYS;
	//DepthTestMode = GL_LESS;
	//depthTestEnable = false;
	//blendEnable = false;

	InitPrimitiveAssembly();

	tUnit.ClearTexCache();
	sCore[1].tUnit.ClearTexCache();

	for (int i=0; i<MAX_TEXTURE_UNIT; i++) {
		tUnit.minFilter[i] = minFilter[i];
		tUnit.magFilter[i] = magFilter[i];
		tUnit.wrapS[i] = wrapS[i];
		tUnit.wrapT[i] = wrapT[i];
		tUnit.texImage[i] = texImage[i];

		sCore[1].tUnit.minFilter[i] = minFilter[i];
		sCore[1].tUnit.magFilter[i] = magFilter[i];
		sCore[1].tUnit.wrapS[i] = wrapS[i];
		sCore[1].tUnit.wrapT[i] = wrapT[i];
		sCore[1].tUnit.texImage[i] = texImage[i];
	}

    for (int vCnt=0; vCnt<vtxCount; vCnt++) {

		///Each vertex will be injected into Geometry's curVtx here
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

		///Vertex-based operation starts here
        VertexShaderEXE(0, &curVtx);
        PerspectiveCorrection();
        ViewPort();
        PrimitiveAssembly();

        ///Primitive-based operation starts here
        if (primitiveRdy)
        {
            TriangleSetup();

            ///Fragment-based operation starts here
			for(int y=LY; y<HY; y+=16) {
				for(int x=LX; x<RX; x+=16) {
					PIXPRINTF("Recursive Entry:-------(%d,%d)-----\n",x,y);
					pixBufferP = 0;

					pixelSplit(x,y,3);
					for (int i=0; i<pixBufferP; i++) {
						//pixBuffer[i] = ShaderEXE(pixBuffer[i]);
						FragmentShaderEXE(1,&pixBuffer[i]);
						PerFragmentOp(pixBuffer[i]);
					}
				}
			}

			primitiveRdy = false;
        }
    }

    GPUPRINTF("Texture cache hit: %d\n",tUnit.hit);
    GPUPRINTF("Texture cache miss: %d\n",tUnit.miss);

#ifdef GPU_INFO_FILE
	fclose(GPUINFOfp);
#endif // GPU_INFO

#ifdef PIXEL_INFO_FILE
	fclose(PIXELINFOfp);
#endif // PIXEL_INFO_FILE

#ifdef TEXEL_INFO_FILE
	fclose(TEXELINFOfp);
#endif // TEXEL_INFO_FILE

}
