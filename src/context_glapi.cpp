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

    textureContext[activeTexture].textureBindID = texture;
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

    TextureState *texObj = new TextureState[n];

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

    if (level < 0 || level > 12)
    {
        RecordError(GL_INVALID_ENUM);
        return;
    }

    if (border != 0 || width < 0 || height < 0 )
    {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    GLint externalFormat = (GLint)format;

    // @todo : check type between internalformat and externalformat
    if (internalformat != externalFormat)
    {
        RecordError(GL_INVALID_OPERATION);
        return;
    }

    // @todo : image data should be copied into buffer of mipmap arrays
    TextureImage *temp = new TextureImage();
    temp->border = border;
    temp->internalFormat = internalformat;
    temp->format = format;
    temp->level = level;
    temp->type = type;
    temp->width = width;
    temp->height = height;

    int biSizeImage = 0;

    switch (format)
    {
    case GL_RGB:                biSizeImage = width*height*3;   break;
    case GL_RGBA:               biSizeImage = width*height*4;   break;
    case GL_ALPHA:
    case GL_LUMINANCE:          biSizeImage = width*height*1;   break;
    case GL_LUMINANCE_ALPHA:    biSizeImage = width*height*2;   break;

    default:                    biSizeImage = width*height*3;   break;
    }

    unsigned char * image = new unsigned char[biSizeImage];

    for (int i=0; i<biSizeImage; i++)
        image[i] = *((unsigned char *)pixels+i);

    temp->data[0] = image;

    //Create default texture object for texture2D if GenTexture() is not be called.
    if(texDataVec.empty())
    {
        TextureState texObj;
        texDataVec.push_back(texObj);
        textureTotalSeq++;
        textureContext[activeTexture].textureBindID = 0;
    }

    texDataVec[textureContext[activeTexture].textureBindID].texImage = temp;
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
