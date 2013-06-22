/**
 *	@file gpu_core.h
 *  @brief The GPU TOP module simulator header
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#ifndef GPU_CORE_H_INCLUDED
#define GPU_CORE_H_INCLUDED

//#include "geometry.h"
#include "rasterizer.h"
#include "gpu_config.h"
#include "gpu_type.h"

class GPU_Core
{
public:

	FILE *GPUINFOfp;

    //Geometry    gm;
    Rasterizer  rm;

    int         	vtxCount;
    int         	vtxFirst;
    const void  	*vtxPointer[MAX_ATTRIBUTE_NUMBER];
    int         	attrSize[MAX_ATTRIBUTE_NUMBER];
    bool        	attrEnable[MAX_ATTRIBUTE_NUMBER];

	GLenum      	drawMode;
    float       	depthRangeN, depthRangeF;
    int         	viewPortLX, viewPortLY,
					viewPortW, viewPortH;

    floatVec4		uniformPool[MAX_VERTEX_UNIFORM_VECTORS+MAX_FRAGMENT_UNIFORM_VECTORS];
    int				VSinstCnt , FSinstCnt;
    instruction		*VSinstPool, *FSinstPool;

    unsigned int	clearMask;
    bool			clearStat;

    void        	Run();

private:
	ShaderCore		sCore[2];

	//Geometry
	vertex      	vtxInput;
	primitive   	prim;

	///How many vertex is insufficient to form a primitive.
    int         	vtxCntDwn;
    int         	stripCnt;
    bool        	fanCnt;
    bool        	primitiveReady;

	///Function module
    void 			VertexShaderEXE(int sid);

    void        	PerspectiveCorrection();
    void        	ViewPort();

    void        	InitPrimitiveAssembly();
    void        	InitVCD();    //vtxCntDown
    void        	PrimitiveAssembly();
    void        	Clipping();
    void        	Culling();



};

extern GPU_Core gpu;

#endif // GPU_CORE_H_INCLUDED
