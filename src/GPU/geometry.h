#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include <GLES3/gl3.h>
#include "gpu_type.h"

class Geometry{
public:
    vertex      VtxInput;
    vertex      VtxPrimitive[3];
    int         vtxIndex;
    GLenum      DrawMode;
    float       depthRangeNear, depthRangeFar;

    int viewPortLX, viewPortLY, viewPortWidth, viewPortHeight;

    void        initialize();
    void        ViewPort();



};


#endif
