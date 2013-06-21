/**
 *	@file geometry.cpp
 *  @brief The Geometry module simulator (GPU submodule)
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#include "geometry.h"

Geometry::Geometry()
{
    depthRangeN = 0.0;
    depthRangeF = 1.0;
    drawMode = GL_TRIANGLES;
	sCore.shaderType = 0;
}

void Geometry::InitVCD()
{
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

void Geometry::Initialize()
{
    primitiveReady = false;
    fanCnt = false;
    stripCnt = 2;
    InitVCD();
}

/****** Grahphic Related Function ******/

void Geometry::ShaderEXE()
{
	sCore.Init();
	sCore.input = &vtxInput;
	sCore.Exec();
}

void Geometry::PerspectiveCorrection()
{
	float w = vtxInput.attr[0].w;
	vtxInput.attr[0].w = (float)1/w;
	for (int i=1; i<MAX_ATTRIBUTE_NUMBER; i++) {
		if (attrEnable[i] == false)
			continue;
		else{
			vtxInput.attr[i].s = vtxInput.attr[i].s / w;
			vtxInput.attr[i].t = vtxInput.attr[i].t / w;
			vtxInput.attr[i].p = vtxInput.attr[i].p / w;
			vtxInput.attr[i].q = vtxInput.attr[i].q / w;
		}
	}
}

void Geometry::ViewPort()
{
    float x,y,z,w;

    x = vtxInput.attr[0].x;
    y = vtxInput.attr[0].y;
    z = vtxInput.attr[0].z;

    x = x*viewPortW/2 + viewPortLX + viewPortW/2;
    y = y*viewPortH/2 + viewPortLY + viewPortH/2;
    z = z*(depthRangeF-depthRangeN)/2 + (depthRangeF+depthRangeN)/2;

    vtxInput.attr[0].x = x;
    vtxInput.attr[0].y = y;
    vtxInput.attr[0].z = z;
}

/// @todo (elvis#1#): the vertex order has been compromised.
void Geometry::PrimitiveAssembly()
{
    switch (drawMode) {
    case GL_TRIANGLES:
            prim.v[vtxCntDwn-1] = vtxInput;
        break;

    case GL_TRIANGLE_STRIP:
        prim.v[stripCnt] = vtxInput;
        stripCnt = (stripCnt==0)?2:stripCnt-1;
        break;

    case GL_TRIANGLE_FAN:
        if (vtxCntDwn == 1) {
            prim.v[fanCnt] = vtxInput;
            fanCnt = !fanCnt;
        }
        else
            prim.v[vtxCntDwn-1] = vtxInput;
        break;

    default:
        break;
    }

    vtxCntDwn--;

    if (vtxCntDwn == 0)
    {
        primitiveReady = true;

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


