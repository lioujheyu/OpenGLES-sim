/**
 *	@file Context.h
 *  @brief Record all gl state from gl function
 *  @author Liou Jhe-Yu (lioujheyu@gmail.com)
 */

#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <stack>
#include <GLES3/gl3.h>

#include "GPU/driver.h"
#include "GPU/gpu_config.h"
#include "common.h"

struct attribute
{
    attribute()
    {
        enable = normalized = GL_FALSE;
        size = 0;
        type = 0;
        stride = 0;
        ptr = nullptr;
    }

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

struct textureContext
{
    GLboolean		genMipmap;
    GLenum      	minFilter, magFilter;
    GLenum      	wrapS, wrapT;
    GLubyte			baseLevel;
    GLubyte			maxLevel;

    ///Which Texture Image ID will be binded to this texture context.
    GLuint			tex2DBindID;
    GLuint			texCubeNXBindID, texCubePXBindID;
    GLuint			texCubeNYBindID, texCubePYBindID;
    GLuint			texCubeNZBindID, texCubePZBindID;

    inline textureContext() {
        genMipmap = GL_FALSE;
        minFilter = GL_NEAREST_MIPMAP_LINEAR;
        magFilter = GL_LINEAR;
        wrapS = GL_REPEAT;
        wrapT = GL_REPEAT;
        baseLevel = 0;
        maxLevel = 12;
    }
};

struct shaderObject
{
	GLboolean isCompiled;
	GLboolean delFlag;
	GLsizei count;
	GLenum type;

	std::string src;
	std::string asmSrc;
	std::vector<GLuint> attachList;

	inline shaderObject()
	{
		isCompiled = GL_FALSE;
		delFlag = GL_FALSE;
		count = 0;
		type = 0;
	}
};

struct symbol
{
	std::string name;
	std::string declareType;
	int idx;
	int element;

	inline symbol()
	{
		name.clear();
		declareType.clear();
		idx = 0;
		element = 0;
	}

	void Print()
	{
		printf("%s %s Idx:%d element:%d\n",
				declareType.c_str(),
				name.c_str(),
				idx,
				element );
	}
};

struct programObject
{
	GLuint sid4VS;	///Shader ID for Vertex Shader
	GLuint sid4FS;	///Shader ID for Fragment Shader
	GLboolean isLinked;
	GLboolean delFlag;
	GLboolean varyEnable[MAX_ATTRIBUTE_NUMBER];

	///@name Resource Statistic
	///@{
	int VSinCnt, VSoutCnt, VSuniformCnt, FSinCnt, FSoutCnt, FSuniformCnt,
		uniformCnt, texCnt;
	///@}

	///Linker's error/warning message
	std::string	linkInfo;

/** @name Naming Table
 *	GLSL variable name <-> ASM symbol attribute.
 *	For location retrieving by user.
 */
///@{
	std::map<std::string, symbol> srcVSin;
	std::map<std::string, symbol> srcVSout;
	std::map<std::string, symbol> srcFSin;
	std::map<std::string, symbol> srcFSout;
	std::map<std::string, symbol> srcUniform;
	std::map<std::string, symbol> srcTexture;
///@}

/**	@name Index Table
 *	True uniform index -> glsl variable name.
 *	For uniform value setting function
 */
	std::map<GLint, std::string> uniformUsage;

/**	@name Index Table
 *	asm uniform index -> ASM symbol attribute.
 *	For grammar check and resource remapping.
 */
///@{
	std::map<GLint, symbol> asmVSIdx;
	std::map<GLint, symbol> asmFSIdx;
///@}

/**	@name Index Table
 *	asm texture index -> asm symbol attribute.
 *	For grammar check and texture resource remapping.
 */
///@{
	std::map<int, symbol> asmVStexIdx;
	std::map<int, symbol> asmFStexIdx;
///@}

/**	@name Instruction pool
 *	Custom Format Instruction pool for hardware shader core simulator
 */
///@{
	std::vector<instruction> VSinstructionPool;
	std::vector<instruction> FSinstructionPool;
///@}

	inline programObject()
	{
		sid4VS = 0;
		sid4FS = 0;
		isLinked = GL_FALSE;
		delFlag = GL_FALSE;
		for (int i=0;i<MAX_ATTRIBUTE_NUMBER;i++)
			varyEnable[i] = GL_FALSE;
		VSinCnt = 0;
		VSoutCnt = 0;
		VSuniformCnt = 0;
		FSinCnt = 0;
		FSoutCnt = 0;
		FSuniformCnt = 0;
		uniformCnt = 0;
		texCnt = 0;
	}

	/// Initialize the members which is related for program linkage
	void LinkInit()
	{
		isLinked = GL_FALSE;
		for (int i=0;i<MAX_ATTRIBUTE_NUMBER;i++)
			varyEnable[i] = GL_FALSE;
		VSinCnt = 0;
		VSoutCnt = 0;
		VSuniformCnt = 0;
		FSinCnt = 0;
		FSoutCnt = 0;
		FSuniformCnt = 0;
		uniformCnt = 0;
		texCnt = 0;
		linkInfo.clear();
		srcVSin.clear();
		srcVSout.clear();
		srcFSin.clear();
		srcFSout.clear();
		srcUniform.clear();
		srcTexture.clear();
		uniformUsage.clear();
		asmVSIdx.clear();
		asmFSIdx.clear();
		VSinstructionPool.clear();
		FSinstructionPool.clear();
	}
};

class Context
{
public:

    Context();
    ~Context();

