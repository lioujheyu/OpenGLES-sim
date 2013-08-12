/**
 *	@file shader_core.h
 *  @brief Shader Core class
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#ifndef SHADER_CORE_H_INCLUDED
#define SHADER_CORE_H_INCLUDED

#include <stack>

#include "gpu_type.h"
#include "gpu_config.h"
#include "texture_unit.h"
#include "instruction_def.h"

#ifdef SHADER_INFO
#	define SHADERPRINTF(fmt, ...) \
		do { if (DBG_ON) fprintf(SHADER_INFO_PTR, fmt, ##__VA_ARGS__); } while (0)
#else
#	define SHADERPRINTF(fmt, ...)
#endif //SHADER_INFO

#ifdef SHADER_INFO_FILE
#	define SHADER_INFO_PTR SHADERINFOfp
#else
#	define SHADER_INFO_PTR stderr
#endif

class ShaderCore {
public:
	ShaderCore()
	{
		instCnt = 0;
		shaderType = VERTEX_SHADER;
		for (int i=0; i<MAX_SHADER_REG_VECTOR; i++)
			reg[i].x = reg[i].y = reg[i].z = reg[i].w = 0.0f;

		tid = -1; tType = 0; input = nullptr;
		instPool = nullptr;
		uniformPool = nullptr;
		vtxPtr = nullptr;
		pixPtr = nullptr;
		curInst.Init();
		Init();
	}

	TextureUnit texUnit;

	int shaderType; ///< Vertex/Fragment Shader
	void *input; ///< Input pointer, can be further convert into vertex or pixel
	int instCnt; ///< Program Length
	instruction const *instPool; ///< Instruction Pool pointer
	floatVec4 const *uniformPool; ///< Uniform Pool pointer

	///statitic
	FILE *SHADERINFOfp;

	void Init();
	void Exec();
	void Print();
	void FetchData();
	void WriteBack();
	floatVec4 ReadByMask(floatVec4 in, char *mask);
	void WriteByMask(floatVec4 val, floatVec4 *fvdst, char *mask);

private:
	int PC; ///<Program Counter
	instruction	curInst; ///< Current Instruction
	vertex *vtxPtr;
	pixel *pixPtr;
	bool curCCState;
	std::stack<bool> ccStack;

	floatVec4 reg[MAX_SHADER_REG_VECTOR];
	floatVec4 CCisSigned[2], CCisZero[2];
	floatVec4 dst, src[3];
	int tid, tType;
};


#endif // SHADER_CORE_H_INCLUDED
