/* 
 * Copyright (c) 2013, Liou Jhe-Yu <lioujheyu@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 *	@file context_glapi.cpp
 *  @brief OpenGL ES 2.0 API Layer Implementation (no shader related API)
 *  @author Liou Jhe-Yu (lioujheyu@gmail.com)
 */

#include "context.h"

///Define U_PROG is the program which is in current used
#define U_PROG programPool[usePID]

void Context::ActiveTexture(GLenum texture)
{
    if (texture < GL_TEXTURE0) {
        RecordError(GL_INVALID_ENUM);
        return;
    }

    activeTexCtx = texture - GL_TEXTURE0;
}

void Context::BindTexture(GLenum target, GLuint texture)
{
	if (texObjPool.find(texture) == texObjPool.end()) {
		RecordError(GL_INVALID_VALUE);
		return;
	}

	switch (target) {
	case GL_TEXTURE_2D:
	case GL_TEXTURE_3D:
	case GL_TEXTURE_CUBE_MAP:
		break;
	default:
		RecordError(GL_INVALID_ENUM);
		break;
	}

	texCtx[activeTexCtx].texObjBindID = texture;
}

void Context::Clear(GLbitfield mask)
{
	if ((mask & (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)) != mask) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    clearMask = mask;
    clearStat = GL_TRUE;

    ActiveGPU2CleanBuffer();
    clearStat = GL_FALSE;
}

void Context::ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    // Set RM's registers
    clearColor.r = red;
    clearColor.g = green;
    clearColor.b = blue;
    clearColor.a = alpha;
}

void Context::ClearDepthf (GLfloat depth)
{
	clearDepth = depth;
}

void Context::CullFace(GLenum mode)
{
	cullFaceMode = mode;
}

void Context::DeleteTextures(GLsizei n, const GLuint *textures)
{
    if (n < 0) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    for (int i=0; i<n; ++i) {
        if (texObjPool.find(*(textures+i)) == texObjPool.end())
			continue;

        for (int l=0;l<=texObjPool[*(textures+i)].tex2D.maxLevel;l++)
			delete[] texObjPool[*(textures+i)].tex2D.data[l];

		for (int l=0;l<=texObjPool[*(textures+i)].texCubeNX.maxLevel;l++)
			delete[] texObjPool[*(textures+i)].texCubeNX.data[l];

		for (int l=0;l<=texObjPool[*(textures+i)].texCubeNY.maxLevel;l++)
			delete[] texObjPool[*(textures+i)].texCubeNY.data[l];

		for (int l=0;l<=texObjPool[*(textures+i)].texCubeNZ.maxLevel;l++)
			delete[] texObjPool[*(textures+i)].texCubeNZ.data[l];

		for (int l=0;l<=texObjPool[*(textures+i)].texCubePX.maxLevel;l++)
			delete[] texObjPool[*(textures+i)].texCubePX.data[l];

		for (int l=0;l<=texObjPool[*(textures+i)].texCubePY.maxLevel;l++)
			delete[] texObjPool[*(textures+i)].texCubePY.data[l];

		for (int l=0;l<=texObjPool[*(textures+i)].texCubePZ.maxLevel;l++)
			delete[] texObjPool[*(textures+i)].texCubePZ.data[l];

        texObjPool.erase(*(textures+i));

        printf("Del texture ID: %d\n",*(textures+i));
    }
}

void Context::DepthRangef(GLfloat n, GLfloat f)
{
    vp.n = (n<0)?0:(n>1)?1:n;
    vp.f = (f<0)?0:(f>1)?1:f;
}

