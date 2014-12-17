/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         nvgp4ASM_parse
#define yylex           nvgp4ASM_lex
#define yyerror         nvgp4ASM_error
#define yylval          nvgp4ASM_lval
#define yychar          nvgp4ASM_char
#define yydebug         nvgp4ASM_debug
#define yynerrs         nvgp4ASM_nerrs


/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 17 "nvgp4ASM.y"

#include "context.h"

#include "GPU/instruction_def.h"
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


/* Line 189 of yacc.c  */
#line 100 "nvgp4ASM.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TEXTURE = 258,
     VERTEX = 259,
     FRAGMENT = 260,
     RESULT = 261,
     PROF = 262,
     END = 263,
     ATTRIB = 264,
     POSITION = 265,
     RESULT_COLOR0 = 266,
     SHADERTYPE = 267,
     INTERP_MODE = 268,
     IDENTIFIER = 269,
     INTEGER = 270,
     FLOAT = 271,
     VECTOROP = 272,
     SCALAROP = 273,
     BINSCOP = 274,
     VECSCAOP = 275,
     BINOP = 276,
     TRIOP = 277,
     SWZOP = 278,
     TEXOP = 279,
     TXDOP = 280,
     BRAOP = 281,
     FLOWCCOP = 282,
     IFOP = 283,
     REPOP = 284,
     ENDFLOWOP = 285,
     KILOP = 286,
     DERIVEOP = 287,
     OPMODIFIER = 288,
     TEXTARGET = 289,
     CCMASKRULE = 290,
     XYZW_SWIZZLE = 291,
     RGBA_SWIZZLE = 292,
     REG = 293
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 36 "nvgp4ASM.y"

	int		ival;
	float	fval;
	char	sval[30];



