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

/**
 *	@brief Unified shader core class
 *
 *	Responsible for executing NVGP4 assembly code. It also contain texture_unit
 *	for tex instruction execution.
 */
class ShaderCore {
public:
	ShaderCore()
	{
		instCnt = 0;
		totalInstructionCnt = 0;
		totalScaleOperation = 0;
		shaderType = VERTEX_SHADER;
		for (int i=0; i<MAX_SHADER_REG_VECTOR*4; i++)
			reg[i].x = reg[i].y = reg[i].z = reg[i].w = 0.0f;

		tid = -1; tType = 0;
		input[0] = input[1] = input[2] = input[3] = nullptr;
		instPool = nullptr;
		uniformPool = nullptr;
		vtxPtr[0] = vtxPtr[1] = vtxPtr[2] = vtxPtr[3] = nullptr;
		pixPtr[0] = pixPtr[1] = pixPtr[2] = pixPtr[3] = nullptr;
		curInst.Init();
		Init();
	}

	TextureUnit texUnit;

	int shaderType; ///< Vertex/Fragment Shader
	bool enableFlag[4];
	void *input[4]; ///< Input pointer, can be further convert into vertex or pixel
	int instCnt; ///< Program Length
	instruction const *instPool; ///< Instruction Pool pointer
	floatVec4 const *uniformPool; ///< Uniform Pool pointer

	///Statistic
	///@{
	FILE *SHADERINFOfp;
	int totalInstructionCnt;
	int totalScaleOperation;
	///@}

	void Init();
	void Run();
	void Exec(int idx);
	void Print();
	void FetchData(int idx);
	void WriteBack(int idx);
	floatVec4 ReadByMask(floatVec4 in, char *mask);
	void WriteByMask(floatVec4 val, floatVec4 *fvdst, char *mask, int idx);

private:
	int PC; ///<Program Counter
	instruction	curInst; ///< Current Instruction
	vertex *vtxPtr[4];	vertex vtxTemp[4];
	pixel *pixPtr[4];	pixel pixTemp[4];
	bool curCCState[4];
	std::stack<bool> ccStack[4];

	floatVec4 reg[MAX_SHADER_REG_VECTOR*4];
	floatVec4 CCisSigned[4][2], CCisZero[4][2];
	floatVec4 dst[4], src[4][3];
	int tid, tType;
};


#endif // SHADER_CORE_H_INCLUDED
