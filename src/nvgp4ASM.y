%{
#include "context_link_def.h"
#include "context.h"
#include "GPU/gpu_config.h"

int nvgp4ASM_lex(void);
void nvgp4ASM_error(char *s);
void nvgp4ASM_str_in(const char *s);

instruction t_inst;
operand t_operand;
std::vector<operand> operandPool;
std::vector<instruction> instructionPool;

extern programObject t_program;
extern unsigned int shaderType;
%}

%union {
	int		ival;
	float	fval;
	char	sval[30];
}

%token TEXTURE VERTEX FRAGMENT RESULT PROF
%token ATTRIB POSITION RESULT_COLOR0
%token <ival> SHADERTYPE
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

%type <ival> opModifierItem
%type <sval> component xyzwComponent rgbaComponent swizzleSuffix

%type <fval> constantScalar
%type <ival> texImageUnit

%type <sval> optSign
%%

input
	:	line input
	|	/* empty */
	;

line:	profile
	|	instruction ';' {
			if (shaderType == 0)
				t_program.VSinstructionPool.push_back(t_inst);
			else
				t_program.FSinstructionPool.push_back(t_inst);
				
			t_inst.init();
			t_operand.init();
			operandPool.clear();
		};
	|	instLabel ':'
/*	|	namingStatement ';'*/
	;
	
profile: PROF SHADERTYPE {shaderType = $2;}

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
		t_inst.op = $1;
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
	};

SCALARop_instruction: SCALAROP opModifiers instResult ',' instOperand {
		t_inst.op = $1;
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
	};

BINSCop_instruction: BINSCOP opModifiers instResult ',' instOperand ',' instOperand {
		t_inst.op = $1;
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
		t_inst.src1 = operandPool[2];
	};

VECSCAop_instruction: VECSCAOP opModifiers instResult ',' instOperand ',' instOperand {
		t_inst.op = $1;
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
		t_inst.src1 = operandPool[2];
	};

BINop_instruction: BINOP opModifiers instResult ',' instOperand ',' instOperand {
		t_inst.op = $1;
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
		t_inst.src1 = operandPool[2];
	};

TRIop_instruction: TRIOP opModifiers instResult ',' instOperand ',' instOperand ',' instOperand {
		t_inst.op = $1;
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
		t_inst.src1 = operandPool[2];
		t_inst.src2 = operandPool[3];
	};

SWZop_instruction: SWZOP opModifiers instResult ',' instOperand ',' extendedSwizzle {
		t_inst.op = $1;
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
	};

TEXop_instruction: TEXOP opModifiers instResult ',' instOperand ',' texAccess {
		t_inst.op = $1;
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
		t_inst.src1 = operandPool[2];
	};

TXDop_instruction: TXDOP opModifiers instResult ',' instOperand ',' instOperand ',' instOperand ',' texAccess

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

opModifierItem: '.' OPMODIFIER	{t_inst.opModifiers.push_back($2);}

texAccess: texImageUnit ',' TEXTARGET {
		t_operand.id = $1;
		t_operand.type = INST_TEXTURE;
		t_operand.val[0] = $3;
		operandPool.push_back(t_operand);
	};

texImageUnit: TEXTURE '[' INTEGER ']' {$$ = $3;}

optBranchCond
	:	/* empty */
	|	ccMask
	;

instOperand
	:	instOperandAbs	{operandPool.push_back(t_operand);}
	|	instOperandBase	{operandPool.push_back(t_operand);}
	;

instOperandAbs: optSign '|' instOperandBase '|' {t_operand.abs = true;}

instOperandBase
	:	optSign primitive '.' ATTRIB '[' INTEGER ']' swizzleSuffix {
			if (shaderType == 0) // Vertex shader {
				t_operand.id = $6;
			else // Fragment shader
				t_operand.id = $6 + 1;
			t_operand.type = INST_ATTRIB;
			strncpy(t_operand.modifier, $8, 5);
			if ($1[0] == '-')
				t_operand.inverse = true;
		};
	|	optSign 'c' '[' INTEGER ']' swizzleSuffix {
			if (shaderType == 0) { // Vertex shader {
				int id  = $4 - t_program.asmVSIdx[$4].idx;
				t_operand.id = t_program.srcUniform[t_program.asmVSIdx[$4].name].idx + id;
			}
			else {// Fragment shader
				int id  = $4 - t_program.asmFSIdx[$4].idx;
				t_operand.id = t_program.srcUniform[t_program.asmFSIdx[$4].name].idx + id;
			}
			t_operand.type = INST_UNIFORM;
			strncpy(t_operand.modifier, $6, 5);
			if ($1[0] == '-')
				t_operand.inverse = true;
		};
	|	optSign REG swizzleSuffix {
			t_operand.id = $2;
			t_operand.type = INST_REG;
			strncpy(t_operand.modifier, $3, 5);
			if ($1[0] == '-')
				t_operand.inverse = true;
		};
	|	optSign constantVector swizzleSuffix {
			t_operand.type = INST_CONSTANT;
			strncpy(t_operand.modifier, $3, 5);
			if ($1[0] == '-')
				t_operand.inverse = true;
		};
	;

primitive
	:	FRAGMENT
	|	VERTEX
	;

instResult
	:	instResultCC
	|	instResultBase	{operandPool.push_back(t_operand);}
	;

instResultCC: instResultBase ccMask

instResultBase
	:	REG swizzleSuffix {
			t_operand.id = $1;
			t_operand.type = INST_REG;
			strncpy(t_operand.modifier, $2, 5);
		};
	|	RESULT '.' POSITION swizzleSuffix {
			t_operand.id = 0;
			t_operand.type = INST_ATTRIB;
			strncpy(t_operand.modifier, $4, 5);
		};
	|	RESULT '.' ATTRIB '[' INTEGER ']' swizzleSuffix {
			t_operand.id = $5 + 1;
			t_operand.type = INST_ATTRIB;
			strncpy(t_operand.modifier, $7, 5);
		};
	|	RESULT_COLOR0 swizzleSuffix {
			t_operand.type = INST_COLOR;
			strncpy(t_operand.modifier, $2, 5);
		};
	;

ccMask: '(' ccTest ')'

ccTest: CCMASKRULE swizzleSuffix

constantVector: '{' constantVectorList '}'

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
	:	/* empty */			{strcpy($$, "xyzw");}
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
	:	/* empty */	{$$[0] = '\0';};
	|	'-'			{$$[0] = '-'; $$[1] = '\0';};
	|	'+'			{$$[0] = '+'; $$[1] = '\0';};

instTarget: IDENTIFIER

instLabel: IDENTIFIER

%%

