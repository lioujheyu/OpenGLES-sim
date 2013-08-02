/**
 *	@file common.h
 *  @brief Data structures and functions for common use.
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */
#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#include <vector>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#ifdef USE_SSE
    #include <xmmintrin.h>

    #ifndef WIN32
        #include <malloc.h>
    #endif // WIN32
#endif // USE_SSE

#include "GPU/gpu_config.h"

#ifdef USE_SSE
    #define _MM_ALIGN16 __attribute__((aligned (16)))
#endif // USE_SSE
#define VERTEX_SHADER 0
#define FRAGMENT_SHADER 1

/**
 *	@brief Vector class with 4 floating component
 *
 *	Vector component-wised operation instruction(using SSE).
 *
 *	This SSE vector class's implementation is refered to this site:
 *	http://fastcpp.blogspot.tw/2011/12/simple-vector3-class-with-sse-support.html
 *	It works like a charm.
 */
#ifdef USE_SSE
struct _MM_ALIGN16 floatVec4
{
#ifdef WIN32
	inline void* operator new[](size_t x) { return _aligned_malloc(x, 16); }
	inline void  operator delete[](void* x) { if (x) _aligned_free(x); }
#else
	inline void* operator new[](size_t x) { return memalign(16, x); }
	inline void operator delete[](void* x) { if(x) free(x); }
#endif

	union {
		__m128 sse;
		struct { float x, y, z, w; };
		struct { float r, g, b, a; };
		struct { float s, t, p, q; };
	};

	inline floatVec4() {}

	inline floatVec4(float xv, float yv, float zv, float wv) :
		sse(_mm_setr_ps(xv, yv, zv, wv)) {}

	inline floatVec4(__m128 m) : sse(m) {}

    inline const floatVec4 operator+(const floatVec4 &other) const
    {
		return _mm_add_ps(sse, other.sse);
    }

    inline const floatVec4 operator+(const float other) const
    {
        return _mm_add_ps(sse, _mm_set1_ps(other));
    }

    inline const floatVec4 operator-(const floatVec4 &other) const
    {
		return _mm_sub_ps(sse, other.sse);
    }

    inline const floatVec4 operator-(const float other) const
    {
    	return _mm_sub_ps(sse, _mm_set1_ps(other));
    }

    inline const floatVec4 operator*(const floatVec4 &other) const
	{
		return _mm_mul_ps(sse, other.sse);
	}

	inline const floatVec4 operator*(const float other) const
    {
    	return _mm_mul_ps(sse, _mm_set1_ps(other));
    }

    inline const floatVec4 operator/(const floatVec4 &other) const
	{
		return _mm_div_ps(sse, other.sse);
	}

    inline const floatVec4 operator/(const float other) const
    {
    	return _mm_div_ps(sse, _mm_set1_ps(other));
    }

    inline const floatVec4 operator>(const floatVec4 &other) const
	{
		return _mm_cmpgt_ps(sse, other.sse);
	}

	inline const floatVec4 operator>=(const floatVec4 &other) const
	{
		return _mm_cmpge_ps(sse, other.sse);
	}

	inline const floatVec4 operator<(const floatVec4 &other) const
	{
		return _mm_cmplt_ps(sse, other.sse);
	}

	inline const floatVec4 operator<=(const floatVec4 &other) const
	{
		return _mm_cmple_ps(sse, other.sse);
	}

	inline const floatVec4 operator==(const floatVec4 &other) const
	{
		return _mm_cmpeq_ps(sse, other.sse);
	}

	inline const floatVec4 operator!=(const floatVec4 &other) const
	{
		return _mm_cmpneq_ps(sse, other.sse);
	}

//    // dot product with another vector
//	inline float dot(const floatVec4& other) const
//	{
//		return _mm_cvtss_f32(_mm_dp_ps(sse, other.sse, 0x71));
//	}
//	// length of the vector
//	inline float length() const
//	{
//		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(sse, sse, 0x71)));
//	}
//	// 1/length() of the vector
//	inline float rlength() const
//	{
//		return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_dp_ps(sse, sse, 0x71)));
//	}
//	// returns the vector scaled to unit length
//	inline floatVec4 normalize() const
//	{
//		return _mm_mul_ps(sse, _mm_rsqrt_ps(_mm_dp_ps(sse, sse, 0x7F)));
//	}
};