void Context::Disable(GLenum cap)
{
    switch (cap) {
    case GL_BLEND:
        blendEnable = GL_FALSE;
        break;
    case GL_CULL_FACE:
    	cullingEnable = GL_FALSE;
        break;
    case GL_DEPTH_TEST:
        depthTestEnable = GL_FALSE;
        break;
    case GL_DITHER:
        break;
    case GL_POLYGON_OFFSET_FILL:
        break;
    case GL_SAMPLE_ALPHA_TO_COVERAGE:
        break;
    case GL_SCISSOR_TEST:
        break;
    case GL_STENCIL_TEST:
        break;
        //OpenGL ES 3.0
    case GL_PRIMITIVE_RESTART_FIXED_INDEX:
        break;
    case GL_RASTERIZER_DISCARD:
        break;
    default:
        RecordError(GL_INVALID_VALUE);
        return;
    }
}

///DrawArrays will also call driver to active GPU for drawing.
void Context::DrawArrays(GLenum mode, GLint first, GLsizei count)
{
    if (usePID == 0) {
		printf("Current program is invalid.\n");
		return;
    }
    else if (U_PROG.isLinked == GL_FALSE) {
		printf("Current program is invalid.\n");
		return;
    }

    if (first < 0)
        RecordError(GL_INVALID_VALUE);
    else if (count < 0)
        RecordError(GL_INVALID_VALUE);
    else {
        switch (mode) {
        case GL_TRIANGLES:
        case GL_TRIANGLE_FAN:
        case GL_TRIANGLE_STRIP:
            break;
        case GL_POINTS:
        case GL_LINES:
        case GL_LINE_LOOP:
        case GL_LINE_STRIP:
            printf("draw modes in points and lines are not implemented yet");
            return;
        default:
            RecordError(GL_INVALID_ENUM);
            return;
        }

        drawCmd.mode = mode;
        drawCmd.first = first;
        drawCmd.count = count;
    }

    ActiveGPU(0);
}

void Context::DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
{
    if (usePID == 0) {
		printf("Current program is invalid.\n");
		return;
    }
    else if (U_PROG.isLinked == GL_FALSE) {
		printf("Current program is invalid.\n");
		return;
    }

    if (count < 0)
        RecordError(GL_INVALID_VALUE);
    else {
        switch (mode) {
        case GL_TRIANGLES:
        case GL_TRIANGLE_FAN:
        case GL_TRIANGLE_STRIP:
            break;
        case GL_POINTS:
        case GL_LINES:
        case GL_LINE_LOOP:
        case GL_LINE_STRIP:
            printf("draw modes in points and lines are not implemented yet");
            return;
        default:
            RecordError(GL_INVALID_ENUM);
            return;
        }

        switch (type) {
		case GL_UNSIGNED_BYTE:
		case GL_UNSIGNED_SHORT:
		case GL_UNSIGNED_INT:
			drawCmd.type = type;
			break;
		default:
			drawCmd.type = GL_UNSIGNED_INT;
        }

        drawCmd.mode = mode;
        drawCmd.count = count;
        drawCmd.indices = indices;
    }

    ActiveGPU(1);
}

void Context::Enable(GLenum cap)
{
    switch (cap) {
    case GL_BLEND:
        blendEnable = GL_TRUE;
        break;
    case GL_CULL_FACE:
    	cullingEnable = GL_TRUE;
        break;
    case GL_DEPTH_TEST:
        depthTestEnable = GL_TRUE;
        break;
    case GL_DITHER:
        break;
    case GL_POLYGON_OFFSET_FILL:
        break;
    case GL_SAMPLE_ALPHA_TO_COVERAGE:
        break;
    case GL_SCISSOR_TEST:
        break;
    case GL_STENCIL_TEST:
        break;
	///OpenGL ES 3.0
    case GL_PRIMITIVE_RESTART_FIXED_INDEX:
        break;
    case GL_RASTERIZER_DISCARD:
        break;
    default:
        RecordError(GL_INVALID_ENUM);
        return;
    }
}

void Context::EnableVertexAttribArray(GLuint index)
{
    if (index >= MAX_ATTRIBUTE_NUMBER) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    vertexAttrib[index].enable = GL_TRUE;
}

