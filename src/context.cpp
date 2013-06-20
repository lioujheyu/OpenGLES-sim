#include "context.h"

static Context *currentContext = NULL;

Context::Context()
{
    m_current = false;
    activeTexture = 0;
    usePID = 0;
//    textureTotalSeq = 0;

    for (int i=0;i<8;i++)
        vertexAttrib[i].enable = false;

	depthTestEnable = GL_FALSE;
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
	if (error == GL_OUT_OF_MEMORY) {
		printf("GL_OUT_OF_MEMORY!!! \n");
		exit(EXIT_FAILURE);
	}
	else {
		errorStack.push(error);

		switch(error){
		case GL_INVALID_ENUM:
			printf("GL_INVALID_ENUM \n");
			break;
		case GL_INVALID_VALUE:
			printf("GL_INVALID_VALUE \n");
			break;
		case GL_INVALID_OPERATION:
			printf("GL_INVALID_OPERATION \n");
			break;
		}
	}
}


void Context::DumpImage()
{
	FILE *CLRfp;
	CLRfp = fopen("colormap.bmp","wb");

	int x,y,i;

	for (i=0; i<54; i++) {
		switch (i) {
		default:    putc (0x00, CLRfp);					break;
		case 0: 	putc (0x42, CLRfp);					break;
		case 1:		putc (0x4D, CLRfp);					break;
		case 2:		putc (0x38, CLRfp);					break;
		case 3:		putc (0x10, CLRfp);					break;
		case 0xA:	putc (0x36, CLRfp);					break;
		case 0xE:	putc (0x28, CLRfp);					break;
		case 0x12:	putc (vp.w&0x000000FF, CLRfp);		break;
		case 0x13:	putc ((vp.w>>8)&0x000000FF, CLRfp);	break;
		case 0x14:	putc ((vp.w>>16)&0x000000FF, CLRfp);break;
		case 0x15:	putc ((vp.w>>24)&0x000000FF, CLRfp);break;
		case 0x16:	putc (vp.h&0x000000FF, CLRfp);		break;
		case 0x17:	putc ((vp.h>>8)&0x000000FF, CLRfp);	break;
		case 0x18:	putc ((vp.h>>16)&0x000000FF, CLRfp);break;
		case 0x19:	putc ((vp.h>>24)&0x000000FF, CLRfp);break;
		case 0x1A:	putc (0x01, CLRfp);					break;
		case 0x1C:	putc (0x18, CLRfp);					break;
		case 0x26:	putc (0x12, CLRfp);					break;
		case 0x27:	putc (0x0B, CLRfp);					break;
		case 0x2A:	putc (0x12, CLRfp);					break;
		case 0x2B:	putc (0x0B, CLRfp);					break;
		}
	}

	for (y=0; y<vp.h; y++){
		for (x=0; x<vp.w; x++) {
//			putc(*((unsigned char*)drawBuffer[0] + y*vp.w*4 + x*4 + 3), CLRfp);// A
			putc(*((unsigned char*)drawBuffer[0] + y*vp.w*4 + x*4 + 2), CLRfp);// B
			putc(*((unsigned char*)drawBuffer[0] + y*vp.w*4 + x*4 + 1), CLRfp);// G
			putc(*((unsigned char*)drawBuffer[0] + y*vp.w*4 + x*4 + 0), CLRfp);// R
		}
	}

	fclose(CLRfp);
}
