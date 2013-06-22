/**
 *	@file geometry.cpp
 *  @brief The Geometry related GPU function module
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#include "gpu_core.h"

void GPU_Core::InitPrimitiveAssembly()
{
    primitiveRdy = false;
    fanCnt = false;
    stripCnt = 2;

    switch (drawMode) {
    case GL_TRIANGLES:
    case GL_TRIANGLE_FAN:
    case GL_TRIANGLE_STRIP:
        vtxCntDwn = 3;
        break;
    case GL_LINES:
    case GL_LINE_LOOP:
    case GL_LINE_STRIP:
        vtxCntDwn = 2;
        break;
    default:
        vtxCntDwn = 1;
    }
}

/****** Grahphic Related Function ******/

void GPU_Core::VertexShaderEXE(int sid)
{
	sCore[sid].Init();
	sCore[sid].input = &curVtx;
	sCore[sid].Exec();
}

void GPU_Core::PerspectiveCorrection()
{
	float w = curVtx.attr[0].w;
	curVtx.attr[0].w = (float)1/w;
	for (int i=1; i<MAX_ATTRIBUTE_NUMBER; i++) {
		if (attrEnable[i] == false)
			continue;
		else{
			curVtx.attr[i].s = curVtx.attr[i].s / w;
			curVtx.attr[i].t = curVtx.attr[i].t / w;
			curVtx.attr[i].p = curVtx.attr[i].p / w;
			curVtx.attr[i].q = curVtx.attr[i].q / w;
		}
	}
}

void GPU_Core::ViewPort()
{
    float x,y,z,w;

    x = curVtx.attr[0].x;
    y = curVtx.attr[0].y;
    z = curVtx.attr[0].z;

    x = x*viewPortW/2 + viewPortLX + viewPortW/2;
    y = y*viewPortH/2 + viewPortLY + viewPortH/2;
    z = z*(depthRangeF-depthRangeN)/2 + (depthRangeF+depthRangeN)/2;

    curVtx.attr[0].x = x;
    curVtx.attr[0].y = y;
    curVtx.attr[0].z = z;
}

/// @todo (elvis#1#): the vertex order has been compromised.
void GPU_Core::PrimitiveAssembly()
{
    switch (drawMode) {
    case GL_TRIANGLES:
            prim.v[vtxCntDwn-1] = curVtx;
        break;

    case GL_TRIANGLE_STRIP:
        prim.v[stripCnt] = curVtx;
        stripCnt = (stripCnt==0)?2:stripCnt-1;
        break;

    case GL_TRIANGLE_FAN:
        if (vtxCntDwn == 1) {
            prim.v[fanCnt] = curVtx;
            fanCnt = !fanCnt;
        }
        else
            prim.v[vtxCntDwn-1] = curVtx;
        break;

    default:
        break;
    }

    vtxCntDwn--;

    if (vtxCntDwn == 0)
    {
        primitiveRdy = true;

        switch (drawMode) {
        case GL_TRIANGLES:
            vtxCntDwn = 3;
            break;
        case GL_TRIANGLE_STRIP:
        case GL_TRIANGLE_FAN:
            vtxCntDwn = 1;
            break;
        default:
            break;
        }
    }
}


