#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include <GLES3/gl3.h>
#include "gpu_config.h"
#include "../type.h"

class Geometry{
public:
    vertex      vtxInput;
    bool        attrEnable[MAX_ATTRIBUTE_NUMBER];
    primitive   prim;
    GLenum      drawMode;

    float       depthRangeN, depthRangeF;
    int         viewPortLX, viewPortLY,
                viewPortW, viewPortH;

    bool        primitiveReady;
    int         posIndx;

                Geometry();
    void        Initialize();

    void 		ShaderEXE();
    void        PerspectiveCorrection();
    void        ViewPort();
    void        PrimitiveAssembly();
    void        Clipping();
    void        Culling();

    void        InitVCD();    //vtxCntDown

private:
    int         vtxCntDwn; // VCD
    int         stripCnt;
    bool        fanCnt;



};


#endif
