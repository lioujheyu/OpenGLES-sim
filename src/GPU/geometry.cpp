#include "geometry.h"

Geometry::Geometry()
{
    depthRangeN = VPNEAR;
    depthRangeF = VPFAR;
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


