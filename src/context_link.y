%{
#include <string>
#include "context_link_glapi.h"
#include "context.h"


int context_link_lex(void);
void context_link_error(char *s);

programObject t_program;
unsigned int shaderType;
unsigned int element;
unsigned int idx;
%}

%union {
	int		ival;
	char	sval[30];
}

%token PROFILE
%token PROG
%token SEMT
%token VAR
%token <sval> TYPE
%token VIN
%token VOUT
%token <sval> IDENTIFIER
%token <ival> INTEGER

%type <ival> io_type
%type <sval> complex_id

%%

input:	/* empty */
	|	input line
	;

line:	profile
	|	program
	|	semantic
	|	link_info
	;


profile: PROFILE IDENTIFIER

program: PROG IDENTIFIER

semantic
	: 	SEMT IDENTIFIER
	;

link_info: VAR TYPE IDENTIFIER ':' io_type ':' complex_id ':' INTEGER ':' INTEGER {
			/* printf("name: %s ",$3); */
			symbol t_symbol;

			t_symbol.name = $3;
			t_symbol.declareType = $2;

			if (strcmp($7,"HPOS") == 0) {
				t_symbol.ioType = CG_OUT_POSITION;
				t_symbol.idx = 0;
				t_symbol.element = element;
			}
			else if (strncmp($7,"ATTR",4) == 0) {
				if ($5 == CG_IN)
					t_symbol.ioType = CG_IN_ATTR;
				else
					t_symbol.ioType = CG_OUT_ATTR;

				t_symbol.idx = (unsigned int)$7[4] - 48;
				t_symbol.element = element;
			}
			else if (strncmp($7,"texunit",7) == 0) {
				t_symbol.ioType = CG_IN_UNIFORM_TEXTURE;
				t_symbol.idx = idx;
				t_symbol.element = element;
			}
			//Need to care the multi color situation
			else if (strncmp($7,"COL",3) == 0) {
				t_symbol.ioType = CG_OUT_COLOR;
				t_symbol.idx = 0;
				t_symbol.element = element;
			}
			else if ($7[0] == 'c') {
				t_symbol.ioType = CG_IN_UNIFORM;
				t_symbol.idx = idx;
				t_symbol.element = element;
			}

			t_symbol.print();

			if (shaderType == 0)
				t_program.symTableVS[t_symbol.name] = t_symbol;
			else
				t_program.symTableFS[t_symbol.name] = t_symbol;
		}
	;

complex_id
	:	IDENTIFIER					{strcpy($$,$1); element = 1;}
	|	IDENTIFIER '[' INTEGER ']'	{strcpy($$,$1); idx = $3; element = 1;}
	|	IDENTIFIER '[' INTEGER ']' ',' INTEGER	{strcpy($$,$1); element = $6;}
	|	IDENTIFIER INTEGER	{strcpy($$,$1); idx = $2; element = 1;}
	;

io_type
	:	/* empty */					{$$ = 0;}
	|	'$' VIN '.' IDENTIFIER 		{$$ = CG_IN;}
	|	'$' VOUT '.' IDENTIFIER 	{$$ = CG_OUT;}
	;

%%

