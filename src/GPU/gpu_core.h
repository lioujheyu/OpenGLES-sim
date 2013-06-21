/**
 *  @file GPU Top module
 *
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 *
 */

#ifndef GPU_CORE_H_INCLUDED
#define GPU_CORE_H_INCLUDED

#include "geometry.h"
#include "rasterizer.h"
#include "gpu_config.h"
#include "gpu_type.h"

class GPU_Core
{
public:

	FILE *GPUINFOfp;

    Geometry    gm;
    Rasterizer  rm;

    int         	vtxCount;
    int         	vtxFirst;
    const void  	*vtxPointer[MAX_ATTRIBUTE_NUMBER];
    int         	attrSize[MAX_ATTRIBUTE_NUMBER];
    bool        	attrEnable[MAX_ATTRIBUTE_NUMBER];

    floatVec4		uniformPool[MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS];
    int				VSinstCnt , FSinstCnt;
    instruction		*VSinstPool, *FSinstPool;
    unsigned int	clearMask;
    bool			clearStat;

    void        	Run();
};

extern GPU_Core gpu;

#endif // GPU_CORE_H_INCLUDED
