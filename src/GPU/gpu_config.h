/**
 *	@file gpu_config.h
 *  @brief GPU simulator related config and debug setting
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#ifndef GPU_CONFIG_H_INCLUDED
#define GPU_CONFIG_H_INCLUDED


/************************** Simulation Setting ************************/
/**
 *	@def USE_SSE
 *	Enable USE_SSE will use x86 SSE instruction set to accelerate vector
 *	operation by those varaible whose type is floatVec4.
 */
#define USE_SSE

/******************** GPU implementation config************************/
#define MAX_SHADER_CORE					3  //No effect now for temporary.

#define MAX_ATTRIBUTE_NUMBER    		8
#define MAX_VERTEX_UNIFORM_VECTORS		128
#define MAX_FRAGMENT_UNIFORM_VECTORS	16
#define MAX_TEXTURE_CONTEXT	    		2
#define MAX_SHADER_REG_VECTOR			16

#define MAX_UNIFORM_VECTORS  									\
	( MAX_VERTEX_UNIFORM_VECTORS + MAX_FRAGMENT_UNIFORM_VECTORS )

/**
 *	@def NO_TEX_CACHE
 *	Whether disable texture cache or not
 */
#define NO_TEX_CACHE
/*************************************************************************
 *	The whole texture cache size is determined be
 *	TEX_WAY_ASSOCIATION * TEX_CACHE_BLOCK_SIZE * TEX_CACHE_ENTRY_SIZE * 4B
 ************************************************************************/
/**
 *	@def TEX_WAY_ASSOCIATION
 *	Define how many way association texture cache will use. If
 *	\ref TEX_WAY_ASSOCIATION = 1, the cache is direct mapped.
 */
#define TEX_WAY_ASSOCIATION 4

///@name Define the texture cache's block and entry size
///@{
#define TEX_CACHE_BLOCK_SIZE 16
#define TEX_CACHE_ENTRY_SIZE 16
///@}

/******************** Texture debugging option ********************/
/**
 *	@def SHOW_MIPMAP_LEVEL
 *	Enable SHOW_MIPMAP_LEVEL will replace the texture color with
 *	level-represented luminance on the textured primitive nomatter
 *	which filter this primitive uses.
 *	level 0 - 1.0	maximum white
 *		  1 - 0.9
 *		  2 - 0.8
 *		  3 - 0.7
 *		  4 - .
 *		      .
 */
//#define SHOW_MIPMAP_LEVEL

/**
 *	@def SHOW_TEXCACHE_COLD_MISS
 *	Enable SHOW_TEXCACHE_COLD_MISS will let texture cache return color red
 *	rather then the origianl texel's color when texture cache cold miss is
 *	occured. This opotion can be enable with SHOW_TEXCACHE_MISS and has no
 *	conflict.
 */
//#define SHOW_TEXCACHE_COLD_MISS

/**
 *	@def SHOW_TEXCACHE_MISS
 *	Enable SHOW_TEXCACHE_MISS will let texture cache return color green rather
 *	then the origianl texel's color when texture cache miss is occured. This
 *	opotion can be enable with SHOW_TEXCACHE_COLD_MISS and has no conflict.
 */
//#define SHOW_TEXCACHE_MISS

/**
 *	Debug information
 */
//#define DEBUG

#define GPU_INFO
#define SHADER_INFO
#define PIXEL_INFO
#define TEXEL_INFO

#define GPU_INFO_FILE "gpu_info"
#define SHADER_INFO_FILE "shader_info"
#define PIXEL_INFO_FILE "pixel_info"
#define TEXEL_INFO_FILE "texel_info"

/***************Debugging marco for simulator use*****************/
#ifdef DEBUG
	#define DBG_ON 1
#else
	#define DBG_ON 0
#endif

#endif // GPU_CONFIG_H_INCLUDED
