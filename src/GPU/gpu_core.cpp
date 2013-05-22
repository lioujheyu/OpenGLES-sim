/**
 *  @file GPU Top module
 *
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 *
 */

#include "gpu_core.h"
#include <stdio.h>

GPU_Core gpu;

void GPU_Core::Run()
{
#ifdef PIXEL_GENERATE_DEBUG
	rm.PIXEL_GENERATE_DEBUGfp = fopen("PixelGenerateDebug.txt","w");
#endif

    gm.Initialize();

    if (clearStat) {
		rm.ClearBuffer(clearMask);
		clearStat = false;
		return;
	}

    //Each vertex will be injected into Geometry's vtxInput here
    for (int vCnt=0;vCnt<vtxCount;vCnt++) {

        for (int attrCnt=0;attrCnt<8;attrCnt++) {
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

        gm.ShaderEXE();
        //gm.PerspectiveCorrection();
        gm.ViewPort();
        gm.PrimitiveAssembly();

        if (gm.primitiveReady)
        {
            gm.primitiveReady = false;

            rm.posIndx =gm.posIndx;
            rm.prim = gm.prim;

            rm.TriangleSetup();
            rm.PixelGenerateHiber();

        }

    }
}
