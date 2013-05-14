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
    gm.Initialize();
    //Each vertex will be injected into Geometry's vtxInput here
    for (int vCnt=0;vCnt<vtxCount;vCnt++) {


        for (int attCnt=0;attCnt<8;attCnt++) {
            if (vtxPointer[attCnt] != NULL) {
                gm.vtxInput.varying[attCnt].a =
                    *( (float*)vtxPointer[attCnt] + attribSize[attCnt]*vCnt );
                gm.vtxInput.varying[attCnt].b =
                    *( (float*)vtxPointer[attCnt] + attribSize[attCnt]*vCnt + 1 );
                if (attribSize[attCnt] > 2)
                    gm.vtxInput.varying[attCnt].c =
                        *( (float*)vtxPointer[attCnt] + attribSize[attCnt]*vCnt + 2 );
                else
                    gm.vtxInput.varying[attCnt].c = 0.0;
                if (attribSize[attCnt] > 3)
                    gm.vtxInput.varying[attCnt].d =
                        *( (float*)vtxPointer[attCnt] + attribSize[attCnt]*vCnt + 3 );
                else
                    gm.vtxInput.varying[attCnt].d = 1.0;

                //printf("")
            }

        }

        gm.ShaderEXE();
        vtxPosIndx = gm.vtxPosIndx;
        //gm.PerspectiveCorrection();
        gm.ViewPort();
        gm.PrimitiveAssembly();

        if (gm.primitiveReady)
        {

        }


    }
}
