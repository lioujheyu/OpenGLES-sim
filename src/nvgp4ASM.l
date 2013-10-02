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
%option prefix="nvgp4ASM_"
%option always-interactive

D	[0-9]
L	[a-zA-Z_]

%{
#include "nvgp4ASM.tab.h"
#include "GPU/instruction_def.h"
#include "GPU/gpu_config.h"

#define COL_NO nvgp4ASM_col+=strlen(yytext)

unsigned int nvgp4ASM_col = 0;
%}

%%
#[ ].*$				/* Comment */
#version.*$
#vendor.*$
#program.*$
#semantic.*$
#var.*$
^!.*$				/* Comment */
ATTRIB.*$
TEMP.*$
PARAM.*$
OUTPUT.*$

"#profile"	COL_NO; return PROF;
"gp4vp"		COL_NO; nvgp4ASM_lval.ival=0; return SHADERTYPE;
"gp4fp"		COL_NO; nvgp4ASM_lval.ival=1; return SHADERTYPE;
"END"		COL_NO; return END;

"texture"	COL_NO;	return TEXTURE;

"ABS"				COL_NO;	nvgp4ASM_lval.ival=OP_ABS; return VECTOROP;
"CEIL"              COL_NO;	nvgp4ASM_lval.ival=OP_CEIL; return VECTOROP;
"FLR"               COL_NO;	nvgp4ASM_lval.ival=OP_FLR; return VECTOROP;
"FRC"               COL_NO;	nvgp4ASM_lval.ival=OP_FRC; return VECTOROP;
"I2F"               COL_NO;	nvgp4ASM_lval.ival=OP_I2F; return VECTOROP;
"LIT"               COL_NO;	nvgp4ASM_lval.ival=OP_LIT; return VECTOROP;
"MOV"               COL_NO;	nvgp4ASM_lval.ival=OP_MOV; return VECTOROP;
"NOT"               COL_NO;	nvgp4ASM_lval.ival=OP_NOT; return VECTOROP;
"NRM"               COL_NO;	nvgp4ASM_lval.ival=OP_NRM; return VECTOROP;
"PK2H"              COL_NO;	nvgp4ASM_lval.ival=OP_PK2H; return VECTOROP;
"PK2US"             COL_NO;	nvgp4ASM_lval.ival=OP_PK2US; return VECTOROP;
"PK4B"              COL_NO;	nvgp4ASM_lval.ival=OP_PK4B; return VECTOROP;
"PK4UB"             COL_NO;	nvgp4ASM_lval.ival=OP_PK4UB; return VECTOROP;
"ROUND"             COL_NO;	nvgp4ASM_lval.ival=OP_ROUND; return VECTOROP;
"SSG"               COL_NO;	nvgp4ASM_lval.ival=OP_SSG; return VECTOROP;
"TRUNC"             COL_NO;	nvgp4ASM_lval.ival=OP_TRUNC; return VECTOROP;
"COS"               COL_NO;	nvgp4ASM_lval.ival=OP_COS; return SCALAROP;
"EX2"               COL_NO;	nvgp4ASM_lval.ival=OP_EX2; return SCALAROP;
"LG2"               COL_NO;	nvgp4ASM_lval.ival=OP_LG2; return SCALAROP;
"RCC"               COL_NO;	nvgp4ASM_lval.ival=OP_RCC; return SCALAROP;
"RCP"               COL_NO;	nvgp4ASM_lval.ival=OP_RCP; return SCALAROP;
"RSQ"               COL_NO;	nvgp4ASM_lval.ival=OP_RSQ; return SCALAROP;
"SCS"               COL_NO;	nvgp4ASM_lval.ival=OP_SCS; return SCALAROP;
"SIN"               COL_NO;	nvgp4ASM_lval.ival=OP_SIN; return SCALAROP;
"UP2H"              COL_NO;	nvgp4ASM_lval.ival=OP_UP2H; return SCALAROP;
"UP2US"             COL_NO;	nvgp4ASM_lval.ival=OP_UP2US; return SCALAROP;
"UP4B"              COL_NO;	nvgp4ASM_lval.ival=OP_UP4B; return SCALAROP;
"UP4UB"             COL_NO;	nvgp4ASM_lval.ival=OP_UP4UB; return SCALAROP;
"POW"               COL_NO;	nvgp4ASM_lval.ival=OP_POW;  return BINSCOP;
"DIV"               COL_NO;	nvgp4ASM_lval.ival=OP_DIV; return VECSCAOP;
"SHL"               COL_NO;	nvgp4ASM_lval.ival=OP_SHL; return VECSCAOP;
"SHR"               COL_NO;	nvgp4ASM_lval.ival=OP_SHR; return VECSCAOP;
"MOD"               COL_NO;	nvgp4ASM_lval.ival=OP_MOD; return VECSCAOP;
"ADD"               COL_NO;	nvgp4ASM_lval.ival=OP_ADD; return BINOP;
"AND"               COL_NO;	nvgp4ASM_lval.ival=OP_AND; return BINOP;
"DP3"               COL_NO;	nvgp4ASM_lval.ival=OP_DP3; return BINOP;
"DP4"               COL_NO;	nvgp4ASM_lval.ival=OP_DP4; return BINOP;
"DPH"               COL_NO;	nvgp4ASM_lval.ival=OP_DPH; return BINOP;
"DST"               COL_NO;	nvgp4ASM_lval.ival=OP_DST; return BINOP;
"MAX"               COL_NO;	nvgp4ASM_lval.ival=OP_MAX; return BINOP;
"MIN"               COL_NO;	nvgp4ASM_lval.ival=OP_MIN; return BINOP;
"MUL"               COL_NO;	nvgp4ASM_lval.ival=OP_MUL; return BINOP;
"OR"                COL_NO;	nvgp4ASM_lval.ival=OP_OR; return BINOP;
"RFL"               COL_NO;	nvgp4ASM_lval.ival=OP_RFL; return BINOP;
"SEQ"               COL_NO;	nvgp4ASM_lval.ival=OP_SEQ; return BINOP;
"SFL"               COL_NO;	nvgp4ASM_lval.ival=OP_SFL; return BINOP;
"SGE"               COL_NO;	nvgp4ASM_lval.ival=OP_SGE; return BINOP;
"SGT"               COL_NO;	nvgp4ASM_lval.ival=OP_SGT; return BINOP;
"SLE"               COL_NO;	nvgp4ASM_lval.ival=OP_SLE; return BINOP;
"SLT"               COL_NO;	nvgp4ASM_lval.ival=OP_SLT; return BINOP;
"SNE"               COL_NO;	nvgp4ASM_lval.ival=OP_SNE; return BINOP;
"STR"               COL_NO;	nvgp4ASM_lval.ival=OP_STR; return BINOP;
"SUB"               COL_NO;	nvgp4ASM_lval.ival=OP_SUB; return BINOP;
"XPD"               COL_NO;	nvgp4ASM_lval.ival=OP_XPD; return BINOP;
"DP2"               COL_NO;	nvgp4ASM_lval.ival=OP_DP2; return BINOP;
"XOR"               COL_NO;	nvgp4ASM_lval.ival=OP_XOR; return BINOP;
"CMP"               COL_NO;	nvgp4ASM_lval.ival=OP_CMP; return TRIOP;
"DP2A"              COL_NO;	nvgp4ASM_lval.ival=OP_DP2A; return TRIOP;
"LRP"               COL_NO;	nvgp4ASM_lval.ival=OP_LRP; return TRIOP;
"MAD"               COL_NO;	nvgp4ASM_lval.ival=OP_MAD; return TRIOP;
"SAD"               COL_NO;	nvgp4ASM_lval.ival=OP_SAD; return TRIOP;
"X2D"               COL_NO;	nvgp4ASM_lval.ival=OP_X2D; return TRIOP;
"SWZ"               COL_NO;	nvgp4ASM_lval.ival=OP_SWZ; return SWZOP;
"TEX"               COL_NO;	nvgp4ASM_lval.ival=OP_TEX; return TEXOP;
"TXB"               COL_NO;	nvgp4ASM_lval.ival=OP_TXB; return TEXOP;
"TXF"               COL_NO;	nvgp4ASM_lval.ival=OP_TXF; return TEXOP;
"TXL"               COL_NO;	nvgp4ASM_lval.ival=OP_TXL; return TEXOP;
"TXP"               COL_NO;	nvgp4ASM_lval.ival=OP_TXP; return TEXOP;
"TXQ"               COL_NO;	nvgp4ASM_lval.ival=OP_TXQ; return TEXOP;
"TXD"               COL_NO;	nvgp4ASM_lval.ival=OP_TXD; return TXDOP;
"CAL"               COL_NO;	nvgp4ASM_lval.ival=OP_CAL; return BRAOP;
"RET"               COL_NO;	nvgp4ASM_lval.ival=OP_RET; return FLOWCCOP;
"BRK"               COL_NO;	nvgp4ASM_lval.ival=OP_BRK; return FLOWCCOP;
"CONT"              COL_NO;	nvgp4ASM_lval.ival=OP_CONT; return FLOWCCOP;
"IF"                COL_NO;	nvgp4ASM_lval.ival=OP_IF; return IFOP;
"REP"               COL_NO;	nvgp4ASM_lval.ival=OP_REP; return REPOP;
"ELSE"              COL_NO;	nvgp4ASM_lval.ival=OP_ELSE; return ENDFLOWOP;
"ENDIF"             COL_NO;	nvgp4ASM_lval.ival=OP_ENDIF; return ENDFLOWOP;
"ENDREP"            COL_NO;	nvgp4ASM_lval.ival=OP_ENDREP; return ENDFLOWOP;
"KIL"				COL_NO;	nvgp4ASM_lval.ival=OP_KIL; return KILOP;
"DDX"				COL_NO;	nvgp4ASM_lval.ival=OP_DDX; return DERIVEOP;
"DDY"				COL_NO;	nvgp4ASM_lval.ival=OP_DDY; return DERIVEOP;
"F"                 COL_NO;	nvgp4ASM_lval.ival=OPM_F; return OPMODIFIER;
"U"                 COL_NO;	nvgp4ASM_lval.ival=OPM_U; return OPMODIFIER;
"S"                 COL_NO;	nvgp4ASM_lval.ival=OPM_S; return OPMODIFIER;
"CC"                COL_NO;	nvgp4ASM_lval.ival=OPM_CC; return OPMODIFIER;
"CC0"               COL_NO;	nvgp4ASM_lval.ival=OPM_CC0; return OPMODIFIER;
"CC1"               COL_NO;	nvgp4ASM_lval.ival=OPM_CC1; return OPMODIFIER;
"SAT"               COL_NO;	nvgp4ASM_lval.ival=OPM_SAT; return OPMODIFIER;
"SSAT"              COL_NO;	nvgp4ASM_lval.ival=OPM_SSAT; return OPMODIFIER;
"NTC"               COL_NO;	nvgp4ASM_lval.ival=OPM_NTC; return OPMODIFIER;
"S24"               COL_NO;	nvgp4ASM_lval.ival=OPM_S24; return OPMODIFIER;
"U24"               COL_NO;	nvgp4ASM_lval.ival=OPM_U24; return OPMODIFIER;
"HI"                COL_NO;	nvgp4ASM_lval.ival=OPM_HI; return OPMODIFIER;
"1D"                COL_NO;	nvgp4ASM_lval.ival=TT_1D; return TEXTARGET;
"2D"                COL_NO;	nvgp4ASM_lval.ival=TT_2D; return TEXTARGET;
"3D"                COL_NO;	nvgp4ASM_lval.ival=TT_3D; return TEXTARGET;
"CUBE"              COL_NO;	nvgp4ASM_lval.ival=TT_CUBE; return TEXTARGET;
"RECT"              COL_NO;	nvgp4ASM_lval.ival=TT_RECT; return TEXTARGET;
"SHADOW1D"          COL_NO;	nvgp4ASM_lval.ival=TT_SHADOW1D; return TEXTARGET;
"SHADOW2D"          COL_NO;	nvgp4ASM_lval.ival=TT_SHADOW2D; return TEXTARGET;
"SHADOWRECT"        COL_NO;	nvgp4ASM_lval.ival=TT_SHADOWRECT; return TEXTARGET;
"ARRAY1D"           COL_NO;	nvgp4ASM_lval.ival=TT_ARRAY1D; return TEXTARGET;
"ARRAY2D"           COL_NO;	nvgp4ASM_lval.ival=TT_ARRAY2D; return TEXTARGET;
"SHADOWCUBE"        COL_NO;	nvgp4ASM_lval.ival=TT_SHADOWCUBE; return TEXTARGET;
"SHADOWARRAY1D"     COL_NO;	nvgp4ASM_lval.ival=TT_SHADOWARRAY1D; return TEXTARGET;
"SHADOWARRAY2D"     COL_NO;	nvgp4ASM_lval.ival=TT_SHADOWARRAY2D; return TEXTARGET;
"EQ"                COL_NO;	nvgp4ASM_lval.ival=CC_EQ; return CCMASKRULE;
"GE"                COL_NO;	nvgp4ASM_lval.ival=CC_GE; return CCMASKRULE;
"GT"                COL_NO;	nvgp4ASM_lval.ival=CC_GT; return CCMASKRULE;
"LE"                COL_NO;	nvgp4ASM_lval.ival=CC_LE; return CCMASKRULE;
"LT"                COL_NO;	nvgp4ASM_lval.ival=CC_LT; return CCMASKRULE;
"NE"                COL_NO;	nvgp4ASM_lval.ival=CC_NE; return CCMASKRULE;
"TR"                COL_NO;	nvgp4ASM_lval.ival=CC_TR; return CCMASKRULE;
"FL"                COL_NO;	nvgp4ASM_lval.ival=CC_FL; return CCMASKRULE;
"EQ0"               COL_NO;	nvgp4ASM_lval.ival=CC_EQ0; return CCMASKRULE;
"GE0"               COL_NO;	nvgp4ASM_lval.ival=CC_GE0; return CCMASKRULE;
"GT0"               COL_NO;	nvgp4ASM_lval.ival=CC_GT0; return CCMASKRULE;
"LE0"               COL_NO;	nvgp4ASM_lval.ival=CC_LE0; return CCMASKRULE;
"LT0"               COL_NO;	nvgp4ASM_lval.ival=CC_LT0; return CCMASKRULE;
"NE0"               COL_NO;	nvgp4ASM_lval.ival=CC_NE0; return CCMASKRULE;
"TR0"               COL_NO;	nvgp4ASM_lval.ival=CC_TR0; return CCMASKRULE;
"FL0"               COL_NO;	nvgp4ASM_lval.ival=CC_FL0; return CCMASKRULE;
"EQ1"               COL_NO;	nvgp4ASM_lval.ival=CC_EQ1; return CCMASKRULE;
"GE1"               COL_NO;	nvgp4ASM_lval.ival=CC_GE1; return CCMASKRULE;
"GT1"               COL_NO;	nvgp4ASM_lval.ival=CC_GT1; return CCMASKRULE;
"LE1"               COL_NO;	nvgp4ASM_lval.ival=CC_LE1; return CCMASKRULE;
"LT1"               COL_NO;	nvgp4ASM_lval.ival=CC_LT1; return CCMASKRULE;
"NE1"               COL_NO;	nvgp4ASM_lval.ival=CC_NE1; return CCMASKRULE;
"TR1"               COL_NO;	nvgp4ASM_lval.ival=CC_TR1; return CCMASKRULE;
"FL1"               COL_NO;	nvgp4ASM_lval.ival=CC_FL1; return CCMASKRULE;
"NAN"               COL_NO;	nvgp4ASM_lval.ival=CC_NAN; return CCMASKRULE;
"NAN0"              COL_NO;	nvgp4ASM_lval.ival=CC_NAN0; return CCMASKRULE;
"NAN1"              COL_NO;	nvgp4ASM_lval.ival=CC_NAN1; return CCMASKRULE;
"LEG"               COL_NO;	nvgp4ASM_lval.ival=CC_LEG; return CCMASKRULE;
"LEG0"              COL_NO;	nvgp4ASM_lval.ival=CC_LEG0; return CCMASKRULE;
"LEG1"              COL_NO;	nvgp4ASM_lval.ival=CC_LEG1; return CCMASKRULE;
"CF"                COL_NO;	nvgp4ASM_lval.ival=CC_CF; return CCMASKRULE;
"CF0"               COL_NO;	nvgp4ASM_lval.ival=CC_CF0; return CCMASKRULE;
"CF1"               COL_NO;	nvgp4ASM_lval.ival=CC_CF1; return CCMASKRULE;
"NCF"               COL_NO;	nvgp4ASM_lval.ival=CC_NCF; return CCMASKRULE;
"NCF0"              COL_NO;	nvgp4ASM_lval.ival=CC_NCF0; return CCMASKRULE;
"NCF1"              COL_NO;	nvgp4ASM_lval.ival=CC_NCF1; return CCMASKRULE;
"OF"                COL_NO;	nvgp4ASM_lval.ival=CC_OF; return CCMASKRULE;
"OF0"               COL_NO;	nvgp4ASM_lval.ival=CC_OF0; return CCMASKRULE;
"OF1"               COL_NO;	nvgp4ASM_lval.ival=CC_OF1; return CCMASKRULE;
"NOF"               COL_NO;	nvgp4ASM_lval.ival=CC_NOF; return CCMASKRULE;
"NOF0"              COL_NO;	nvgp4ASM_lval.ival=CC_NOF0; return CCMASKRULE;
"NOF1"              COL_NO;	nvgp4ASM_lval.ival=CC_NOF1; return CCMASKRULE;
"AB"                COL_NO;	nvgp4ASM_lval.ival=CC_AB; return CCMASKRULE;
"AB0"               COL_NO;	nvgp4ASM_lval.ival=CC_AB0; return CCMASKRULE;
"AB1"               COL_NO;	nvgp4ASM_lval.ival=CC_AB1; return CCMASKRULE;
"BLE"               COL_NO;	nvgp4ASM_lval.ival=CC_BLE; return CCMASKRULE;
"BLE0"              COL_NO;	nvgp4ASM_lval.ival=CC_BLE0; return CCMASKRULE;
"BLE1"              COL_NO;	nvgp4ASM_lval.ival=CC_BLE1; return CCMASKRULE;
"SF"                COL_NO;	nvgp4ASM_lval.ival=CC_SF; return CCMASKRULE;
"SF0"               COL_NO;	nvgp4ASM_lval.ival=CC_SF0; return CCMASKRULE;
"SF1"               COL_NO;	nvgp4ASM_lval.ival=CC_SF1; return CCMASKRULE;
"NSF"               COL_NO;	nvgp4ASM_lval.ival=CC_NSF; return CCMASKRULE;
"NSF0"              COL_NO;	nvgp4ASM_lval.ival=CC_NSF0; return CCMASKRULE;
"NSF1"              COL_NO;	nvgp4ASM_lval.ival=CC_NSF1; return CCMASKRULE;
"vertex"            COL_NO; return VERTEX;
"fragment"          COL_NO; return FRAGMENT;
"result"            COL_NO; return RESULT;
"attrib"            COL_NO; return ATTRIB;
"position"          COL_NO; return POSITION;
"result_color0"     COL_NO; return RESULT_COLOR0;
[xyzwrgbac]         COL_NO;	return *nvgp4ASM_text;
"HC"				COL_NO; nvgp4ASM_lval.ival=-1; return REG;
"RC"				COL_NO; nvgp4ASM_lval.ival=-1; return REG;

