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
#ifndef DRIVER_H_INCLUDED
#define DRIVER_H_INCLUDED

#include "../context.h"
//#include "gpu_config.h"
#include "gpu_core.h"

#define NO_MODIFIER -1

/**
 *  Write All context status into GPU, and then activate GPU.
 *  @param vtxInputMode This active command is drawArray or drawElement
 */
void ActiveGPU(int vtxInputMode);

//void ActiveGPU2GenMipMap(int tid);	//Use GPU to generate mipmap
void ActiveGPU2CleanBuffer();

/**
 *	Generate mip-map structure image from base level.
 *	@param tid Specified which texture Context's image will be used as source
 *	@param target Specified which texture target(2D, 3D, cubemap) will be used.
 */
void GenMipMap(int tid, GLenum target);	//Use CPU to generate mipmap

void BilinearFilter4MipMap();


/**
 *	Convert NVGP4 instruction into scalar version's IR and then push these
 *	instruction into the given std::vector.
 */
int CheckSwizzleModifier(int modifier);
int NVGP4toScalar(instruction in, std::vector<scalarInstruction> *ISpool);

/**
 *	Copy texture image data into a simulated dram model. This also includes a
 *	image data sequence rearrange in simulated dram model for better cache
 *	performance if @def IMAGE_MEMORY_OPTIMIZE is defined in @file gpu_config.h.
 *	@param tex_ptr The pointer for target textureImage object.
 *	@param dram_ptr The destination address of the simulated dram model.
 */
uint32_t CopyTexData2Dram (textureImage* tex_ptr, uint32_t dram_ptr);


#endif // DRIVER_H_INCLUDED
