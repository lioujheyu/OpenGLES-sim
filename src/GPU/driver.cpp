/**
 *	@file driver.cpp
 *  @brief Write all statements from current context into GPU_Core
 *  @author Liou Jhe-Yu (lioujheyu@gmail.com)
 */

#include "driver.h"

void BilinearFilter4MipMap(textureImage *texImage)
{
	unsigned int width, height;
	unsigned int nextWidth, nextHeight;

	unsigned char * image;

	fixColor4 texel[4], texelAvg;
	width = texImage->widthLevel[0];
	height = texImage->heightLevel[0];

	for (int i = 0;i<13;i++) {
		if ((width < 1) || (height < 1)){
			texImage->maxLevel = i-1;
			break;
		}

		nextWidth = texImage->widthLevel[i+1] = width >> 1;
		nextHeight = texImage->heightLevel[i+1] = height >> 1;

		image = new unsigned char[nextWidth * nextHeight * 4];

		for (unsigned int y=0;y<nextHeight;y++){
			for (unsigned int x=0;x<nextWidth;x++){
				texel[0].r = *(texImage->data[i] + (2*y*width + 2*x)*4    );
				texel[0].g = *(texImage->data[i] + (2*y*width + 2*x)*4 + 1);
				texel[0].b = *(texImage->data[i] + (2*y*width + 2*x)*4 + 2);
				texel[0].a = *(texImage->data[i] + (2*y*width + 2*x)*4 + 3);

				texel[1].r = *(texImage->data[i] + (2*y*width + 2*x + 1)*4    );
				texel[1].g = *(texImage->data[i] + (2*y*width + 2*x + 1)*4 + 1);
				texel[1].b = *(texImage->data[i] + (2*y*width + 2*x + 1)*4 + 2);
				texel[1].a = *(texImage->data[i] + (2*y*width + 2*x + 1)*4 + 3);

				texel[2].r = *(texImage->data[i] + ((2*y+1)*width + 2*x)*4    );
				texel[2].g = *(texImage->data[i] + ((2*y+1)*width + 2*x)*4 + 1);
				texel[2].b = *(texImage->data[i] + ((2*y+1)*width + 2*x)*4 + 2);
				texel[2].a = *(texImage->data[i] + ((2*y+1)*width + 2*x)*4 + 3);

				texel[3].r = *(texImage->data[i] + ((2*y+1)*width + 2*x + 1)*4    );
				texel[3].g = *(texImage->data[i] + ((2*y+1)*width + 2*x + 1)*4 + 1);
				texel[3].b = *(texImage->data[i] + ((2*y+1)*width + 2*x + 1)*4 + 2);
				texel[3].a = *(texImage->data[i] + ((2*y+1)*width + 2*x + 1)*4 + 3);

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

		texImage->data[i+1] = image;

		width = nextWidth;
		height = nextHeight;
	}

#ifdef DEBUG
	printf("\nMip-map generation complete!!!\n");
	printf("Base level width:%d, height:%d\n",
			texImage->widthLevel[0],
			texImage->heightLevel[0] );
	printf("Max level:%d width:%d, height:%d\n",
			texImage->maxLevel,
			texImage->widthLevel[texImage->maxLevel],
			texImage->heightLevel[texImage->maxLevel] );
#endif
}

void GenMipMap(int tid, GLenum target)
{
	Context * ctx = Context::GetCurrentContext();
	unsigned int texObjID = ctx->texCtx[tid].texObjBindID;

	switch (target) {
	case GL_TEXTURE_2D:
		BilinearFilter4MipMap(&ctx->texObjPool[texObjID].tex2D);
		ctx->texCtx[tid].genMipMap2D = false;
		break;
	case GL_TEXTURE_CUBE_MAP:
		BilinearFilter4MipMap(&ctx->texObjPool[texObjID].texCubeNX);
		BilinearFilter4MipMap(&ctx->texObjPool[texObjID].texCubeNY);
		BilinearFilter4MipMap(&ctx->texObjPool[texObjID].texCubeNZ);
		BilinearFilter4MipMap(&ctx->texObjPool[texObjID].texCubePX);
		BilinearFilter4MipMap(&ctx->texObjPool[texObjID].texCubePY);
		BilinearFilter4MipMap(&ctx->texObjPool[texObjID].texCubePZ);
		ctx->texCtx[tid].genMipMapCubeMap = false;
		break;
	default:
		printf("Driver: unknown target texture %x for mipmap generation\n", target);
		break;
	}
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
void ActiveGPU(int vtxInputMode)
{
    Context *ctx = Context::GetCurrentContext();
    programObject *t_program = &ctx->programPool[ctx->usePID];

    for (int i=0;i<MAX_TEXTURE_CONTEXT;i++){
		if (ctx->texCtx[i].genMipMap2D)
			GenMipMap(i, GL_TEXTURE_2D);
		if (ctx->texCtx[i].genMipMapCubeMap)
			GenMipMap(i, GL_TEXTURE_CUBE_MAP);
    }

    for (int i=0;i<MAX_ATTRIBUTE_NUMBER;i++){
        gpu.attrEnable[i] = ctx->vertexAttrib[i].enable;
        if(ctx->vertexAttrib[i].enable){
            gpu.vtxPointer[i] = ctx->vertexAttrib[i].ptr;
            gpu.attrSize[i] = ctx->vertexAttrib[i].size;
        }
        gpu.varyEnable[i] = t_program->varyEnable[i];
    }

    gpu.drawMode = ctx->drawCmd.mode;
    gpu.vtxCount = ctx->drawCmd.count;
    if (vtxInputMode == 0) { //DrawArray
		gpu.vtxInputMode = 0;
		gpu.vtxFirst = ctx->drawCmd.first;
    }
    else { //DrawElements
    	gpu.vtxInputMode = 1;
		gpu.vtxIndicesType = ctx->drawCmd.type;
		gpu.vtxIndicesPointer = ctx->drawCmd.indices;
    }

	gpu.clearStat = ctx->clearStat;
	gpu.clearMask = ctx->clearMask;

	gpu.viewPortLX = ctx->vp.x;
    gpu.viewPortLY = ctx->vp.y;
    gpu.viewPortW = ctx->vp.w;
    gpu.viewPortH = ctx->vp.h;
    gpu.depthRangeN = ctx->vp.n;
    gpu.depthRangeF = ctx->vp.f;

    gpu.cullingEnable = ctx->cullingEnable;
    if (ctx->frontFace == GL_CCW)
		gpu.cullFaceMode = ctx->cullFaceMode;
	else if (ctx->frontFace == GL_CW) {
		if (ctx->cullFaceMode == GL_FRONT)
			gpu.cullFaceMode = GL_BACK;
		else if (ctx->cullFaceMode == GL_BACK)
			gpu.cullFaceMode = GL_FRONT;
		else
			gpu.cullFaceMode = ctx->cullFaceMode;
	}

    gpu.blendEnable = ctx->blendEnable;
    gpu.depthTestEnable = ctx->depthTestEnable;
    gpu.cBufPtr = (unsigned char*)ctx->drawBuffer[0];
    gpu.dBufPtr = (float*)ctx->drawBuffer[1];

    //Texture Statement
    for (int i=0; i<t_program->texCnt; i++){
		gpu.minFilter[i] = ctx->texCtx[ctx->samplePool[i]].minFilter;
		gpu.magFilter[i] = ctx->texCtx[ctx->samplePool[i]].magFilter;
		gpu.wrapS[i] = ctx->texCtx[ctx->samplePool[i]].wrapS;
		gpu.wrapT[i] = ctx->texCtx[ctx->samplePool[i]].wrapT;
		gpu.texImage[i] = ctx->texObjPool[ ctx->texCtx[ctx->samplePool[i]].texObjBindID ].tex2D;
		gpu.texCubeNX[i] = ctx->texObjPool[ ctx->texCtx[ctx->samplePool[i]].texObjBindID ].texCubeNX;
		gpu.texCubeNY[i] = ctx->texObjPool[ ctx->texCtx[ctx->samplePool[i]].texObjBindID ].texCubeNY;
		gpu.texCubeNZ[i] = ctx->texObjPool[ ctx->texCtx[ctx->samplePool[i]].texObjBindID ].texCubeNZ;
		gpu.texCubePX[i] = ctx->texObjPool[ ctx->texCtx[ctx->samplePool[i]].texObjBindID ].texCubePX;
		gpu.texCubePY[i] = ctx->texObjPool[ ctx->texCtx[ctx->samplePool[i]].texObjBindID ].texCubePY;
		gpu.texCubePZ[i] = ctx->texObjPool[ ctx->texCtx[ctx->samplePool[i]].texObjBindID ].texCubePZ;
    }

    for (int i=0; i<t_program->uniformCnt; i++)
		gpu.uniformPool[i] = ctx->uniformPool[i];

/*	Unsure shall we copy whole instruction into GPU or just use pointer to
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
