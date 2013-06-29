/**
 *	@file texture_unit.h
 *  @brief Texture unit class
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#ifndef TEXTURE_UNIT_H_INCLUDED
#define TEXTURE_UNIT_H_INCLUDED

#include <cmath>
#include <GLES3/gl3.h>

#include "gpu_type.h"
#include "gpu_config.h"

#ifdef TEXEL_INFO
	#define TEXPRINTF(fmt, ...) \
		do { if (DBG_ON) fprintf(TEXEL_INFO_PTR, fmt, ##__VA_ARGS__); } while (0)
#else
	#define TEXPRINTF(fmt, ...)
#endif //TEXEL_INFO
#ifdef TEXEL_INFO_FILE
	#define TEXEL_INFO_PTR TEXELINFOfp
#else
	#define TEXEL_INFO_PTR stderr
#endif

const int TEX_CACHE_BLOCK_SIZE_ROOT = (int)sqrt(TEX_CACHE_BLOCK_SIZE);
const int TEX_CACHE_BLOCK_SIZE_ROOT_LOG = (int)log2(TEX_CACHE_BLOCK_SIZE_ROOT);

const int TEX_CACHE_ENTRY_SIZE_ROOT = (int)sqrt(TEX_CACHE_ENTRY_SIZE);
const int TEX_CACHE_ENTRY_SIZE_ROOT_LOG = (int)log2(TEX_CACHE_ENTRY_SIZE_ROOT);

class TextureUnit {
public:
    TextureUnit()
    {
        ClearTexCache();
    }

	///@name Texture filtering mode
	///@{
    GLenum minFilter[MAX_TEXTURE_CONTEXT];
    GLenum magFilter[MAX_TEXTURE_CONTEXT];
    ///@}

	///@name Texture Wrap mode on s, t, or r-axis
	///@{
    GLenum wrapS[MAX_TEXTURE_CONTEXT];
    GLenum wrapT[MAX_TEXTURE_CONTEXT];
    ///@}

	textureImage texImage[MAX_TEXTURE_CONTEXT];

	void		ClearTexCache();

	floatVec4	GetTexColor(floatVec4 coordIn, int level, int tid);
    floatVec4	TextureSample(floatVec4 coordIn,
							  int level,
							  floatVec4 scaleFacDX,
							  floatVec4 scaleFacDY,
							  int tid );

    ///statistic
	///@{
	FILE *TEXELINFOfp;

	int hit;
	int miss;
	int coldMiss;
	///@}

private:

	int		CalcTexAdd( short int us, short int ub, short int uo,
						short int vs, short int vb, short int vo,
						int width);
	floatVec4 TexCoordWrap(floatVec4 coordIn, int level, int tid);
    floatVec4 BilinearFilter(floatVec4 coordIn, int level, int tid);
    floatVec4 TrilinearFilter(floatVec4 coordIn, int level, float w_ratio, int tid);

	struct {
        bool            valid[TEX_CACHE_ENTRY_SIZE][TEX_WAY_ASSOCIATION];
        unsigned int	tag[TEX_CACHE_ENTRY_SIZE][TEX_WAY_ASSOCIATION];
        floatVec4       color[TEX_CACHE_ENTRY_SIZE][TEX_CACHE_BLOCK_SIZE][TEX_WAY_ASSOCIATION];
		unsigned char	LRU[TEX_CACHE_ENTRY_SIZE][TEX_WAY_ASSOCIATION];
    }TexCache;
};

#endif // TEXTURE_UNIT_H_INCLUDED
