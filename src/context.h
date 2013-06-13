#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <GLES3/gl3.h>

#include "type.h"
#include "GPU/driver.h"

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
    char		name[20];
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
        genMipmap = GL_FALSE;
        minFilter = GL_NEAREST_MIPMAP_LINEAR;
        magFilter = GL_LINEAR;
        wrapS = GL_REPEAT;
        wrapT = GL_REPEAT;
        baseLevel = 0;
        maxLevel = 12;
    }

    GLboolean		genMipmap;
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
		genMipmap = rhs.genMipmap;
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

struct shaderObject
{
	inline shaderObject()
	{
		isCompiled = GL_FALSE;
		delFlag = GL_FALSE;
		count = 0;
		type = 0;
	}

	GLboolean isCompiled;
	GLboolean delFlag;
	GLsizei count;
	GLenum type;

	std::vector<std::string> sourcePool;
	std::vector<std::string> compiledSourcePool;
	std::vector<GLuint> attachList;

	inline shaderObject& operator=(const shaderObject &rhs)
	{
		if (this == &rhs)
            return *this;
		isCompiled = rhs.isCompiled;
		delFlag = rhs.delFlag;
		type = rhs.type;
		count = rhs.count;

		// STL's copy operator is efficient.
		sourcePool = rhs.sourcePool;
		compiledSourcePool = rhs.compiledSourcePool;
		attachList = rhs.attachList;
		return *this;
	}
};

struct symbol
{
	std::string name;
	std::string declareType;
	unsigned char ioType;
	unsigned char idx;

	void print()
	{
		printf("%s %s IO:%d Idx:%d \n",
				declareType.c_str(),
				name.c_str(),
				ioType,
				idx	);
	}
};

struct programObject
{
	inline programObject()
	{
		sid4VS = 0;
		sid4FS = 0;
		isLinked = GL_FALSE;
		delFlag = GL_FALSE;
	}

	GLuint sid4VS;
	GLuint sid4FS;
	GLboolean isLinked;
	GLboolean delFlag;

	std::map<std::string, symbol> symTableVS;
	std::map<std::string, symbol> symTableFS;
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
	void 		AttachShader(GLuint program, GLuint shader);
	void 		ActiveTexture(GLenum texture);
	void 		BindTexture (GLenum target, GLuint texture);
    void 		Clear (GLbitfield mask);
    void 		ClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    void 		ClearDepthf (GLfloat depth);
    void		CompileShader(GLuint shader);
    GLuint 		CreateProgram (void);
    GLint		CreateShader (GLenum type);
    void		DeleteProgram (GLuint program);
    void		DeleteShader (GLuint shader);
    void 		DeleteTextures (GLsizei n, const GLuint* textures);
    void 		DepthRangef (GLfloat n, GLfloat f);
    void 		DetachShader (GLuint program, GLuint shader);
    void 		Disable (GLenum cap);
    void 		DrawArrays (GLenum mode, GLint first, GLsizei count);
    void 		Enable (GLenum cap);
    void 		EnableVertexAttribArray (GLuint index);
    void 		GenerateMipmap(GLenum target);
    void 		GenTextures (GLsizei n, GLuint* textures);
    GLenum		GetError (void);
    GLboolean	IsProgram (GLuint program);
    GLboolean	IsShader (GLuint shader);
    GLboolean	IsTexture (GLuint texture);
	void 		LinkProgram (GLuint program);
    void 		ShaderSource (GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
    void 		TexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
    void 		TexParameteri(GLenum target, GLenum pname, GLint param);
    void 		VertexAttribPointer (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
    void 		Viewport (GLint x, GLint y, GLsizei width, GLsizei height);


/// @fixme (elvis#1#): dirty buffer setting before buffer management is ready
    void           *drawBuffer[2]; //0 - color buffer, 1 - depth buffer

    viewPort        vp;
    floatVec4		clearColor;
    GLfloat			clearDepth;
    GLboolean		clearStat;
    GLuint		 	clearMask;

    GLboolean       blendEnable;
    GLboolean       depthTestEnable;

	textureState	texContext[2];
    attribute       vertexAttrib[8];
    drawCommand     drawCmd;

    GLuint			useProgramID;

    std::map<GLuint, textureImage> texImagePool;

	std::map<GLuint, programObject> programPool;
    std::map<GLuint, shaderObject> shaderPool;

private:
	bool            m_current;
	GLubyte			activeTexture;

	std::stack<GLenum> errorStack;
};

#endif // CONTEXT_H_INCLUDED

