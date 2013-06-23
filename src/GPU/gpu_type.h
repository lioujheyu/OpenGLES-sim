/**
 *	@file gpu_type.h
 *  @brief Data structure for GPU used only
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#ifndef GPU_TYPE_H_INCLUDED
#define GPU_TYPE_H_INCLUDED

#include "../type.h"
#include "gpu_config.h"

#define VERTEX_SHADER 0
#define FRAGMENT_SHADER 1

/**
 *	@brief Unit thread class
 *	Contain the thread's program counter and it id generated from thread pool
 */
class unitThread
{
public:
	int pc;
	int threadId;
};

/**
 *	@brief Vertex thread class (child class to unit thread)
 *	Contain the vertex's attribute value pass from user.
 */
class vertex : unitThread {
public:
    floatVec4   attr[MAX_ATTRIBUTE_NUMBER];
};

/**
 *	@brief Pixel thread class (child class to unit thread)
 *	Inaddition to attribute value, this pixel class also contain the x-axis and
 *	y-axis scale factors for each attribute. The pixel's special barycentric
 *	coordinate is also stored here.
 */
class pixel : unitThread {
public:
	pixel()
	{
		isKilled == false;
	}

    //The position will always use the 1st attribute slot in whole GPU design.
    floatVec4   attr[MAX_ATTRIBUTE_NUMBER];
    floatVec4   scaleFacDX[MAX_ATTRIBUTE_NUMBER];//scalefactor[0] is unused.
    floatVec4   scaleFacDY[MAX_ATTRIBUTE_NUMBER];//scalefactor[0] is unused.
    float       baryCenPos3[3];
    bool		isKilled;
};

struct primitive{
    vertex v[3];
};

#endif // GPU_TYPE_H_INCLUDED
