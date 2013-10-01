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
#include "gpu_core.h"

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

#endif // DRIVER_H_INCLUDED
