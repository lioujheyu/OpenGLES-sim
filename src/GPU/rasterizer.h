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

    vertex  vtxPrimitive[3];

    float   Edge[3][3];
    float   area2Reciprocal;
    int     LX, RX;
    int     LY, HY;
    pixel   pixBuffer[4];
    GLubyte ColorBuffer[1024][512][4];
    float   DepthBuffer[1024][512];
    int     pixBufferP;
    bool    varyingEnable[MAX_VARYING_NUMBER];
    int     vtxPosIndx;

    bool    TexMappingEn,AlphaBlendingEn,FogEn;
    int     TexMinFilterMode, TexMaxFilterMode;  //Texture filtering mode
    int     TexWrapModeS,TexWrapModeT;
    int     AlphaTestMode,DepthTestMode;
    int     AlphaBlendingMode;
    float   AlphaRef,DepthRef;
    float   ColorClearVal[4];
    int     FogColor[4];

    void        TriangleSetup();
    void        PixelGenerate();
    void        PixelGenerateHiber();
    void        pixelSplit(int x, int y, int level);
    int         CalcTexAdd(short int us,short int ub,short int uo,short int vs,short int vb,short int vo,int level);
    fixColor4   GetTexColor(const unsigned short u, const unsigned short v, const unsigned int level);
    void        TextureMapping();
    void        PerFragmentOp();
    void        DumpImage();


    //FILE *TEXfp;
    FILE *TEXDEBUGfp;
    FILE *PIXEL_GENERATE_DEBUGfp;


    texture texImage;
};

extern Rasterizer rm;

#endif


