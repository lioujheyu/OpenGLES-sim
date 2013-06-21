/**
 *	@file geometry.h
 *  @brief The Geometry module simulator (GPU submodule) header
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include <GLES3/gl3.h>
#include "gpu_config.h"
#include "gpu_type.h"
#include "shader_core.h"

class Geometry{
public:

    vertex      	vtxInput;
    bool        	attrEnable[MAX_ATTRIBUTE_NUMBER];
    primitive   	prim;
    GLenum      	drawMode;

    float       	depthRangeN, depthRangeF;
    int         	viewPortLX, viewPortLY,
					viewPortW, viewPortH;

    bool        	primitiveReady;

					Geometry();
    void        	Initialize();
    void        	InitVCD();    //vtxCntDown

    void 			ShaderEXE();
    void        	PerspectiveCorrection();
    void        	ViewPort();
    void        	PrimitiveAssembly();
    void        	Clipping();
    void        	Culling();

	ShaderCore		sCore;

private:
    int         	vtxCntDwn; // VCD
    int         	stripCnt;
    bool        	fanCnt;

};


#endif