void Context::FrontFace(GLenum mode)
{
	frontFace = mode;
}

void Context::GenerateMipmap(GLenum target)
{
	switch (target) {
	case GL_TEXTURE_2D:
		texCtx[activeTexCtx].genMipMap2D = GL_TRUE;
		break;
	case GL_TEXTURE_CUBE_MAP:
		texCtx[activeTexCtx].genMipMapCubeMap = GL_TRUE;
		break;
	default:
		RecordError(GL_INVALID_ENUM);
	}
}

/// @note Searching the free texture id under std::map is not efficient.
void Context::GenTextures(GLsizei n, GLuint* textures)
{
	if (n < 0) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    textureObject texObj;

	int i = 0;
	int key = 1;
	while(i<n) {
		if (texObjPool.find(key) == texObjPool.end()) {
			texObjPool[key] = texObj;
			*(textures+i) = key;
			printf("Gen Texture ID: %d\n",key);

			i++;
			key++;
		}
		else
			key++;
	}
}

GLenum Context::GetError(void)
{
	GLenum errorFlag;

	if (errorStack.empty())
		return GL_NO_ERROR;
	else{
		errorFlag = errorStack.top();
		errorStack.pop();
		return errorFlag;
	}
}

GLboolean Context::IsTexture(GLuint texture)
{
	return (texObjPool.find(texture) != texObjPool.end());
}

void Context::TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
{
	unsigned int texObjID;

    if (level < 0 || (float)level > log2f((float)std::max(width,height))) {
        RecordError(GL_INVALID_ENUM);
        return;
    }

    if (border != 0 || width < 64 || height < 64 ) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    if (target != GL_TEXTURE_2D && target != GL_TEXTURE_3D) {
		if (width != height) {
			RecordError(GL_INVALID_VALUE);
			return;
		}
	}

    GLint externalFormat = (GLint)format;

    int biSizeImage = width*height;
    unsigned char * image;

    switch (internalformat) {
	case GL_RGBA:
		image = new unsigned char[biSizeImage*4];
		break;

	default:
		RecordError(GL_INVALID_ENUM);
		printf("glTexImage2D: Undefined or unimplemented internal format\n");
		return;
    }

	/// @note Unsure format conversion is performed in API implementation or in Hardware
	for (int i=0; i<biSizeImage;i++) {
		switch (externalFormat) {
		case GL_ALPHA:
			switch (type){
			case GL_UNSIGNED_BYTE:
				image[i*4] = image[i*4+1] = image[i*4+2] = image[i*4+3] =
					*((unsigned char *)pixels+i);
				break;

			default:
				RecordError(GL_INVALID_OPERATION);
				return;
			}
			break;

		case GL_RGB:
			switch (type){
			case GL_UNSIGNED_BYTE:
				image[i*4]   = *((unsigned char *)pixels+i*3);
				image[i*4+1] = *((unsigned char *)pixels+i*3+1);
				image[i*4+2] = *((unsigned char *)pixels+i*3+2);
				image[i*4+3] = 255;
				break;

			default:
				RecordError(GL_INVALID_OPERATION);
				return;
			}
			break;

		case GL_RGBA:
			switch (type){
			case GL_UNSIGNED_BYTE:
				image[i*4]   = *((unsigned char *)pixels+i*4);
				image[i*4+1] = *((unsigned char *)pixels+i*4+1);
				image[i*4+2] = *((unsigned char *)pixels+i*4+2);
				image[i*4+3] = *((unsigned char *)pixels+i*4+3);
				break;

			default:
				RecordError(GL_INVALID_OPERATION);
				return;
			}
			break;

		case GL_LUMINANCE:
			switch (type){
			case GL_UNSIGNED_BYTE:
				image[i*4] = image[i*4+1] = image[i*4+2] = *((unsigned char *)pixels+i);
				image[i*4+3] = 255;
				break;

			default:
				RecordError(GL_INVALID_OPERATION);
				return;
			}
			break;

		case GL_LUMINANCE_ALPHA:
			switch (type){
			case GL_UNSIGNED_BYTE:
				image[i*4] = image[i*4+1] = image[i*4+2] = *((unsigned char *)pixels+i*2);
				image[i*4+3] = *((unsigned char *)pixels+i*2+1);
				break;

			default:
				RecordError(GL_INVALID_OPERATION);
				return;
			}
			break;

		default:
			RecordError(GL_INVALID_ENUM);
			printf("glTexImage2D: Undefined or unimplemented format\n");
			return;
		}
    }

	textureImage *t_image;
	texObjID = texCtx[activeTexCtx].texObjBindID;
	switch(target){
	case GL_TEXTURE_2D:
		t_image = &texObjPool[texObjID].tex2D;
		break;
	case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
		t_image = &texObjPool[texObjID].texCubeNX;
		break;
	case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
		t_image = &texObjPool[texObjID].texCubeNY;
		break;
	case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
		t_image = &texObjPool[texObjID].texCubeNZ;
		break;
	case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
		t_image = &texObjPool[texObjID].texCubePX;
		break;
	case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
		t_image = &texObjPool[texObjID].texCubePY;
		break;
	case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
		t_image = &texObjPool[texObjID].texCubePZ;
		break;
	default:
		RecordError(GL_INVALID_ENUM);
		printf("TexImage2D: undefined or unimplemented target\n");
        return;
	}

	t_image->border = border;
    t_image->widthLevel[level] = width;
    t_image->heightLevel[level] = height;
    t_image->maxLevel = (level>t_image->maxLevel)?level:t_image->maxLevel;
    t_image->data[level] = image;
}

