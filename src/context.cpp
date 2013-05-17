#include "context.h"
#include "GPU/driver.h"

static Context *currentContext = NULL;

Context::Context()
{
    m_current = false;

    for (int i=0;i<8;i++)
        vertexAttrib[i].enable = false;
}

Context::~Context()
{

}

void Context::SetCurrent(bool current)
{
    m_current = current;

    if (!m_current) //&& m_disposed)
        delete this;
}

void Context::SetCurrentContext(Context* context)
{
    Context* oldContext = GetCurrentContext();

    if (oldContext != context)
    {
        if (oldContext != 0)
            oldContext->SetCurrent(false);

        currentContext = context;

        if (context != 0)
            context->SetCurrent(true);
    }
}

Context* Context::GetCurrentContext()
{
    return currentContext;
}

void Context::RecordError(GLenum error)
{

}

/*****************************************

    OpenGL ES 3.0 API Layer Implemention

*****************************************/

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

}

void Context::EnableVertexAttribArray(GLuint index)
{
    if (index > 8) {
        RecordError(GL_INVALID_VALUE);
        return;
    }

    vertexAttrib[index].enable = GL_TRUE;
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
}

void Context::DumpImage()
{
	FILE *CLRfp;
	CLRfp = fopen("colormap.bmp","wb");

	int x,y,i;

	for (i=0; i<54; i++) {
		switch (i) {
		default:
			putc (0x00, CLRfp);
			break;
		case 0:
			putc (0x42, CLRfp);
			break;
		case 1:
			putc (0x4D, CLRfp);
			break;
		case 2:
			putc (0x38, CLRfp);
			break;
		case 3:
			putc (0x10, CLRfp);
			break;
		case 0xA:
			putc (0x36, CLRfp);
			break;
		case 0xE:
			putc (0x28, CLRfp);
			break;
		case 0x12:
			putc (vp.w&0x000000FF, CLRfp);
			break;
		case 0x13:
			putc ((vp.w>>8)&0x000000FF, CLRfp);
			break;
		case 0x14:
			putc ((vp.w>>16)&0x000000FF, CLRfp);
			break;
		case 0x15:
			putc ((vp.w>>24)&0x000000FF, CLRfp);
			break;
		case 0x16:
			putc (vp.h&0x000000FF, CLRfp);
			break;
		case 0x17:
			putc ((vp.h>>8)&0x000000FF, CLRfp);
			break;
		case 0x18:
			putc ((vp.h>>16)&0x000000FF, CLRfp);
			break;
		case 0x19:
			putc ((vp.h>>24)&0x000000FF, CLRfp);
			break;
		case 0x1A:
			putc (0x01, CLRfp);
			break;
		case 0x1C:
			putc (0x18, CLRfp);
			break;
		case 0x26:
			putc (0x12, CLRfp);
			break;
		case 0x27:
			putc (0x0B, CLRfp);
			break;
		case 0x2A:
			putc (0x12, CLRfp);
			break;
		case 0x2B:
			putc (0x0B, CLRfp);
			break;
		}
	}

	for (y=0; y<vp.h; y++)
		for (x=0; x<vp.w; x++) {
			putc(*(drawBuffer0 + y*vp.w*4 + x*4 + 3), CLRfp);// A
			putc(*(drawBuffer0 + y*vp.w*4 + x*4 + 2), CLRfp);// B
			putc(*(drawBuffer0 + y*vp.w*4 + x*4 + 1), CLRfp);// G
			putc(*(drawBuffer0 + y*vp.w*4 + x*4 + 0), CLRfp);// R
		}

	fclose(CLRfp);
}
