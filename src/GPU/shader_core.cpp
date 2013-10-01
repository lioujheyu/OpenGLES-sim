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
 *	@file shader_core.cpp
 *  @brief Shader Core implementation
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#include "shader_core.h"

void ShaderCore::Init()
{
	PC = 0;
	isEnable[0] = isEnable[1] = isEnable[2] = isEnable[3] = false;
	curCCState[0] = curCCState[1] = curCCState[2] = curCCState[3] = true;
}

void ShaderCore::Run()
{
	int i;

	for (i=0; i<4; i++) {
		if (isEnable[i]) {
			thread[i] = *threadPtr[i];
		}
	}

	while(PC < instCnt) {
		curInst = instPool[PC];

		tid = curInst.tid;
		tType = curInst.tType;

/* Each pipeline needs to fetch data before other pipeline write result
 * back when they are in the same instruction. It avoids the barrier-
 * like instruction(DDX, DDY, TEX with auto scale factor computation)'s
 * result is corrupted.
 */
		for (i=0; i<4; i++) {
			if (isEnable[i])
				FetchData(i);
		}

		for (i=0; i<4; i++) {
			if (isEnable[i]){
				Exec(i);
				if (curCCState[i] == true) {
					totalInstructionCnt+=1;
					WriteBack(i);
				}
			}
		}

		PC++;
	}

	for (i=0; i<4; i++) {
		if (isEnable[i])
			threadPtr[i]->isKilled = thread[i].isKilled;
	}
}

