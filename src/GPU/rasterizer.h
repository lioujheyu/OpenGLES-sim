#ifndef RASTERIZER_H_INCLUDED
#define RASTERIZER_H_INCLUDED

#include <stdlib.h>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <GLES3/gl3.h>
#include "gpu_type.h"

struct textureRM
{
    unsigned char  *data[12]; //max: 4096, so there are 12 levels at most.
    int             height;
    int             width;

    bool            mipmap;
    int             level;

    textureRM() {
        data[0] = NULL;
        level = 0;
    }
};

class Rasterizer
{
public:

    Rasterizer();

    primitive   	prim;

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
    int             texIndx;

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
    fixColor4       TextureMapping(float TexUin, float TexVin, int texPtr, int attrIndx, pixel pixelInput);
    pixel           ShaderEXE(pixel pixelInput);
    void            PerFragmentOp();
    void 			ClearBuffer(unsigned int mask);
    fixColor4   	BilinearFilter(float texU,float texV,int level);
    fixColor4   	TrilinearFilter(float texU,float texV,int level, float w_ratio);

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

    textureRM texImage;
};

extern Rasterizer rm;

#endif