    /// @name Context management function
	///@{
    void                SetCurrent(bool current);
    static void         SetCurrentContext(Context * context);
    static Context *    GetCurrentContext();
    void                RecordError(GLenum error);
    void                DumpImage();
    ///@}

	/// @name OpenGL ES 2.0 API
	///@{
	void 		ActiveTexture(GLenum texture);
	void 		AttachShader(GLuint program, GLuint shader);
	void 		BindTexture (GLenum target, GLuint texture);
    void 		Clear (GLbitfield mask);
    void 		ClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    void 		ClearDepthf (GLfloat depth);
    void		CompileShader(GLuint shader);
    GLuint 		CreateProgram (void);
    GLint		CreateShader (GLenum type);
    void		CullFace (GLenum mode);
    void		DeleteProgram (GLuint program);
    void		DeleteShader (GLuint shader);
    void 		DeleteTextures (GLsizei n, const GLuint* textures);
    void 		DepthRangef (GLfloat n, GLfloat f);
    void 		DetachShader (GLuint program, GLuint shader);
    void 		Disable (GLenum cap);
    void 		DrawArrays (GLenum mode, GLint first, GLsizei count);
    void 		Enable (GLenum cap);
    void 		EnableVertexAttribArray (GLuint index);
    void		FrontFace(GLenum mode);
    void 		GenerateMipmap(GLenum target);
    void 		GenTextures (GLsizei n, GLuint* textures);
    int			GetAttribLocation (GLuint program, const GLchar* name);
    GLenum		GetError (void);
    void		GetProgramiv (GLuint program, GLenum pname, GLint* params);
    void		GetShaderiv (GLuint shader, GLenum pname, GLint* params);
    int			GetUniformLocation (GLuint program, const GLchar* name);
    GLboolean	IsProgram (GLuint program);
    GLboolean	IsShader (GLuint shader);
    GLboolean	IsTexture (GLuint texture);
	void 		LinkProgram (GLuint program);
    void 		ShaderSource (GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
    void 		TexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
    void 		TexParameteri (GLenum target, GLenum pname, GLint param);
    void		Uniform1f (GLint location, GLfloat x);
    void		Uniform2f (GLint location, GLfloat x, GLfloat y);
    void		Uniform3f (GLint location, GLfloat x, GLfloat y, GLfloat z);
    void		Uniform4f (GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void		Uniform1i (GLint location, GLint x);
    void		Uniform2i (GLint location, GLint x, GLint y);
    void		Uniform3i (GLint location, GLint x, GLint y, GLint z);
    void		Uniform4i (GLint location, GLint x, GLint y, GLint z, GLint w);
    void		Uniform1fv (GLint location, GLsizei count, const GLfloat * value);
    void		Uniform2fv (GLint location, GLsizei count, const GLfloat * value);
    void		Uniform3fv (GLint location, GLsizei count, const GLfloat * value);
    void		Uniform4fv (GLint location, GLsizei count, const GLfloat * value);
    void		Uniform1iv (GLint location, GLsizei count, const GLint * value);
    void		Uniform2iv (GLint location, GLsizei count, const GLint * value);
    void		Uniform3iv (GLint location, GLsizei count, const GLint * value);
    void		Uniform4iv (GLint location, GLsizei count, const GLint * value);
    void		UniformMatrix2fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
	void		UniformMatrix3fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
    void		UniformMatrix4fv (GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
    void		UseProgram (GLuint program);
    void 		ValidateProgram (GLuint program);
    void 		VertexAttribPointer (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
    void 		Viewport (GLint x, GLint y, GLsizei width, GLsizei height);
	///@}

	/// @todo Correct buffer setting after buffer management is ready.
    void           *drawBuffer[2]; ///< 0 - color buffer, 1 - depth buffer

    viewPort        vp;
    GLenum			frontFace;
    GLboolean		cullingEn;
    GLenum			cullFaceMode;

    /// @name clear function related variable
    ///@{
    floatVec4		clearColor;
    GLfloat			clearDepth;
    GLboolean		clearStat;
    GLuint		 	clearMask;
    ///@}

    GLboolean       blendEnable;
    GLboolean       depthTestEnable;

	///Texture Context
	textureContext	texCtx[MAX_TEXTURE_CONTEXT];

    attribute       vertexAttrib[MAX_ATTRIBUTE_NUMBER];
    drawCommand     drawCmd;

	///The Program ID prepared for using.
    GLuint			usePID;

///@name Object Pool
///@{
/**
 *	All created texture objects will push into texImagePool, and their ID from
 *	their created function will also be used as std::map key value.
 */
    std::map<GLuint, textureImage> texImagePool;

/**
 *	All created program objects will push into programPool, and their ID from
 *	their created function will also be used as std::map key value.
 */
	std::map<GLuint, programObject> programPool;

/**
 *	All created shader objects will push into shaderPool, and their ID from
 *	their created function will also be used as std::map key value.
 */
    std::map<GLuint, shaderObject> shaderPool;

/**
 *	All specified uniform value will be stored in uniformPool and it's ID
 *	queried from getLocation function will be used as its std::map key value.
 */
    std::map<GLint, floatVec4> uniformPool;

/**
 *	The specified texture context ID will be stored in samplePool and use
 *	the uniform sample id as the key value.
 *	In short, Sample ID -> texture context ID
 */
    std::map<GLint, GLint> samplePool;
///@}

private:
	bool            m_current;
	GLubyte			activeTexture;

	std::stack<GLenum> errorStack;
};

#endif // CONTEXT_H_INCLUDED

