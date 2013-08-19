/**
 *	@file gpu_type.h
 *  @brief Data structure for GPU used only
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#ifndef GPU_TYPE_H_INCLUDED
#define GPU_TYPE_H_INCLUDED

#include "gpu_config.h"
#include "../common.h"

/**
 *	@brief Unit thread class
 *
 *	Contain the thread's program counter and its id generated from thread pool.
 */
class unitThread
{
public:
	int pc; ///< Program counter
	int threadId; ///< Thread ID
};

/**
 *	@brief Vertex thread class (child class to unit thread)
 *
 *	Contain the vertex's attribute value pass from user.
 */
class vertex : unitThread {
public:
    floatVec4   attr[MAX_ATTRIBUTE_NUMBER];
};

/**
 *	@brief Pixel thread class (child class to unit thread)
 *
 *	In addition to attribute value, this pixel class also contain the x-axis and
 *	y-axis scale factors for each attribute. The pixel's special barycentric
 *	coordinate is also stored here.
 */
class pixel : unitThread {
public:
	pixel()
	{
		isKilled = false;
		isGhost = true;
	}

    //The position will always use the 1st attribute slot in whole GPU design.
    floatVec4   attr[MAX_ATTRIBUTE_NUMBER];

    ///Barycentric Coordinate
    float       baryCenPos3[3];
    bool		isKilled;
    bool		isGhost;
};

struct primitive{
    vertex v[3];
};

#endif // GPU_TYPE_H_INCLUDED
