#include "../type.h"

#ifndef GPU_CONFIG_H_INCLUDED
#define GPU_CONFIG_H_INCLUDED

#define MAX_ATTRIBUTE_NUMBER    8

#define VPNEAR 	    0.0
#define VPFAR 	    1.0

#define PIXEL_GENERATE_DEBUG

#define TEX_CACHE_BLOCK_SIZE_ROOT_LOG 2
#define TEX_CACHE_BLOCK_SIZE_ROOT 4
#define TEX_CACHE_BLOCK_SIZE 16
#define TEX_CACHE_ENTRY_X_LOG 2
#define TEX_CACHE_ENTRY_X 4
#define TEX_CACHE_ENTRY_Y_LOG 2
#define TEX_CACHE_ENTRY_Y 4

struct vertex{
    floatVec4   attr[MAX_ATTRIBUTE_NUMBER];

    inline vertex& operator=(const vertex &rhs)
    {
    	if (this == &rhs)
            return *this;
        for (int i=0;i<MAX_ATTRIBUTE_NUMBER;i++)
			attr[i] = rhs.attr[i];
        return *this;
    }
};

struct pixel
{
    //The position will always be in 1st attribute slot in whole rm design.
    floatVec4   attr[MAX_ATTRIBUTE_NUMBER];
    floatVec4   scaleFacDX[MAX_ATTRIBUTE_NUMBER];//scalefactor[0] is unused.
    floatVec4   scaleFacDY[MAX_ATTRIBUTE_NUMBER];//scalefactor[0] is unused.
    float       baryCenPos3[3];

    inline pixel& operator=(const pixel &rhs)
    {
    	if (this == &rhs)
            return *this;

        for (int i=0;i<MAX_ATTRIBUTE_NUMBER;i++){
			attr[i] = rhs.attr[i];
			scaleFacDX[i] = rhs.scaleFacDX[i];
			scaleFacDY[i] = rhs.scaleFacDY[i];
        }
        baryCenPos3[0] = rhs.baryCenPos3[0];
        baryCenPos3[1] = rhs.baryCenPos3[1];
        baryCenPos3[2] = rhs.baryCenPos3[2];

        return *this;
    }
};

struct primitive{
    vertex v[3];

    inline primitive& operator=(const primitive &rhs)
    {
    	if (this == &rhs)
            return *this;

		v[0] = rhs.v[0];
		v[1] = rhs.v[1];
		v[2] = rhs.v[2];
        return *this;
    }
};

#endif // GPU_CONFIG_H_INCLUDED
