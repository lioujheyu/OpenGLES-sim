/**
 *	@file driver.cpp
 *  @brief Write all statements from current context into GPU_Core
 *  @author Liou Jhe-Yu (lioujheyu@gmail.com)
 */

#include "driver.h"

//void ActiveGPU2GenMipMap(int tid)
//{
//	Context * ctx = Context::GetCurrentContext();
//
//	float quad[] = {-1.0f, -1.0f,
//					 1.0f, -1.0f,
//					 1.0f,  1.0f,
//					-1.0f,  1.0f
//					};
//
//	float quad_tex[] = {0.0f, 0.0f,
//						1.0f, 0.0f,
//						1.0f, 1.0f,
//						0.0f, 1.0f
//						};
//
//	gpu.attrEnable[0] = true;
//	gpu.vtxPointer[0] = quad;
//	gpu.attrSize[0] = 2;
//
//	gpu.attrEnable[4] = true;
//	gpu.vtxPointer[4] = quad_tex;
//	gpu.attrSize[4] = 2;
//
//	gpu.attrEnable[1] = gpu.attrEnable[2] = gpu.attrEnable[3] =
//		gpu.attrEnable[5] = gpu.attrEnable[6] = gpu.attrEnable[7] = false;
//
//    gpu.gm.drawMode = GL_TRIANGLE_FAN;
//    gpu.rm.depthTestEnable = false;
//    gpu.rm.blendEnable = false;
//
//    gpu.rm.minFilter[0] = GL_LINEAR_MIPMAP_NEAREST;
//    gpu.rm.magFilter[0] = GL_LINEAR;
//    gpu.rm.texImage[0] = ctx->texImagepool[ctx->texCtx[tid].texBindID];
//}

void GenMipMap(int tid)
{
	Context * ctx = Context::GetCurrentContext();

	unsigned int width, height;
	unsigned int nextWidth, nextHeight;

	unsigned char * image;

	fixColor4 texel[4], texelAvg;

	textureImage *tempImg = &ctx->texImagePool[ctx->texCtx[tid].texBindID];
	width = tempImg->widthLevel[0];
	height = tempImg->heightLevel[0];

	for (int i = 0;i<13;i++) {
		if ((width < 1) || (height < 1)){
			tempImg->maxLevel = i-1;
			break;
		}

		nextWidth = tempImg->widthLevel[i+1] = width >> 1;
		nextHeight = tempImg->heightLevel[i+1] = height >> 1;

		image = new unsigned char[nextWidth * nextHeight * 4];

		for (unsigned int y=0;y<nextHeight;y++){
			for (unsigned int x=0;x<nextWidth;x++){
				texel[0].r = *(tempImg->data[i] + (2*y*width + 2*x)*4    );
				texel[0].g = *(tempImg->data[i] + (2*y*width + 2*x)*4 + 1);
				texel[0].b = *(tempImg->data[i] + (2*y*width + 2*x)*4 + 2);
				texel[0].a = *(tempImg->data[i] + (2*y*width + 2*x)*4 + 3);

				texel[1].r = *(tempImg->data[i] + (2*y*width + 2*x + 1)*4    );
				texel[1].g = *(tempImg->data[i] + (2*y*width + 2*x + 1)*4 + 1);
				texel[1].b = *(tempImg->data[i] + (2*y*width + 2*x + 1)*4 + 2);
				texel[1].a = *(tempImg->data[i] + (2*y*width + 2*x + 1)*4 + 3);

				texel[2].r = *(tempImg->data[i] + ((2*y+1)*width + 2*x)*4    );
				texel[2].g = *(tempImg->data[i] + ((2*y+1)*width + 2*x)*4 + 1);
				texel[2].b = *(tempImg->data[i] + ((2*y+1)*width + 2*x)*4 + 2);
				texel[2].a = *(tempImg->data[i] + ((2*y+1)*width + 2*x)*4 + 3);

				texel[3].r = *(tempImg->data[i] + ((2*y+1)*width + 2*x + 1)*4    );
				texel[3].g = *(tempImg->data[i] + ((2*y+1)*width + 2*x + 1)*4 + 1);
				texel[3].b = *(tempImg->data[i] + ((2*y+1)*width + 2*x + 1)*4 + 2);
				texel[3].a = *(tempImg->data[i] + ((2*y+1)*width + 2*x + 1)*4 + 3);

				texelAvg.r = (unsigned char)((int)(texel[0].r + texel[1].r + texel[2].r + texel[3].r)/4);
				texelAvg.g = (unsigned char)((int)(texel[0].g + texel[1].g + texel[2].g + texel[3].g)/4);
				texelAvg.b = (unsigned char)((int)(texel[0].b + texel[1].b + texel[2].b + texel[3].b)/4);
				texelAvg.a = (unsigned char)((int)(texel[0].a + texel[1].a + texel[2].a + texel[3].a)/4);

				image[(y*nextWidth+x)*4    ] = texelAvg.r;
				image[(y*nextWidth+x)*4 + 1] = texelAvg.g;
				image[(y*nextWidth+x)*4 + 2] = texelAvg.b;
				image[(y*nextWidth+x)*4 + 3] = texelAvg.a;
			}
		}

		tempImg->data[i+1] = image;

		width = nextWidth;
		height = nextHeight;
	}

	//ctx->texImagePool[ctx->texCtx[tid].texBindID] = tempImg;

	printf("\nMip-map generation complete!!!\n");
	printf("Base level width:%d, height:%d\n",tempImg->widthLevel[0], tempImg->heightLevel[0]);
	printf("Max level:%d width:%d, height:%d\n", tempImg->maxLevel, tempImg->widthLevel[tempImg->maxLevel],
																  tempImg->heightLevel[tempImg->maxLevel]);

	ctx->texCtx[tid].genMipmap = false;
}

