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
%option noyywrap
%option yylineno
%option prefix="nvgp4Info_"
%option always-interactive

D	[0-9]
L	[a-zA-Z_]

%{
#include "nvgp4Info.tab.h"

#include "GPU/instruction_def.h"
#include "GPU/gpu_config.h"

#define COL_NO nvgp4Info_col+=strlen(yytext)

unsigned int nvgp4Info_col = 0;
%}

%%

^[ ]*[^#!].*$       /* Non-# or ! begin sentence, means real instruction */
"!!"[a-zA-Z0-9.]*	/* Compiler's name */
#[ ].*$				/* Comment */
#version.*$
#vendor.*$

"#profile"	COL_NO; return PROF;
"#program"	COL_NO; return PROG;
"#semantic"	COL_NO; return SEMT;
"#var"		COL_NO; return VAR;
"gp4vp"		COL_NO; nvgp4Info_lval.ival=0; return SHADERTYPE;
"gp4fp"		COL_NO; nvgp4Info_lval.ival=1; return SHADERTYPE;

((float)|(int)){D}?	{ COL_NO;
		strcpy(nvgp4Info_lval.sval,nvgp4Info_text);
		return TYPE;
	}
((float)|(int)){D}x{D}	{ COL_NO;
		strcpy(nvgp4Info_lval.sval,nvgp4Info_text);
		return TYPE;
	}
(sampler2D)|(samplerCUBE)	{ COL_NO;
		strcpy(nvgp4Info_lval.sval,nvgp4Info_text);
		return TYPE;
	}
"vin"	COL_NO;	return VIN;
"vout"	COL_NO;	return VOUT;


{L}({L}|{D})* { COL_NO;
		strcpy(nvgp4Info_lval.sval,nvgp4Info_text);
		return IDENTIFIER;
	}
[-+]?{D}+ { COL_NO;
		nvgp4Info_lval.ival = atoi(nvgp4Info_text);
		return INTEGER;
	}
[-+]?{D}+\.{D}+ { COL_NO;
		nvgp4Info_lval.ival = atof(nvgp4Info_text);
		return FLOAT;
	}
[:\[\].$,;\-\+{}|()<>]  COL_NO; return *nvgp4Info_text;

[ \t]*	COL_NO;		/* remove all space-related char */
\n		nvgp4Info_col = 0;
%%

void nvgp4Info_error(char *s)
{
    printf("(%d,%d) %s at %s\n",
			nvgp4Info_lineno,
			nvgp4Info_col,
			s,
			nvgp4Info_text);
}

void nvgp4Info_str_in(const char *s)
{
	nvgp4Info__scan_string(s);
}