void Context::TexParameteri(GLenum target, GLenum pname, GLint param)
{
	if (target != GL_TEXTURE_2D && target != GL_TEXTURE_CUBE_MAP) {
        RecordError(GL_INVALID_ENUM);
        return;
    }

    switch (pname)
    {
    case GL_TEXTURE_MIN_FILTER:
        /*****************************************************
            GL_NEAREST or GL_LINEAR mode : Not apply mipmap

            GL_NEAREST_MIPMAP_NEAREST
            GL_NEAREST_MIPMAP_LINEAR     apply mipmap
            GL_LINEAR_MIPMAP_NEAREST
            GL_LINEAR_MIPMAP_LINEAR
        *****************************************************/
        switch (param){
        case GL_NEAREST:
		case GL_LINEAR:
		case GL_NEAREST_MIPMAP_NEAREST:
		case GL_NEAREST_MIPMAP_LINEAR:
		case GL_LINEAR_MIPMAP_NEAREST:
		case GL_LINEAR_MIPMAP_LINEAR:
			texCtx[activeTexCtx].minFilter = param;
			break;
		default:
			RecordError(GL_INVALID_OPERATION);
			return;
        }
        break;

    case GL_TEXTURE_MAG_FILTER:
        /*****************************************************
            support GL_NEAREST or GL_LINEAR mode
        *****************************************************/
        switch (param){
        case GL_NEAREST:
		case GL_LINEAR:
			texCtx[activeTexCtx].magFilter = param;
			break;
		default:
			RecordError(GL_INVALID_OPERATION);
			return;
        }
        break;

    case GL_TEXTURE_WRAP_S:
        texCtx[activeTexCtx].wrapS = param;
        break;

    case GL_TEXTURE_WRAP_T:
        texCtx[activeTexCtx].wrapT = param;
        break;

/********  OpenGL ES 3.0 ***********/
	case GL_TEXTURE_BASE_LEVEL:
		texCtx[activeTexCtx].baseLevel = param;
		break;

	case GL_TEXTURE_MAX_LEVEL:
		texCtx[activeTexCtx].maxLevel = param;
		break;

	case GL_TEXTURE_MIN_LOD:
		break;

	case GL_TEXTURE_MAX_LOD:
		break;

	case GL_TEXTURE_SWIZZLE_R:
	case GL_TEXTURE_SWIZZLE_G:
	case GL_TEXTURE_SWIZZLE_B:
	case GL_TEXTURE_SWIZZLE_A:
		break;

	case GL_TEXTURE_WRAP_R:
		break;

    default:
        RecordError(GL_INVALID_ENUM);
        break;
    }
}

