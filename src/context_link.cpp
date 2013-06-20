#include "context.h"
#include "context_link_def.h"

#include "nvgp4Info.tab.h"
#include "nvgp4ASM.tab.h"

extern int nvgp4Info_parse();
extern void nvgp4Info_str_in(const char *s);
extern int nvgp4Info_lineno;
extern int nvgp4ASM_parse();
extern void nvgp4ASM_str_in(const char *s);
extern int nvgp4ASM_lineno;

extern programObject t_program;
extern unsigned int shaderType;
extern std::vector<instruction> instructionPool;

void Context::LinkProgram(GLuint program)
{
	shaderObject VS, FS;
	VS = shaderPool[programPool[program].sid4VS];
	FS = shaderPool[programPool[program].sid4FS];

	if (programPool.find(program) == programPool.end()) {
		RecordError(GL_INVALID_VALUE);
		return;
	}

	if (programPool[program].isLinked == GL_TRUE)
		return;

	if ((programPool[program].sid4VS == 0) || (programPool[program].sid4FS == 0)) {
		programPool[program].linkStatus = LS_SHADER_MISSING;
		programPool[program].linkInfo = "A vertex shader and a fragment shader are not both present in the program object.";
		return;
	}
	else if ((VS.isCompiled == GL_FALSE) || (FS.isCompiled == GL_FALSE)) {
		programPool[program].linkStatus = LS_SHADER_IS_NOT_COMPILED;
		programPool[program].linkInfo = "One or more of the attached shader objects has not been successfully compiled or loaded with a pre-compiled shader binary.";
		return;
	}

	t_program = programPool[program];


/**
 * 	1st pass parsing for Link information retriving. Will also perfrom linkage
 *	check.
 */
	nvgp4Info_lineno = 1;
	nvgp4Info_str_in(VS.asmSrc.c_str());
	nvgp4Info_parse();

	printf("\n");

	nvgp4Info_lineno = 1;
	nvgp4Info_str_in(FS.asmSrc.c_str());
	nvgp4Info_parse();

	///Check both's shader's in/output are matched.
	std::map<std::string, symbol>::iterator it;
	for (it = t_program.symbolVSout.begin(); it!=t_program.symbolVSout.end(); it++) {
		if (t_program.symbolFSin.find(it->first) == t_program.symbolFSin.end()) {
			programPool[program].linkStatus = LS_VS_FS_VARRYING_UNMATCH;
			programPool[program].linkInfo = "L0008: Type mismatch between vertex output and fragment input";
			printf("%s \n",it->first.c_str());
			return;
		}
		else {
			if (t_program.symbolVSout[it->first].declareType !=
			    t_program.symbolFSin[it->first].declareType) {
				programPool[program].linkStatus = LS_VS_FS_VARRYING_UNMATCH;
				programPool[program].linkInfo = "L0008: Type mismatch between vertex output and fragment input";
				printf("%s \n",it->first.c_str());
				return;
			}
		}
	}

	t_program.linkInfo.clear();

	programPool[program] = t_program;
	programPool[program].linkStatus = LS_NO_ERROR;
	programPool[program].isLinked = GL_TRUE;

/**
 * 	2nd pass parsing for Custum instruction structure establishing from NVGP4
 *	assembly code.
 */
	nvgp4ASM_lineno = 1;
	nvgp4ASM_str_in(VS.asmSrc.c_str());
	nvgp4ASM_parse();

	printf("\n");

	nvgp4ASM_lineno = 1;
	nvgp4ASM_str_in(FS.asmSrc.c_str());
	nvgp4ASM_parse();
}
