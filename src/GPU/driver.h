#ifndef DRIVER_H_INCLUDED
#define DRIVER_H_INCLUDED

#include "../context.h"
#include "gpu_core.h"

void ActiveGPU();
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
