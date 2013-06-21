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
	rm.PIXELINFOfp = fopen(PIXEL_INFO_FILE,"w");
#endif // PIXEL_INFO_FILE

#ifdef TEXEL_INFO_FILE
	rm.TEXELINFOfp = fopen(TEXEL_INFO_FILE,"w");
#endif // TEXEL_INFO_FILE

    gm.Initialize();
    rm.ClearTexCache();

    ///clear frame buffer if needed
    if (clearStat) {
		rm.ClearBuffer(clearMask);
		clearStat = false;
		return;
	}

	gm.sCore.instPool = VSinstPool;
	gm.sCore.instCnt = VSinstCnt;
	gm.sCore.uniformPool = uniformPool;
	rm.sCore.instPool = FSinstPool;
	rm.sCore.instCnt = FSinstCnt;
	rm.sCore.uniformPool = uniformPool;

    ///Each vertex will be injected into Geometry's vtxInput here
    for (int vCnt=0;vCnt<vtxCount;vCnt++) {

        for (int attrCnt=0;attrCnt<MAX_ATTRIBUTE_NUMBER;attrCnt++) {
            if (attrEnable[attrCnt]) {
                gm.attrEnable[attrCnt] = true;
                rm.attrEnable[attrCnt] = true;
                gm.vtxInput.attr[attrCnt].x =
                    *( (float*)vtxPointer[attrCnt] + attrSize[attrCnt]*vCnt );
                gm.vtxInput.attr[attrCnt].y =
                    *( (float*)vtxPointer[attrCnt] + attrSize[attrCnt]*vCnt + 1 );
                if (attrSize[attrCnt] > 2)
                    gm.vtxInput.attr[attrCnt].z =
                        *( (float*)vtxPointer[attrCnt] + attrSize[attrCnt]*vCnt + 2 );
                else
                    gm.vtxInput.attr[attrCnt].z = 0.0;

                if (attrSize[attrCnt] > 3)
                    gm.vtxInput.attr[attrCnt].w =
                        *( (float*)vtxPointer[attrCnt] + attrSize[attrCnt]*vCnt + 3 );
                else
                    gm.vtxInput.attr[attrCnt].w = 1.0;
            }
        }

		///Vertex-based operation starts here
        gm.ShaderEXE();
        gm.PerspectiveCorrection();
        gm.ViewPort();
        gm.PrimitiveAssembly();

        ///Primitive-based operation starts here
        if (gm.primitiveReady)
        {
            gm.primitiveReady = false;

            rm.prim = gm.prim;

            rm.TriangleSetup();

            ///Fragment-based operation starts here
            rm.PixelGenerateHiber();

        }
    }

    GPUPRINTF("Texture cache hit: %d\n",rm.TexCache.hit);
    GPUPRINTF("Texture cache miss: %d\n",rm.TexCache.miss);

#ifdef GPU_INFO_FILE
	fclose(GPUINFOfp);
#endif // GPU_INFO

#ifdef PIXEL_INFO_FILE
	fclose(rm.PIXELINFOfp);
#endif // PIXEL_INFO_FILE

#ifdef TEXEL_INFO_FILE
	fclose(rm.TEXELINFOfp);
#endif // TEXEL_INFO_FILE

}