#define SET_UNIFORM_CHECK_PROCEDURE(type)											\
	if (usePID == 0) {																\
		RecordError(GL_INVALID_OPERATION);											\
		return;																		\
	}																				\
	if (location >= MAX_UNIFORM_VECTORS) {											\
		RecordError(GL_INVALID_OPERATION);											\
		return;																		\
	}																				\
	else if (location < 0) {														\
		RecordError(GL_INVALID_OPERATION);											\
		return;																		\
	}																				\
	else if (U_PROG.uniformUsage.find(location) ==									\
			U_PROG.uniformUsage.end()) {											\
		RecordError(GL_INVALID_OPERATION);											\
		return;																		\
	}																				\
	else if (U_PROG.srcUniform[U_PROG.uniformUsage[location]].declareType != type) {\
		RecordError(GL_INVALID_OPERATION);											\
		return;																		\
	}

void Context::Uniform1f (GLint location, GLfloat x)
{
	SET_UNIFORM_CHECK_PROCEDURE("float");

	uniformPool[location].x = x;
}

void Context::Uniform2f(GLint location, GLfloat x, GLfloat y)
{
	SET_UNIFORM_CHECK_PROCEDURE("float2");

	uniformPool[location].x = x;
	uniformPool[location].y = y;
}

void Context::Uniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z)
{
	SET_UNIFORM_CHECK_PROCEDURE("float3");

	uniformPool[location].x = x;
	uniformPool[location].y = y;
	uniformPool[location].z = z;
}

void Context::Uniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	SET_UNIFORM_CHECK_PROCEDURE("float4");

	uniformPool[location].x = x;
	uniformPool[location].y = y;
	uniformPool[location].z = z;
	uniformPool[location].w = w;
}

void Context::Uniform1i(GLint location, GLint x)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	if (location >= MAX_UNIFORM_VECTORS) {
		location = location - MAX_UNIFORM_VECTORS;
		if (location >= U_PROG.texCnt)
			RecordError(GL_INVALID_OPERATION);
		else
			samplePool[location] = x;
	}
	else if (location < 0)
		RecordError(GL_INVALID_OPERATION);
	else {
		if (location >= U_PROG.uniformCnt)
			RecordError(GL_INVALID_OPERATION);
		else if (U_PROG.srcUniform[U_PROG.uniformUsage[location]].declareType != "int")
			RecordError(GL_INVALID_OPERATION);
		else
			uniformPool[location].x = (float)x;
	}
}

void Context::Uniform2i(GLint location, GLint x, GLint y)
{
	SET_UNIFORM_CHECK_PROCEDURE("int2");

	uniformPool[location].x = (float)x;
	uniformPool[location].y = (float)y;
}

void Context::Uniform3i(GLint location, GLint x, GLint y, GLint z)
{
	SET_UNIFORM_CHECK_PROCEDURE("int3");

	uniformPool[location].x = (float)x;
	uniformPool[location].y = (float)y;
	uniformPool[location].z = (float)z;
}

void Context::Uniform4i(GLint location, GLint x, GLint y, GLint z, GLint w)
{
	SET_UNIFORM_CHECK_PROCEDURE("int4");

	uniformPool[location].x = (float)x;
	uniformPool[location].y = (float)y;
	uniformPool[location].z = (float)z;
	uniformPool[location].w = (float)w;
}