void ShaderCore::Exec(int idx)
{
	floatVec4 scaleFacDX, scaleFacDY;

	switch (curInst.op) {
	//VECTORop
	case OP_ABS:
		dst[idx] = fvabs(src[idx][0]);
		break;
	case OP_CEIL:
		dst[idx] = fvceil(src[idx][0]);
		break;
	case OP_FLR:
		dst[idx] = fvfloor(src[idx][0]);
		break;
	case OP_FRC:
		dst[idx] = fvfrc(src[idx][0]);
		break;
	case OP_I2F:
		dst[idx] = fvInt2Float(src[idx][0]);
		break;
//	case OP_LIT:
//		break;
	case OP_MOV:
		dst[idx] = src[idx][0];
		break;
//	case OP_NOT:
//		break;
//	case OP_NRM:
//		break;
//	case OP_PK2H:
//		break;
//	case OP_PK2US:
//		break;
//	case OP_PK4B:
//		break;
//	case OP_PK4UB:
//		break;
	case OP_ROUND:
		dst[idx] = fvround(src[idx][0]);
		break;
//		case OP_SSG:
//			break;
	case OP_TRUNC:
		dst[idx] = fvtrunc(src[idx][0]);
		break;
	// SCALARop
//	case OP_COS:
//		break;
//	case OP_EX2:
//		break;
//	case OP_LG2;
//		break;
//	case OP_RCC:
//		break;
	case OP_RCP:
		dst[idx].x = dst[idx].y = dst[idx].z = dst[idx].w = (1/src[idx][0].x);
		break;
//	case OP_SCS:
//		break;
//	case OP_SIN:
//		break;
//	case OP_UP2H:
//		break;
//	case OP_UP2US:
//		break;
//	case OP_UP4B:
//		break;
//	case OP_UP4UB:
//		break;
	// BINop
	case OP_ADD:
		dst[idx] = src[idx][0] + src[idx][1];
		break;
//	case OP_AND:
//		break;
	case OP_DIV:
		dst[idx] = src[idx][0] / src[idx][1];
		break;
	case OP_DP2:
		dst[idx] = src[idx][0] * src[idx][1];
		dst[idx].x = dst[idx].y = dst[idx].z = dst[idx].w =
			(dst[idx].x + dst[idx].y);
		totalScaleOperation+=1;
		break;
	case OP_DP3:
		dst[idx] = src[idx][0] * src[idx][1];
		dst[idx].x = dst[idx].y = dst[idx].z = dst[idx].w =
			(dst[idx].x + dst[idx].y + dst[idx].z);
		totalScaleOperation+=2;
		break;
	case OP_DP4:
		dst[idx] = floatVec4( dot(src[idx][0], src[idx][1]) );
		totalScaleOperation+=3;
		break;
//	case OP_DPH:
//		break;
	case OP_DST:	//Distance vector
		dst[idx].x = 1.0;
		dst[idx].y = src[idx][0].y * src[idx][1].y;
		dst[idx].z = src[idx][0].z;
		dst[idx].w = src[idx][1].w;
		break;
	case OP_MAX:
		dst[idx] = fvmax(src[idx][0], src[idx][1]);
		break;
	case OP_MIN:
		dst[idx] = fvmin(src[idx][0], src[idx][1]);
		break;
	case OP_MUL:
		dst[idx] = src[idx][0] * src[idx][1];
		break;
//	case OP_OR:
//		break;
//	case OP_RFL:
//		break;
	case OP_RSQ:	//Reciprocal square root
		//dst[idx].x = dst[idx].y = dst[idx].z = dst[idx].w = 1/sqrt(src[idx][0].x);
		dst[idx] = floatVec4( Q_rsqrt(src[idx][0].x) );
		break;
	case OP_SEQ:
		dst[idx] = src[idx][0] == src[idx][1];
		break;
//	case OP_SFL:
//		break;
	case OP_SGE:
		dst[idx] = src[idx][0] >= src[idx][1];
		break;
	case OP_SGT:
		dst[idx] = src[idx][0] > src[idx][1];
		break;
	case OP_SLE:
		dst[idx] = src[idx][0] <= src[idx][1];
		break;
	case OP_SLT:
		dst[idx] = src[idx][0] < src[idx][1];
		break;
	case OP_SNE:
		dst[idx] = src[idx][0] != src[idx][1];
		break;
//	case OP_STR:
//		break;
	case OP_SUB:
		dst[idx] = src[idx][0] - src[idx][1];
		break;
//	case OP_XPD:
//		break;
//	case OP_XOR:
//		break;
	//TRIop
//	case OP_CMP:
//		break;
	case OP_DP2A:
		{
			float dot;
			dot = (src[idx][0].x * src[idx][1].x) + (src[idx][0].y * src[idx][1].y) + src[idx][2].x;
			dst[idx] = floatVec4(dot);
			break;
		}
		break;
//	case OP_LRP:
//		break;
	case OP_MAD:
		dst[idx] = src[idx][0] * src[idx][1] + src[idx][2];
		break;
//	case OP_SAD:
//		break;
//	case OP_X2D:
//		break;
	//TEXop
	case OP_TEX:
/* The scale factor in this instruction comes from directly difference between
 * current and neighbor thread's texture coordinate. Therefore, compare to get
 * scale factor in texture unit, it has a big advantage that we don't need to
 * know which attribute is used to locate the texel position and even can accept
 * non-attribute variable as texture coordinate without additional DDX or DDY
 * instruction involved (Cause it performs DDX/DDY-like operation in default).
 * The further discussion of finding the gradient of texture coordinate in
 * shader core like right now or in texture unit is needed.
 */
		if (idx == 0 || idx == 1) {
			scaleFacDX = src[1][0] - src[0][0];
			scaleFacDY = src[idx+2][0] - src[idx][0];
		}
		else {
			scaleFacDX = src[3][0] - src[2][0];
			scaleFacDY = src[idx][0] - src[idx-2][0];
		}
		dst[idx] = texUnit.TextureSample(src[idx][0],
										 -1,
										 scaleFacDX,
										 scaleFacDY,
										 curInst.tType,
										 tid );
		break;
//	case OP_TXB:
//		break;
	case OP_TXF:
		dst[idx] = texUnit.GetTexColor(src[idx][0], 0, tid);
		break;
	case OP_TXL:
		dst[idx] = texUnit.TextureSample(src[idx][0],
										 src[idx][0].w,
										 floatVec4(0.0, 0.0, 0.0, 0.0),
										 floatVec4(0.0, 0.0, 0.0, 0.0),
										 curInst.tType,
										 tid );
		break;
//	case OP_TXP:
//		break;
//	case OP_TXQ:
//		break;
	//TXDop
	case OP_TXD:
		dst[idx] = texUnit.TextureSample(src[idx][0],
										 -1,
										 src[idx][1],
										 src[idx][2],
										 curInst.tType,
										 tid );
		break;
	//BRAop
	//FLOWCCop
	//IFop
	case OP_IF:
		switch (curInst.src[0].ccMask) {
		case CC_EQ: case CC_EQ0: case CC_EQ1:
			curCCState[idx] = curCCState[idx] &&
				( (!(src[idx][0].x == 1.0) && (src[idx][1].x == 1.0)) ||
				  (!(src[idx][0].y == 1.0) && (src[idx][1].y == 1.0)) ||
				  (!(src[idx][0].z == 1.0) && (src[idx][1].z == 1.0)) ||
				  (!(src[idx][0].w == 1.0) && (src[idx][1].w == 1.0)) );
			break;

		case CC_NE: case CC_NE0: case CC_NE1:
			curCCState[idx] = curCCState[idx] &&
				( ((src[idx][0].x == 1.0) || !(src[idx][1].x == 1.0)) ||
				  ((src[idx][0].y == 1.0) || !(src[idx][1].y == 1.0)) ||
				  ((src[idx][0].z == 1.0) || !(src[idx][1].z == 1.0)) ||
				  ((src[idx][0].w == 1.0) || !(src[idx][1].w == 1.0)) );
			break;

		default:
			printf("Shader: undefined or unimplemented ccMask:%d\n",
					curInst.src[0].ccMask);
			break;
		}

		ccStack[idx].push(curCCState[idx]);
		break;
	//REPop
	//ENDFLOWop
	case OP_ELSE:
		curCCState[idx] = !ccStack[idx].top();
		break;

	case OP_ENDIF:
		ccStack[idx].pop();

		if (ccStack[idx].empty())
			curCCState[idx] = true;
		else
			curCCState[idx] = ccStack[idx].top();
		break;
	//BINSCop
	case OP_POW:
		dst[idx].x = dst[idx].y = dst[idx].z = dst[idx].w =
			pow(src[idx][0].x, src[idx][1].x);
		break;
	//KILop
	case OP_KIL:
		switch (curInst.src[0].ccMask) {
		case CC_EQ: case CC_EQ0: case CC_EQ1:
			thread[idx].isKilled = curCCState[idx] &&
				( (!(src[idx][0].x == 1.0) && (src[idx][1].x == 1.0)) ||
				  (!(src[idx][0].y == 1.0) && (src[idx][1].y == 1.0)) ||
				  (!(src[idx][0].z == 1.0) && (src[idx][1].z == 1.0)) ||
				  (!(src[idx][0].w == 1.0) && (src[idx][1].w == 1.0)) );
			break;

		case CC_NE: case CC_NE0: case CC_NE1:
			thread[idx].isKilled = curCCState[idx] &&
				( ((src[idx][0].x == 1.0) || !(src[idx][1].x == 1.0)) ||
				  ((src[idx][0].y == 1.0) || !(src[idx][1].y == 1.0)) ||
				  ((src[idx][0].z == 1.0) || !(src[idx][1].z == 1.0)) ||
				  ((src[idx][0].w == 1.0) || !(src[idx][1].w == 1.0)) );
			break;

		default:
			printf("Shader: undefined or unimplemented ccMask:%d\n",
					curInst.src[0].ccMask);
			break;
		}
		break;
	//DERIVEop
	case OP_DDX:
		if (idx==0 || idx==2)
			dst[idx] = src[idx+1][0] - src[idx][0];
		else // idx==1 || idx==3
			dst[idx] = src[idx][0] - src[idx-1][0];
		break;

	case OP_DDY:
		if (idx==0 || idx==1)
			dst[idx] = src[idx+2][0] - src[idx][0];
		else // idx==2 || idx==3
			dst[idx] = src[idx][0] - src[idx-2][0];
		break;

	default:
		fprintf(stderr,
			"Shader: Undefined or unimplemented OPcode: %x\n",curInst.op);
		break;
	}
}

