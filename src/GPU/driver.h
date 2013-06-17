#ifndef DRIVER_H_INCLUDED
#define DRIVER_H_INCLUDED

#include "../context.h"
#include "gpu_core.h"

void ActiveGPU();
void ActiveGPU2GenMipMap(int tid);	//Use GPU to generate mipmap
void ActiveGPU2CleanBuffer();
void GenMipMap(int tid);	//Use CPU to generate mipmap

#endif // DRIVER_H_INCLUDED
