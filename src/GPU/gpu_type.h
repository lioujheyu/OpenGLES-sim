/**
 *	@file gpu_type.cpp
 *  @brief Data structure for GPU used only
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#ifndef GPU_TYPE_H_INCLUDED
#define GPU_TYPE_H_INCLUDED

#include "../type.h"
#include "gpu_config.h"

/**
 *	@brief Vertex data structure
 *	Only contain the vertex's attribute value pass from user.
 */
struct vertex {
    floatVec4   attr[MAX_ATTRIBUTE_NUMBER];
};

/**
 *	@brief Pixel data structure
 *	Inaddition to attribute value, this pixel structure also contain the x-axis
 *	and y-axis scale factors for each attribute. The pixel's special barycentric
 *	coordinate is also stored here.
 */
struct pixel {
    ///The position will always use the 1st attribute slot in whole GPU design.
    floatVec4   attr[MAX_ATTRIBUTE_NUMBER];
    floatVec4   scaleFacDX[MAX_ATTRIBUTE_NUMBER];//scalefactor[0] is unused.
    floatVec4   scaleFacDY[MAX_ATTRIBUTE_NUMBER];//scalefactor[0] is unused.
    float       baryCenPos3[3];
};

struct primitive{
    vertex v[3];
};

#endif // GPU_TYPE_H_INCLUDED
