/**
 *	@file type.h
 *  @brief Data structures and functions for common use.
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */
#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#include <vector>
#include <cmath>
#include <cstdio>
#include <cstring>
//#include <cstdlib>
#include <xmmintrin.h>

/**
 *	@brief floating vector with 4 component
 *	scalar/vector component-wised add, multiply operator using SSE instruction.
 */
union floatVec4
{
	__m128 sse;
    alignas(alignof(sse)) struct { float x, y, z, w; };
    alignas(alignof(sse)) struct { float r, g, b, a; };
    alignas(alignof(sse)) struct { float s, t, p, q; };

    inline floatVec4() {}

    inline floatVec4(float xv, float yv, float zv, float wv)
    {
    	sse = _mm_setr_ps(xv, yv, zv, wv);
    }

	// Since the explict assignment operator is faster than mine, this
	// assignment overload has been blocked.
//    inline floatVec4& operator=(const floatVec4 &rhs)
//    {
//    	if (this == &rhs)
//            return *this;
//
//		x = rhs.x;
//		y = rhs.y;
//		z = rhs.z;
//		w = rhs.w;
//
//		// Don't know why the following two command are not work. I think this
//		// problem is involved with incorrect memory alignment.
//
//		//sse = rhs.sse;
//		//sse = _mm_setr_ps(rhs.x, rhs.y, rhs.z, rhs.w);
//        return *this;
//    }

    inline const floatVec4 operator+(const floatVec4 &other) const
    {
		floatVec4 tmp;

    	tmp.sse = _mm_add_ps(sse, other.sse);

		return tmp;
    }

    inline const floatVec4 operator+(const float other) const
    {
    	__m128 sseSrc;
    	floatVec4 tmp;

    	sseSrc = _mm_set1_ps(other);
    	tmp.sse = _mm_add_ps(sse, sseSrc);

        return tmp;
    }

    inline const floatVec4 operator-(const floatVec4 &other) const
    {
		floatVec4 tmp;

    	tmp.sse = _mm_sub_ps(sse, other.sse);

		return tmp;
    }

    inline const floatVec4 operator-(const float other) const
    {
    	__m128 sseSrc;
    	floatVec4 tmp;

    	sseSrc = _mm_set1_ps(other);
    	tmp.sse = _mm_sub_ps(sse, sseSrc);

        return tmp;
    }

    inline const floatVec4 operator*(const floatVec4 &other) const
	{
		floatVec4 tmp;

		tmp.sse = _mm_mul_ps(sse, other.sse);

		return tmp;
	}

	inline const floatVec4 operator*(const float other) const
    {
    	__m128 sseSrc;
    	floatVec4 tmp;

    	sseSrc = _mm_set1_ps(other);
    	tmp.sse = _mm_mul_ps(sse, sseSrc);

        return tmp;
    }

    inline const floatVec4 operator/(const floatVec4 &other) const
	{
		floatVec4 tmp;

		tmp.sse = _mm_div_ps(sse, other.sse);

		return tmp;
	}

    inline const floatVec4 operator/(const float other) const
    {
    	__m128 sseSrc;
    	floatVec4 tmp;

    	sseSrc = _mm_set1_ps(other);
    	tmp.sse = _mm_div_ps(sse, sseSrc);

        return tmp;
    }
};

inline const floatVec4 fvabs(const floatVec4 &x)
{
	floatVec4 tmp;
	tmp.x = fabs(x.x);
	tmp.y = fabs(x.y);
	tmp.z = fabs(x.z);
	tmp.w = fabs(x.w);
	return tmp;
}

inline const floatVec4 fvceil(const floatVec4 &x)
{
	floatVec4 tmp;
	tmp.x = ceil(x.x);
	tmp.y = ceil(x.y);
	tmp.z = ceil(x.z);
	tmp.w = ceil(x.w);
	return tmp;
}

inline const floatVec4 fvfloor(const floatVec4 &x)
{
	floatVec4 tmp;
	tmp.x = floor(x.x);
	tmp.y = floor(x.y);
	tmp.z = floor(x.z);
	tmp.w = floor(x.w);
	return tmp;
}

//typedef std::aligned_storage<__m128,__m128>::type A_pod;


class fixColor4
{
public:
    unsigned char r,g,b,a;

    inline fixColor4() {}

    inline fixColor4(unsigned char rv, unsigned char gv, unsigned char bv, unsigned char av)
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

    inline const fixColor4 operator*(const float other) const
    {
        fixColor4 tmp;
        tmp.r = r*other;
        tmp.g = g*other;
        tmp.b = b*other;
        tmp.a = a*other;
        return tmp;
    }

    inline const fixColor4 operator/(const float other) const
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

inline const fixColor4 fv2bv(const floatVec4 &fv)
{
	fixColor4 bvtmp;

	bvtmp.r = floor(fv.x == 1.0 ? 255 : fv.x * 256.0);
	bvtmp.g = floor(fv.y == 1.0 ? 255 : fv.y * 256.0);
	bvtmp.b = floor(fv.z == 1.0 ? 255 : fv.z * 256.0);
	bvtmp.a = floor(fv.w == 1.0 ? 255 : fv.w * 256.0);
	return bvtmp;
}

struct textureImage
{
	inline textureImage():maxLevel(-1),border(0){}

    int				maxLevel;
    unsigned int	border;
	unsigned int	widthLevel[13];
	unsigned int	heightLevel[13];

    unsigned char	*data[13];

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

struct operand
{
	int id;
	int type;
	bool abs;
	bool inverse;
	char modifier[5];
	floatVec4 val;

	inline operand() { Init(); }

	inline void Init()
	{
		id = 0;
		type = 0;
		abs = false;
		inverse = false;
		modifier[0] = '\0';
		val.x = val.y = val.z = val.w = 0;
	}

	void print()
	{
		if (type != 0)
			printf(" %d[%d].%s", type, id, modifier);
	}
};

struct instruction
{
	int op;
	std::vector<int> opModifiers;
	operand dst;
	operand src[3];
	int tid, tType;

	inline instruction() { Init(); }

	inline void Init()
	{
		op = 0;
		tid = -1;
		tType = 0;
		opModifiers.clear();
		dst.Init();
		src[0].Init();
		src[1].Init();
		src[2].Init();
	}

	void Print()
	{
		printf("%d",op);
		for (unsigned int i=0; i<opModifiers.size(); i++)
			printf(".%d",opModifiers[i]);
		dst.print();
		src[0].print();
		src[1].print();
		src[2].print();
		if (tid != -1)
			printf(" Tex%d.%d", tid, tType);
		printf("\n");
	}
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
