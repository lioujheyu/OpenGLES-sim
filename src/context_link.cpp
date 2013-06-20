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
		programPool[program].linkInfo = "A vertex shader and a fragment shader are not both present in the program object.";
		return;
	}
	else if ((VS.isCompiled == GL_FALSE) || (FS.isCompiled == GL_FALSE)) {
		programPool[program].linkInfo = "One or more of the attached shader objects has not been successfully compiled or loaded with a pre-compiled shader binary.";
		return;
	}

	t_program = programPool[program];
	t_program.linkInfo.clear();

/**
 * 	1st pass parsing for Link information retriving, including resource usage
 *	check and indexing. This stage Will also chech whether VS/FS's resource is
 *	matched.
 */
	nvgp4Info_lineno = 1;
	nvgp4Info_str_in(VS.asmSrc.c_str());
	nvgp4Info_parse();

	printf("\n");

	nvgp4Info_lineno = 1;
	nvgp4Info_str_in(FS.asmSrc.c_str());
	nvgp4Info_parse();

	if (t_program.linkInfo.size() != 0) {
		programPool[program].linkInfo = t_program.linkInfo;
		printf("%s\n", t_program.linkInfo.c_str());
		return;
	}

/**
 * 	2nd pass parsing for Custum instruction structure establishing from NVGP4
 *	assembly code. Resource remapping is performed in this stage.
 */
 	printf("\n");

	nvgp4ASM_lineno = 1;
	nvgp4ASM_str_in(VS.asmSrc.c_str());
	nvgp4ASM_parse();

	nvgp4ASM_lineno = 1;
	nvgp4ASM_str_in(FS.asmSrc.c_str());
	nvgp4ASM_parse();

	programPool[program] = t_program;
	programPool[program].isLinked = GL_TRUE;

	for (int i=0; i<t_program.VSinstructionPool.size(); i++)
		t_program.VSinstructionPool[i].Print();
	printf("\n");
	for (int i=0; i<t_program.FSinstructionPool.size(); i++)
		t_program.FSinstructionPool[i].Print();
}