void ActiveGPU2CleanBuffer()
{
	Context * ctx = Context::GetCurrentContext();

	gpu.clearStat = ctx->clearStat;
	gpu.clearMask = ctx->clearMask;
	gpu.clearColor = ctx->clearColor;
    gpu.clearDepth = ctx->clearDepth;
    gpu.viewPortW = ctx->vp.w;
    gpu.viewPortH = ctx->vp.h;
    gpu.cBufPtr = (unsigned char*)ctx->drawBuffer[0];
    gpu.dBufPtr = (float*)ctx->drawBuffer[1];

    gpu.Run();
}

/**	@todo Use link-list or command buffer to set the states only when they
 *	differ from previous context, not all of them.
 */
void ActiveGPU()
{
    Context *ctx = Context::GetCurrentContext();
    programObject *t_program = &ctx->programPool[ctx->usePID];

    for (int i=0;i<MAX_TEXTURE_CONTEXT;i++){
		if (ctx->texCtx[i].genMipmap)
			GenMipMap(i);
			//ActiveGPU2GenMipMap(i);
    }

    for (int i=0;i<MAX_ATTRIBUTE_NUMBER;i++){
        gpu.attrEnable[i] = ctx->vertexAttrib[i].enable;
        if(ctx->vertexAttrib[i].enable){
            gpu.vtxPointer[i] = ctx->vertexAttrib[i].ptr;
            gpu.attrSize[i] = ctx->vertexAttrib[i].size;
        }
    }

    gpu.vtxCount = ctx->drawCmd.count;
    gpu.vtxFirst = ctx->drawCmd.first;
	gpu.clearStat = ctx->clearStat;
	gpu.clearMask = ctx->clearMask;

	gpu.drawMode = ctx->drawCmd.mode;
	gpu.viewPortLX = ctx->vp.x;
    gpu.viewPortLY = ctx->vp.y;
    gpu.viewPortW = ctx->vp.w;
    gpu.viewPortH = ctx->vp.h;
    gpu.depthRangeN = ctx->vp.n;
    gpu.depthRangeF = ctx->vp.f;

    gpu.blendEnable = ctx->blendEnable;
    gpu.depthTestEnable = ctx->depthTestEnable;
    gpu.cBufPtr = (unsigned char*)ctx->drawBuffer[0];
    gpu.dBufPtr = (float*)ctx->drawBuffer[1];

    //Texture Statement
    for (int i=0; i<t_program->texCnt; i++){
		gpu.minFilter[i] = ctx->texCtx[ctx->samplePool[i]-1].minFilter;
		gpu.magFilter[i] = ctx->texCtx[ctx->samplePool[i]-1].magFilter;
		gpu.wrapS[i] = ctx->texCtx[ctx->samplePool[i]-1].wrapS;
		gpu.wrapT[i] = ctx->texCtx[ctx->samplePool[i]-1].wrapT;
		gpu.texImage[i] = ctx->texImagePool[ctx->texCtx[ctx->samplePool[i]-1].texBindID];
    }

    for (int i=0; i<t_program->uniformCnt; i++)
		gpu.uniformPool[i] = ctx->uniformPool[i];

/*	Unsure shall we copy whole instruction into gpu or just use pointer to
 *	get instruction from outside
 */
	gpu.VSinstCnt = t_program->VSinstructionPool.size();
	gpu.VSinstPool = new instruction[gpu.VSinstCnt];
	for (int i=0; i<gpu.VSinstCnt; i++)
		*(gpu.VSinstPool + i) = t_program->VSinstructionPool[i];

	gpu.FSinstCnt = t_program->FSinstructionPool.size();
	gpu.FSinstPool = new instruction[gpu.FSinstCnt];
	for (int i=0; i<gpu.FSinstCnt; i++)
		*(gpu.FSinstPool + i) = t_program->FSinstructionPool[i];

    gpu.Run();
}
