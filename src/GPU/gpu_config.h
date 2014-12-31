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
 *	@file gpu_config.h
 *  @brief GPU simulator related configuration and debug setting
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#ifndef GPU_CONFIG_H_INCLUDED
#define GPU_CONFIG_H_INCLUDED

/**
 *	@def USE_SSE
 *	Enable USE_SSE will use x86 SSE instruction set to accelerate vector
 *	operation involved with the variable declared as floatVec4.
 */
#define USE_SSE

/**
 *	@def START_SPLIT_LEVEL
 *	Which tile split level will the tile split unit start? 3 means starting in
 *	16*16, 2 for 8*8, 1 for 4*4, 0 for 2*2. If this number is undefined, the
 *	default value will be set in 3(16*16).
 */
#define START_SPLIT_LEVEL 3


/// @name GPU internal resource configuration.
///@{
/** @def MAX_SHADER_CORE
 *	This option cannot be defined less than 2 because 1 shader core for vertex
 *	shader and another one for fragment shader. Currently it has no effect if
 *	it is larger than 2 until the task scheduler is finished.
 */
#define MAX_SHADER_CORE					2

/** @def SHADER_EXECUNIT
 *	This option defines how many execution unit a shader core has. More
 *	execution unit a shader core has, more thread can be concurrently executed.
 *	It will significantly affect the texture cache performance and increase
 *	the size of total register pool.
 */
#define SHADER_EXECUNIT					256

#define MAX_ATTRIBUTE_NUMBER    		8
#define MAX_VERTEX_UNIFORM_VECTORS		128
#define MAX_FRAGMENT_UNIFORM_VECTORS	16
#define MAX_TEXTURE_CONTEXT	    		2
#define MAX_SHADER_REG_VECTOR			16

#define MAX_UNIFORM_VECTORS  									\
	( MAX_VERTEX_UNIFORM_VECTORS + MAX_FRAGMENT_UNIFORM_VECTORS )
///@}

/**
 *	@def MAX_TEXTURE_MAX_ANISOTROPY
 *	The maximum anisotropic filter ratio that accepts by texture unit
 */
#define MAX_TEXTURE_MAX_ANISOTROPY 8

/**
 *	@def NO_TEX_CACHE
 *	Disable texture cache if this option is defined.
 */
//#define NO_TEX_CACHE

/**
 *	@def IMAGE_MEMORY_OPTIMIZE
 *	IMAGE_MEMORY_OPTIMIZE will tell driver to rearrange the texture image's
 *	sequence in memory by texture cache's block size so that texture cache could
 *	get a whole cache block data in one single burst read.
 *	Note: if NO_TEX_CACHE is defined, IMAGE_MEMORY_OPTIMIZE will be undefined.
 */
#define IMAGE_MEMORY_OPTIMIZE

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
//#define SHOW_TEXCACHE_MISS
///@}

/**
 *	@def DEBUG
 *	Enable Debug mode. The other debug macro define are directly dependent on
 *	this define.
 */
#define DEBUG

/// @name Definition for whether print the defined target's information.
///@{
//#define ASM_INFO
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
#	undef GPU_INFO
#	undef SHADER_INFO
#endif

#ifdef NO_TEX_CACHE
#	undef IMAGE_MEMORY_OPTIMIZE
#endif

#endif // GPU_CONFIG_H_INCLUDED
