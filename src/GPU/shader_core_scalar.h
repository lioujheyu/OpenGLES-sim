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
 *	@file shader_core_scalar.h
 *  @brief Scalar Shader Core class
 *  @author Liou Jhe-Yu(lioujheyu@gmail.com)
 */

#ifndef SHADER_CORE_H_INCLUDED
#define SHADER_CORE_H_INCLUDED

#include <stack>
#include <cstring>

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
 *	Respond for executing NVGP4 assembly code. It also contains texture_unit
 *	for TEX instruction execution. Currently, there are four fetch, execution,
 *	and write-back units in one shader core. Such architecture is served for one
 *	purpose - Find partial differential value from adjacent thread. It also has
 *	the ability to get texture scale factor without fixing hardware pipeline's
 *	help. But have a defect that it wastes resource on the ghost pixels which
 *	has already known as failed on edge test in previous stage.
 */
class ScalarShaderCore {
public:
	ScalarShaderCore()
	{
		instCnt = 0;
		totalInstructionCnt = 0;
		totalScaleOperation = 0;

		texID = -1; texType = 0;
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

private:
	int PC; ///<Program Counter
	instruction	curInst; ///< Current Instruction
	unitThread thread[4];

	bool curCCState[4]; ///< Current branch condition
	std::stack<bool> ccStack[4]; ///< Branch condition stack for nest IF block
	std::stack<int> RepCntStack; ///< Repeat Counter for each nest REP block
	std::stack<int> RepNumStack; ///< Repeat number for each nest REP block
	std::stack<int> RepPCStack; ///< Start PC for each nest REP block

	float reg[MAX_SHADER_REG_VECTOR*4*4];
	bool predReg[8];
	floatVec4 CCisSigned[4][2], CCisZero[4][2];
	float dst[4], src[4][3];
	floatVec4 dstVec4[4], srcVec4[4][3];
	int texID, texType;
};


#endif // SHADER_CORE_H_INCLUDED