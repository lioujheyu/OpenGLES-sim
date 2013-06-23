/**
 *	@file shader_core.h
 *  @brief Shader Core simulator
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#ifndef SHADER_CORE_H_INCLUDED
#define SHADER_CORE_H_INCLUDED

#include "gpu_type.h"
#include "gpu_config.h"
#include "texture_unit.h"
#include "instruction_def.h"

class ShaderCore {
public:
	ShaderCore()
	{
		instCnt = 0;
		shaderType = VERTEX_SHADER;
		for (int i=0; i<MAX_SHADER_REG_VECTOR; i++)
			reg[i].x = reg[i].y = reg[i].z = reg[i].w = 0.0f;
		dst.x = dst.y = dst.z = dst.w = 0.0;
		src[0].x = src[0].y = src[0].z = src[0].w = 0.0;
		src[1].x = src[1].y = src[1].z = src[1].w = 0.0;
		src[2].x = src[2].y = src[2].z = src[2].w = 0.0;
		tid = -1, tType = 0;
		curInst.Init();
	}

	TextureUnit texUnit;

	int shaderType; ///< Vertex/Fragment Shader
	void *input;
	int instCnt; ///<Program Length
	instruction const *instPool;
	floatVec4 const *uniformPool;

	///statitic

	void Init();
	void Exec();
	void Print();
	void FetchData();
	void WriteBack();
	floatVec4 ReadByMask(floatVec4 in, char *mask);
	void WriteByMask(floatVec4 val, floatVec4 *fvdst, char *mask);

private:
	int PC; ///<Program Counter
	instruction	curInst;
	vertex *vtxPtr;
	pixel *pixPtr;

	floatVec4 reg[MAX_SHADER_REG_VECTOR];
	floatVec4 dst, src[3];
	int tid, tType;
};


#endif // SHADER_CORE_H_INCLUDED
