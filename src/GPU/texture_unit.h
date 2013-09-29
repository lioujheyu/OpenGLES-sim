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
#include "instruction_def.h"

#ifdef TEXEL_INFO
#	define TEXPRINTF(fmt, ...) \
		do { if (DBG_ON) fprintf(TEXEL_INFO_PTR, fmt, ##__VA_ARGS__); } while (0)
#else
#	define TEXPRINTF(fmt, ...)
#endif //TEXEL_INFO

#ifdef TEXEL_INFO_FILE
#	define TEXEL_INFO_PTR TEXELINFOfp
#else
#	define TEXEL_INFO_PTR stderr
#endif

const int TEX_CACHE_BLOCK_SIZE_ROOT = (int)sqrt(TEX_CACHE_BLOCK_SIZE);
const int TEX_CACHE_BLOCK_SIZE_ROOT_LOG = (int)log2(TEX_CACHE_BLOCK_SIZE_ROOT);

const int TEX_CACHE_ENTRY_SIZE_ROOT = (int)sqrt(TEX_CACHE_ENTRY_SIZE);
const int TEX_CACHE_ENTRY_SIZE_ROOT_LOG = (int)log2(TEX_CACHE_ENTRY_SIZE_ROOT);

#define TEX_2D		0x0
#define CUBE_NEG_X	0x1
#define CUBE_NEG_Y	0x2
#define CUBE_NEG_Z	0x3
#define CUBE_POS_X	0x4
#define CUBE_POS_Y	0x5
#define CUBE_POS_Z	0x6

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
    GLenum wrapR[MAX_TEXTURE_CONTEXT];
    ///@}

	textureImage tex2D[MAX_TEXTURE_CONTEXT];
	textureImage texCubeNX[MAX_TEXTURE_CONTEXT];
	textureImage texCubeNY[MAX_TEXTURE_CONTEXT];
	textureImage texCubeNZ[MAX_TEXTURE_CONTEXT];
	textureImage texCubePX[MAX_TEXTURE_CONTEXT];
	textureImage texCubePY[MAX_TEXTURE_CONTEXT];
	textureImage texCubePZ[MAX_TEXTURE_CONTEXT];

	void		ClearTexCache();

	floatVec4	GetTexColor(const floatVec4 &coordIn, int level, int tid);
    floatVec4	TextureSample(const floatVec4 &coordIn,
							  int level,
							  const floatVec4 &scaleFacDX,
							  const floatVec4 &scaleFacDY,
							  int targetType,
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
	floatVec4 TexCoordWrap(const floatVec4 &coordIn, int level, int tid);
    floatVec4 BilinearFilter(const floatVec4 &coordIn, int level, int tid);
    floatVec4 TrilinearFilter(const floatVec4 &coordIn, int level, float w_ratio, int tid);

	/// Reference texture image address from 2D image or 1 of 6 cube map image;
	textureImage 	*targetImage;
	/// image face selection identifier from 2D image or 1 of 6 cube map image;
	int 			imageSelection;

	/**
	*	@brief Texture cache structure
	*
	*	The whole texture cache size is determined as
	*	TEX_WAY_ASSOCIATION * TEX_CACHE_BLOCK_SIZE * TEX_CACHE_ENTRY_SIZE * 4B
	*/
	struct {
        bool            valid[TEX_CACHE_ENTRY_SIZE][TEX_WAY_ASSOCIATION];
        unsigned int	tag[TEX_CACHE_ENTRY_SIZE][TEX_WAY_ASSOCIATION];
        floatVec4       color[TEX_CACHE_ENTRY_SIZE][TEX_CACHE_BLOCK_SIZE][TEX_WAY_ASSOCIATION];
		unsigned char	RRFlag[TEX_CACHE_ENTRY_SIZE];
    }TexCache;
};

#endif // TEXTURE_UNIT_H_INCLUDED
