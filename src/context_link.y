%{
#include <string>
#include <cstdio>
#include "context_link_def.h"
#include "context.h"

int context_link_lex(void);
void context_link_error(char *s);

programObject t_program;
unsigned int shaderType;
unsigned int element;
unsigned int idx;
instruction t_inst;
operand t_operand;
std::vector<operand> operandPool;
%}

%union {
	int		ival;
	float	fval;
	char	sval[30];
}

%token PROG SEMT VAR VIN VOUT
%token TEXTURE VERTEX FRAGMENT RESULT
%token ATTRIB POSITION RESULT_COLOR0
%token <sval> TYPE
%token <sval> IDENTIFIER
%token <ival> INTEGER
%token <fval> FLOAT

%token <ival> VECTOROP SCALAROP BINSCOP VECSCAOP
%token <ival> BINOP TRIOP SWZOP TEXOP TXDOP
%token <ival> BRAOP FLOWCCOP IFOP REPOP ENDFLOWOP

%token <ival> OPMODIFIER
%token <ival> TEXTARGET
%token <ival> CCMASKRULE
%token <sval> XYZW_SWIZZLE RGBA_SWIZZLE
%token <ival> REG


%type <ival> io_type
%type <sval> complex_id

%type <ival> opModifierItem
%type <sval> component xyzwComponent rgbaComponent swizzleSuffix

%type <fval> constantScalar
%%

input
	:	line input
	|	/* empty */
	;

line:	program
	|	semantic
	|	link_info
/*	|	namingStatement ';'*/
	|	instruction ';'
	|	instLabel ':'
	;


program: PROG IDENTIFIER

semantic
	: 	SEMT IDENTIFIER
	;

link_info: VAR TYPE IDENTIFIER ':' io_type ':' complex_id ':' INTEGER ':' INTEGER {
		/* printf("name: %s ",$3); */
		symbol t_symbol;
		
		t_symbol.name = $3;
		t_symbol.declareType = $2;
		t_symbol.offset = 0;

		if (strcmp($7,"HPOS") == 0) {
			t_symbol.idx = 0;
			t_symbol.element = element;
			//t_program.symbolVSout[t_symbol.name] = t_symbol;
		}
		else if (strncmp($7,"ATTR",4) == 0) {
			t_symbol.idx = (unsigned int)$7[4] - 48;
			t_symbol.element = element;
			if (shaderType == 0) {
				if ($5 == CG_IN)
					t_program.symbolVSin[t_symbol.name]=t_symbol;
				else
					t_program.symbolVSout[t_symbol.name]=t_symbol;
			}
			else {
				if ($5 == CG_IN)
					t_program.symbolFSin[t_symbol.name]=t_symbol;
				else
					t_program.symbolFSout[t_symbol.name]=t_symbol;
			}
		}
		else if (strncmp($7,"texunit",7) == 0) {
			t_symbol.idx = idx + 0x10;
			t_symbol.element = element;
			if (t_program.symbolUniform.find(t_symbol.name) == t_program.symbolUniform.end())
				t_program.symbolUniform[t_symbol.name] = t_symbol;
			else {
				printf("%s \n",$3);
				exit(1);
			}
		}
		//@todo: Need to handle the multi output situation
		else if (strncmp($7,"COL",3) == 0) {
			t_symbol.idx = 0;
			t_symbol.element = element;
			//t_program.symbolFSout[t_symbol.name] = t_symbol;
		}
		else if ($7[0] == 'c') {
			t_symbol.idx = idx;
			t_symbol.element = element;
			if (t_program.symbolUniform.find(t_symbol.name) == t_program.symbolUniform.end())
				t_program.symbolUniform[t_symbol.name] = t_symbol;
			else {
				if (t_program.symbolUniform[t_symbol.name].declareType != t_symbol.declareType) {
					printf("%s \n",$3);
					exit(1);
				}
			}
		}

		//t_symbol.print();
	};

complex_id
	:	IDENTIFIER					{strcpy($$,$1); element = 1;}
	|	IDENTIFIER '[' INTEGER ']'	{strcpy($$,$1); idx = $3; element = 1;}
	|	IDENTIFIER '[' INTEGER ']' ',' INTEGER	{strcpy($$,$1); element = $6;}
	|	IDENTIFIER INTEGER	{strcpy($$,$1); idx = $2; element = 1;}
	;

io_type
	:	/* empty */					{$$ = 0;}
	|	'$' VIN '.' IDENTIFIER		{$$ = CG_IN;}
	|	'$' VOUT '.' IDENTIFIER 	{$$ = CG_OUT;}
	;

instruction
	:	ALUInstruction
	|	TexInstruction
	|	FlowInstruction
	;
	
ALUInstruction
	:	VECTORop_instruction
	|	SCALARop_instruction
	|	BINSCop_instruction
	|	BINop_instruction
	|	VECSCAop_instruction
	|	TRIop_instruction
	|	SWZop_instruction
	;
	
TexInstruction
	:	TEXop_instruction
	|	TXDop_instruction
	;
	
FlowInstruction
	:	BRAop_instruction
	|	FLOWCCop_instruction
	|	IFop_instruction
	|	REPop_instruction
	|	ENDFLOWop_instruction
	;
	
