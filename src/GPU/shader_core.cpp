#include "shader_core.h"
#include "../context_link_def.h"

ShaderCore::ShaderCore()
{
	instCnt = 0;
	shaderType = 0;
	for (int i=0; i<MAX_SHADER_REG_VECTOR; i++)
		reg[i].x = reg[i].y = reg[i].z = reg[i].w = 0.0f;
	dst.x = dst.y = dst.z = dst.w = 0.0;
	src[0].x = src[0].y = src[0].z = src[0].w = 0.0;
	src[1].x = src[1].y = src[1].z = src[1].w = 0.0;
	src[2].x = src[2].y = src[2].z = src[2].w = 0.0;
	tid = -1, tType = 0;
	curInst.Init();
}

void ShaderCore::Init()
{
	PC = 0;
}

void ShaderCore::Exec()
{
	if (instCnt == 0) {
		printf("Shader: Program Length = 0.\n");
		return;
	}

	if (shaderType == 0)
		vtxPtr = (vertex*)input;
	else
		pixPtr = (pixel*)input;

	while(PC < instCnt) {
		FetchData();

		switch (curInst.op) {
		//VECTORop
		case OP_ABS:
			break;
		case OP_CEIL:
			break;
		case OP_FLR:
			break;
		case OP_FRC:
			break;
		case OP_I2F:
			break;
		case OP_LIT:
			break;
		case OP_MOV:
			dst = src[0];
			break;
		case OP_NOT:
			break;
		case OP_NRM:
			break;
		case OP_PK2H:
			break;
		case OP_PK2US:
			break;
		case OP_PK4B:
			break;
		case OP_PK4UB:
			break;
		case OP_ROUND:
			break;
		case OP_SSG:
			break;
		case OP_TRUNC:

		// BINop
		case OP_ADD:
			dst = src[0] + src[1];
			break;
		case OP_AND:
			break;
		case OP_DP3:
			dst.x = dst.y = dst.z = dst.w =
				src[0].x*src[1].x + src[0].y*src[1].y + src[0].z*src[1].z;
			break;
		case OP_DP4:
			dst.x = dst.y = dst.z = dst.w =
				src[0].x*src[1].x + src[0].y*src[1].y + src[0].z*src[1].z + src[0].w*src[1].w;
			break;
		case OP_DPH:
			break;
		case OP_DST:
			break;
		case OP_MAX:
			break;
		case OP_MIN:
			break;
		case OP_MUL:
			dst = src[0] * src[1];
			break;
		case OP_OR:
			break;
		case OP_RFL:
			break;
		case OP_SEQ:
			break;
		case OP_SFL:
			break;
		case OP_SGE:
			break;
		case OP_SGT:
			break;
		case OP_SLE:
			break;
		case OP_SLT:
			break;
		case OP_SNE:
			break;
		case OP_STR:
			break;
		case OP_SUB:
			break;
		case OP_XPD:
			break;
		case OP_DP2:
			break;
		case OP_XOR:
			break;
		//TRIop
		case OP_CMP:
			break;
		case OP_DP2A:
			break;
		case OP_LRP:
			break;
		case OP_MAD:
			dst = src[0] * src[1] + src[2];
			break;
		case OP_SAD:
			break;
		case OP_X2D:
			break;
		//TEXop
		case OP_TEX:
			break;
		case OP_TXB:
			break;
		case OP_TXF:
			break;
		case OP_TXL:
			break;
		case OP_TXP:
			break;
		case OP_TXQ:
			break;
		//TXDop
		case OP_TXD:
			break;


		default:
			printf("Shader: Undefined OPcode: %x\n",curInst.op);
			break;

		}

		WriteBack();
		PC++;
	}
}

void ShaderCore::FetchData()
{
	curInst = instPool[PC];

	//Fetch data
	for (int i=0; i<3; i++) {
		if (curInst.src[i].type != 0) {
			switch (curInst.src[i].type) {
			case INST_NO_TYPE:
				goto endSrcOperand;
			case INST_ATTRIB:
				if (shaderType == 0)
					src[i] =ReadByMask(vtxPtr->attr[curInst.src[i].id], curInst.src[i].modifier);
				else
					src[i] =ReadByMask(pixPtr->attr[curInst.src[i].id], curInst.src[i].modifier);
				break;

			case INST_UNIFORM:
				src[i] = ReadByMask(uniformPool[curInst.src[i].id], curInst.src[i].modifier);
				break;

			case INST_REG:
				src[i] = ReadByMask(reg[curInst.src[i].id], curInst.src[i].modifier);
				break;

			case INST_CONSTANT:
				src[i] = ReadByMask(curInst.src[i].val, curInst.src[i].modifier);
				break;

			default:
				printf("Shader(Exec): Encounter unknow operand type \n");
				return;
			}
		}
		else
			break;
	}
endSrcOperand:
	return;
}

void ShaderCore::WriteBack()
{
	switch (curInst.dst.type) {
	case INST_ATTRIB:
		if (shaderType == 0)
			WriteByMask(dst, &(vtxPtr->attr[curInst.dst.id]), curInst.dst.modifier);
		else
			WriteByMask(dst, &(pixPtr->attr[curInst.dst.id]), curInst.dst.modifier);
		break;

	case INST_REG:
		WriteByMask(dst, &(reg[curInst.dst.id]), curInst.dst.modifier);
		break;

	case INST_COLOR:
		if (shaderType ==1)
			WriteByMask(dst, &(pixPtr->attr[1]), curInst.dst.modifier);
		else
			printf("Shader: Pix attribute color is not available in this shader");
	}
}

floatVec4 ShaderCore::ReadByMask(floatVec4 in, char *mask)
{
	floatVec4 temp;
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

void ShaderCore::WriteByMask(floatVec4 val, floatVec4* fvdst, char *mask)
{
	for (int i=0; i<4; i++) {
		switch (mask[i]) {
		case 'x':
		case 'r':
			fvdst->x = val.x;
			break;

		case 'y':
		case 'g':
			fvdst->y = val.y;
			break;

		case 'z':
		case 'b':
			fvdst->z = val.z;
			break;

		case 'w':
		case 'a':
			fvdst->w = val.w;
			break;
		default: //'\0'
			goto endLabel;
		}
	}
endLabel:
	return;
}

void ShaderCore::Print()
{

}
