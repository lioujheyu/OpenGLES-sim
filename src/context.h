#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include <cstdio>
#include <vector>
#include <GLES3/gl3.h>

#include "type.h"

struct attribute
{
    GLboolean   enable;
    GLint       size;
    GLenum      type;
    GLboolean   normalized;
    GLsizei     stride;
    const GLvoid * ptr;
};

struct drawCommand
{
    GLenum      mode;
    GLint       first;
    GLsizei     count;
    const GLvoid  * indices;
};

struct viewPort
{
    GLint       x,y;
    GLint       w,h;

    GLfloat     n;
    GLfloat     f;

    inline viewPort() {
        w = 1024;
        h = 1024;
        x = 0;
        y = 0;
        n = 0.0f;
        f = 1.0f;
    }
};

struct textureState
{
    inline textureState() {
        enable = GL_FALSE;
        minFilter = GL_NEAREST_MIPMAP_LINEAR;
        magFilter = GL_LINEAR;
        wrapS = GL_REPEAT;
        wrapT = GL_REPEAT;
        baseLevel = 0;
        maxLevel = 12;
    }

    GLboolean   	enable;
    GLenum      	minFilter;
    GLenum      	magFilter;
    GLenum      	wrapS;
    GLenum      	wrapT;
    GLubyte			baseLevel;
    GLubyte			maxLevel;
    GLuint			texBindID;

    GLuint      	texArrayNum;

    inline textureState& operator=(const textureState &rhs)
    {
    	if (this == &rhs)
            return *this;
        enable = rhs.enable;
        minFilter = rhs.minFilter;
        magFilter = rhs.magFilter;
        wrapS = rhs.wrapS;
        wrapT = rhs.wrapT;
        baseLevel = rhs.baseLevel;
        maxLevel = rhs.maxLevel;
        texArrayNum = rhs.texArrayNum;
		texBindID = rhs.texBindID;
        return *this;
    }
};

class Context
{
public:

    Context();
    ~Context();

    void                SetCurrent(bool current);
    static void         SetCurrentContext(Context * context);
    static Context *    GetCurrentContext();
    void                RecordError(GLenum error);
    void                DumpImage();

//OpenGL ES 2.0 API
	void ActiveTexture(GLenum texture);
	void BindTexture (GLenum target, GLuint texture);
    void Clear (GLbitfield mask);
    void ClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    void ClearDepthf (GLfloat depth);
    void DeleteTextures (GLsizei n, const GLuint* textures);
    void DepthRangef (GLfloat n, GLfloat f);
    void DrawArrays (GLenum mode, GLint first, GLsizei count);
    void EnableVertexAttribArray (GLuint index);
    void GenTextures (GLsizei n, GLuint* textures);
    void TexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
    void TexParameteri(GLenum target, GLenum pname, GLint param);
    void VertexAttribPointer (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
    void Viewport (GLint x, GLint y, GLsizei width, GLsizei height);


/// @fixme (elvis#1#): dirty buffer setting before buffer management is ready
    void           *drawBuffer[2]; //0 - color buffer, 1 - depth buffer

    viewPort        vp;
    floatVec4		clearColor;
    float			clearDepth;
    bool			clearStat;
    unsigned int 	clearMask;
    GLuint 			textureTotalSeq;

	textureState	texContext[2];
    attribute       vertexAttrib[8];
    drawCommand     drawCmd;

    std::vector<textureImage> texDataVec;

private:
	bool            m_current;
	GLubyte			activeTexture;
};

#endif // CONTEXT_H_INCLUDED