VECTORop_instruction: VECTOROP opModifiers instResult ',' instOperand {
		t_inst.op = VECTOROP;
	};

SCALARop_instruction: SCALAROP opModifiers instResult ',' instOperand

BINSCop_instruction: BINSCOP opModifiers instResult ',' instOperand ',' instOperand

VECSCAop_instruction: VECSCAOP opModifiers instResult ',' instOperand ',' instOperand

BINop_instruction: BINOP opModifiers instResult ',' instOperand ',' instOperand

TRIop_instruction: TRIOP opModifiers instResult ',' instOperand ',' instOperand ',' instOperand

SWZop_instruction: SWZOP opModifiers instResult ',' instOperand ',' extendedSwizzle

TEXop_instruction: TEXOP opModifiers instResult ',' instOperand ',' texAccess

TXDop_instruction : TXDOP opModifiers instResult ',' instOperand ',' instOperand ',' instOperand ',' texAccess

BRAop_instruction: BRAOP opModifiers instTarget optBranchCond

FLOWCCop_instruction: FLOWCCOP opModifiers optBranchCond

IFop_instruction: IFOP opModifiers ccTest

REPop_instruction
	:	REPOP opModifiers instOperand
	|	REPOP opModifiers
	;

ENDFLOWop_instruction: ENDFLOWOP opModifiers

opModifiers
	: 	/* empty */
	|	opModifierItem opModifiers
	;

opModifierItem: '.' OPMODIFIER	{t_inst.opModifier.push_back($2);}

texAccess: texImageUnit ',' TEXTARGET

texImageUnit: TEXTURE '[' INTEGER ']'

optBranchCond
	:	/* empty */
	|	ccMask
	;

instOperand
	:	instOperandAbs
	|	instOperandBase
	;

instOperandAbs: optSign '|' instOperandBase '|'

instOperandBase
	:	optSign primitive '.' ATTRIB '[' INTEGER ']' swizzleSuffix
	|	optSign 'c' '[' INTEGER ']' swizzleSuffix
	|	optSign REG swizzleSuffix
	|	optSign constantVector swizzleSuffix
	;

primitive
	:	FRAGMENT
	|	VERTEX
	;

instResult
	:	instResultCC
	|	instResultBase
	;

instResultCC: instResultBase ccMask

instResultBase
	:	REG swizzleSuffix
	|	RESULT '.' POSITION swizzleSuffix
	|	RESULT '.' ATTRIB '[' INTEGER ']' swizzleSuffix
	|	RESULT_COLOR0 swizzleSuffix
	;
						  
ccMask: '(' ccTest ')'

ccTest: CCMASKRULE swizzleSuffix

constantVector: '{' constantVectorList '}' {t_operand.type = INST_CONSTANT;}

constantVectorList
	:	constantScalar	{
			t_operand.val[0] = t_operand.val[1] = 
			t_operand.val[2] = t_operand.val[3] = $1;
		};
	|	constantScalar ',' constantScalar {
			t_operand.val[0] = $1;
			t_operand.val[1] = t_operand.val[2] = t_operand.val[3] = $3;
		};
	|	constantScalar ',' constantScalar ',' constantScalar {
			t_operand.val[0] = $1;
			t_operand.val[1] = $3;
			t_operand.val[2] = t_operand.val[3] = $5;
		};
	|	constantScalar ',' constantScalar ',' constantScalar ',' constantScalar {
			t_operand.val[0] = $1;
			t_operand.val[1] = $3;
			t_operand.val[2] = $5;
			t_operand.val[3] = $7;
		};
	;
	
constantScalar
	:	INTEGER	{$$ = $1;}
	|	FLOAT	{$$ = $1;}
	;

swizzleSuffix
	:	/* empty */			{$$[0] = '\0';}
	|	'.' component		{strcpy($$, $2);}
	|	'.' XYZW_SWIZZLE	{strcpy($$, $2);}
	|	'.' RGBA_SWIZZLE	{strcpy($$, $2);}
	;

extendedSwizzle: extSwizComp ',' extSwizComp ',' extSwizComp ',' extSwizComp

extSwizComp 
	:	optSign xyzwExtSwizSel
	|	optSign rgbaExtSwizSel
	;
	
xyzwExtSwizSel
	:	INTEGER
	|	xyzwComponent
	;

rgbaExtSwizSel: rgbaComponent

component
	:	xyzwComponent {strcpy($$, $1);}
	|	rgbaComponent {strcpy($$, $1);}
	;

xyzwComponent
	:	'x'	{$$[0] = 'x'; $$[1] = '\0';};
	|	'y' {$$[0] = 'y'; $$[1] = '\0';};
	|	'z' {$$[0] = 'z'; $$[1] = '\0';};
	|	'w' {$$[0] = 'w'; $$[1] = '\0';};
	;

rgbaComponent
	:	'r' {$$[0] = 'r'; $$[1] = '\0';};
	|	'g' {$$[0] = 'g'; $$[1] = '\0';};
	|	'b' {$$[0] = 'b'; $$[1] = '\0';};
	|	'a' {$$[0] = 'a'; $$[1] = '\0';};
	;
optSign
	:	/* empty */
	|	'-'
	|	'+'
	
instTarget: IDENTIFIER
	
instLabel: IDENTIFIER

%%

