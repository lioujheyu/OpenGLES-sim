#ifndef GPU_TYPE_H_INCLUDED
#define GPU_TYPE_H_INCLUDED

#include <GLES3/gl3.h>
#include "gpu_config.h"

class fixColor4{
public:
    GLubyte r,g,b,a;

    inline fixColor4():r(0xff), g(0xff), b(0xff), a(0xff){}

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

struct floatVec4{
    GLfloat a,b,c,d;
};

struct vertex{
    floatVec4   varying[MAX_VARYING_NUMBER];
};

struct pixel{
    floatVec4   pos4;
    floatVec4   varying[MAX_VARYING_NUMBER-1];
};



#endif // GPU_TYPE_H_INCLUDED
