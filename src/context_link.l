%option noyywrap
%option yylineno
%option prefix="context_link_"
%option always-interactive

D	[0-9]
L	[a-zA-Z_]

%{
#include "context_link.tab.h"
#include "context.h"
#include "context_link_def.h"

#define COL_NO context_link_col+=strlen(yytext)

unsigned int context_link_col = 1;

extern int context_link_parse();
extern programObject t_program;
extern unsigned int shaderType;
%}

%%

^[ ]*[^#!].*$		/* Non-# or ! begin sentence, means real instruction */
"!!"[a-zA-Z0-9.]*	/* Compiler's name */
#[ ].*$				/* Comment */
#version.*$
#vendor.*$

"#profile"	COL_NO; return PROFILE;
"#program"	COL_NO; return PROG;
"#semantic"	COL_NO; return SEMT;
"#var"		COL_NO; return VAR;
((float)|(int)){D}?	{ COL_NO;
		strcpy(context_link_lval.sval,context_link_text);
		return TYPE;
	}
((float)|(int)){D}x{D}	{ COL_NO;
		strcpy(context_link_lval.sval,context_link_text);
		return TYPE;
	}
"sampler2D"	{ COL_NO;
		strcpy(context_link_lval.sval,context_link_text);
		return TYPE;
	}
"vin"	COL_NO;	return VIN;
"vout"	COL_NO;	return VOUT;
{L}({L}|{D})* { COL_NO;
		strcpy(context_link_lval.sval,context_link_text);
		return IDENTIFIER;
	}
[-+]?{D}+ { COL_NO;
		context_link_lval.ival = atoi(context_link_text);
		return INTEGER;
	}
[:\[\].$,]  return *context_link_text;

[ \t]*	COL_NO;		/* remove all space-related char */
\n		context_link_col = 1;
%%

void context_link_error(char *s)
{
    printf("(%d,%d)syntax error:%s\n",
			context_link_lineno,
			context_link_col,
			context_link_text);
}

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
		
	context_link_lineno = 1;
	shaderType = 0;
	context_link__scan_string(VS.asmSrc.c_str());
	context_link_parse();
	
	printf("\n");

	context_link_lineno = 1;
	shaderType = 1;
	context_link__scan_string(FS.asmSrc.c_str());
	context_link_parse();
	
	///Check both's shader's in/output are matched.
	std::map<std::string, symbol>::iterator it;
	for (it = t_program.symbolVSout.begin(); it!=t_program.symbolVSout.end(); it++) {
		if (t_program.symbolFSin.find(it->first) == t_program.symbolFSin.end()) {
			programPool[program].linkStatus = LS_VS_FS_VARRYING_UNMATCH;
			printf("%s \n",it->first.c_str());
			return;
		}
		else {
			if (t_program.symbolVSout[it->first].declareType != 
			    t_program.symbolFSin[it->first].declareType) {
				programPool[program].linkStatus = LS_VS_FS_VARRYING_UNMATCH;
				printf("%s \n",it->first.c_str());
				return;
			}
		}
	}
	
	t_program.linkInfo.clear();
	
//	printf("\nVSin: ");
//	for (it = t_program.symbolVSin.begin(); it!=t_program.symbolVSin.end(); it++)
//		printf("%s ",it->first.c_str());
//	printf("\nVSout: ");
//	for (it = t_program.symbolVSout.begin(); it!=t_program.symbolVSout.end(); it++)
//		printf("%s ",it->first.c_str());
//	printf("\nVSin: ");
//	for (it = t_program.symbolFSin.begin(); it!=t_program.symbolFSin.end(); it++)
//		printf("%s ",it->first.c_str());
//	printf("\nVSout: ");
//	for (it = t_program.symbolFSout.begin(); it!=t_program.symbolFSout.end(); it++)
//		printf("%s ",it->first.c_str());
//	printf("\nUniform: ");
//	for (it = t_program.symbolUniform.begin(); it!=t_program.symbolUniform.end(); it++)
//		printf("%s ",it->first.c_str());
//	printf("\n");
	
	programPool[program] = t_program;
	programPool[program].linkStatus = LS_NO_ERROR;
	programPool[program].isLinked = GL_TRUE;
	
}
