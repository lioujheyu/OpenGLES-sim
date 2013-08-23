/**
 *	@file gpu_config.h
 *  @brief GPU simulator related configuration and debug setting
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#ifndef GPU_CONFIG_H_INCLUDED
#define GPU_CONFIG_H_INCLUDED

/**
 *	@def USE_SSE
 *	Enable USE_SSE will use x86 SSE instruction set to accelerate vector
 *	operation involved with the variable whose data type is floatVec4.
 */
#define USE_SSE

/// @name GPU internal resource configuration.
///@{
/** @def MAX_SHADER_CORE
 *	This option cannot be define less than 2 because 1 shader core for vertex
 *	shader and another one for fragment shader. Currently it has no effect if
 *	it is larger than 2 until the task scheduler is finished.
 */
#define MAX_SHADER_CORE					3

#define MAX_ATTRIBUTE_NUMBER    		8
#define MAX_VERTEX_UNIFORM_VECTORS		128
#define MAX_FRAGMENT_UNIFORM_VECTORS	16
#define MAX_TEXTURE_CONTEXT	    		2
#define MAX_SHADER_REG_VECTOR			16

#define MAX_UNIFORM_VECTORS  									\
	( MAX_VERTEX_UNIFORM_VECTORS + MAX_FRAGMENT_UNIFORM_VECTORS )
///@}

/**
 *	@def NO_TEX_CACHE
 *	Disable texture cache if this option is defined.
 */
//#define NO_TEX_CACHE

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

///	@name Texture debugging option
///@{
/**
 *	@def SHOW_TEXCACHE_COLD_MISS
 *	Enable SHOW_TEXCACHE_COLD_MISS will let texture cache return color red
 *	rather then the original texel's color when texture cache cold miss is
 *	occurred. This option can be enable with SHOW_TEXCACHE_MISS and has no
 *	conflict.
 */
//#define SHOW_TEXCACHE_COLD_MISS

/**
 *	@def SHOW_TEXCACHE_MISS
 *	Enable SHOW_TEXCACHE_MISS will let texture cache return color green rather
 *	then the original texel's color when texture cache miss is occurred. This
 *	option can be enable with SHOW_TEXCACHE_COLD_MISS and has no conflict.
 */
#define SHOW_TEXCACHE_MISS
///@}

/**
 *	@def DEBUG
 *	Enable Debug mode. The other debug marco define are directly dependent on
 *	this define.
 */
#define DEBUG

/// @name Definition for whether print the defined target's information.
///@{
#define GPU_INFO
#define SHADER_INFO
//#define PIXEL_INFO
//#define TEXEL_INFO
///@}

/**
 *	@name Specify the file name for information dump.
 *	If file name is empty, the target's information will be printed directly
 *	on screen.
 */
///@{
#define GPU_INFO_FILE "gpu_info"
#define SHADER_INFO_FILE "shader_info"
#define PIXEL_INFO_FILE "pixel_info"
#define TEXEL_INFO_FILE "texel_info"
///@}

/*************** !!! DO NOT TOUCH STUFF BELOW !!! *****************/
#ifdef DEBUG
#	define DBG_ON 1
#else
#	define DBG_ON 0
#	undef SHOW_TEXCACHE_COLD_MISS
#	undef SHOW_TEXCACHE_MISS
#endif

#endif // GPU_CONFIG_H_INCLUDED
