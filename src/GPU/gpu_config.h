/**
 *	@file gpu_config.h
 *  @brief GPU simulator related config and debug setting
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#ifndef GPU_CONFIG_H_INCLUDED
#define GPU_CONFIG_H_INCLUDED

#include <cstdio>

/**
 *	GPU implementation config
 */
#define MAX_ATTRIBUTE_NUMBER    		8
#define MAX_VERTEX_UNIFORM_VECTORS		128
#define MAX_FRAGMENT_UNIFORM_VECTORS	16
#define MAX_TEXTURE_UNIT	    		2
#define MAX_SHADER_REG_VECTOR			16


/******************** Texture debuging and setting ********************/
/**
 *	Enable SHOW_MIPMAP_LEVEL will replace the texture color with
 *	level-represented luminance on the textured primitive nomatter
 *	which filter this primitive uses.
 *	level 0 - 255	maximum white
 *		  1 - 225	each level will reduce 30 value from white color
 *		  2 - 195
 *		  3 - 165
 *		  4 - .
 *		      .
 */
//#define SHOW_MIPMAP_LEVEL

/**
 *	The whole texture cache size is determined be
 *	TEX_WAY_ASSOCIATION * TEX_CACHE_BLOCK_SIZE * TEX_CACHE_ENTRY_SIZE * 4B
 */
/**
 *	define how many way association texture cache will use
 *	if TEX_WAY_ASSOCIATION = 1, the cache is direct mapped.
 */
#define TEX_WAY_ASSOCIATION 4

/**
 *	define the texture cache's block and entry size
 */
#define TEX_CACHE_BLOCK_SIZE 16
#define TEX_CACHE_ENTRY_SIZE 16

/**
 *	Enable SHOW_TEXCACHE_COLD_MISS will let texture cache return color red
 *	rather then the origianl texel's color when texture cache cold miss is
 *	occured. This opotion can be enable with SHOW_TEXCACHE_MISS and has no
 *	conflict.
 */
//#define SHOW_TEXCACHE_COLD_MISS

/**
 *	Enable SHOW_TEXCACHE_MISS will let texture cache return color green rather
 *	then the origianl texel's color when texture cache miss is occured. This
 *	opotion can be enable with SHOW_TEXCACHE_COLD_MISS and has no conflict.
 */
//#define SHOW_TEXCACHE_MISS

/**
 *	Debug information
 */
#define DEBUG 1
#define GPU_INFO
//#define PIXEL_INFO
//#define TEXEL_INFO

#define GPU_INFO_FILE "gpu_info.txt"
#define PIXEL_INFO_FILE "pixel_info.txt"
#define TEXEL_INFO_FILE "texel_info.txt"

/***************Debugging marco for simulator use*****************/
#ifdef DEBUG
	#define DBG_ON 1
#else
	#define DBG_ON 0
#endif

#ifdef GPU_INFO
	#define GPUPRINTF(fmt, ...) \
		do { if (DBG_ON) fprintf(GPU_INFO_PTR, fmt, ##__VA_ARGS__); } while (0)
#else
	#define GPUPRINTF(fmt, ...)
#endif //GPU_INFO

#ifdef PIXEL_INFO
	#define PIXPRINTF(fmt, ...) \
		do { if (DBG_ON) fprintf(PIXEL_INFO_PTR, fmt, ##__VA_ARGS__); } while (0)
#else
	#define PIXPRINTF(fmt, ...)
#endif //PIXEL_INFO

#ifdef TEXEL_INFO
	#define TEXPRINTF(fmt, ...) \
		do { if (DBG_ON) fprintf(TEXEL_INFO_PTR, fmt, ##__VA_ARGS__); } while (0)
#else
	#define TEXPRINTF(fmt, ...)
#endif //TEXEL_INFO

#ifdef GPU_INFO_FILE
	#define GPU_INFO_PTR GPUINFOfp
#else
	#define GPU_INFO_PTR stderr
#endif

#ifdef PIXEL_INFO_FILE
	#define PIXEL_INFO_PTR PIXELINFOfp
#else
	#define PIXEL_INFO_PTR stderr
#endif

#ifdef TEXEL_INFO_FILE
	#define TEXEL_INFO_PTR TEXELINFOfp
#else
	#define TEXEL_INFO_PTR stderr
#endif

#endif // GPU_CONFIG_H_INCLUDED

