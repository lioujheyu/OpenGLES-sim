#ifndef RASTERIZER_H_INCLUDED
#define RASTERIZER_H_INCLUDED

#include <stdlib.h>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <GLES3/gl3.h>
#include "gpu_type.h"

typedef struct texture {
    unsigned char  *data[12]; //max: 4096, so there are 12 levels at most.
    int             height;
    int             width;

    bool            mipmap;
    int             level;

    texture() {
        data[0] = NULL;
        level = 0;
    }
}texture;

class Rasterizer
{
public:

    Rasterizer();

    primitive   prim;

    float           Edge[3][3];
    float           area2Reciprocal;
    int             LX, RX;
    int             LY, HY;
    pixel           pixBuffer[4];
    unsigned char*  cBufPtr;
    float*          dBufPtr;
    int             pixBufferP;
    bool            attrEnable[MAX_ATTRIBUTE_NUMBER];
    int             posIndx;
    int             colIndx;

    int             viewPortW, viewPortH;
    bool            TexMappingEn,AlphaBlendingEn,FogEn;
    int             TexMinFilterMode, TexMaxFilterMode;  //Texture filtering mode
    int             TexWrapModeS,TexWrapModeT;
    int             AlphaTestMode,DepthTestMode;
    int             AlphaBlendingMode;
    float           AlphaRef,DepthRef;
    floatVec4		clearColor;
    float			clearDepth;
    int             FogColor[4];

    void            TriangleSetup();
    void            PixelGenerate();
    void            PixelGenerateHiber();
    void            pixelSplit(int x, int y, int level);
    int             CalcTexAdd(short int us,short int ub,short int uo,short int vs,short int vb,short int vo,int level);
    fixColor4       GetTexColor(const unsigned short u, const unsigned short v, const unsigned int level);
    void            TextureMapping();
    void            ShaderEXE();
    void            PerFragmentOp();
    void 			ClearBuffer(unsigned int mask);


    //FILE *TEXfp;
    FILE *TEXDEBUGfp;
    FILE *PIXEL_GENERATE_DEBUGfp;


    texture texImage;
};

extern Rasterizer rm;

#endif


