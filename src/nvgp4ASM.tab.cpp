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
#line 1 "nvgp4ASM.y"

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
     IDENTIFIER = 268,
     INTEGER = 269,
     FLOAT = 270,
     VECTOROP = 271,
     SCALAROP = 272,
     BINSCOP = 273,
     VECSCAOP = 274,
     BINOP = 275,
     TRIOP = 276,
     SWZOP = 277,
     TEXOP = 278,
     TXDOP = 279,
     BRAOP = 280,
     FLOWCCOP = 281,
     IFOP = 282,
     REPOP = 283,
     ENDFLOWOP = 284,
     KILOP = 285,
     DERIVEOP = 286,
     OPMODIFIER = 287,
     TEXTARGET = 288,
     CCMASKRULE = 289,
     XYZW_SWIZZLE = 290,
     RGBA_SWIZZLE = 291,
     REG = 292
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 20 "nvgp4ASM.y"

	int		ival;
	float	fval;
	char	sval[30];



/* Line 214 of yacc.c  */
#line 181 "nvgp4ASM.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 193 "nvgp4ASM.tab.c"

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
#define YYFINAL  64
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   190

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNRULES -- Number of states.  */
#define YYNSTATES  222

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      46,    47,     2,    59,    40,    58,    41,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    39,    38,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    42,     2,    43,     2,     2,     2,    57,    56,    45,
       2,     2,     2,    55,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    54,     2,     2,     2,     2,    53,
      50,    51,    52,    48,    44,    49,     2,     2,     2,     2,
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
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,     9,    12,    15,    17,    20,
      22,    24,    26,    28,    30,    32,    34,    36,    38,    40,
      42,    44,    46,    48,    50,    52,    54,    56,    58,    60,
      66,    72,    80,    88,    96,   106,   114,   122,   134,   139,
     143,   147,   151,   154,   157,   161,   167,   168,   171,   174,
     178,   183,   184,   186,   188,   190,   195,   204,   211,   215,
     219,   221,   223,   225,   227,   230,   233,   238,   246,   249,
     253,   256,   260,   262,   266,   272,   280,   282,   284,   285,
     288,   291,   294,   302,   305,   308,   310,   312,   314,   316,
     318,   320,   322,   324,   326,   328,   330,   332,   334,   335,
     337,   339,   341
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      61,     0,    -1,    62,    61,    -1,    -1,    63,    -1,    64,
      38,    -1,   112,    39,    -1,     8,    -1,     7,    12,    -1,
      65,    -1,    66,    -1,    67,    -1,    68,    -1,    69,    -1,
      70,    -1,    71,    -1,    73,    -1,    72,    -1,    74,    -1,
      75,    -1,    76,    -1,    77,    -1,    78,    -1,    79,    -1,
      80,    -1,    81,    -1,    82,    -1,    83,    -1,    84,    -1,
      16,    85,    94,    40,    90,    -1,    17,    85,    94,    40,
      90,    -1,    18,    85,    94,    40,    90,    40,    90,    -1,
      19,    85,    94,    40,    90,    40,    90,    -1,    20,    85,
      94,    40,    90,    40,    90,    -1,    21,    85,    94,    40,
      90,    40,    90,    40,    90,    -1,    22,    85,    94,    40,
      90,    40,   103,    -1,    23,    85,    94,    40,    90,    40,
      87,    -1,    24,    85,    94,    40,    90,    40,    90,    40,
      90,    40,    87,    -1,    25,    85,   111,    89,    -1,    26,
      85,    89,    -1,    27,    85,    98,    -1,    28,    85,    90,
      -1,    28,    85,    -1,    29,    85,    -1,    30,    85,    98,
      -1,    31,    85,    94,    40,    90,    -1,    -1,    86,    85,
      -1,    41,    32,    -1,    88,    40,    33,    -1,     3,    42,
      14,    43,    -1,    -1,    97,    -1,    91,    -1,    92,    -1,
     110,    44,    92,    44,    -1,   110,    93,    41,     9,    42,
      14,    43,   102,    -1,   110,    45,    42,    14,    43,   102,
      -1,   110,    37,   102,    -1,   110,    99,   102,    -1,     5,
      -1,     4,    -1,    95,    -1,    96,    -1,    96,    97,    -1,
      37,   102,    -1,     6,    41,    10,   102,    -1,     6,    41,
       9,    42,    14,    43,   102,    -1,    11,   102,    -1,    46,
      98,    47,    -1,    34,   102,    -1,    48,   100,    49,    -1,
     101,    -1,   101,    40,   101,    -1,   101,    40,   101,    40,
     101,    -1,   101,    40,   101,    40,   101,    40,   101,    -1,
      14,    -1,    15,    -1,    -1,    41,   107,    -1,    41,    35,
      -1,    41,    36,    -1,   104,    40,   104,    40,   104,    40,
     104,    -1,   110,   105,    -1,   110,   106,    -1,    14,    -1,
     108,    -1,   109,    -1,   108,    -1,   109,    -1,    50,    -1,
      51,    -1,    52,    -1,    53,    -1,    54,    -1,    55,    -1,
      56,    -1,    57,    -1,    -1,    58,    -1,    59,    -1,    13,
      -1,    13,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    54,    54,    55,    58,    59,    69,    70,    74,    77,
      78,    79,    80,    84,    85,    86,    87,    88,    89,    90,
      94,    95,    99,   100,   101,   102,   103,   107,   108,   111,
     117,   123,   130,   137,   144,   152,   158,   164,   172,   174,
     176,   244,   245,   248,   253,   325,   331,   333,   336,   338,
     351,   353,   355,   359,   360,   363,   366,   376,   391,   398,
     407,   408,   412,   413,   416,   419,   424,   429,   434,   440,
     442,   447,   450,   454,   458,   463,   472,   473,   477,   478,
     479,   480,   483,   486,   487,   491,   492,   495,   498,   499,
     503,   504,   505,   506,   510,   511,   512,   513,   517,   518,
     519,   521,   523
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TEXTURE", "VERTEX", "FRAGMENT",
  "RESULT", "PROF", "END", "ATTRIB", "POSITION", "RESULT_COLOR0",
  "SHADERTYPE", "IDENTIFIER", "INTEGER", "FLOAT", "VECTOROP", "SCALAROP",
  "BINSCOP", "VECSCAOP", "BINOP", "TRIOP", "SWZOP", "TEXOP", "TXDOP",
  "BRAOP", "FLOWCCOP", "IFOP", "REPOP", "ENDFLOWOP", "KILOP", "DERIVEOP",
  "OPMODIFIER", "TEXTARGET", "CCMASKRULE", "XYZW_SWIZZLE", "RGBA_SWIZZLE",
  "REG", "';'", "':'", "','", "'.'", "'['", "']'", "'|'", "'c'", "'('",
  "')'", "'{'", "'}'", "'x'", "'y'", "'z'", "'w'", "'r'", "'g'", "'b'",
  "'a'", "'-'", "'+'", "$accept", "input", "line", "profile",
  "instruction", "ALUInstruction", "TexInstruction", "FlowInstruction",
  "SpecialInstrution", "VECTORop_instruction", "SCALARop_instruction",
  "BINSCop_instruction", "VECSCAop_instruction", "BINop_instruction",
  "TRIop_instruction", "SWZop_instruction", "TEXop_instruction",
  "TXDop_instruction", "BRAop_instruction", "FLOWCCop_instruction",
  "IFop_instruction", "REPop_instruction", "ENDFLOWop_instruction",
  "KILop_instruction", "DERIVEop_instruction", "opModifiers",
  "opModifierItem", "texAccess", "texImageUnit", "optBranchCond",
  "instOperand", "instOperandAbs", "instOperandBase", "primitive",
  "instResult", "instResultCC", "instResultBase", "ccMask", "ccTest",
  "constantVector", "constantVectorList", "constantScalar",
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
     285,   286,   287,   288,   289,   290,   291,   292,    59,    58,
      44,    46,    91,    93,   124,    99,    40,    41,   123,   125,
     120,   121,   122,   119,   114,   103,    98,    97,    45,    43
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    61,    61,    62,    62,    62,    62,    63,    64,
      64,    64,    64,    65,    65,    65,    65,    65,    65,    65,
      66,    66,    67,    67,    67,    67,    67,    68,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    81,    82,    83,    84,    85,    85,    86,    87,
      88,    89,    89,    90,    90,    91,    92,    92,    92,    92,
      93,    93,    94,    94,    95,    96,    96,    96,    96,    97,
      98,    99,   100,   100,   100,   100,   101,   101,   102,   102,
     102,   102,   103,   104,   104,   105,   105,   106,   107,   107,
     108,   108,   108,   108,   109,   109,   109,   109,   110,   110,
     110,   111,   112
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     1,     2,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       5,     7,     7,     7,     9,     7,     7,    11,     4,     3,
       3,     3,     2,     2,     3,     5,     0,     2,     2,     3,
       4,     0,     1,     1,     1,     4,     8,     6,     3,     3,
       1,     1,     1,     1,     2,     2,     4,     7,     2,     3,
       2,     3,     1,     3,     5,     7,     1,     1,     0,     2,
       2,     2,     7,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     7,   102,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
       0,     3,     4,     0,     9,    10,    11,    12,    13,    14,
      15,    17,    16,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,     0,     8,     0,     0,    46,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    51,     0,
      98,    43,     0,     0,     1,     2,     5,     6,    48,     0,
      78,    78,     0,    62,    63,    47,     0,     0,     0,     0,
       0,     0,     0,     0,   101,    51,     0,    39,    52,    78,
      40,    99,   100,    41,    53,    54,     0,    44,     0,     0,
       0,    68,    65,    98,    64,    98,    98,    98,    98,    98,
      98,    98,    98,    38,     0,    70,    61,    60,    78,    98,
       0,     0,     0,    78,    98,     0,    78,    80,    81,    90,
      91,    92,    93,    94,    95,    96,    97,    79,    88,    89,
      29,    30,     0,     0,     0,     0,     0,     0,     0,    69,
      58,     0,     0,     0,    76,    77,     0,    72,     0,    59,
      45,     0,    66,    98,    98,    98,    98,    98,     0,    98,
      55,     0,    71,     0,     0,     0,    31,    32,    33,     0,
      35,     0,     0,     0,    36,     0,     0,    78,    73,     0,
      78,    98,    98,    85,    83,    84,    86,    87,     0,     0,
      98,    57,     0,     0,    67,    34,     0,     0,    49,     0,
      74,    78,    98,    50,     0,     0,    56,     0,    37,    75,
      98,    82
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    47,    48,   184,   185,    87,
      93,    94,    95,   122,    72,    73,    74,    88,    90,   123,
     156,   157,   101,   180,   181,   194,   195,   137,   138,   139,
      96,    85,    44
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -171
static const yytype_int16 yypact[] =
{
     104,    -9,  -171,  -171,   -22,   -22,   -22,   -22,   -22,   -22,
     -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,
      21,   104,  -171,     7,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,    12,  -171,    34,     6,   -22,     6,
       6,     6,     6,     6,     6,     6,     6,    45,    23,    39,
       2,  -171,    39,     6,  -171,  -171,  -171,  -171,  -171,    50,
      51,    51,    55,  -171,    23,  -171,    56,    57,    58,    60,
      61,    73,    74,    75,  -171,    23,    39,  -171,  -171,    51,
    -171,  -171,  -171,  -171,  -171,  -171,     9,  -171,    78,    62,
      53,  -171,  -171,    26,  -171,    26,    26,    26,    26,    26,
      26,    26,    26,  -171,    46,  -171,  -171,  -171,    51,    26,
      94,    72,    96,    51,    26,    97,    51,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,    98,   109,   110,   111,   112,   113,   114,  -171,
    -171,   115,    11,   142,  -171,  -171,   108,   118,   151,  -171,
    -171,   147,  -171,    26,    26,    26,    26,    26,   159,    26,
    -171,   120,  -171,    72,   122,   123,  -171,  -171,  -171,   125,
    -171,   127,    25,   126,  -171,   129,   130,    51,   131,   158,
      51,    26,    26,  -171,  -171,  -171,  -171,  -171,   160,   140,
      26,  -171,    72,   132,  -171,  -171,   136,   134,  -171,   138,
     139,    51,    26,  -171,   159,    72,  -171,   141,  -171,  -171,
      26,  -171
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -171,   161,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,  -171,
    -171,  -171,  -171,  -171,  -171,    19,  -171,   -34,  -171,    99,
    -101,  -171,    64,  -171,    92,  -171,  -171,   116,   -42,  -171,
    -171,  -132,   -71,  -171,  -170,  -171,  -171,  -171,     3,     4,
    -118,  -171,  -171
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -43
static const yytype_int16 yytable[] =
{
     102,   152,   140,    45,   141,   142,   143,   144,   145,   146,
     147,   148,    69,   116,   117,   116,   117,    70,   115,    46,
      97,    64,   206,   160,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,   193,
     -42,   188,   217,    71,   114,    66,   118,   150,   118,   182,
     221,    67,   159,   119,   120,   162,   120,   121,    84,   121,
      91,    92,   176,   177,   178,   179,    68,    75,   186,    86,
     210,   125,   126,    89,   182,   129,   130,   131,   132,   133,
     134,   135,   136,   219,    91,    92,   154,   155,   127,   128,
     205,    99,   100,   149,   182,   103,   105,   106,   107,   209,
     108,   109,   182,   129,   130,   131,   132,   133,   134,   135,
     136,     1,     2,   110,   111,   112,   201,     3,   124,   204,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,   153,   158,   163,   161,
     216,    76,    77,    78,    79,    80,    81,    82,    83,   164,
     165,   166,   167,   168,   169,    98,   171,   172,   173,   170,
     174,   175,   183,   187,   189,   191,   190,   192,   198,   199,
     200,   202,   203,   208,   207,   211,   212,   213,   214,   215,
     218,   220,    65,   151,   113,   196,   197,     0,     0,     0,
     104
};

static const yytype_int16 yycheck[] =
{
      71,   119,   103,    12,   105,   106,   107,   108,   109,   110,
     111,   112,     6,     4,     5,     4,     5,    11,    89,    41,
      62,     0,   192,   124,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    14,
      38,   173,   212,    37,    86,    38,    37,   118,    37,   167,
     220,    39,   123,    44,    45,   126,    45,    48,    13,    48,
      58,    59,   163,   164,   165,   166,    32,    48,   169,    46,
     202,     9,    10,    34,   192,    50,    51,    52,    53,    54,
      55,    56,    57,   215,    58,    59,    14,    15,    35,    36,
     191,    41,    41,    47,   212,    40,    40,    40,    40,   200,
      40,    40,   220,    50,    51,    52,    53,    54,    55,    56,
      57,     7,     8,    40,    40,    40,   187,    13,    40,   190,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    42,    41,    40,    42,
     211,    49,    50,    51,    52,    53,    54,    55,    56,    40,
      40,    40,    40,    40,    40,    63,    14,    49,    40,    44,
       9,    14,     3,    43,    42,    40,    43,    40,    42,    40,
      40,    40,    14,    33,    14,    43,    40,    43,    40,    40,
     214,    40,    21,   119,    85,   182,   182,    -1,    -1,    -1,
      74
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,    13,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,   112,    12,    41,    85,    86,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,     0,    61,    38,    39,    32,     6,
      11,    37,    94,    95,    96,    85,    94,    94,    94,    94,
      94,    94,    94,    94,    13,   111,    46,    89,    97,    34,
      98,    58,    59,    90,    91,    92,   110,    98,    94,    41,
      41,   102,   102,    40,    97,    40,    40,    40,    40,    40,
      40,    40,    40,    89,    98,   102,     4,     5,    37,    44,
      45,    48,    93,    99,    40,     9,    10,    35,    36,    50,
      51,    52,    53,    54,    55,    56,    57,   107,   108,   109,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    47,
     102,    92,   110,    42,    14,    15,   100,   101,    41,   102,
      90,    42,   102,    40,    40,    40,    40,    40,    40,    40,
      44,    14,    49,    40,     9,    14,    90,    90,    90,    90,
     103,   104,   110,     3,    87,    88,    90,    43,   101,    42,
      43,    40,    40,    14,   105,   106,   108,   109,    42,    40,
      40,   102,    40,    14,   102,    90,   104,    14,    33,    90,
     101,    43,    40,    43,    40,    40,   102,   104,    87,   101,
      40,   104
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
        case 5:

/* Line 1464 of yacc.c  */
#line 59 "nvgp4ASM.y"
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

  case 8:

/* Line 1464 of yacc.c  */
#line 74 "nvgp4ASM.y"
    {shaderType = (yyvsp[(2) - (2)].ival);;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 111 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (5)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
	;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 117 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (5)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
	;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 123 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
		t_inst.src[1] = operandPool[2];
	;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 130 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
		t_inst.src[1] = operandPool[2];
	;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 137 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
		t_inst.src[1] = operandPool[2];
	;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 144 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (9)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
		t_inst.src[1] = operandPool[2];
		t_inst.src[2] = operandPool[3];
	;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 152 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
	;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 158 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
	;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 164 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (11)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
		t_inst.src[1] = operandPool[2];
		t_inst.src[2] = operandPool[3];
	;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 176 "nvgp4ASM.y"
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

  case 43:

/* Line 1464 of yacc.c  */
#line 248 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (2)].ival);
	;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 253 "nvgp4ASM.y"
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

  case 45:

/* Line 1464 of yacc.c  */
#line 325 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (5)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src[0] = operandPool[1];
	;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 336 "nvgp4ASM.y"
    {t_inst.opModifiers[(yyvsp[(2) - (2)].ival)] = true;;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 338 "nvgp4ASM.y"
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

  case 50:

/* Line 1464 of yacc.c  */
#line 351 "nvgp4ASM.y"
    {(yyval.ival) = (yyvsp[(3) - (4)].ival);;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 359 "nvgp4ASM.y"
    {operandPool.push_back(t_operand); t_operand.Init();;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 360 "nvgp4ASM.y"
    {operandPool.push_back(t_operand); t_operand.Init();;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 363 "nvgp4ASM.y"
    {t_operand.abs = true;;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 366 "nvgp4ASM.y"
    {
			if (shaderType == 0) // Vertex shader {
				t_operand.id = (yyvsp[(6) - (8)].ival);
			else // Fragment shader
				t_operand.id = (yyvsp[(6) - (8)].ival) + 1;
			t_operand.type = INST_ATTRIB;
			strncpy(t_operand.modifier, (yyvsp[(8) - (8)].sval), 5);
			if ((yyvsp[(1) - (8)].sval)[0] == '-')
				t_operand.inverse = true;
		;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 376 "nvgp4ASM.y"
    {
			if (shaderType == 0) { // Vertex shader {
				//Use idx to record the array element if target is array type.
				int idx  = (yyvsp[(4) - (6)].ival) - t_program.asmVSIdx[(yyvsp[(4) - (6)].ival)].idx;
				t_operand.id = t_program.srcUniform[t_program.asmVSIdx[(yyvsp[(4) - (6)].ival)].name].idx + idx;
			}
			else {// Fragment shader
				int idx  = (yyvsp[(4) - (6)].ival) - t_program.asmFSIdx[(yyvsp[(4) - (6)].ival)].idx;
				t_operand.id = t_program.srcUniform[t_program.asmFSIdx[(yyvsp[(4) - (6)].ival)].name].idx + idx;
			}
			t_operand.type = INST_UNIFORM;
			strncpy(t_operand.modifier, (yyvsp[(6) - (6)].sval), 5);
			if ((yyvsp[(1) - (6)].sval)[0] == '-')
				t_operand.inverse = true;
		;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 391 "nvgp4ASM.y"
    {
			t_operand.id = (yyvsp[(2) - (3)].ival);
			t_operand.type = INST_REG;
			strncpy(t_operand.modifier, (yyvsp[(3) - (3)].sval), 5);
			if ((yyvsp[(1) - (3)].sval)[0] == '-')
				t_operand.inverse = true;
		;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 398 "nvgp4ASM.y"
    {
			t_operand.type = INST_CONSTANT;
			strncpy(t_operand.modifier, (yyvsp[(3) - (3)].sval), 5);
			if ((yyvsp[(1) - (3)].sval)[0] == '-')
				t_operand.inverse = true;
		;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 413 "nvgp4ASM.y"
    {operandPool.push_back(t_operand);;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 419 "nvgp4ASM.y"
    {
			t_operand.id = (yyvsp[(1) - (2)].ival);
			t_operand.type = INST_REG;
			strncpy(t_operand.modifier, (yyvsp[(2) - (2)].sval), 5);
		;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 424 "nvgp4ASM.y"
    {
			t_operand.id = 0;
			t_operand.type = INST_ATTRIB;
			strncpy(t_operand.modifier, (yyvsp[(4) - (4)].sval), 5);
		;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 429 "nvgp4ASM.y"
    {
			t_operand.id = (yyvsp[(5) - (7)].ival) + 1;
			t_operand.type = INST_ATTRIB;
			strncpy(t_operand.modifier, (yyvsp[(7) - (7)].sval), 5);
		;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 434 "nvgp4ASM.y"
    {
			t_operand.type = INST_COLOR;
			strncpy(t_operand.modifier, (yyvsp[(2) - (2)].sval), 5);
		;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 442 "nvgp4ASM.y"
    {
		t_operand.ccMask = (yyvsp[(1) - (2)].ival);
		strncpy(t_operand.ccModifier, (yyvsp[(2) - (2)].sval), 5);
	;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 450 "nvgp4ASM.y"
    {
			t_operand.val.x = t_operand.val.y =
			t_operand.val.z = t_operand.val.w = (yyvsp[(1) - (1)].fval);
		;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 454 "nvgp4ASM.y"
    {
			t_operand.val.x = (yyvsp[(1) - (3)].fval);
			t_operand.val.y = t_operand.val.z = t_operand.val.w = (yyvsp[(3) - (3)].fval);
		;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 458 "nvgp4ASM.y"
    {
			t_operand.val.x = (yyvsp[(1) - (5)].fval);
			t_operand.val.y = (yyvsp[(3) - (5)].fval);
			t_operand.val.z = t_operand.val.w = (yyvsp[(5) - (5)].fval);
		;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 463 "nvgp4ASM.y"
    {
			t_operand.val.x = (yyvsp[(1) - (7)].fval);
			t_operand.val.y = (yyvsp[(3) - (7)].fval);
			t_operand.val.z = (yyvsp[(5) - (7)].fval);
			t_operand.val.w = (yyvsp[(7) - (7)].fval);
		;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 472 "nvgp4ASM.y"
    {(yyval.fval) = (yyvsp[(1) - (1)].ival);;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 473 "nvgp4ASM.y"
    {(yyval.fval) = (yyvsp[(1) - (1)].fval);;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 477 "nvgp4ASM.y"
    {strcpy((yyval.sval), "xyzw");;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 478 "nvgp4ASM.y"
    {strcpy((yyval.sval), (yyvsp[(2) - (2)].sval));;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 479 "nvgp4ASM.y"
    {strcpy((yyval.sval), (yyvsp[(2) - (2)].sval));;}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 480 "nvgp4ASM.y"
    {strcpy((yyval.sval), (yyvsp[(2) - (2)].sval));;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 498 "nvgp4ASM.y"
    {strcpy((yyval.sval), (yyvsp[(1) - (1)].sval));;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 499 "nvgp4ASM.y"
    {strcpy((yyval.sval), (yyvsp[(1) - (1)].sval));;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 503 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'x'; (yyval.sval)[1] = '\0';;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 504 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'y'; (yyval.sval)[1] = '\0';;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 505 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'z'; (yyval.sval)[1] = '\0';;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 506 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'w'; (yyval.sval)[1] = '\0';;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 510 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'r'; (yyval.sval)[1] = '\0';;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 511 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'g'; (yyval.sval)[1] = '\0';;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 512 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'b'; (yyval.sval)[1] = '\0';;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 513 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'a'; (yyval.sval)[1] = '\0';;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 517 "nvgp4ASM.y"
    {(yyval.sval)[0] = '\0';;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 518 "nvgp4ASM.y"
    {(yyval.sval)[0] = '-'; (yyval.sval)[1] = '\0';;}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 519 "nvgp4ASM.y"
    {(yyval.sval)[0] = '+'; (yyval.sval)[1] = '\0';;}
    break;



/* Line 1464 of yacc.c  */
#line 2241 "nvgp4ASM.tab.c"
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
#line 525 "nvgp4ASM.y"



