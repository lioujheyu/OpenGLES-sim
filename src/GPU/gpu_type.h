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