void Context::Uniform1fv(GLint location, GLsizei count, const GLfloat * value)
{
	SET_UNIFORM_CHECK_PROCEDURE("float");

	if (count > 1 && U_PROG.srcUniform[U_PROG.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++)
		uniformPool[location+i].x = *(value+i);
}

void Context::Uniform2fv(GLint location, GLsizei count, const GLfloat * value)
{
	SET_UNIFORM_CHECK_PROCEDURE("float2");

	if (count > 1 && U_PROG.srcUniform[U_PROG.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++) {
		uniformPool[location+i].x = *(value + 2*i);
		uniformPool[location+i].y = *(value + 2*i + 1);
	}
}

void Context::Uniform3fv(GLint location, GLsizei count, const GLfloat * value)
{
	SET_UNIFORM_CHECK_PROCEDURE("float3");

	if (count > 1 && U_PROG.srcUniform[U_PROG.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++) {
		uniformPool[location+i].x = *(value + 3*i);
		uniformPool[location+i].y = *(value + 3*i + 1);
		uniformPool[location+i].z = *(value + 3*i + 2);
	}
}

void Context::Uniform4fv(GLint location, GLsizei count, const GLfloat * value)
{
	SET_UNIFORM_CHECK_PROCEDURE("float4");

	if (count > 1 && U_PROG.srcUniform[U_PROG.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++) {
		uniformPool[location+i].x = *(value + 4*i);
		uniformPool[location+i].y = *(value + 4*i + 1);
		uniformPool[location+i].z = *(value + 4*i + 2);
		uniformPool[location+i].w = *(value + 4*i + 3);
	}
}

void Context::Uniform1iv(GLint location, GLsizei count, const GLint * value)
{
	if (usePID == 0) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	if (count > 1 && U_PROG.srcUniform[U_PROG.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	if (location >= MAX_UNIFORM_VECTORS ) {
		location = location - MAX_UNIFORM_VECTORS;
		if (location >= U_PROG.texCnt)
			RecordError(GL_INVALID_OPERATION);
		else {
			for(int i=0; i<count; i++)
				samplePool[location+i] = *(value + i);
		}
	}
	else if (location < 0)
		RecordError(GL_INVALID_OPERATION);
	else {
		if (location >= U_PROG.uniformCnt)
			RecordError(GL_INVALID_OPERATION);
		else if (U_PROG.srcUniform[U_PROG.uniformUsage[location]].declareType != "int")
			RecordError(GL_INVALID_OPERATION);
		else {
			for(int i=0; i<count; i++)
				uniformPool[location+i].x = (float)*(value + i);
		}
	}
}

void Context::Uniform2iv(GLint location, GLsizei count, const GLint * value)
{
	SET_UNIFORM_CHECK_PROCEDURE("int2");

	if (count > 1 && U_PROG.srcUniform[U_PROG.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++) {
		uniformPool[location+i].x = (float)*(value + 2*i);
		uniformPool[location+i].y = (float)*(value + 2*i + 1);
	}
}

void Context::Uniform3iv(GLint location, GLsizei count, const GLint * value)
{
	SET_UNIFORM_CHECK_PROCEDURE("int3");

	if (count > 1 && U_PROG.srcUniform[U_PROG.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++) {
		uniformPool[location+i].x = (float)*(value + 3*i);
		uniformPool[location+i].y = (float)*(value + 3*i + 1);
		uniformPool[location+i].z = (float)*(value + 3*i + 2);
	}
}

void Context::Uniform4iv(GLint location, GLsizei count, const GLint * value)
{
	SET_UNIFORM_CHECK_PROCEDURE("int4");

	if (count > 1 && U_PROG.srcUniform[U_PROG.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++) {
		uniformPool[location+i].x = (float)*(value + 4*i);
		uniformPool[location+i].y = (float)*(value + 4*i + 1);
		uniformPool[location+i].z = (float)*(value + 4*i + 2);
		uniformPool[location+i].w = (float)*(value + 4*i + 3);
	}
}

void Context::UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	SET_UNIFORM_CHECK_PROCEDURE("float2x2");

	if (count > 1 && U_PROG.srcUniform[U_PROG.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++) {
		uniformPool[location+ 2*i].x     = *(value + 4*i);
		uniformPool[location+ 2*i].y     = *(value + 4*i + 1);
		uniformPool[location+ 2*i + 1].x = *(value + 4*i + 2);
		uniformPool[location+ 2*i + 1].y = *(value + 4*i + 3);
	}
}

void Context::UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	SET_UNIFORM_CHECK_PROCEDURE("float3x3");

	if (count > 1 && U_PROG.srcUniform[U_PROG.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++) {
		uniformPool[location+ 3*i].x     = *(value + 9*i);
		uniformPool[location+ 3*i].y     = *(value + 9*i + 1);
		uniformPool[location+ 3*i].z     = *(value + 9*i + 2);
		uniformPool[location+ 3*i + 1].x = *(value + 9*i + 3);
		uniformPool[location+ 3*i + 1].y = *(value + 9*i + 4);
		uniformPool[location+ 3*i + 1].z = *(value + 9*i + 5);
		uniformPool[location+ 3*i + 2].x = *(value + 9*i + 6);
		uniformPool[location+ 3*i + 2].y = *(value + 9*i + 7);
		uniformPool[location+ 3*i + 2].z = *(value + 9*i + 8);
	}
}

void Context::UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	SET_UNIFORM_CHECK_PROCEDURE("float4x4");

	if (count > 1 && U_PROG.srcUniform[U_PROG.uniformUsage[location]].name.find('[') == std::string::npos) {
		RecordError(GL_INVALID_OPERATION);
		return;
	}

	for(int i=0; i<count; i++) {
		uniformPool[location + 4*i].x     = *(value + 16*i);
		uniformPool[location + 4*i].y     = *(value + 16*i + 1);
		uniformPool[location + 4*i].z     = *(value + 16*i + 2);
		uniformPool[location + 4*i].w     = *(value + 16*i + 3);
		uniformPool[location + 4*i + 1].x = *(value + 16*i + 4);
		uniformPool[location + 4*i + 1].y = *(value + 16*i + 5);
		uniformPool[location + 4*i + 1].z = *(value + 16*i + 6);
		uniformPool[location + 4*i + 1].w = *(value + 16*i + 7);
		uniformPool[location + 4*i + 2].x = *(value + 16*i + 8);
		uniformPool[location + 4*i + 2].y = *(value + 16*i + 9);
		uniformPool[location + 4*i + 2].z = *(value + 16*i + 10);
		uniformPool[location + 4*i + 2].w = *(value + 16*i + 11);
		uniformPool[location + 4*i + 3].x = *(value + 16*i + 12);
		uniformPool[location + 4*i + 3].y = *(value + 16*i + 13);
		uniformPool[location + 4*i + 3].z = *(value + 16*i + 14);
		uniformPool[location + 4*i + 3].w = *(value + 16*i + 15);
	}
}

void Context::VertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)
{
    if (size<2 || size>4) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    if (indx >= MAX_ATTRIBUTE_NUMBER) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    switch(type) {
    case GL_SHORT:
    case GL_BYTE:
    case GL_FLOAT:
        break;
    default:
        RecordError(GL_INVALID_ENUM);
        return;
    }

    if (stride < 0) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    vertexAttrib[indx].size = size;
    vertexAttrib[indx].type = type;
    vertexAttrib[indx].normalized = normalized;
    vertexAttrib[indx].stride = stride;
    vertexAttrib[indx].ptr = ptr;
}

void Context::Viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    if (width < 0 || height < 0)
    {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    vp.x = x;
    vp.y = y;
    vp.w = width;
    vp.h = height;

/// @todo Correct buffer setting after buffer management is ready.
    drawBuffer[0] = new unsigned char [width*height*4];
    drawBuffer[1] = new float [width*height];
}
