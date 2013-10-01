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
 *	@file context_link.cpp
 *  @brief Link vertex shader and fragment shader under specified program object
 *  @author Liou Jhe-Yu (lioujheyu@gmail.com)
 */

#include "context.h"

#include "nvgp4Info.tab.h"
#include "nvgp4ASM.tab.h"

///Parse assembly source's header info into symbol table.
extern int nvgp4Info_parse();
///Setting which string will be the info-parsing input.
extern void nvgp4Info_str_in(const char *s);
extern int nvgp4Info_lineno;

///Parse assembly instruction into custom instruction format.
extern int nvgp4ASM_parse();
///Setting which string will be the instruction-parsing input.
extern void nvgp4ASM_str_in(const char *s);
extern int nvgp4ASM_lineno;

extern programObject t_program;
extern unsigned int shaderType;

/**
 *	@brief Link target programObject
 *
 *	The link function will link the both ASM source in vertex shaderObjects
 *	and fragment shaderObject which are attached under target programObject.
 */
void Context::LinkProgram(GLuint program)
{
	GLuint VS, FS;
	VS = programPool[program].sid4VS;
	FS = programPool[program].sid4FS;

	if (programPool.find(program) == programPool.end()) {
		RecordError(GL_INVALID_VALUE);
		return;
	}

	if (programPool[program].isLinked == GL_TRUE)
		return;

	if ((VS == 0) || (FS == 0)) {
		programPool[program].linkInfo = "A vertex shader and a fragment shader are not both present in the program object.";
		fprintf(stderr, "%s\n", programPool[program].linkInfo.c_str());
		return;
	}
	else if ((shaderPool[VS].isCompiled == GL_FALSE) ||
			 (shaderPool[FS].isCompiled == GL_FALSE)) {
		programPool[program].linkInfo = "One or more of the attached shader objects has not been successfully compiled or loaded with a pre-compiled shader binary.";
		fprintf(stderr, "%s\n", programPool[program].linkInfo.c_str());
		return;
	}

	t_program = programPool[program];
	t_program.linkInfo.clear();

/*
 * 	1st pass parsing for Link information retrieving, including resource usage
 *	check and indexing. This stage Will also check whether VS/FS's resource are
 *	matched.
 */
	nvgp4Info_lineno = 1;
	nvgp4Info_str_in(shaderPool[VS].asmSrc.c_str());
	nvgp4Info_parse();

//	printf("\n");

	nvgp4Info_lineno = 1;
	nvgp4Info_str_in(shaderPool[FS].asmSrc.c_str());
	nvgp4Info_parse();

	if (t_program.VSinCnt > MAX_ATTRIBUTE_NUMBER)
		programPool[program].linkInfo = "L0003: Too many vertex input values";
	else if (t_program.VSoutCnt > MAX_ATTRIBUTE_NUMBER)
		programPool[program].linkInfo = "L0004: Too many vertex output values";
	else if (t_program.VSuniformCnt > MAX_VERTEX_UNIFORM_VECTORS ||
			 t_program.FSuniformCnt > MAX_FRAGMENT_UNIFORM_VECTORS ||
			 t_program.texCnt > MAX_TEXTURE_CONTEXT)
		programPool[program].linkInfo = "L0005: Too many uniform values";

	if (t_program.linkInfo.size() != 0) {
		programPool[program].linkInfo = t_program.linkInfo;
		fprintf(stderr, "%s\n", programPool[program].linkInfo.c_str());
		return;
	}
	else if (programPool[program].linkInfo.size() != 0){
		fprintf(stderr, "%s\n", programPool[program].linkInfo.c_str());
		return;
	}

/*
 * 	2nd pass parsing for custom instruction structure establishing from NVGP4
 *	assembly code. Resource remapping is performed in this stage.
 */
// 	printf("\n");

	nvgp4ASM_lineno = 1;
	nvgp4ASM_str_in(shaderPool[VS].asmSrc.c_str());
	nvgp4ASM_parse();

	nvgp4ASM_lineno = 1;
	nvgp4ASM_str_in(shaderPool[FS].asmSrc.c_str());
	nvgp4ASM_parse();

	programPool[program] = t_program;
	programPool[program].isLinked = GL_TRUE;

//	for (unsigned int i=0; i<t_program.VSinstructionPool.size(); i++)
//		t_program.VSinstructionPool[i].Print();
//	printf("\n");
//	for (unsigned int i=0; i<t_program.FSinstructionPool.size(); i++)
//		t_program.FSinstructionPool[i].Print();
}
