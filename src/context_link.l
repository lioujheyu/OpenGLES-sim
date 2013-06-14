%option noyywrap
%option yylineno
%option prefix="context_link_"
%option always-interactive

D	[0-9]
L	[a-zA-Z_]

%{
#include "context_link.tab.h"
#include "context.h"
#include "context_link_glapi.h"

#define COL_NO context_link_col+=strlen(yytext)

unsigned int context_link_col = 1;

extern int context_link_parse();
extern programObject currentProgram;
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
":"		COL_NO;	return ':';
"["		COL_NO;	return '[';
"]"		COL_NO;	return ']';
"."		COL_NO;	return '.';
"$"		COL_NO;	return '$';
","		COL_NO;	return ',';

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
	
	if ((programPool[program].sid4VS == 0) || (programPool[program].sid4FS == 0)) {
		programPool[program].linkStatus = LS_SHADER_MISSING;
		return;
	}
	else if ((VS.isCompiled == GL_FALSE) || (FS.isCompiled == GL_FALSE)) {
		programPool[program].linkStatus = LS_SHADER_ISNOTCOMPILED;
		return;
	}
	
	currentProgram = programPool[program];
		
	for (int i=0; i<VS.count; i++) {
		context_link_lineno = 1;
		shaderType = 0;
		context_link__scan_string(VS.compiledSourcePool[i].c_str());
		context_link_parse();
	}

	for (int i=0; i<FS.count; i++) {
		context_link_lineno = 1;
		shaderType = 1;
		context_link__scan_string(FS.compiledSourcePool[i].c_str());
		context_link_parse();
	}
	
	///Check both's shader's in/output are matched.
	
	
	programPool[program] = currentProgram;
	programPool[program].linkStatus = LS_NO_ERROR;
	programPool[program].isLinked = GL_TRUE;
}


