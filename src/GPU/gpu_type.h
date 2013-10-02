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
 *	Contain the thread's id generated from thread pool, attribute data, and
 *	kill flag.
 */
class unitThread {
public:
	unitThread() : isKilled(false) {}

	bool isKilled;
	int threadId; ///< Thread ID
	floatVec4   attr[MAX_ATTRIBUTE_NUMBER];
};

/**
 *	@brief Vertex thread class (derived class from unitThread)
 *
 *	The same as the unit thread, this derived class is for preservation of
 *	future vertex specified data.
 */
class vertex : public unitThread {
public:
};

/**
 *	@brief Pixel thread class (child class to unit thread)
 *
 *	In addition to attribute value, this pixel class also contains pixel's
 *	barycentric coordinate and ghost flag which is used to inform per-fragment
 *	operation this pixel should by dropped.
 *
 *	@note The pixel thread's 1st attr slot will always be its screen position.
 */
class pixel : public unitThread {
public:
	pixel() : isGhost(true) {}

    ///Barycentric Coordinate
    float       baryCenPos3[3];
    bool		isGhost;
};

struct primitive {
	primitive() : iskilled(false), isGenerated(false) {}

	bool iskilled, isGenerated;
    vertex v[3];
};

#endif // GPU_TYPE_H_INCLUDED
