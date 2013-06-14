%{
#include "context_link_glapi.h"
#include "context.h"

int context_link_lex(void);
void context_link_error(char *s);

programObject currentProgram;
unsigned int shaderType;
symbol t_symbol;
%}

%union {
	int 	ival;
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

semantic: SEMT IDENTIFIER

link_info: VAR TYPE IDENTIFIER ':' io_type ':' complex_id ':' INTEGER ':' INTEGER {
			/* printf("name: %s ",$3); */
			t_symbol.symbol();
			
			t_symbol.name = $3;
			t_symbol.declareType = $2;

			if (strcmp($7,"HPOS") == 0) {
				t_symbol.ioType = CG_OUT_POSITION;
				t_symbol.idx = 0;
			}
			else if (strncmp($7,"ATTR",4) == 0) {
				if ($5 == CG_IN)
					t_symbol.ioType = CG_IN_ATTR;
				else
					t_symbol.ioType = CG_OUT_ATTR;
					
				t_symbol.idx = (unsigned int)$7[4] - 48;
			}
			else if (strncmp($7,"texunit",7) == 0) {
				t_symbol.ioType = CG_IN_UNIFORM_TEXTURE;
			}
			else if (strncmp($7,"COL",3) == 0) {
				t_symbol.ioType = CG_OUT_COLOR;
				t_symbol.idx = 0;
			}
			else if ($7[0] == 'c') {
				t_symbol.ioType = CG_IN_UNIFORM;
				t_symbol.idx = 0;
			}

			t_symbol.print();

			if (shaderType == 0)
				currentProgram.symTableVS[t_symbol.name] = t_symbol;
			else
				currentProgram.symTableFS[t_symbol.name] = t_symbol;
		}
	;

complex_id
	:	IDENTIFIER					{strcpy($$,$1);}
	|	IDENTIFIER '[' INTEGER ']'	{strcpy($$,$1);}
	|	IDENTIFIER '[' INTEGER ']' ',' INTEGER	{strcpy($$,$1); t_symbol.element = $6;};
	|	IDENTIFIER INTEGER	{strcpy($$,$1); t_symbol.idx = $2;}
	;

io_type
	:	/* empty */					{$$ = 0;}
	|	'$' VIN '.' IDENTIFIER 		{$$ = CG_IN;}
	|	'$' VOUT '.' IDENTIFIER 	{$$ = CG_OUT;}
	;

%%

