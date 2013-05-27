#include "driver.h"

void ActiveGPU()
{
    Context * ctx = Context::GetCurrentContext();

    for (int i=0;i<8;i++){
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

	gpu.gm.drawMode = ctx->drawCmd.mode;
	gpu.gm.viewPortLX = ctx->vp.x;
    gpu.gm.viewPortLY = ctx->vp.y;
    gpu.rm.viewPortW = gpu.gm.viewPortW = ctx->vp.w;
    gpu.rm.viewPortH = gpu.gm.viewPortH = ctx->vp.h;
    gpu.gm.depthRangeN = ctx->vp.n;
    gpu.gm.depthRangeF = ctx->vp.f;

    gpu.rm.blendEnable = ctx->blendEnable;
    gpu.rm.depthTestEnable = ctx->depthTestEnable;
    gpu.rm.cBufPtr = (unsigned char*)ctx->drawBuffer[0];
    gpu.rm.dBufPtr = (float*)ctx->drawBuffer[1];
    gpu.rm.clearColor = ctx->clearColor;
    gpu.rm.clearDepth = ctx->clearDepth;

    //Statement of Texture 0
    gpu.rm.minFilter[0] = ctx->texContext[0].minFilter;
    gpu.rm.magFilter[0] = ctx->texContext[0].magFilter;
	gpu.rm.texImage[0] = ctx->texDataVec[ctx->texContext[0].texBindID];

    //Statement of Texture 0
	gpu.rm.minFilter[1] = ctx->texContext[1].minFilter;
    gpu.rm.magFilter[1] = ctx->texContext[1].magFilter;
	gpu.rm.texImage[1] = ctx->texDataVec[ctx->texContext[1].texBindID];

    gpu.Run();
}