void ShaderCore::FetchData(int idx)
{
	for (int i=0; i<3; i++) {
		switch (curInst.src[i].type) {
		case INST_NO_TYPE:
			return;
		case INST_ATTRIB:
			src[idx][i] = ReadByMask(thread[idx].attr[curInst.src[i].id],
									 curInst.src[i].modifier );
			break;

		case INST_UNIFORM:
			src[idx][i] = ReadByMask(uniformPool[curInst.src[i].id],
									 curInst.src[i].modifier );
			break;

		case INST_REG:
			src[idx][i] = ReadByMask(reg[curInst.src[i].id*4 + idx],
									 curInst.src[i].modifier );
			break;

		case INST_CCREG:
			src[idx][0] = ReadByMask(CCisSigned[idx][curInst.src[i].id],
									 curInst.src[i].ccModifier );
			src[idx][1] = ReadByMask(CCisZero[idx][curInst.src[i].id],
									 curInst.src[i].ccModifier);
			break;

		case INST_CONSTANT:
			src[idx][i] = ReadByMask(curInst.src[i].val,
									 curInst.src[i].modifier);
			break;

		default:
			fprintf(stderr,
				"Shader(Exec): Unknown operand type \n");
			return;
		}

		if (curInst.src[i].inverse) {
			src[idx][i].x = -src[idx][i].x;
			src[idx][i].y = -src[idx][i].y;
			src[idx][i].z = -src[idx][i].z;
			src[idx][i].w = -src[idx][i].w;
		}

		if (curInst.src[i].abs) {
			src[idx][i] = fvabs(src[idx][i]);
		}
	}
}

