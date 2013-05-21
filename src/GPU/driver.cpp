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

    gpu.gm.drawMode = ctx->drawCmd.mode;
    gpu.vtxCount = ctx->drawCmd.count;
    gpu.vtxFirst = ctx->drawCmd.first;
	gpu.clearStat = ctx->clearStat;
	gpu.clearMask = ctx->clearMask;

	gpu.gm.viewPortLX = ctx->vp.x;
    gpu.gm.viewPortLY = ctx->vp.y;
    gpu.rm.viewPortW = gpu.gm.viewPortW = ctx->vp.w;
    gpu.rm.viewPortH = gpu.gm.viewPortH = ctx->vp.h;
    gpu.gm.depthRangeN = ctx->vp.n;
    gpu.gm.depthRangeF = ctx->vp.f;

    gpu.rm.cBufPtr = (unsigned char*)ctx->drawBuffer[0];
    gpu.rm.dBufPtr = (float*)ctx->drawBuffer[1];
    gpu.rm.clearColor = ctx->clearColor;
    gpu.rm.clearDepth = ctx->clearDepth;

    gpu.Run();
}
