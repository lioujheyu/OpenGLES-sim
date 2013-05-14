#include "geometry.h"

Geometry::Geometry()
{
    depthRangeN = VPNEAR;
    depthRangeF = VPFAR;
    drawMode = GL_TRIANGLES;
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
    stripCnt = 0;
    InitVCD();
}


/****** Grahphic Related Function ******/

void Geometry::ShaderEXE()
{

}

void Geometry::ViewPort()
{
    float x,y,z,w;

    x = vtxInput.varying[vtxPosIndx].a;
    y = vtxInput.varying[vtxPosIndx].b;
    z = vtxInput.varying[vtxPosIndx].c;

    x = x*viewPortW/2 + viewPortLX + viewPortW/2;
    y = y*viewPortH/2 + viewPortLY + viewPortH/2;
    z = z*(depthRangeF-depthRangeN)/2 + (depthRangeF+depthRangeN)/2;

    vtxInput.varying[vtxPosIndx].a = x;
    vtxInput.varying[vtxPosIndx].b = y;
    vtxInput.varying[vtxPosIndx].c = z;
}

void Geometry::PrimitiveAssembly()
{
    switch (drawMode) {
    case GL_TRIANGLES:
            vtxPrimitive[vtxCntDwn-1] = vtxInput;
        break;

    case GL_TRIANGLE_STRIP:
        vtxPrimitive[stripCnt] = vtxInput;
        stripCnt = (stripCnt==0)?2:stripCnt--;
        break;

    case GL_TRIANGLE_FAN:
        if (vtxCntDwn == 1) {
            vtxPrimitive[fanCnt] = vtxInput;
            fanCnt = !fanCnt;
        }
        else
            vtxPrimitive[vtxCntDwn-1] = vtxInput;
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