void ShaderCore::WriteBack(int idx)
{
	switch (curInst.dst.type) {
	case INST_ATTRIB:
		WriteByMask(dst[idx], &(threadPtr[idx]->attr[curInst.dst.id]), curInst.dst.modifier, idx);
		break;

	case INST_REG:
		if (curInst.dst.id < 0)
			WriteByMask(dst[idx], nullptr, curInst.dst.modifier, idx);
		else
			WriteByMask(dst[idx], &(reg[curInst.dst.id*4 + idx]), curInst.dst.modifier, idx);
		break;

	case INST_COLOR:
		WriteByMask(dst[idx], &(threadPtr[idx]->attr[1]), curInst.dst.modifier, idx);
		break;
	}
}

floatVec4 ShaderCore::ReadByMask(const floatVec4 &in, char *mask)
{
	floatVec4 temp;

	if (strcmp(mask, "xyzw")==0 || strcmp(mask, "rgba")==0)
		return in;

	temp.x = (mask[0]=='x' || mask[0]=='r')? in.x:
			 (mask[0]=='y' || mask[0]=='g')? in.y:
			 (mask[0]=='z' || mask[0]=='b')? in.z:in.w;

	if (mask[1] == '\0') {
		temp.y = temp.z = temp.w = temp.x;
		return temp;
	}
	else {
		temp.y = (mask[1]=='x' || mask[1]=='r')? in.x:
				 (mask[1]=='y' || mask[1]=='g')? in.y:
				 (mask[1]=='z' || mask[1]=='b')? in.z:in.w;
	}

	if (mask[2] == '\0') {
		temp.z = temp.w = temp.y;
		return temp;
	}
	else {
		temp.z = (mask[2]=='x' || mask[2]=='r')? in.x:
				 (mask[2]=='y' || mask[2]=='g')? in.y:
				 (mask[2]=='z' || mask[2]=='b')? in.z:in.w;
	}

	if (mask[3] == '\0') {
		temp.w = temp.z;
		return temp;
	}
	else {
		temp.w = (mask[3]=='x' || mask[3]=='r')? in.x:
				 (mask[3]=='y' || mask[3]=='g')? in.y:
				 (mask[3]=='z' || mask[3]=='b')? in.z:in.w;
	}

	return temp;
}

