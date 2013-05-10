#ifndef RASTERIZER_H_INCLUDED
#define RASTERIZER_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GL/gl.h"
//#include "GLES3/gl3.h"
#include "RM_define.h"
#include "bitmap.h"
#include "vector_type.h"

typedef struct vertex{
    float pos4[4];  //(x,y,z,w)
    float TexU[2];  //8 texture unit
    float TexV[2];  //8 texture unit
    float color[4]; //(r,g,b,a) in float format

    vertex(){
        pos4[0] = pos4[1] = pos4[2] = pos4[3] = 1.0f;
        TexU[0] = TexV[0] = 0;
        color[0] = color[1] = color[2] = color[3] = 1.0f;
    }
} vertex;

typedef struct pixel {
    float pos4[4];              //(x,y,z,w)
    float baryCentricPos3[3];   //(u,v,w)
    float texU[2];              //8 texture unit
    float texV[2];              //8 texture unit
    float color[4];             //(r,g,b,a)
    float scaleFactorDuDx[2],scaleFactorDuDy[2],scaleFactorDvDx[2],scaleFactorDvDy[2];

    pixel() {
        pos4[0] = pos4[1] = pos4[2] = pos4[3] = 1.0f;
        texU[0] = texV[0] = 0;
        color[0] = color[1] = color[2] = color[3] = 1.0f;
        scaleFactorDuDx[0] = scaleFactorDuDx[0] = scaleFactorDuDy[0] = scaleFactorDuDy[0] = 1.0f;
    }
} pixel;

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

    vertex  vertexREG[3];

    float   Edge[3][3];
    float   area2Reciprocal;
    int     LX, RX;
    int     LY, HY;
    pixel   pixBuffer[4];
    GLubyte ColorBuffer[HEIGHT][WIDTH][4];
    float   DepthBuffer[HEIGHT][WIDTH];
    int     pixBufferP;

    bool    TexMappingEn,AlphaBlendingEn,FogEn;
    int     TexMinFilterMode, TexMaxFilterMode;  //Texture filtering mode
    int     TexWrapModeS,TexWrapModeT;
    int     TexEnvMode;
    int     TexEnvColor[4];
    int     AlphaTestMode,DepthTestMode;
    int     AlphaBlendingMode;
    float   AlphaRef,DepthRef;
    float   ColorClearVal[4];
    int     FogColor[4];

    void        TriangleSetup();
    bool        Inside(int e,int a,int b);
    void        PixelGenerate();
    void        PixelGenerateHiber();
    void        pixelSplit(int x, int y, int level);
    int         CalcTexAdd(short int us,short int ub,short int uo,short int vs,short int vb,short int vo,int level);
    fixColor4   GetTexColor(const unsigned short u, const unsigned short v, const unsigned int level);
    void        TextureMapping();
    void        PerFragmentOp();
    void        DumpImage();

    fixColor4   BilinearFilter(float texU,float texV,int level);
    fixColor4   TrilinearFilter(float texU,float texV,int level, float w_ratio);

    //FILE *TEXfp;
    FILE *TEXDEBUGfp;
    FILE *PIXEL_GENERATE_DEBUGfp;

    struct {
        bool            valid[TEX_CACHE_ENTRY_X*TEX_CACHE_ENTRY_Y];
        int             pos[TEX_CACHE_ENTRY_X*TEX_CACHE_ENTRY_Y];
        fixColor4       color[TEX_CACHE_ENTRY_X*TEX_CACHE_ENTRY_Y][TEX_CACHE_BLOCK_SIZE];
        int             TexCacheHit;
        int             TexCacheMiss;
        int             TexCacheColdMiss;
    } TexCache;

    texture texImage;
};

extern Rasterizer rm;

#endif


