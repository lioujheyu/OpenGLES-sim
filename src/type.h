#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#include <GLES3/gl3.h>
#include <vector>

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

    inline const float operator*(const floatVec4 &other)
	{
		float tmp;
		tmp = (x*other.x + y*other.y + z*other.z + w*other.w);
		return tmp;
	}

};

class fixColor4
{
public:
    GLubyte r,g,b,a;

    inline fixColor4() {}

    inline fixColor4(GLubyte rv, GLubyte gv, GLubyte bv, GLubyte av)
    {
    	r = rv;
    	g = gv;
    	b = bv;
    	a = av;
    }

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

struct textureImage
{
	inline textureImage():maxLevel(-1),border(0){}

    GLint		maxLevel;
    GLuint		border;
	GLuint		widthLevel[13];
	GLuint		heightLevel[13];

    GLubyte     *data[13];

    inline textureImage& operator=(const textureImage &rhs)
    {
    	if (this == &rhs)
            return *this;
        maxLevel = rhs.maxLevel;
        border = rhs.border;

        for (int i=0;i<13;i++) {
			data[i] = rhs.data[i];
			widthLevel[i] = rhs.widthLevel[i];
			heightLevel[i] = rhs.heightLevel[i];
		}

        return *this;
    }
};

struct operand {
	void init()
	{
		id = 0;
		type = 0;
		inverse = false;
		for (int i=0; i<4; i++) {
			modifier[i] = '\0';
			val[i] = 0;
		}
	}

	int id;
	int type;
	bool inverse;
	char modifier[4];
	float val[4];
};

struct instruction {
	void init()
	{
		op = 0;
		opModifier.clear();
		dst.init();
		src0.init();
		src1.init();
		src2.init();
	}

	int op;
	std::vector<int> opModifier;

	operand dst;
	operand src0, src1, src2;
};



template <typename T> const T& MIN3(const T& a, const T& b, const T& c)
{
  return (b<a)?((c<b)?c:b):((c<a)?c:a);
}

template <typename T> const T& MAX3(const T& a, const T& b, const T& c)
{
  return (b>a)?((c>b)?c:b):((c>a)?c:a);
}

template <typename T> T CLAMP(const T& V, const T& L, const T& H)
{
  return V < L ? L : (V > H ? H : V);
}
#endif // TYPE_H_INCLUDED
