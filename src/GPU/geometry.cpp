#include "geometry.h"

Geometry::Geometry()
{
    depthRangeN = 0.0;
    depthRangeF = 1.0;
    drawMode = GL_TRIANGLES;

    posIndx = 0;
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
//	floatVec4 temp = vtxInput.attr[posIndx];
//	floatVec4 row[4];
//	row[0].x =  1; row[0].y =  0; row[0].z =     1; row[0].w = 0;
//	row[1].x =  0; row[1].y =  1; row[1].z =     1; row[1].w = 0;
//	row[2].x =  0; row[2].y =  0; row[2].z = (float)-3; row[2].w = (float)-20;
//	row[3].x =  0; row[3].y =  0; row[3].z =    -1; row[3].w = 0;
//
//	vtxInput.attr[posIndx].x = row[0]*temp;
//	vtxInput.attr[posIndx].y = row[1]*temp;
//	vtxInput.attr[posIndx].z = row[2]*temp;
//	vtxInput.attr[posIndx].w = row[3]*temp;
}

void Geometry::PerspectiveCorrection()
{
	float w = vtxInput.attr[posIndx].w;
	vtxInput.attr[posIndx].w = (float)1/w;
	for (int i=0;i<MAX_ATTRIBUTE_NUMBER;i++){
		if (i == posIndx || attrEnable[i] == false)
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

    x = vtxInput.attr[posIndx].x;
    y = vtxInput.attr[posIndx].y;
    z = vtxInput.attr[posIndx].z;

    x = x*viewPortW/2 + viewPortLX + viewPortW/2;
    y = y*viewPortH/2 + viewPortLY + viewPortH/2;
    z = z*(depthRangeF-depthRangeN)/2 + (depthRangeF+depthRangeN)/2;

    vtxInput.attr[posIndx].x = x;
    vtxInput.attr[posIndx].y = y;
    vtxInput.attr[posIndx].z = z;
}

/// @fixme (elvis#1#): the vertex order has been compromised.
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


