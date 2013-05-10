#include "geometry.h"

Geometry gm;

Geometry::Geometry()
{
    depthRangeNear = VPNEAR;
    depthRangefar = VPFAR;
}

void Geometry::ViewPort()
{
    float x,y,z,w;
    for (int i=0;i<3;i++){
        x = VtxPrimitive[i].attribute[VtxPrimitive[i].posIndex].a;
        y = VtxPrimitive[i].attribute[VtxPrimitive[i].posIndex].b;
        z = VtxPrimitive[i].attribute[VtxPrimitive[i].posIndex].c;

        x = x*viewPortWidth/2 + viewPortLX + viewPortWidth/2;
        y = y*viewPortHeight/2 + viewPortLY + viewPortHeight/2;
        z = z*(depthRangeFar-depthRangeNear)/2 + (depthRangeFar+depthRangeNear)/2;

        VtxPrimitive[i].attribute[VtxPrimitive[i].posIndex].a = x;
        VtxPrimitive[i].attribute[VtxPrimitive[i].posIndex].b = y;
        VtxPrimitive[i].attribute[VtxPrimitive[i].posIndex].c = z;
    }
}
