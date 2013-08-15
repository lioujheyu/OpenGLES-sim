%{
#include "context.h"

#include "GPU/instruction_def.h"
#include "GPU/gpu_config.h"

int nvgp4Info_lex(void);
void nvgp4Info_error(char *s);
void nvgp4Info_str_in(const char *s);

programObject t_program;
unsigned int shaderType;
int t_element;
int t_idx;
symbol t_symbol;
%}

%union {
	int		ival;
	float	fval;
	char	sval[30];
}

%token PROF PROG SEMT VAR VIN VOUT
%token <ival> SHADERTYPE
%token <sval> IDENTIFIER
%token <ival> INTEGER
%token <fval> FLOAT
%token <sval> TYPE

%type <ival> io_type
%type <sval> complex_id resource

%%

input
	:	line input
	|	/* empty */
	;

line:	profile
	|	program
	|	semantic
	|	link_info
	;

profile: PROF SHADERTYPE {shaderType = $2}

program: PROG IDENTIFIER

semantic
	: 	SEMT IDENTIFIER
	|	SEMT IDENTIFIER IDENTIFIER
	;

link_info: VAR TYPE complex_id ':' io_type ':' resource ':' INTEGER ':' INTEGER {
		t_symbol.name = $3;
		t_symbol.declareType = $2;

		//Force position to use the first attribute slot
		if (strcmp($7,"HPOS") == 0) {
			t_symbol.idx = 0;
			t_symbol.element = t_element;
			t_program.VSoutCnt+= t_element;
			t_program.srcVSout[t_symbol.name] = t_symbol;
			t_program.varyEnable[0] = true;
		}
		else if (strncmp($7,"ATTR",4) == 0) {
			t_idx = (unsigned int)$7[4] - 48;
			t_symbol.element = t_element;
			if (shaderType == VERTEX_SHADER) {
				if ($5 == CG_IN) {
					t_symbol.idx = t_idx;
					t_program.VSinCnt += t_element;
					t_program.srcVSin[$3]=t_symbol;
				}
				else { //Varying
					//Cause position has already occupy the attribute slot 0
					t_symbol.idx = t_idx + 1;
					t_symbol.element = t_element;
					t_program.VSoutCnt+= t_element;
					t_program.srcVSout[t_symbol.name]=t_symbol;
					t_program.varyEnable[t_symbol.idx] = true;
				}
			}
			else { //Fragment Shader
				if ($5 == CG_IN) { //Varying
					//Check whether VS.output and FS.input are matched.
					if (t_program.srcVSout.find(t_symbol.name) == t_program.srcVSout.end()) {
						t_program.linkInfo = "L0007: Fragment shader uses an input where there is no corresponding vertex output";
						fprintf(stderr, "Linker: %s \n", $3);
						YYABORT;
					}
					else {
						if (t_program.srcVSout[t_symbol.name].declareType != $2) {
							t_program.linkInfo = "L0008: Type mismatch between vertex output and fragment input";
							fprintf(stderr, "Linker: Type mismatch %s \n", $3);
							YYABORT;
						}
						else {
							//Cause position has already occupy the attribute slot 0
							t_symbol.idx = t_idx + 1;
							t_symbol.element = t_element;
							t_program.FSinCnt+= t_element;
							t_program.srcFSin[t_symbol.name]=t_symbol;
						}
					}
				}
				else
					fprintf(stderr, "Linker: ATTR can NOT be used under Fragment shader.\n");
			}
		}
		else if (strncmp($7,"texunit",7) == 0) {
			if (t_program.srcTexture.find(t_symbol.name) == t_program.srcTexture.end()) {
				t_symbol.idx = t_idx;
				t_symbol.element = t_element;
				t_program.texCnt+= t_element;
				t_program.srcTexture[t_symbol.name] = t_symbol;
			}
			else { // VS has already declared this texture
				if (t_program.srcTexture[t_symbol.name].declareType != $2) {
					t_program.linkInfo = "L0008: Type mismatch between vertex output and fragment input";
					fprintf(stderr, "Linker: Type mismatch %s \n", $3);
					YYABORT;
				}
			}
			
			if (shaderType == VERTEX_SHADER) {
				for (int i=0;i<t_element; i++) {
					t_program.asmVStexIdx[i + t_idx].name = t_symbol.name;
					t_program.asmVStexIdx[i + t_idx].idx = t_idx;
				}
			}
			else { //Fragment Shader
				for (int i=0;i<t_element; i++) {
					t_program.asmFStexIdx[i + t_idx].name = t_symbol.name;
					t_program.asmFStexIdx[i + t_idx].idx = t_idx;
				}
			}
		}
		//@todo: Need to handle the multi output situation
		else if (strncmp($7,"COL",3) == 0) {
			t_symbol.idx = 0;
			t_symbol.element = t_element;
			t_program.FSoutCnt+= t_element;
			t_program.srcFSout[t_symbol.name] = t_symbol;
		}
		else if ($7[0] == 'c') {
			t_symbol.element = t_element;
			if (t_program.srcUniform.find(t_symbol.name) == t_program.srcUniform.end()) {
				t_symbol.idx = t_program.uniformCnt;
				t_program.uniformCnt+= t_element;
				t_program.uniformUsage[t_symbol.idx] = t_symbol.name;
				t_program.srcUniform[t_symbol.name] = t_symbol;
			}
			else {
				if (t_program.srcUniform[t_symbol.name].declareType != t_symbol.declareType) {
					t_program.linkInfo = "L0001: Global variables must have the same type (including the same names for structure and field names and the same size for arrays) and precision.";
					fprintf(stderr, "Linker: %s \n",$3);
					YYABORT;
				}
				else
					t_symbol = t_program.srcUniform[t_symbol.name];
			}

			if (shaderType == 0) {
				for (int i=0;i<t_element; i++) {
					t_program.asmVSIdx[i + t_idx].name = t_symbol.name;
					t_program.asmVSIdx[i + t_idx].idx = t_idx;
				}
				t_program.VSuniformCnt+= t_element;
			}
			else {
				for (int i=0;i<t_element; i++) {
					t_program.asmFSIdx[i + t_idx].name = t_symbol.name;
					t_program.asmFSIdx[i + t_idx].idx = t_idx;
				}
				t_program.FSuniformCnt+= t_element;
			}
		}
//		else //The variable is useless in current program (maybe)
//			return 0;
		
		t_symbol.Print();
	};

complex_id
	:	IDENTIFIER					{strcpy($$,$1);}
	|	IDENTIFIER '[' INTEGER ']' {
			strcpy($$, $1); 
			strcat($$, "[");
			sprintf($$, "%s%d", $$, $3);
			strcat($$,"]");
		};
	;
	
resource
	:	/* empty */					{$$[0] = '\0';}
	|	IDENTIFIER					{strcpy($$,$1); t_element = 1;}
	|	IDENTIFIER '[' INTEGER ']'	{strcpy($$,$1); t_idx = $3; t_element = 1;}
	|	IDENTIFIER '[' INTEGER ']' ',' INTEGER	{strcpy($$,$1); t_idx = $3; t_element = $6;}
	|	',' INTEGER					{$$[0] = '\0';}
	|	IDENTIFIER INTEGER			{strcpy($$,$1); t_idx = $2; t_element = 1;}
	;

io_type
	:	/* empty */					{$$ = 0;}
	|	'$' VIN '.' IDENTIFIER		{$$ = CG_IN;}
	|	'$' VOUT '.' IDENTIFIER 	{$$ = CG_OUT;}
	;

%%

