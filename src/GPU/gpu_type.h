#ifndef GPU_TYPE_H_INCLUDED
#define GPU_TYPE_H_INCLUDED

#include <GLES3/gl3.h>
#include "gpu_config.h"

class fixColor4{
public:
    GLubyte r,g,b,a;

    inline fixColor4():r(0x0), g(0x0), b(0x0), a(0xff){}

    inline fixColor4(GLubyte rv, GLubyte gv, GLubyte bv, GLubyte av):
        r(rv), g(gv), b(bv), a(av) {}

    inline fixColor4& operator=(const fixColor4 &rhs) {
        if (this == &rhs)
            return *this;
        r = rhs.r;
        g = rhs.g;
        b = rhs.b;
        a = rhs.a;
        return *this;
    }

    inline const fixColor4 operator*(const GLfloat other) const {
        fixColor4 tmp;
        tmp.r = r*other;
        tmp.g = g*other;
        tmp.b = b*other;
        tmp.a = a*other;
        return tmp;
    }

    inline const fixColor4 operator/(const GLfloat other) const {
        fixColor4 tmp;
        tmp.r = r/other;
        tmp.g = g/other;
        tmp.b = b/other;
        tmp.a = a/other;
        return tmp;
    }

    inline const fixColor4 operator+(const fixColor4 &other) const {
        fixColor4 tmp;
        tmp.r = r + other.r;
        tmp.g = g + other.g;
        tmp.b = b + other.b;
        tmp.a = a + other.a;
        return tmp;
    }
};

union floatVec4
{
    struct { float x, y, z, w; };
    struct { float r, g, b, a; };
    struct { float s, t, p, q; };
};

struct vertex{
    floatVec4   attr[MAX_ATTRIBUTE_NUMBER];
};

struct pixel{
    //The position will always be in 1st attribute slot in whole rm design.
    floatVec4   attr[MAX_ATTRIBUTE_NUMBER];
    floatVec4   scaleFacDX[MAX_ATTRIBUTE_NUMBER];//scalefactor[0] is unused.
    floatVec4   scaleFacDY[MAX_ATTRIBUTE_NUMBER];//scalefactor[0] is unused.
    float       baryCenPos3[3];
};

struct primitive{
    vertex v[3];
};

template <class T> const T& min3 (const T& a, const T& b, const T& c) {
  return (b<a)?((c<b)?c:b):((c<a)?c:a);
}

template <class T> const T& max3 (const T& a, const T& b, const T& c) {
  return (b>a)?((c>b)?c:b):((c>a)?c:a);
}

#endif // GPU_TYPE_H_INCLUDED