//component-wise maximums
inline const floatVec4 fvmax(const floatVec4& x, const floatVec4& y)
{
	floatVec4 tmp;
	tmp.sse = _mm_max_ps(x.sse, y.sse);
	return tmp;
}

//component-wise minimums
inline const floatVec4 fvmin(const floatVec4& x, const floatVec4& y)
{
	floatVec4 tmp;
	tmp.sse = _mm_min_ps(x.sse, y.sse);
	return tmp;
}

//Calculate reciprocal square root of input (for HW: approximate)
inline const floatVec4 fvrsqrt(const floatVec4 &x)
{
	floatVec4 tmp;
	tmp.sse = _mm_rsqrt_ss(x.sse);
	return tmp;
}

#else
struct floatVec4
{
	union
	{
		struct { float x, y, z, w; };
		struct { float r, g, b, a; };
		struct { float s, t, p, q; };
	};

	inline floatVec4() {}

	inline floatVec4(float xv, float yv, float zv, float wv)
	{
		x = xv;
		y = yv;
		z = zv;
		w = wv;
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

	inline const floatVec4 operator+(const float other) const
	{
		floatVec4 tmp;
		tmp.x = x+other;
		tmp.y = y+other;
		tmp.z = z+other;
		tmp.w = w+other;
		return tmp;
	}

	inline const floatVec4 operator-(const floatVec4 &other) const
	{
		floatVec4 tmp;
		tmp.x = x - other.x;
		tmp.y = y - other.y;
		tmp.z = z - other.z;
		tmp.w = w - other.w;
		return tmp;
	}

	inline const floatVec4 operator-(const float other) const
	{
		floatVec4 tmp;
		tmp.x = x - other;
		tmp.y = y - other;
		tmp.z = z - other;
		tmp.w = w - other;
		return tmp;
	}

	inline const floatVec4 operator*(const floatVec4 &other) const
	{
		floatVec4 tmp;
		tmp.x = x * other.x;
		tmp.y = y * other.y;
		tmp.z = z * other.z;
		tmp.w = w * other.w;
		return tmp;
	}

	inline const floatVec4 operator*(const float other) const
	{
		floatVec4 tmp;
		tmp.x = x * other;
		tmp.y = y * other;
		tmp.z = z * other;
		tmp.w = w * other;
		return tmp;
	}

	inline const floatVec4 operator/(const floatVec4 &other) const
	{
		floatVec4 tmp;
		tmp.x = x / other.x;
		tmp.y = y / other.y;
		tmp.z = z / other.z;
		tmp.w = w / other.w;
		return tmp;
	}

	inline const floatVec4 operator/(const float other) const
	{
		floatVec4 tmp;
		tmp.x = x / other;
		tmp.y = y / other;
		tmp.z = z / other;
		tmp.w = w / other;
		return tmp;
	}

	inline const floatVec4 operator>(const floatVec4 &other) const
    {
        floatVec4 tmp;
        tmp.x = (x > other.x)?0xffffffff:0x0;
        tmp.y = (y > other.y)?0xffffffff:0x0;
        tmp.z = (z > other.z)?0xffffffff:0x0;
        tmp.w = (w > other.w)?0xffffffff:0x0;
        return tmp;
    }

    inline const floatVec4 operator>=(const floatVec4 &other) const
    {
        floatVec4 tmp;
        tmp.x = (x >= other.x)?0xffffffff:0x0;
        tmp.y = (y >= other.y)?0xffffffff:0x0;
        tmp.z = (z >= other.z)?0xffffffff:0x0;
        tmp.w = (w >= other.w)?0xffffffff:0x0;
        return tmp;
    }

    inline const floatVec4 operator<(const floatVec4 &other) const
    {
        floatVec4 tmp;
        tmp.x = (x < other.x)?0xffffffff:0x0;
        tmp.y = (y < other.y)?0xffffffff:0x0;
        tmp.z = (z < other.z)?0xffffffff:0x0;
        tmp.w = (w < other.w)?0xffffffff:0x0;
        return tmp;
    }

    inline const floatVec4 operator<=(const floatVec4 &other) const
    {
        floatVec4 tmp;
        tmp.x = (x <= other.x)?0xffffffff:0x0;
        tmp.y = (y <= other.y)?0xffffffff:0x0;
        tmp.z = (z <= other.z)?0xffffffff:0x0;
        tmp.w = (w <= other.w)?0xffffffff:0x0;
        return tmp;
    }

    inline const floatVec4 operator==(const floatVec4 &other) const
    {
        floatVec4 tmp;
        tmp.x = (x == other.x)?0xffffffff:0x0;
        tmp.y = (y == other.y)?0xffffffff:0x0;
        tmp.z = (z == other.z)?0xffffffff:0x0;
        tmp.w = (w == other.w)?0xffffffff:0x0;
        return tmp;
    }

	inline const floatVec4 operator!=(const floatVec4 &other) const
    {
        floatVec4 tmp;
        tmp.x = (x != other.x)?0xffffffff:0x0;
        tmp.y = (y != other.y)?0xffffffff:0x0;
        tmp.z = (z != other.z)?0xffffffff:0x0;
        tmp.w = (w != other.w)?0xffffffff:0x0;
        return tmp;
    }
};

//component-wise maximums
inline const floatVec4 fvmax(const floatVec4& x, const floatVec4& y)
{
	floatVec4 tmp;
	tmp.x = std::max(x.x, y.x);
	tmp.y = std::max(x.y, y.y);
	tmp.z = std::max(x.z, y.z);
	tmp.w = std::max(x.w, y.w);
	return tmp;
}

//component-wise minimums
inline const floatVec4 fvmin(const floatVec4& x, const floatVec4& y)
{
	floatVec4 tmp;
	tmp.x = std::min(x.x, y.x);
	tmp.y = std::min(x.y, y.y);
	tmp.z = std::min(x.z, y.z);
	tmp.w = std::min(x.w, y.w);
	return tmp;
}

//Calculate reciprocal square root of input (for HW: approximate)
inline const floatVec4 fvrsqrt(const floatVec4 &x)
{
	floatVec4 tmp;
	tmp.x = 1.0/sqrt(x.x);
	tmp.y = x.y;
	tmp.z = x.z;
	tmp.w = x.w;
	return tmp;
}

#endif

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

inline const floatVec4 fvround(const floatVec4 &x)
{
	floatVec4 tmp;
	tmp.x = round(x.x);
	tmp.y = round(x.y);
	tmp.z = round(x.z);
	tmp.w = round(x.w);
	return tmp;
}

inline const floatVec4 fvtrunc(const floatVec4 &x)
{
	floatVec4 tmp;
	tmp.x = trunc(x.x);
	tmp.y = trunc(x.y);
	tmp.z = trunc(x.z);
	tmp.w = trunc(x.w);
	return tmp;
}

//Returns the fractional portion of each input component
inline const floatVec4 fvfrc(const floatVec4 &x)
{
	floatVec4 tmp;
	tmp.x = x.x - floor(x.x);
	tmp.y = x.y - floor(x.y);
	tmp.z = x.z - floor(x.z);
	tmp.w = x.w - floor(x.w);
	return tmp;
}

struct fixColor4
{
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
	int ccMask;
	char ccModifier[5];
	bool abs;
	bool inverse;
	char modifier[5];
	floatVec4 val;

	inline operand() { Init(); }

	inline void Init()
	{
		id = 0;
		type = 0;
		ccMask = 0;
		ccModifier[0] = '\0';
		abs = false;
		inverse = false;
		modifier[0] = '\0';
		val.x = val.y = val.z = val.w = 0;
	}

	void print()
	{
		if (inverse)
			printf(" -");
		if (type != 0)
			printf("%d[%d].%s", type, id, modifier);
	}
};

struct instruction
{
	int op;
	bool opModifiers[12];
	operand dst;
	operand src[3];
	int tid, tType;

	inline instruction() { Init(); }

	inline void Init()
	{
		op = 0;
		for (unsigned int i=0; i<12; i++)
			opModifiers[i] = false;
		tid = -1;
		tType = 0;
		dst.Init();
		src[0].Init();
		src[1].Init();
		src[2].Init();
	}

	void Print()
	{
		printf("%d.",op);
		for (unsigned int i=0; i<12; i++)
			printf("%d",(opModifiers[i])?1:0);
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