/* Line 214 of yacc.c  */
#line 182 "nvgp4ASM.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 194 "nvgp4ASM.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  66
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   210

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNRULES -- Number of states.  */
#define YYNSTATES  243

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      50,    51,     2,    61,    47,    60,    42,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    40,    39,
       2,    46,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    43,     2,    44,     2,     2,     2,    59,    58,    49,
       2,     2,     2,    57,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    56,     2,     2,     2,     2,    55,
      52,    53,    54,    41,    48,    45,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,     9,    12,    15,    18,    20,
      23,    37,    38,    41,    47,    49,    51,    53,    55,    57,
      59,    61,    63,    65,    67,    69,    71,    73,    75,    77,
      79,    81,    83,    85,    87,    93,    99,   107,   115,   123,
     133,   141,   149,   161,   166,   170,   174,   178,   181,   184,
     188,   194,   195,   198,   201,   205,   210,   211,   213,   215,
     217,   222,   231,   238,   242,   246,   248,   250,   252,   254,
     257,   260,   265,   273,   276,   280,   283,   287,   289,   293,
     299,   307,   309,   311,   312,   315,   318,   321,   329,   332,
     335,   337,   339,   341,   343,   345,   347,   349,   351,   353,
     355,   357,   359,   361,   362,   364,   366,   368
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      63,     0,    -1,    64,    63,    -1,    -1,    65,    -1,    66,
      39,    -1,    69,    39,    -1,   117,    40,    -1,     8,    -1,
       7,    12,    -1,    67,    68,    41,    98,    42,     9,    43,
      15,    42,    42,    15,    44,    45,    -1,    -1,    67,    13,
      -1,     9,    14,    43,    44,    46,    -1,    70,    -1,    71,
      -1,    72,    -1,    73,    -1,    74,    -1,    75,    -1,    76,
      -1,    78,    -1,    77,    -1,    79,    -1,    80,    -1,    81,
      -1,    82,    -1,    83,    -1,    84,    -1,    85,    -1,    86,
      -1,    87,    -1,    88,    -1,    89,    -1,    17,    90,    99,
      47,    95,    -1,    18,    90,    99,    47,    95,    -1,    19,
      90,    99,    47,    95,    47,    95,    -1,    20,    90,    99,
      47,    95,    47,    95,    -1,    21,    90,    99,    47,    95,
      47,    95,    -1,    22,    90,    99,    47,    95,    47,    95,
      47,    95,    -1,    23,    90,    99,    47,    95,    47,   108,
      -1,    24,    90,    99,    47,    95,    47,    92,    -1,    25,
      90,    99,    47,    95,    47,    95,    47,    95,    47,    92,
      -1,    26,    90,   116,    94,    -1,    27,    90,    94,    -1,
      28,    90,   103,    -1,    29,    90,    95,    -1,    29,    90,
      -1,    30,    90,    -1,    31,    90,   103,    -1,    32,    90,
      99,    47,    95,    -1,    -1,    91,    90,    -1,    42,    33,
      -1,    93,    47,    34,    -1,     3,    43,    15,    44,    -1,
      -1,   102,    -1,    96,    -1,    97,    -1,   115,    48,    97,
      48,    -1,   115,    98,    42,     9,    43,    15,    44,   107,
      -1,   115,    49,    43,    15,    44,   107,    -1,   115,    38,
     107,    -1,   115,   104,   107,    -1,     5,    -1,     4,    -1,
     100,    -1,   101,    -1,   101,   102,    -1,    38,   107,    -1,
       6,    42,    10,   107,    -1,     6,    42,     9,    43,    15,
      44,   107,    -1,    11,   107,    -1,    50,   103,    51,    -1,
      35,   107,    -1,    41,   105,    45,    -1,   106,    -1,   106,
      47,   106,    -1,   106,    47,   106,    47,   106,    -1,   106,
      47,   106,    47,   106,    47,   106,    -1,    15,    -1,    16,
      -1,    -1,    42,   112,    -1,    42,    36,    -1,    42,    37,
      -1,   109,    47,   109,    47,   109,    47,   109,    -1,   115,
     110,    -1,   115,   111,    -1,    15,    -1,   113,    -1,   114,
      -1,   113,    -1,   114,    -1,    52,    -1,    53,    -1,    54,
      -1,    55,    -1,    56,    -1,    57,    -1,    58,    -1,    59,
      -1,    -1,    60,    -1,    61,    -1,    14,    -1,    14,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    71,    71,    72,    75,    76,    77,    87,    88,    91,
      94,   101,   102,   105,   108,   109,   110,   111,   115,   116,
     117,   118,   119,   120,   121,   125,   126,   130,   131,   132,
     133,   134,   138,   139,   142,   148,   154,   161,   168,   175,
     183,   189,   195,   203,   205,   209,   277,   281,   286,   291,
     363,   369,   371,   374,   376,   389,   391,   393,   397,   398,
     401,   404,   414,   429,   436,   445,   446,   450,   451,   454,
     457,   462,   467,   472,   478,   480,   485,   488,   492,   496,
     501,   510,   511,   515,   516,   517,   539,   563,   566,   567,
     571,   572,   575,   578,   579,   583,   584,   585,   586,   590,
     591,   592,   593,   597,   598,   599,   601,   603
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TEXTURE", "VERTEX", "FRAGMENT",
  "RESULT", "PROF", "END", "ATTRIB", "POSITION", "RESULT_COLOR0",
  "SHADERTYPE", "INTERP_MODE", "IDENTIFIER", "INTEGER", "FLOAT",
  "VECTOROP", "SCALAROP", "BINSCOP", "VECSCAOP", "BINOP", "TRIOP", "SWZOP",
  "TEXOP", "TXDOP", "BRAOP", "FLOWCCOP", "IFOP", "REPOP", "ENDFLOWOP",
  "KILOP", "DERIVEOP", "OPMODIFIER", "TEXTARGET", "CCMASKRULE",
  "XYZW_SWIZZLE", "RGBA_SWIZZLE", "REG", "';'", "':'", "'{'", "'.'", "'['",
  "']'", "'}'", "'='", "','", "'|'", "'c'", "'('", "')'", "'x'", "'y'",
  "'z'", "'w'", "'r'", "'g'", "'b'", "'a'", "'-'", "'+'", "$accept",
  "input", "line", "profile", "namingStatement", "interpModifier",
  "ATTRIB_statement", "instruction", "ALUInstruction", "TexInstruction",
  "FlowInstruction", "SpecialInstrution", "VECTORop_instruction",
  "SCALARop_instruction", "BINSCop_instruction", "VECSCAop_instruction",
  "BINop_instruction", "TRIop_instruction", "SWZop_instruction",
  "TEXop_instruction", "TXDop_instruction", "BRAop_instruction",
  "FLOWCCop_instruction", "IFop_instruction", "REPop_instruction",
  "ENDFLOWop_instruction", "KILop_instruction", "DERIVEop_instruction",
  "opModifiers", "opModifierItem", "texAccess", "texImageUnit",
  "optBranchCond", "instOperand", "instOperandAbs", "instOperandBase",
  "primitive", "instResult", "instResultCC", "instResultBase", "ccMask",
  "ccTest", "constantVector", "constantVectorList", "constantScalar",
  "swizzleSuffix", "extendedSwizzle", "extSwizComp", "xyzwExtSwizSel",
  "rgbaExtSwizSel", "component", "xyzwComponent", "rgbaComponent",
  "optSign", "instTarget", "instLabel", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,    59,
      58,   123,    46,    91,    93,   125,    61,    44,   124,    99,
      40,    41,   120,   121,   122,   119,   114,   103,    98,    97,
      45,    43
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    62,    63,    63,    64,    64,    64,    64,    64,    65,
      66,    67,    67,    68,    69,    69,    69,    69,    70,    70,
      70,    70,    70,    70,    70,    71,    71,    72,    72,    72,
      72,    72,    73,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    86,    87,    88,
      89,    90,    90,    91,    92,    93,    94,    94,    95,    95,
      96,    97,    97,    97,    97,    98,    98,    99,    99,   100,
     101,   101,   101,   101,   102,   103,   104,   105,   105,   105,
     105,   106,   106,   107,   107,   107,   107,   108,   109,   109,
     110,   110,   111,   112,   112,   113,   113,   113,   113,   114,
     114,   114,   114,   115,   115,   115,   116,   117
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     1,     2,     2,     2,     1,     2,
      13,     0,     2,     5,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     5,     7,     7,     7,     9,
       7,     7,    11,     4,     3,     3,     3,     2,     2,     3,
       5,     0,     2,     2,     3,     4,     0,     1,     1,     1,
       4,     8,     6,     3,     3,     1,     1,     1,     1,     2,
       2,     4,     7,     2,     3,     2,     3,     1,     3,     5,
       7,     1,     1,     0,     2,     2,     2,     7,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      11,     0,     8,   107,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
       0,    11,     4,     0,     0,     0,    14,    15,    16,    17,
      18,    19,    20,    22,    21,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,     0,     9,     0,     0,
      51,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      56,     0,   103,    48,     0,     0,     1,     2,     5,     0,
      12,     0,     6,     7,    53,     0,    83,    83,     0,    67,
      68,    52,     0,     0,     0,     0,     0,     0,     0,     0,
     106,    56,     0,    44,    57,    83,    45,   104,   105,    46,
      58,    59,     0,    49,     0,     0,     0,     0,     0,    73,
      70,   103,    69,   103,   103,   103,   103,   103,   103,   103,
     103,    43,     0,    75,    66,    65,    83,     0,   103,     0,
       0,    83,   103,     0,     0,     0,    83,    85,    86,    95,
      96,    97,    98,    99,   100,   101,   102,    84,    93,    94,
      34,    35,     0,     0,     0,     0,     0,     0,     0,    74,
      63,    81,    82,     0,    77,     0,     0,     0,     0,    64,
      50,     0,     0,     0,    71,   103,   103,   103,   103,   103,
       0,   103,    76,     0,    60,     0,     0,    13,     0,     0,
      36,    37,    38,     0,    40,     0,     0,     0,    41,     0,
       0,    78,    83,     0,     0,    83,   103,   103,    90,    88,
      89,    91,    92,     0,     0,   103,     0,    62,     0,     0,
      72,    39,     0,     0,    54,     0,    79,    83,     0,   103,
      55,     0,     0,    61,     0,     0,    42,    80,     0,   103,
       0,    87,    10
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    20,    21,    22,    23,    24,    71,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    49,    50,
     198,   199,    93,    99,   100,   101,   130,    78,    79,    80,
      94,    96,   131,   163,   164,   109,   194,   195,   209,   210,
     147,   148,   149,   102,    91,    46
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -172
static const yytype_int16 yypact[] =
{
     113,    -9,  -172,  -172,   -25,   -25,   -25,   -25,   -25,   -25,
     -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,
      22,   113,  -172,   -15,    33,     1,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,    11,  -172,    27,    10,
     -25,    10,    10,    10,    10,    10,    10,    10,    10,    48,
      21,    30,    16,  -172,    30,    10,  -172,  -172,  -172,    84,
    -172,    60,  -172,  -172,  -172,    65,    66,    66,    62,  -172,
      21,  -172,    63,    64,    67,    68,    71,    72,    75,    76,
    -172,    21,    30,  -172,  -172,    66,  -172,  -172,  -172,  -172,
    -172,  -172,     9,  -172,    77,    73,    70,    69,   110,  -172,
    -172,    39,  -172,    39,    39,    39,    39,    39,    39,    39,
      39,  -172,    78,  -172,  -172,  -172,    66,    89,    39,    74,
     106,    66,    39,    82,   107,   108,    66,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,   105,   109,   111,   112,   114,   123,   124,  -172,
    -172,  -172,  -172,   115,   125,   126,    15,   138,   145,  -172,
    -172,   127,   146,   142,  -172,    39,    39,    39,    39,    39,
     172,    39,  -172,    89,  -172,   132,   134,  -172,   135,   136,
    -172,  -172,  -172,   137,  -172,   139,    29,   140,  -172,   141,
     143,   144,    66,   164,   166,    66,    39,    39,  -172,  -172,
    -172,  -172,  -172,   167,   151,    39,    89,  -172,   148,   147,
    -172,  -172,   149,   150,  -172,   152,   153,    66,   155,    39,
    -172,   172,    89,  -172,   178,   154,  -172,  -172,   158,    39,
     159,  -172,  -172
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -172,   174,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,    20,  -172,
     -44,  -172,   116,  -109,  -172,    80,    92,    38,  -172,  -172,
     129,   -49,  -172,  -172,  -171,   -77,  -172,  -166,  -172,  -172,
    -172,     7,    14,  -127,  -172,  -172
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -48
static const yytype_int16 yytable[] =
{
     110,   166,   150,    47,   151,   152,   153,   154,   155,   156,
     157,   158,   201,   124,   125,   103,    75,    48,   123,   124,
     125,    76,    66,   170,    68,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      72,   222,    69,   122,   208,   226,    70,   126,    77,   160,
     127,    73,   196,   126,   169,   -47,   127,   128,   129,   174,
      74,   237,    90,   235,   129,    95,   190,   191,   192,   193,
      81,    92,   200,   241,   124,   125,    97,    98,   135,   136,
     196,   139,   140,   141,   142,   143,   144,   145,   146,    82,
      83,    84,    85,    86,    87,    88,    89,   221,   105,    97,
      98,   106,   196,   104,   161,   162,   225,   107,   108,   111,
     113,   114,   196,    -3,   115,   116,   133,   167,   117,   118,
       1,     2,   119,   120,   132,   217,   171,     3,   220,   159,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,   137,   138,   168,   172,
     233,   173,   175,   185,   186,   188,   176,   189,   177,   178,
     182,   179,   139,   140,   141,   142,   143,   144,   145,   146,
     180,   181,   183,   187,   184,   197,   202,   203,   204,   218,
     205,   219,   223,   213,   206,   224,   207,   236,   214,   228,
     215,   216,   227,   238,   230,    67,   229,   234,   134,   231,
     232,   239,   240,   211,   242,     0,     0,   121,   165,   112,
     212
};

static const yytype_int16 yycheck[] =
{
      77,   128,   111,    12,   113,   114,   115,   116,   117,   118,
     119,   120,   183,     4,     5,    64,     6,    42,    95,     4,
       5,    11,     0,   132,    39,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      39,   207,     9,    92,    15,   216,    13,    38,    38,   126,
      41,    40,   179,    38,   131,    39,    41,    48,    49,   136,
      33,   232,    14,   229,    49,    35,   175,   176,   177,   178,
      50,    50,   181,   239,     4,     5,    60,    61,     9,    10,
     207,    52,    53,    54,    55,    56,    57,    58,    59,    51,
      52,    53,    54,    55,    56,    57,    58,   206,    14,    60,
      61,    41,   229,    65,    15,    16,   215,    42,    42,    47,
      47,    47,   239,     0,    47,    47,    43,    43,    47,    47,
       7,     8,    47,    47,    47,   202,    44,    14,   205,    51,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    36,    37,    42,    42,
     227,    43,    47,    15,     9,     9,    47,    15,    47,    47,
      45,    47,    52,    53,    54,    55,    56,    57,    58,    59,
      47,    47,    47,    46,    48,     3,    44,    43,    43,    15,
      44,    15,    15,    43,    47,    34,    47,   231,    47,    42,
      47,    47,    44,    15,    44,    21,    47,    42,   106,    47,
      47,    47,    44,   196,    45,    -1,    -1,    91,   128,    80,
     196
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,    14,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      63,    64,    65,    66,    67,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,   117,    12,    42,    90,
      91,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,     0,    63,    39,     9,
      13,    68,    39,    40,    33,     6,    11,    38,    99,   100,
     101,    90,    99,    99,    99,    99,    99,    99,    99,    99,
      14,   116,    50,    94,   102,    35,   103,    60,    61,    95,
      96,    97,   115,   103,    99,    14,    41,    42,    42,   107,
     107,    47,   102,    47,    47,    47,    47,    47,    47,    47,
      47,    94,   103,   107,     4,     5,    38,    41,    48,    49,
      98,   104,    47,    43,    98,     9,    10,    36,    37,    52,
      53,    54,    55,    56,    57,    58,    59,   112,   113,   114,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    51,
     107,    15,    16,   105,   106,    97,   115,    43,    42,   107,
      95,    44,    42,    43,   107,    47,    47,    47,    47,    47,
      47,    47,    45,    47,    48,    15,     9,    46,     9,    15,
      95,    95,    95,    95,   108,   109,   115,     3,    92,    93,
      95,   106,    44,    43,    43,    44,    47,    47,    15,   110,
     111,   113,   114,    43,    47,    47,    47,   107,    15,    15,
     107,    95,   109,    15,    34,    95,   106,    44,    42,    47,
      44,    47,    47,   107,    42,   109,    92,   106,    15,    47,
      44,   109,    45
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 6:

/* Line 1464 of yacc.c  */
#line 77 "nvgp4ASM.y"
    {
			if (shaderType == 0)
				t_program.VSinstructionPool.push_back(t_inst);
			else
				t_program.FSinstructionPool.push_back(t_inst);
				
			t_inst.Init();
			t_operand.Init();
			operandPool.clear();
		;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 91 "nvgp4ASM.y"
    {shaderType = (yyvsp[(2) - (2)].ival);;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 94 "nvgp4ASM.y"
    {
			for (int i= (yyvsp[(8) - (13)].ival) + 1; i <= ((yyvsp[(11) - (13)].ival)+1); i++) {
				t_program.varyInterpMode[i] = (yyvsp[(1) - (13)].ival);
			}
		;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 101 "nvgp4ASM.y"
    {(yyval.ival) = 0;;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 102 "nvgp4ASM.y"
    {(yyval.ival) = (yyvsp[(1) - (2)].ival)|(yyvsp[(2) - (2)].ival);;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 142 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (5)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
	;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 148 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (5)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
	;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 154 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
		t_inst.src[1] = operandPool[2];
	;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 161 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
		t_inst.src[1] = operandPool[2];
	;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 168 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
		t_inst.src[1] = operandPool[2];
	;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 175 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (9)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
		t_inst.src[1] = operandPool[2];
		t_inst.src[2] = operandPool[3];
	;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 183 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
	;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 189 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
	;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 195 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (11)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
		t_inst.src[1] = operandPool[2];
		t_inst.src[2] = operandPool[3];
	;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 205 "nvgp4ASM.y"
    {
		
	;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 209 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (3)].ival);
		t_inst.src[0] = t_operand;
		t_inst.src[0].type = INST_CCREG;
		switch (t_operand.ccMask) {
		case CC_EQ:
		case CC_EQ0:
		case CC_GE:
		case CC_GE0:
		case CC_GT:
		case CC_GT0:
		case CC_LE:
		case CC_LE0:
		case CC_LT:
		case CC_LT0:
		case CC_NE:
		case CC_NE0:
		case CC_TR:
		case CC_TR0:
		case CC_FL:
		case CC_FL0:
		case CC_NAN:
		case CC_NAN0:
		case CC_LEG:
		case CC_LEG0:
		case CC_CF:
		case CC_CF0:
		case CC_NCF:
		case CC_NCF0:
		case CC_OF:
		case CC_OF0:
		case CC_NOF:
		case CC_NOF0:
		case CC_AB:
		case CC_AB0:
		case CC_BLE:
		case CC_BLE0:
		case CC_SF:
		case CC_SF0:
		case CC_NSF:
		case CC_NSF0:
			t_inst.src[0].id = 0;
			break;
				
		case CC_EQ1:
		case CC_GE1:
		case CC_GT1:
		case CC_LE1:
		case CC_LT1:
		case CC_NE1:
		case CC_TR1:
		case CC_FL1:
		case CC_NAN1:
		case CC_LEG1:
		case CC_CF1:
		case CC_NCF1:
		case CC_OF1:
		case CC_NOF1:
		case CC_AB1:
		case CC_BLE1:
		case CC_SF1:
		case CC_NSF1:
			t_inst.src[0].id = 1;
			break;
		}
	;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 277 "nvgp4ASM.y"
    {
			t_inst.op = (yyvsp[(1) - (3)].ival);
			t_inst.src[0] = operandPool[0];
		;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 281 "nvgp4ASM.y"
    {
			t_inst.op = (yyvsp[(1) - (2)].ival);
		;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 286 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (2)].ival);
	;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 291 "nvgp4ASM.y"
    {
			t_inst.op = (yyvsp[(1) - (3)].ival);
			t_inst.src[0] = t_operand;
			t_inst.src[0].type = INST_CCREG;
			switch (t_operand.ccMask) {
			case CC_EQ:
			case CC_EQ0:
			case CC_GE:
			case CC_GE0:
			case CC_GT:
			case CC_GT0:
			case CC_LE:
			case CC_LE0:
			case CC_LT:
			case CC_LT0:
			case CC_NE:
			case CC_NE0:
			case CC_TR:
			case CC_TR0:
			case CC_FL:
			case CC_FL0:
			case CC_NAN:
			case CC_NAN0:
			case CC_LEG:
			case CC_LEG0:
			case CC_CF:
			case CC_CF0:
			case CC_NCF:
			case CC_NCF0:
			case CC_OF:
			case CC_OF0:
			case CC_NOF:
			case CC_NOF0:
			case CC_AB:
			case CC_AB0:
			case CC_BLE:
			case CC_BLE0:
			case CC_SF:
			case CC_SF0:
			case CC_NSF:
			case CC_NSF0:
				t_inst.src[0].id = 0;
				break;
					
			case CC_EQ1:
			case CC_GE1:
			case CC_GT1:
			case CC_LE1:
			case CC_LT1:
			case CC_NE1:
			case CC_TR1:
			case CC_FL1:
			case CC_NAN1:
			case CC_LEG1:
			case CC_CF1:
			case CC_NCF1:
			case CC_OF1:
			case CC_NOF1:
			case CC_AB1:
			case CC_BLE1:
			case CC_SF1:
			case CC_NSF1:
				t_inst.src[0].id = 1;
				break;
			}
		;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 363 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (5)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
	;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 374 "nvgp4ASM.y"
    {t_inst.opModifiers[(yyvsp[(2) - (2)].ival)] = true;;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 376 "nvgp4ASM.y"
    {
		if (shaderType == 0) { // Vertex shader {
			//Use idx to record the array element if target is array type.
			int idx  = (yyvsp[(1) - (3)].ival) - t_program.asmVStexIdx[(yyvsp[(1) - (3)].ival)].idx;
			t_inst.tid = t_program.srcTexture[t_program.asmVStexIdx[(yyvsp[(1) - (3)].ival)].name].idx + idx;
		}
		else {// Fragment shader
			int idx  = (yyvsp[(1) - (3)].ival) - t_program.asmFStexIdx[(yyvsp[(1) - (3)].ival)].idx;
			t_inst.tid = t_program.srcTexture[t_program.asmFStexIdx[(yyvsp[(1) - (3)].ival)].name].idx + idx;
		}
		t_inst.tType = (yyvsp[(3) - (3)].ival);
	;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 389 "nvgp4ASM.y"
    {(yyval.ival) = (yyvsp[(3) - (4)].ival);;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 397 "nvgp4ASM.y"
    {operandPool.push_back(t_operand); t_operand.Init();;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 398 "nvgp4ASM.y"
    {operandPool.push_back(t_operand); t_operand.Init();;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 401 "nvgp4ASM.y"
    {t_operand.abs = true;;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 404 "nvgp4ASM.y"
    {
			if (shaderType == VERTEX_SHADER)
				t_operand.id = (yyvsp[(6) - (8)].ival);
			else // Fragment shader
				t_operand.id = t_program.srcFSin[t_program.asmFSinIdx[(yyvsp[(6) - (8)].ival)]].idx;
			t_operand.type = INST_ATTRIB;
			t_operand.modifier = (yyvsp[(8) - (8)].ival);
			if ((yyvsp[(1) - (8)].sval)[0] == '-')
				t_operand.inverse = true;
		;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 414 "nvgp4ASM.y"
    {
			if (shaderType == 0) { // Vertex shader {
				//Use idx to record the array element if target is array type.
				int idx  = (yyvsp[(4) - (6)].ival) - t_program.asmUniformVSIdx[(yyvsp[(4) - (6)].ival)].idx;
				t_operand.id = t_program.srcUniform[t_program.asmUniformVSIdx[(yyvsp[(4) - (6)].ival)].name].idx + idx;
			}
			else {// Fragment shader
				int idx  = (yyvsp[(4) - (6)].ival) - t_program.asmUniformFSIdx[(yyvsp[(4) - (6)].ival)].idx;
				t_operand.id = t_program.srcUniform[t_program.asmUniformFSIdx[(yyvsp[(4) - (6)].ival)].name].idx + idx;
			}
			t_operand.type = INST_UNIFORM;
			t_operand.modifier = (yyvsp[(6) - (6)].ival);
			if ((yyvsp[(1) - (6)].sval)[0] == '-')
				t_operand.inverse = true;
		;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 429 "nvgp4ASM.y"
    {
			t_operand.id = (yyvsp[(2) - (3)].ival);
			t_operand.type = INST_REG;
			t_operand.modifier = (yyvsp[(3) - (3)].ival);
			if ((yyvsp[(1) - (3)].sval)[0] == '-')
				t_operand.inverse = true;
		;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 436 "nvgp4ASM.y"
    {
			t_operand.type = INST_CONSTANT;
			t_operand.modifier = (yyvsp[(3) - (3)].ival);
			if ((yyvsp[(1) - (3)].sval)[0] == '-')
				t_operand.inverse = true;
		;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 451 "nvgp4ASM.y"
    {operandPool.push_back(t_operand);;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 457 "nvgp4ASM.y"
    {
			t_operand.id = (yyvsp[(1) - (2)].ival);
			t_operand.type = INST_REG;
			t_operand.modifier = (yyvsp[(2) - (2)].ival);
		;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 462 "nvgp4ASM.y"
    {
			t_operand.id = 0;
			t_operand.type = INST_ATTRIB;
			t_operand.modifier = (yyvsp[(4) - (4)].ival);
		;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 467 "nvgp4ASM.y"
    {
			t_operand.id = (yyvsp[(5) - (7)].ival) + 1;
			t_operand.type = INST_ATTRIB;
			t_operand.modifier = (yyvsp[(7) - (7)].ival);
		;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 472 "nvgp4ASM.y"
    {
			t_operand.type = INST_COLOR;
			t_operand.modifier = (yyvsp[(2) - (2)].ival);
		;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 480 "nvgp4ASM.y"
    {
		t_operand.ccMask = (yyvsp[(1) - (2)].ival);
		t_operand.ccModifier = (yyvsp[(2) - (2)].ival);
	;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 488 "nvgp4ASM.y"
    {
			t_operand.val.x = t_operand.val.y =
			t_operand.val.z = t_operand.val.w = (yyvsp[(1) - (1)].fval);
		;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 492 "nvgp4ASM.y"
    {
			t_operand.val.x = (yyvsp[(1) - (3)].fval);
			t_operand.val.y = t_operand.val.z = t_operand.val.w = (yyvsp[(3) - (3)].fval);
		;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 496 "nvgp4ASM.y"
    {
			t_operand.val.x = (yyvsp[(1) - (5)].fval);
			t_operand.val.y = (yyvsp[(3) - (5)].fval);
			t_operand.val.z = t_operand.val.w = (yyvsp[(5) - (5)].fval);
		;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 501 "nvgp4ASM.y"
    {
			t_operand.val.x = (yyvsp[(1) - (7)].fval);
			t_operand.val.y = (yyvsp[(3) - (7)].fval);
			t_operand.val.z = (yyvsp[(5) - (7)].fval);
			t_operand.val.w = (yyvsp[(7) - (7)].fval);
		;}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 510 "nvgp4ASM.y"
    {(yyval.fval) = (yyvsp[(1) - (1)].ival);;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 511 "nvgp4ASM.y"
    {(yyval.fval) = (yyvsp[(1) - (1)].fval);;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 515 "nvgp4ASM.y"
    {(yyval.ival) = 0x8421;;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 516 "nvgp4ASM.y"
    {(yyval.ival) = (yyvsp[(2) - (2)].ival);;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 517 "nvgp4ASM.y"
    {
			(yyval.ival) = 0;
			for (int i=0; i<4; i++) {
				if ((yyvsp[(2) - (2)].sval)[i] == '/0')
					break;
					
				switch ((yyvsp[(2) - (2)].sval)[i]) {
				case 'x':
					(yyval.ival) = (yyval.ival) | (0x1 << i*4);
					break;
				case 'y':
					(yyval.ival) = (yyval.ival) | (0x2 << i*4);
					break;
				case 'z':
					(yyval.ival) = (yyval.ival) | (0x4 << i*4);
					break;
				case 'w':
					(yyval.ival) = (yyval.ival) | (0x8 << i*4);
					break;
				}
			}
		;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 539 "nvgp4ASM.y"
    {
			(yyval.ival) = 0;
			for (int i=0; i<4; i++) {
				if ((yyvsp[(2) - (2)].sval)[i] == '/0')
					break;
					
				switch ((yyvsp[(2) - (2)].sval)[i]) {
				case 'r':
					(yyval.ival) = (yyval.ival) | (0x1 << i*4);
					break;
				case 'g':
					(yyval.ival) = (yyval.ival) | (0x2 << i*4);
					break;
				case 'b':
					(yyval.ival) = (yyval.ival) | (0x4 << i*4);
					break;
				case 'a':
					(yyval.ival) = (yyval.ival) | (0x8 << i*4);
					break;
				}
			}
		;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 578 "nvgp4ASM.y"
    {(yyval.ival) = (yyvsp[(1) - (1)].ival);;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 579 "nvgp4ASM.y"
    {(yyval.ival) = (yyvsp[(1) - (1)].ival);;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 583 "nvgp4ASM.y"
    {(yyval.ival) = 0x1;;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 584 "nvgp4ASM.y"
    {(yyval.ival) = 0x2;;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 585 "nvgp4ASM.y"
    {(yyval.ival) = 0x4;;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 586 "nvgp4ASM.y"
    {(yyval.ival) = 0x8;;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 590 "nvgp4ASM.y"
    {(yyval.ival) = 0x1;;}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 591 "nvgp4ASM.y"
    {(yyval.ival) = 0x2;;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 592 "nvgp4ASM.y"
    {(yyval.ival) = 0x4;;}
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 593 "nvgp4ASM.y"
    {(yyval.ival) = 0x8;;}
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 597 "nvgp4ASM.y"
    {(yyval.sval)[0] = '\0';;}
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 598 "nvgp4ASM.y"
    {(yyval.sval)[0] = '-'; (yyval.sval)[1] = '\0';;}
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 599 "nvgp4ASM.y"
    {(yyval.sval)[0] = '+'; (yyval.sval)[1] = '\0';;}
    break;



/* Line 1464 of yacc.c  */
#line 2351 "nvgp4ASM.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1684 of yacc.c  */
#line 605 "nvgp4ASM.y"



