#ifndef GPU_CONFIG_H_INCLUDED
#define GPU_CONFIG_H_INCLUDED

/**
 *	GPU implementation config
 */
#define MAX_ATTRIBUTE_NUMBER    8
#define MAX_TEXTURE_UNIT	    2

/**
 *	Enable MIPMAP_LEVEL_TEST will replace the texture color with
 *	level-represented luminance on the textured primitive nomatter
 *	which filter this primitive uses.
 *	level 0 - 255	maximum white
 *		  1 - 225
 *		  2 - 195
 *		  3 - 165
 */
//#define MIPMAP_LEVEL_TEST

//#define PIXEL_GENERATE_DEBUG
//#define TEXDEBUG

#define TEX_CACHE_BLOCK_SIZE_ROOT_LOG 2
#define TEX_CACHE_BLOCK_SIZE_ROOT 4
#define TEX_CACHE_BLOCK_SIZE 16
#define TEX_CACHE_ENTRY_X_LOG 2
#define TEX_CACHE_ENTRY_X 4
#define TEX_CACHE_ENTRY_Y_LOG 2
#define TEX_CACHE_ENTRY_Y 4



#endif // GPU_CONFIG_H_INCLUDED
