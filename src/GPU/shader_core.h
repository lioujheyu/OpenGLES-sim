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
 *	Responsible for executing NVGP4 assembly code. It also contains texture_unit
 *	for TEX instruction execution. Currently, there are four fetch, execution,
 *	and write-back units in one shader core. Such architecture is served for one
 *	purpose - Find partial differential value from adjacent thread. It also has
 *	the ability to get texture scale factor without fixing hardware pipeline's
 *	help. But have a defect that it wastes resource on the ghost pixels which
 *	is already known as fail on edge test.
 */
class ShaderCore {
public:
	ShaderCore()
	{
		instCnt = 0;
		totalInstructionCnt = 0;
		totalScaleOperation = 0;
		for (int i=0; i<MAX_SHADER_REG_VECTOR*4; i++)
			reg[i].x = reg[i].y = reg[i].z = reg[i].w = 0.0f;

		tid = -1; tType = 0;
		instPool = nullptr;
		uniformPool = nullptr;
		threadPtr[0] = threadPtr[1] = threadPtr[2] = threadPtr[3] = nullptr;
		curInst.Init();
		Init();
	}

	TextureUnit texUnit;

	bool isEnable[4];
	int instCnt; ///< Program Length
	instruction const *instPool; ///< Instruction Pool pointer
	floatVec4 const *uniformPool; ///< Uniform Pool pointer
	unitThread* threadPtr[4];

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
	unitThread thread[4];
	bool curCCState[4]; ///< Current branch condition
	std::stack<bool> ccStack[4]; ///< Branch condition stack for nest IF block

	floatVec4 reg[MAX_SHADER_REG_VECTOR*4];
	floatVec4 CCisSigned[4][2], CCisZero[4][2];
	floatVec4 dst[4], src[4][3];
	int tid, tType;
};


#endif // SHADER_CORE_H_INCLUDED
