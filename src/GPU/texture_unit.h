/*
 * Copyright (c) 2013, Liou Jhe-Yu <lioujheyu@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 *	@file texture_unit.h
 *  @brief Texture unit class
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#ifndef TEXTURE_UNIT_H_INCLUDED
#define TEXTURE_UNIT_H_INCLUDED

#include <cmath>
#include <GLES3/gl3.h>
#include <GLES3/gl2ext.h>

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

    unsigned char maxAnisoFilterRatio;

	textureImage tex2D[MAX_TEXTURE_CONTEXT];
	textureImage texCubeNX[MAX_TEXTURE_CONTEXT];
	textureImage texCubeNY[MAX_TEXTURE_CONTEXT];
	textureImage texCubeNZ[MAX_TEXTURE_CONTEXT];
	textureImage texCubePX[MAX_TEXTURE_CONTEXT];
	textureImage texCubePY[MAX_TEXTURE_CONTEXT];
	textureImage texCubePZ[MAX_TEXTURE_CONTEXT];

	void		ClearTexCache();

/**
 *	Get the texel's color in the specified texture coordinate. You can toggle
 *	\ref NO_TEX_CACHE in \ref gpu_config.h to determine whether this function
 *	use texture cache or not.
 *
 *	@param coordIn 	The target texture coordinate.
 *	@param level 	This target coordinate is belongs to which level.
 *	@param tid 		This target coordinate is belongs to which texContext.
 *
 *	@return the target texel's color
 */
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

/**
 *	This function is to convert 6D block-based texture address and return 1D
 *	address and fetch data in system memory.
 *
 *	@param u,v 		Texture coordinate in 2 dimension directions.
 *	@param s,b,o 	3 block-based hierarchy level, Super block, Block, Offset,
 *	in texture coordinate.
 *
 *	@return 1D address
 */
	int		CalcTexAdd( short int us, short int ub, short int uo,
						short int vs, short int vb, short int vo,
						int width);

/**
 *	Perform texture wrap operation on texture coordinate.
 *
 *	@param coordIn 	The target texture coordinate.
 *	@param level 	This target coordinate is belongs to which level.
 *	@param tid 		This target coordinate is belongs to which texContext.
 *
 *	@return "Wrapped" texture coordinate.
 */
	floatVec4 TexCoordWrap(const floatVec4 &coordIn, int level, int tid);

/**
 *	Perform Bi-linear filter on specified texture coordinate.
 *
 *	@param coordIn The target texture coordinate.
 *	@param level This target coordinate is belongs to which level.
 *	@param tid This target coordinate is belongs to which texture unit.
 *
 *	@return The final color.
 */
    floatVec4 BilinearFilter(const floatVec4 &coordIn, int level, int tid);

/**
 *	Perform Tri-linear filter on specified texture coordinate, this operation is
 *	actually invokes TextureUnit::BilinearFilter() twice.
 *
 *	@param coordIn 	The target texture coordinate.
 *	@param level 	This target coordinate is belongs to which level.
 *	@param w_ratio 	The target coordinate's w-axis ratio for color interpolation.
 *	@param tid 		This target coordinate is belongs to which texContext.
 *
 *	@return The final color.
 */
    floatVec4 TrilinearFilter(const floatVec4 &coordIn, const int level, const float w_ratio, const int tid);

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
