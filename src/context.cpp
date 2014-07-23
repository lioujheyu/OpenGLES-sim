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
 *	@file context.cpp
 *  @brief Context management function implementation
 *  @author Liou Jhe-Yu (lioujheyu@gmail.com)
 */

#include "context.h"

static Context *currentContext = NULL;

Context::Context()
{
    m_current = false;
    activeTexCtx = 0;
    usePID = 0;
    drawBuffer[0] = drawBuffer[1] = nullptr;

    for (int i=0;i<MAX_ATTRIBUTE_NUMBER;i++)
        vertexAttrib[i].enable = false;
	for (int i=0; i<MAX_TEXTURE_CONTEXT; i++) {
		texCtx[i].wrapS = texCtx[i].wrapT = GL_REPEAT;
		texCtx[i].minFilter = GL_NEAREST_MIPMAP_LINEAR;
		texCtx[i].magFilter = GL_LINEAR;
	}

	frontFace = GL_CCW;
	cullFaceMode = GL_BACK;

	clearDepth = 1.0;
	clearMask = 0;
	clearStat = GL_FALSE;
    blendEnable = GL_FALSE;
    cullingEnable = GL_FALSE;
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

void Context::DumpImage(int mode)
{
	FILE *CLRfp;
	if (mode == 0)
		CLRfp = fopen("colormap.bmp","wb");
	else
		CLRfp = fopen("depthmap.bmp","wb");

	int x,y,i;

	//the simplest way to write BMP Header
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

	//Put color data
	if (mode == 0) {
		for (y=0; y<vp.h; y++){
			for (x=0; x<vp.w; x++) {
//				putc(*((unsigned char*)drawBuffer[0] + y*vp.w*4 + x*4 + 3), CLRfp);// A
				putc(*((unsigned char*)drawBuffer[0] + y*vp.w*4 + x*4 + 2), CLRfp);// B
				putc(*((unsigned char*)drawBuffer[0] + y*vp.w*4 + x*4 + 1), CLRfp);// G
				putc(*((unsigned char*)drawBuffer[0] + y*vp.w*4 + x*4 + 0), CLRfp);// R
			}
		}
	}
	else {
		for (y=0; y<vp.h; y++){
			for (x=0; x<vp.w; x++) {
				putc((unsigned char)(*((float*)drawBuffer[1] + y*vp.w + x)*255), CLRfp);// R
				putc((unsigned char)(*((float*)drawBuffer[1] + y*vp.w + x)*255), CLRfp);// R
				putc((unsigned char)(*((float*)drawBuffer[1] + y*vp.w + x)*255), CLRfp);// R
			}
		}
	}


	fclose(CLRfp);
}