R{D}+ { COL_NO;
		char *temp = nvgp4ASM_text+1;
		nvgp4ASM_lval.ival=atoi(temp);
		return REG;
	}
[xyzw]{2,4} { COL_NO;
		strcpy(nvgp4ASM_lval.sval,nvgp4ASM_text);
		return XYZW_SWIZZLE;
	}
[rgba]{1,4} { COL_NO;
		strcpy(nvgp4ASM_lval.sval,nvgp4ASM_text);
		return RGBA_SWIZZLE;
	}
{L}({L}|{D})* { COL_NO;
		strcpy(nvgp4ASM_lval.sval,nvgp4ASM_text);
		return IDENTIFIER;
	}
[-+]?{D}+ { COL_NO;
		nvgp4ASM_lval.ival = atoi(nvgp4ASM_text);
		return INTEGER;
	}
[-+]?{D}+\.{D}+([eE][-+]?{D}+)? { COL_NO;
		nvgp4ASM_lval.fval = atof(nvgp4ASM_text);
		return FLOAT;
	}
[:\[\].$,;\-\+{}|()]  COL_NO; return *nvgp4ASM_text;

[ \t]*	COL_NO;		/* remove all space-related char */
\n		nvgp4ASM_col = 0;
%%

void nvgp4ASM_error(char *s)
{
    printf("(%d,%d) %s at %s\n",
			nvgp4ASM_lineno,
			nvgp4ASM_col,
			s,
			nvgp4ASM_text);
}

void nvgp4ASM_str_in(const char *s)
{
	nvgp4ASM__scan_string(s);
}