void ShaderCore::WriteByMask(const floatVec4 &val, floatVec4* fvdst, char *mask, int idx)
{
	for (int i=0; i<4; i++) {
		switch (mask[i]) {
		case 'x':
		case 'r':
			if (fvdst != nullptr)	{
				if(curInst.opModifiers[OPM_SAT])
					fvdst->x = CLAMP(val.x, 0.0f, 1.0f);
				else if(curInst.opModifiers[OPM_SSAT])
					fvdst->x = CLAMP(val.x, -1.0f, 1.0f);
				else
					fvdst->x = val.x;
			}

			if (curInst.opModifiers[OPM_CC] || curInst.opModifiers[OPM_CC0]) {
				CCisSigned[idx][0].x = (val.x < 0)?1.0:0.0;
				CCisZero[idx][0].x = (val.x == 0)?1.0:0.0;
			}
			else if (curInst.opModifiers[OPM_CC1]) {
				CCisSigned[idx][1].x = (val.x < 0)?1.0:0.0;
				CCisZero[idx][1].x = (val.x == 0)?1.0:0.0;
			}
			totalScaleOperation+=1;
			break;

		case 'y':
		case 'g':
			if (fvdst != nullptr)	{
				if(curInst.opModifiers[OPM_SAT])
					fvdst->y = CLAMP(val.y, 0.0f, 1.0f);
				else if(curInst.opModifiers[OPM_SSAT])
					fvdst->y = CLAMP(val.y, -1.0f, 1.0f);
				else
					fvdst->y = val.y;
			}

			if (curInst.opModifiers[OPM_CC] || curInst.opModifiers[OPM_CC0]) {
				CCisSigned[idx][0].y = (val.y < 0)?1.0:0.0;
				CCisZero[idx][0].y = (val.y == 0)?1.0:0.0;
			}
			else if (curInst.opModifiers[OPM_CC1]) {
				CCisSigned[idx][1].y = (val.y < 0)?1.0:0.0;
				CCisZero[idx][1].y = (val.y == 0)?1.0:0.0;
			}
			totalScaleOperation+=1;
			break;

		case 'z':
		case 'b':
			if (fvdst != nullptr)	{
				if(curInst.opModifiers[OPM_SAT])
					fvdst->z = CLAMP(val.z, 0.0f, 1.0f);
				else if(curInst.opModifiers[OPM_SSAT])
					fvdst->z = CLAMP(val.z, -1.0f, 1.0f);
				else
					fvdst->z = val.z;
			}

			if (curInst.opModifiers[OPM_CC] || curInst.opModifiers[OPM_CC0]) {
				CCisSigned[idx][0].z = (val.z < 0)?1.0:0.0;
				CCisZero[idx][0].z = (val.z == 0)?1.0:0.0;
			}
			else if (curInst.opModifiers[OPM_CC1]) {
				CCisSigned[idx][1].z = (val.z < 0)?1.0:0.0;
				CCisZero[idx][1].z = (val.z == 0)?1.0:0.0;
			}
			totalScaleOperation+=1;
			break;

		case 'w':
		case 'a':
			if (fvdst != nullptr)	{
				if(curInst.opModifiers[OPM_SAT])
					fvdst->w = CLAMP(val.w, 0.0f, 1.0f);
				else if(curInst.opModifiers[OPM_SSAT])
					fvdst->w = CLAMP(val.w, -1.0f, 1.0f);
				else
					fvdst->w = val.w;
			}

			if (curInst.opModifiers[OPM_CC] || curInst.opModifiers[OPM_CC0]) {
				CCisSigned[idx][0].w = (val.w < 0)?1.0:0.0;
				CCisZero[idx][0].w = (val.w == 0)?1.0:0.0;
			}
			else if (curInst.opModifiers[OPM_CC1]) {
				CCisSigned[idx][1].w = (val.w < 0)?1.0:0.0;
				CCisZero[idx][1].w = (val.w == 0)?1.0:0.0;
			}
			totalScaleOperation+=1;
			break;

		default: // '\0'
			return;
		}
	}
}

void ShaderCore::Print()
{

}
