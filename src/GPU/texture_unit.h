/**
 *	@file texture_unit.h
 *  @brief Texture funtion unit
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#ifndef TEXTURE_UNIT_H_INCLUDED
#define TEXTURE_UNIT_H_INCLUDED

#include <cmath>

#include "gpu_type.h"
#include "gpu_config.h"

const int TEX_CACHE_BLOCK_SIZE_ROOT = (int)sqrt(TEX_CACHE_BLOCK_SIZE);
const int TEX_CACHE_BLOCK_SIZE_ROOT_LOG = (int)log2(TEX_CACHE_BLOCK_SIZE_ROOT);

const int TEX_CACHE_ENTRY_SIZE_ROOT = (int)sqrt(TEX_CACHE_ENTRY_SIZE);
const int TEX_CACHE_ENTRY_SIZE_ROOT_LOG = (int)log2(TEX_CACHE_ENTRY_SIZE_ROOT);

class TextureUnit {
public:
    int minFilter[MAX_TEXTURE_UNIT], magFilter[MAX_TEXTURE_UNIT]; ///<Texture filtering mode
    int wrapS[MAX_TEXTURE_UNIT],wrapT[MAX_TEXTURE_UNIT];
	textureImage texImage[MAX_TEXTURE_UNIT];

	void		ClearTexCache();
    floatVec4	TextureMapping(floatVec4 coordIn, int attrIndx, pixel pixelInput, unsigned char tid);

    ///statistic
	int hit;
	int miss;
	int coldMiss;

private:
	int		CalcTexAdd( short int us, short int ub, short int uo,
						short int vs, short int vb, short int vo,
						int width);
	floatVec4 GetTexColor(floatVec4 coordIn, const unsigned int level, unsigned char tid);
	floatVec4 TexCoordWrap(floatVec4 coordIn, unsigned int level, unsigned char tid);
    floatVec4 BilinearFilter(floatVec4 coordIn, int level, unsigned char tid);
    floatVec4 TrilinearFilter(floatVec4 coordIn, int level, float w_ratio, unsigned char tid);

	struct {
        bool            valid[TEX_CACHE_ENTRY_SIZE][TEX_WAY_ASSOCIATION];
        unsigned int	tag[TEX_CACHE_ENTRY_SIZE][TEX_WAY_ASSOCIATION];
        floatVec4       color[TEX_CACHE_ENTRY_SIZE][TEX_CACHE_BLOCK_SIZE][TEX_WAY_ASSOCIATION];
		unsigned char	LRU[TEX_CACHE_ENTRY_SIZE][TEX_WAY_ASSOCIATION];
    }TexCache;
};

#endif // TEXTURE_UNIT_H_INCLUDED
