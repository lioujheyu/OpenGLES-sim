#ifndef RASTERIZER_H_INCLUDED
#define RASTERIZER_H_INCLUDED

#include <stdlib.h>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <GLES3/gl3.h>
#include "gpu_config.h"
#include "gpu_type.h"

const int TEX_CACHE_BLOCK_SIZE_ROOT = (int)sqrt(TEX_CACHE_BLOCK_SIZE);
const int TEX_CACHE_BLOCK_SIZE_ROOT_LOG = (int)log2(TEX_CACHE_BLOCK_SIZE_ROOT);

const int TEX_CACHE_ENTRY_SIZE_ROOT = (int)sqrt(TEX_CACHE_ENTRY_SIZE);
const int TEX_CACHE_ENTRY_SIZE_ROOT_LOG = (int)log2(TEX_CACHE_ENTRY_SIZE_ROOT);

class Rasterizer
{
public:

	FILE *PIXELINFOfp;
	FILE *TEXELINFOfp;

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
    bool            blendEnable, depthTestEnable;
    int             minFilter[MAX_TEXTURE_UNIT], magFilter[MAX_TEXTURE_UNIT];  //Texture filtering mode
    int             wrapS[MAX_TEXTURE_UNIT],wrapT[MAX_TEXTURE_UNIT];
    int             AlphaTestMode,DepthTestMode;
    int             AlphaBlendingMode;
    float           AlphaRef,DepthRef;
    floatVec4		clearColor;
    float			clearDepth;

    void            TriangleSetup();
    void            PixelGenerate();
    void            PixelGenerateHiber();
    void            pixelSplit(int x, int y, int level);
    pixel           ShaderEXE(pixel pixelInput);
    int             CalcTexAdd( short int us, short int ub, short int uo,
                                short int vs, short int vb, short int vo,
                                int width);
    fixColor4       GetTexColor(floatVec4 coordIn, const unsigned int level, unsigned char tid);
    fixColor4       TextureMapping(floatVec4 coordIn, int attrIndx, pixel pixelInput, unsigned char tid);
    floatVec4		TexCoordWrap(floatVec4 coordIn, unsigned int level, unsigned char tid);
    fixColor4   	BilinearFilter(floatVec4 coordIn, int level, unsigned char tid);
    fixColor4   	TrilinearFilter(floatVec4 coordIn, int level, float w_ratio, unsigned char tid);
    void            PerFragmentOp(pixel pixInput);
    void 			ClearBuffer(unsigned int mask);
    void 			ClearTexCache();

	struct
	{
        bool            valid[TEX_CACHE_ENTRY_SIZE][TEX_WAY_ASSOCIATION];
        unsigned int	tag[TEX_CACHE_ENTRY_SIZE][TEX_WAY_ASSOCIATION];
        fixColor4       color[TEX_CACHE_ENTRY_SIZE][TEX_CACHE_BLOCK_SIZE][TEX_WAY_ASSOCIATION];
		unsigned char	LRU[TEX_CACHE_ENTRY_SIZE][TEX_WAY_ASSOCIATION];
        int             hit;
        int             miss;
        int             coldMiss;
    }TexCache;

    textureImage texImage[MAX_TEXTURE_UNIT];
};

extern Rasterizer rm;

#endif
