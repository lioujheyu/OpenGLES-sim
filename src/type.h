#ifndef GPU_TYPE_H_INCLUDED
#define GPU_TYPE_H_INCLUDED

#include <GLES3/gl3.h>

class fixColor4
{
public:
    GLubyte r,g,b,a;

    inline fixColor4():r(0x0), g(0x0), b(0x0), a(0xff){}

    inline fixColor4(GLubyte rv, GLubyte gv, GLubyte bv, GLubyte av):
        r(rv), g(gv), b(bv), a(av) {}

    inline fixColor4& operator=(const fixColor4 &rhs)
    {
        if (this == &rhs)
            return *this;
        r = rhs.r;
        g = rhs.g;
        b = rhs.b;
        a = rhs.a;
        return *this;
    }

    inline const fixColor4 operator*(const GLfloat other) const
    {
        fixColor4 tmp;
        tmp.r = r*other;
        tmp.g = g*other;
        tmp.b = b*other;
        tmp.a = a*other;
        return tmp;
    }

    inline const fixColor4 operator/(const GLfloat other) const
    {
        fixColor4 tmp;
        tmp.r = r/other;
        tmp.g = g/other;
        tmp.b = b/other;
        tmp.a = a/other;
        return tmp;
    }

    inline const fixColor4 operator+(const fixColor4 &other) const
    {
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

    inline floatVec4& operator=(const floatVec4 &rhs)
    {
    	if (this == &rhs)
            return *this;
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        w = rhs.w;
        return *this;
    }

    inline const floatVec4 operator+(const floatVec4 &other) const
    {
        floatVec4 tmp;
        tmp.x = x + other.x;
        tmp.y = y + other.y;
        tmp.z = z + other.z;
        tmp.w = w + other.w;
        return tmp;
    }
};

struct textureImage
{
    GLuint      width;
    GLuint      height;
//    GLint       internalFormat;
    GLuint      maxLevel;
    GLuint      border;
//    GLenum      format;
//    GLenum      type;

    GLubyte     *data[12];

	textureImage()
	{
		maxLevel = 0;
		border = 0;
	}

    inline textureImage& operator=(const textureImage &rhs)
    {
    	if (this == &rhs)
            return *this;
        width = rhs.width;
        height = rhs.height;
        maxLevel = rhs.maxLevel;
        border = rhs.border;

        for (int i=0;i<12;i++)
			data[i] = rhs.data[i];

        return *this;
    }
};

template <class T> const T& min3 (const T& a, const T& b, const T& c)
{
  return (b<a)?((c<b)?c:b):((c<a)?c:a);
}

template <class T> const T& max3 (const T& a, const T& b, const T& c)
{
  return (b>a)?((c>b)?c:b):((c>a)?c:a);
}

#endif // GPU_TYPE_H_INCLUDED
