#include "context.h"
#include "GPU/driver.h"


/*****************************************

    OpenGL ES 2.0 API Layer Implemention

*****************************************/

void Context::ActiveTexture(GLenum texture)
{
    if (texture < GL_TEXTURE0) {
        RecordError(GL_INVALID_ENUM);
    }

    activeTexture = texture - GL_TEXTURE0;
}

void Context::BindTexture(GLenum target, GLuint texture)
{
	if (target != GL_TEXTURE_2D)
    {
        RecordError(GL_INVALID_ENUM);
        return;
    }

	texContext[activeTexture].texBindID = texture;
}

void Context::Clear(GLbitfield mask)
{
	if ((mask & (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)) != mask) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    clearMask = mask;
    clearStat = true;

    ActiveGPU();
    clearStat = false;
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

void Context::DepthRangef(GLfloat n, GLfloat f)
{
    vp.n = (n<0)?0:(n>1)?1:n;
    vp.f = (f<0)?0:(f>1)?1:f;
}

void Context::DeleteTextures(GLsizei n, const GLuint *textures)
{
    // @todo : build a complete data structure of texture object
    //        -> garbage collection mechanism
    if (n < 0)
    {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    printf("DeleteTextures-> base:[%d] (VEC size:[%d])\n", *textures, texDataVec.size());

    std::vector<textureImage>::iterator startIterator;

    for (int i=0; i<n; ++i)
    {
        startIterator = texDataVec.begin() + textures[i];
        texDataVec.erase(startIterator);
    }
    printf("DeleteTextures-> VEC size:[%d], capacity:[%d]\n", texDataVec.size(), texDataVec.capacity());
//    delete[] texobj->teximage->data;
//    delete   texobj->teximage;
//    delete[] texobj;
}

void Context::Disable (GLenum cap)
{
    switch (cap) {
    case GL_TEXTURE_2D:
        textureEnable = false;
        break;
    case GL_BLEND:
        blendEnable = false;
        break;
    case GL_CULL_FACE:
        break;
    case GL_DEPTH_TEST:
        depthTestEnable = false;
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
        RecordError(GL_INVALID_VALUE);
        return;
    }
}

void Context::DrawArrays(GLenum mode, GLint first, GLsizei count)
{
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
        drawCmd.indices = NULL;
    }

    ActiveGPU();
    DumpImage();
}

void Context::Enable(GLenum cap)
{
    switch (cap) {
    case GL_TEXTURE_2D:
        textureEnable = true;
        break;
    case GL_BLEND:
        blendEnable = true;
        break;
    case GL_CULL_FACE:
        break;
    case GL_DEPTH_TEST:
        depthTestEnable = true;
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
        RecordError(GL_INVALID_VALUE);
        return;
    }
}

void Context::EnableVertexAttribArray(GLuint index)
{
    if (index > 8) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    vertexAttrib[index].enable = GL_TRUE;
}

void Context::GenTextures(GLsizei n, GLuint* textures)
{
	if (n < 0) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    textureImage *texObj = new textureImage[n];

    for(int i=0;i<n;i++) {
        texDataVec.push_back(texObj[i]);
        *textures = textureTotalSeq;
        *textures++;
        textureTotalSeq++;
    }

    delete []texObj;
}

void Context::TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
{
	if (target != GL_TEXTURE_2D) {
        RecordError(GL_INVALID_ENUM);
        return;
    }

    if (level < 0 || level > 12) {
        RecordError(GL_INVALID_ENUM);
        return;
    }

    if (border != 0 || width < 64 || height < 64 ) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    GLint externalFormat = (GLint)format;

    // @todo : check type between internalformat and externalformat
    if (internalformat != externalFormat) {
        RecordError(GL_INVALID_OPERATION);
        return;
    }

    int biSizeImage = width*height;
    unsigned char * image = new unsigned char[biSizeImage*4];

// @note (elvis#1#): Unsure format conversion is performed in API implementation or not
	for (int i=0; i<biSizeImage;i++){
		switch (format) {
		case GL_ALPHA:
			switch (type){
			case GL_UNSIGNED_BYTE:
				image[i*4] = image[i*4+1] = image[i*4+2] = image[i*4+3] = *((unsigned char *)pixels+i);
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
			return;
		}
    }

    //Create default texture object for texture2D if GenTexture() is not be called.
    if(texDataVec.empty())
    {
        textureImage texObj;
        texDataVec.push_back(texObj);
        textureTotalSeq++;
		texContext[activeTexture].texBindID = 0;
    }

	// @todo : image data should be copied into buffer of mipmap arrays
	textureImage temp;

    temp.border = border;
    temp.width = width;
    temp.height = height;
    temp.maxLevel = (level>temp.maxLevel)?level:temp.maxLevel;

    temp.data[level] = image;

	texDataVec[texContext[activeTexture].texBindID] = temp;
}

void Context::TexParameteri(GLenum target, GLenum pname, GLint param)
{
	if (target != GL_TEXTURE_2D) {
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
			texContext[activeTexture].minFilter = param;
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
			texContext[activeTexture].magFilter = param;
			break;
		default:
			RecordError(GL_INVALID_OPERATION);
			return;
        }

        break;

    case GL_TEXTURE_WRAP_S:
        texContext[activeTexture].wrapS = param;
        break;

    case GL_TEXTURE_WRAP_T:
        texContext[activeTexture].wrapT = param;
        break;

/********  OpenGL ES 3.0 ***********/
	case GL_TEXTURE_BASE_LEVEL:
		texContext[activeTexture].baseLevel = param;
		break;

	case GL_TEXTURE_MAX_LEVEL:
		texContext[activeTexture].maxLevel = param;
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

void Context::VertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)
{
    if (size < 2 || size > 5) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    if (indx > 8) {
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

// @fixme (elvis#1#): dirty buffer setting before buffer management is ready
    drawBuffer[0] = new unsigned char [width*height*4];
    drawBuffer[1] = new float [width*height];
}
