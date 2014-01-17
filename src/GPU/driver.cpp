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

	for (int i=0; i<13; i++) {
		if ((width < 1) || (height < 1)){
			texImage->maxLevel = i-1;
			break;
		}

		nextWidth = texImage->widthLevel[i+1] = width >> 1;
		nextHeight = texImage->heightLevel[i+1] = height >> 1;

		image = new unsigned char[nextWidth * nextHeight * 4];

		for (unsigned int y=0;y<nextHeight;y++) {
			for (unsigned int x=0;x<nextWidth;x++) {
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

int CheckSwizzleModifier(int modifier)
{
	if ( (modifier&0xf) == 0x0)
		return NO_MODIFIER;
	else if ( (modifier&0xf) == 0x1)
		return 0;
	else if ( (modifier&0xf) == 0x2)
		return 1;
	else if ( (modifier&0xf) == 0x4)
		return 2;
	else if ( (modifier&0xf) == 0x8)
		return 3;
	else {
		printf("CheckSwizzleModifier: Swizzle rule undefied!!\n");
		return -2;
	}
}

int NVGP4toScalar(instruction in, std::vector<scalarInstruction> *ISpool)
{
	int cnt;
	scalarInstruction ts_instruction;

	switch (in.op) {
	//undefined or unimplemented
//	case OP_LIT:
//	case OP_NOT:
//	case OP_NRM:
//	case OP_PK2H:
//	case OP_PK2US:
//	case OP_PK4B:
//	case OP_PK4UB:
//	case OP_SSG:
//	case OP_COS:
//	case OP_EX2:
//	case OP_LG2;
//	case OP_RCC:
//	case OP_SCS:
//	case OP_SIN:
//	case OP_UP2H:
//	case OP_UP2US:
//	case OP_UP4B:
//	case OP_UP4UB:
//	case OP_DPH:
//	case OP_OR:
//	case OP_RFL:
//	case OP_SFL:
//	case OP_STR:
//	case OP_XPD:
//	case OP_XOR:
//	case OP_CMP:
//	case OP_LRP:
//	case OP_SAD:
//	case OP_X2D:
//	case OP_TXB:
//	case OP_TXP:
//	case OP_TXQ:

	//Direct translation
	case OP_ABS:	case OP_CEIL:	case OP_FLR:	case OP_FRC:
	case OP_I2F:	case OP_MOV:	case OP_ROUND:	case OP_TRUNC:
	case OP_RCP:	case OP_ADD:	case OP_AND:	case OP_DIV:
	case OP_MAX:	case OP_MIN:	case OP_MUL:	case OP_SEQ:
	case OP_SGE:	case OP_SGT:	case OP_SLE:	case OP_SLT:
	case OP_SNE:	case OP_SUB:	case OP_MAD:	case OP_DDX:
	case OP_DDY:
		for (int cnt=0; cnt<4; cnt++) {
			//check dst operand's each modifier zone to make sure this scalar part is activated.
			if (CheckSwizzleModifier(in.dst.modifier>>cnt*4) != NO_MODIFIER) {
				ts_instruction.Init();

				ts_instruction.op = in.op;
				for (int i=0; i<12; i++)
					ts_instruction.opModifiers[i] = in.opModifiers[i];
				ts_instruction.tid = in.tid;
				ts_instruction.tType = in.tType;

				ts_instruction.dst.id =
					in.dst.id*4 + CheckSwizzleModifier(in.dst.modifier>>cnt*4);
				ts_instruction.dst.type = in.dst.type;
				ts_instruction.dst.ccMask = in.dst.ccMask;
				ts_instruction.dst.ccModifier = in.dst.ccModifier;
				ts_instruction.dst.abs = in.dst.abs;
				ts_instruction.dst.inverse = in.dst.inverse;
				//dst operand's val is not necessary to take care.

				for (int i=0; i<3; i++) {
					if (in.src[i].type == INST_NO_TYPE)
						continue;

					if (CheckSwizzleModifier(in.src[i].modifier>>cnt*4) == NO_MODIFIER)
						ts_instruction.src[i].id =
							in.src[i].id*4 + CheckSwizzleModifier(in.src[i].modifier);
					else
						ts_instruction.src[i].id =
							in.src[i].id*4 + CheckSwizzleModifier(in.src[i].modifier>>cnt*4);
					ts_instruction.src[i].type = in.src[i].type;
					ts_instruction.src[i].ccMask = in.src[i].ccMask;
					ts_instruction.src[i].ccModifier = in.src[i].ccModifier;
					ts_instruction.src[i].abs = in.src[i].abs;
					ts_instruction.src[i].inverse = in.src[i].inverse;
					//decide the instant value from which element of instant vector by the ID.
					ts_instruction.src[i].val =
						(ts_instruction.src[i].id == 0)? in.src[i].val.x:
						(ts_instruction.src[i].id == 1)? in.src[i].val.y:
						(ts_instruction.src[i].id == 2)? in.src[i].val.z: in.src[i].val.w;
				}

				ts_instruction.Print();
				ISpool->assign(ISpool->size() + 1, ts_instruction);
			}
			else
				continue;
		}
		break;

//	//Only take care first modifier
	case OP_REP:
	case OP_ENDREP:
	case OP_ELSE:
	case OP_ENDIF:
		ts_instruction.Init();

		ts_instruction.op = in.op;
		for (int i=0; i<12; i++)
			ts_instruction.opModifiers[i] = in.opModifiers[i];

		ts_instruction.src[0].type = in.src[0].type;
		ts_instruction.src[0].ccMask = in.src[0].ccMask;
		ts_instruction.src[0].ccModifier = in.src[0].ccModifier;
		ts_instruction.src[0].abs = in.src[0].abs;
		ts_instruction.src[0].inverse = in.src[0].inverse;
		//decide which instant value element from the calculated ID before.
		ts_instruction.src[0].val =
			(ts_instruction.src[0].id == 0)? in.src[0].val.x:
			(ts_instruction.src[0].id == 1)? in.src[0].val.y:
			(ts_instruction.src[0].id == 2)? in.src[0].val.z: in.src[0].val.w;

		ts_instruction.Print();
		ISpool->assign(ISpool->size() + 1, ts_instruction);

		break;
//
//	//Indirect translation
//	//move after executing
//	case OP_RCP:
//		dst[idx].x = dst[idx].y = dst[idx].z = dst[idx].w = (1/src[idx][0].x);
//		break;
//	case OP_RSQ:	//Reciprocal square root
//		//dst[idx].x = dst[idx].y = dst[idx].z = dst[idx].w = 1/sqrt(src[idx][0].x);
//		dst[idx] = floatVec4( Q_rsqrt(src[idx][0].x) );
//		break;
//	case OP_POW:
//		dst[idx].x = dst[idx].y = dst[idx].z = dst[idx].w =
//			pow(src[idx][0].x, src[idx][1].x);
//		break;
//	//Dot series, MUL MAD, and ADD are involved
//	case OP_DP2:
//		dst[idx] = src[idx][0] * src[idx][1];
//		dst[idx].x = dst[idx].y = dst[idx].z = dst[idx].w =
//			(dst[idx].x + dst[idx].y);
//		break;
//	case OP_DP3:
//		dst[idx] = src[idx][0] * src[idx][1];
//		dst[idx].x = dst[idx].y = dst[idx].z = dst[idx].w =
//			(dst[idx].x + dst[idx].y + dst[idx].z);
//		break;
//	case OP_DP4:
//		dst[idx] = floatVec4( dot(src[idx][0], src[idx][1]) );
//		break;
//	case OP_DST:	//Distance vector
//		dst[idx].x = 1.0;
//		dst[idx].y = src[idx][0].y * src[idx][1].y;
//		dst[idx].z = src[idx][0].z;
//		dst[idx].w = src[idx][1].w;
//		break;
//	case OP_DP2A:
//		{
//			float dot;
//			dot = (src[idx][0].x * src[idx][1].x) + (src[idx][0].y * src[idx][1].y) + src[idx][2].x;
//			dst[idx] = floatVec4(dot);
//			break;
//		}
//		break;
//	//Texture mapping series, need a new instruction format to fit these long instruction
//	case OP_TEX:
//		if (idx == 0 || idx == 1) {
//			scaleFacDX = src[1][0] - src[0][0];
//			scaleFacDY = src[idx+2][0] - src[idx][0];
//		}
//		else {
//			scaleFacDX = src[3][0] - src[2][0];
//			scaleFacDY = src[idx][0] - src[idx-2][0];
//		}
//		dst[idx] = texUnit.TextureSample(src[idx][0],
//										 -1,
//										 scaleFacDX,
//										 scaleFacDY,
//										 curInst.tType,
//										 tid );
//		break;
//
//	case OP_TXF:
//		dst[idx] = texUnit.GetTexColor(src[idx][0], 0, tid);
//		break;
//	case OP_TXL:
//		dst[idx] = texUnit.TextureSample(src[idx][0],
//										 src[idx][0].w,
//										 floatVec4(0.0, 0.0, 0.0, 0.0),
//										 floatVec4(0.0, 0.0, 0.0, 0.0),
//										 curInst.tType,
//										 tid );
//		break;
//	case OP_TXD:
//		dst[idx] = texUnit.TextureSample(src[idx][0],
//										 -1,
//										 src[idx][1],
//										 src[idx][2],
//										 curInst.tType,
//										 tid );
//		break;
//	//IFop
//	case OP_IF:
//		totalScaleOperation+=1;
//		switch (curInst.src[0].ccMask) {
//		case CC_EQ: case CC_EQ0: case CC_EQ1:
//			curCCState[idx] = curCCState[idx] &&
//				( (!(src[idx][0].x == 1.0) && (src[idx][1].x == 1.0)) ||
//				  (!(src[idx][0].y == 1.0) && (src[idx][1].y == 1.0)) ||
//				  (!(src[idx][0].z == 1.0) && (src[idx][1].z == 1.0)) ||
//				  (!(src[idx][0].w == 1.0) && (src[idx][1].w == 1.0)) );
//			break;
//
//		case CC_NE: case CC_NE0: case CC_NE1:
//			curCCState[idx] = curCCState[idx] &&
//				( ((src[idx][0].x == 1.0) || !(src[idx][1].x == 1.0)) ||
//				  ((src[idx][0].y == 1.0) || !(src[idx][1].y == 1.0)) ||
//				  ((src[idx][0].z == 1.0) || !(src[idx][1].z == 1.0)) ||
//				  ((src[idx][0].w == 1.0) || !(src[idx][1].w == 1.0)) );
//			break;
//
//		default:
//			printf("Shader: undefined or unimplemented ccMask:%d\n",
//					curInst.src[0].ccMask);
//			break;
//		}
//
//		ccStack[idx].push(curCCState[idx]);
//		break;
//	//KILop
//	case OP_KIL:
//		switch (curInst.src[0].ccMask) {
//		case CC_EQ: case CC_EQ0: case CC_EQ1:
//			thread[idx].isKilled = curCCState[idx] &&
//				( (!(src[idx][0].x == 1.0) && (src[idx][1].x == 1.0)) ||
//				  (!(src[idx][0].y == 1.0) && (src[idx][1].y == 1.0)) ||
//				  (!(src[idx][0].z == 1.0) && (src[idx][1].z == 1.0)) ||
//				  (!(src[idx][0].w == 1.0) && (src[idx][1].w == 1.0)) );
//			break;
//
//		case CC_NE: case CC_NE0: case CC_NE1:
//			thread[idx].isKilled = curCCState[idx] &&
//				( ((src[idx][0].x == 1.0) || !(src[idx][1].x == 1.0)) ||
//				  ((src[idx][0].y == 1.0) || !(src[idx][1].y == 1.0)) ||
//				  ((src[idx][0].z == 1.0) || !(src[idx][1].z == 1.0)) ||
//				  ((src[idx][0].w == 1.0) || !(src[idx][1].w == 1.0)) );
//			break;
//
//		default:
//			printf("Shader: undefined or unimplemented ccMask:%d\n",
//					curInst.src[0].ccMask);
//			break;
//		}
//		break;
//
//	default:
//		fprintf(stderr,
//			"Shader: Undefined or unimplemented OPcode: %x\n",curInst.op);
//		break;
//	}


	}
}

/**	@todo Use link-list or command buffer to set the states only when they
 *	differ from previous context, not all of them.
 */
void ActiveGPU(int vtxInputMode)
{
    Context *ctx = Context::GetCurrentContext();
    programObject *t_program = &ctx->programPool[ctx->usePID];

	std::vector<scalarInstruction> scalarISpool;

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
        gpu.varyInterpMode[i] = t_program->varyInterpMode[i];
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
		gpu.maxAnisoFilterRatio = ctx->texCtx[ctx->samplePool[i]].maxAnisoFilterRatio;
		gpu.tex2D[i] = ctx->texObjPool[ ctx->texCtx[ctx->samplePool[i]].texObjBindID ].tex2D;
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
	for (int i=0; i<gpu.VSinstCnt; i++) {
		*(gpu.VSinstPool + i) = t_program->VSinstructionPool[i];
		NVGP4toScalar(t_program->VSinstructionPool[i], &scalarISpool);
	}

	gpu.FSinstCnt = t_program->FSinstructionPool.size();
	gpu.FSinstPool = new instruction[gpu.FSinstCnt];
	for (int i=0; i<gpu.FSinstCnt; i++) {
		*(gpu.FSinstPool + i) = t_program->FSinstructionPool[i];
		NVGP4toScalar(t_program->FSinstructionPool[i], &scalarISpool);
	}

    gpu.Run();
}
