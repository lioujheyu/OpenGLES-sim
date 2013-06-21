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


/* Line 189 of yacc.c  */
#line 99 "nvgp4ASM.tab.c"

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
     ATTRIB = 263,
     POSITION = 264,
     RESULT_COLOR0 = 265,
     SHADERTYPE = 266,
     IDENTIFIER = 267,
     INTEGER = 268,
     FLOAT = 269,
     VECTOROP = 270,
     SCALAROP = 271,
     BINSCOP = 272,
     VECSCAOP = 273,
     BINOP = 274,
     TRIOP = 275,
     SWZOP = 276,
     TEXOP = 277,
     TXDOP = 278,
     BRAOP = 279,
     FLOWCCOP = 280,
     IFOP = 281,
     REPOP = 282,
     ENDFLOWOP = 283,
     OPMODIFIER = 284,
     TEXTARGET = 285,
     CCMASKRULE = 286,
     XYZW_SWIZZLE = 287,
     RGBA_SWIZZLE = 288,
     REG = 289
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 19 "nvgp4ASM.y"

	int		ival;
	float	fval;
	char	sval[30];



/* Line 214 of yacc.c  */
#line 177 "nvgp4ASM.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 189 "nvgp4ASM.tab.c"

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
#define YYFINAL  56
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   187

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNRULES -- Number of states.  */
#define YYNSTATES  210

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      43,    44,     2,    56,    37,    55,    38,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    36,    35,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    40,     2,     2,     2,    54,    53,    42,
       2,     2,     2,    52,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    51,     2,     2,     2,     2,    50,
      47,    48,    49,    45,    41,    46,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,     9,    12,    15,    18,    20,
      22,    24,    26,    28,    30,    32,    34,    36,    38,    40,
      42,    44,    46,    48,    50,    52,    58,    64,    72,    80,
      88,    98,   106,   114,   126,   131,   135,   139,   143,   146,
     149,   150,   153,   156,   160,   165,   166,   168,   170,   172,
     177,   186,   193,   197,   201,   203,   205,   207,   209,   212,
     215,   220,   228,   231,   235,   238,   242,   244,   248,   254,
     262,   264,   266,   267,   270,   273,   276,   284,   287,   290,
     292,   294,   296,   298,   300,   302,   304,   306,   308,   310,
     312,   314,   316,   317,   319,   321,   323
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      58,     0,    -1,    59,    58,    -1,    -1,    60,    -1,    61,
      35,    -1,   106,    36,    -1,     7,    11,    -1,    62,    -1,
      63,    -1,    64,    -1,    65,    -1,    66,    -1,    67,    -1,
      69,    -1,    68,    -1,    70,    -1,    71,    -1,    72,    -1,
      73,    -1,    74,    -1,    75,    -1,    76,    -1,    77,    -1,
      78,    -1,    15,    79,    88,    37,    84,    -1,    16,    79,
      88,    37,    84,    -1,    17,    79,    88,    37,    84,    37,
      84,    -1,    18,    79,    88,    37,    84,    37,    84,    -1,
      19,    79,    88,    37,    84,    37,    84,    -1,    20,    79,
      88,    37,    84,    37,    84,    37,    84,    -1,    21,    79,
      88,    37,    84,    37,    97,    -1,    22,    79,    88,    37,
      84,    37,    81,    -1,    23,    79,    88,    37,    84,    37,
      84,    37,    84,    37,    81,    -1,    24,    79,   105,    83,
      -1,    25,    79,    83,    -1,    26,    79,    92,    -1,    27,
      79,    84,    -1,    27,    79,    -1,    28,    79,    -1,    -1,
      80,    79,    -1,    38,    29,    -1,    82,    37,    30,    -1,
       3,    39,    13,    40,    -1,    -1,    91,    -1,    85,    -1,
      86,    -1,   104,    41,    86,    41,    -1,   104,    87,    38,
       8,    39,    13,    40,    96,    -1,   104,    42,    39,    13,
      40,    96,    -1,   104,    34,    96,    -1,   104,    93,    96,
      -1,     5,    -1,     4,    -1,    89,    -1,    90,    -1,    90,
      91,    -1,    34,    96,    -1,     6,    38,     9,    96,    -1,
       6,    38,     8,    39,    13,    40,    96,    -1,    10,    96,
      -1,    43,    92,    44,    -1,    31,    96,    -1,    45,    94,
      46,    -1,    95,    -1,    95,    37,    95,    -1,    95,    37,
      95,    37,    95,    -1,    95,    37,    95,    37,    95,    37,
      95,    -1,    13,    -1,    14,    -1,    -1,    38,   101,    -1,
      38,    32,    -1,    38,    33,    -1,    98,    37,    98,    37,
      98,    37,    98,    -1,   104,    99,    -1,   104,   100,    -1,
      13,    -1,   102,    -1,   103,    -1,   102,    -1,   103,    -1,
      47,    -1,    48,    -1,    49,    -1,    50,    -1,    51,    -1,
      52,    -1,    53,    -1,    54,    -1,    -1,    55,    -1,    56,
      -1,    12,    -1,    12,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    52,    52,    53,    56,    57,    67,    71,    74,    75,
      76,    80,    81,    82,    83,    84,    85,    86,    90,    91,
      95,    96,    97,    98,    99,   102,   108,   114,   121,   128,
     135,   143,   149,   155,   163,   165,   167,   170,   171,   174,
     176,   178,   181,   183,   196,   198,   200,   204,   205,   208,
     211,   221,   236,   243,   252,   253,   257,   258,   261,   264,
     269,   274,   279,   285,   287,   289,   292,   296,   300,   305,
     314,   315,   319,   320,   321,   322,   325,   328,   329,   333,
     334,   337,   340,   341,   345,   346,   347,   348,   352,   353,
     354,   355,   358,   359,   360,   362,   364
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TEXTURE", "VERTEX", "FRAGMENT",
  "RESULT", "PROF", "ATTRIB", "POSITION", "RESULT_COLOR0", "SHADERTYPE",
  "IDENTIFIER", "INTEGER", "FLOAT", "VECTOROP", "SCALAROP", "BINSCOP",
  "VECSCAOP", "BINOP", "TRIOP", "SWZOP", "TEXOP", "TXDOP", "BRAOP",
  "FLOWCCOP", "IFOP", "REPOP", "ENDFLOWOP", "OPMODIFIER", "TEXTARGET",
  "CCMASKRULE", "XYZW_SWIZZLE", "RGBA_SWIZZLE", "REG", "';'", "':'", "','",
  "'.'", "'['", "']'", "'|'", "'c'", "'('", "')'", "'{'", "'}'", "'x'",
  "'y'", "'z'", "'w'", "'r'", "'g'", "'b'", "'a'", "'-'", "'+'", "$accept",
  "input", "line", "profile", "instruction", "ALUInstruction",
  "TexInstruction", "FlowInstruction", "VECTORop_instruction",
  "SCALARop_instruction", "BINSCop_instruction", "VECSCAop_instruction",
  "BINop_instruction", "TRIop_instruction", "SWZop_instruction",
  "TEXop_instruction", "TXDop_instruction", "BRAop_instruction",
  "FLOWCCop_instruction", "IFop_instruction", "REPop_instruction",
  "ENDFLOWop_instruction", "opModifiers", "opModifierItem", "texAccess",
  "texImageUnit", "optBranchCond", "instOperand", "instOperandAbs",
  "instOperandBase", "primitive", "instResult", "instResultCC",
  "instResultBase", "ccMask", "ccTest", "constantVector",
  "constantVectorList", "constantScalar", "swizzleSuffix",
  "extendedSwizzle", "extSwizComp", "xyzwExtSwizSel", "rgbaExtSwizSel",
  "component", "xyzwComponent", "rgbaComponent", "optSign", "instTarget",
  "instLabel", 0
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
     285,   286,   287,   288,   289,    59,    58,    44,    46,    91,
      93,   124,    99,    40,    41,   123,   125,   120,   121,   122,
     119,   114,   103,    98,    97,    45,    43
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    57,    58,    58,    59,    59,    59,    60,    61,    61,
      61,    62,    62,    62,    62,    62,    62,    62,    63,    63,
      64,    64,    64,    64,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    77,    78,
      79,    79,    80,    81,    82,    83,    83,    84,    84,    85,
      86,    86,    86,    86,    87,    87,    88,    88,    89,    90,
      90,    90,    90,    91,    92,    93,    94,    94,    94,    94,
      95,    95,    96,    96,    96,    96,    97,    98,    98,    99,
      99,   100,   101,   101,   102,   102,   102,   102,   103,   103,
     103,   103,   104,   104,   104,   105,   106
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     1,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     5,     7,     7,     7,
       9,     7,     7,    11,     4,     3,     3,     3,     2,     2,
       0,     2,     2,     3,     4,     0,     1,     1,     1,     4,
       8,     6,     3,     3,     1,     1,     1,     1,     2,     2,
       4,     7,     2,     3,     2,     3,     1,     3,     5,     7,
       1,     1,     0,     2,     2,     2,     7,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,    96,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,     0,     3,     4,
       0,     8,     9,    10,    11,    12,    13,    15,    14,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     0,     7,
       0,     0,    40,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    45,     0,    92,    39,     1,     2,     5,     6,
      42,     0,    72,    72,     0,    56,    57,    41,     0,     0,
       0,     0,     0,     0,     0,     0,    95,    45,     0,    35,
      46,    72,    36,    93,    94,    37,    47,    48,     0,     0,
       0,    62,    59,    92,    58,    92,    92,    92,    92,    92,
      92,    92,    92,    34,     0,    64,    55,    54,    72,    92,
       0,     0,     0,    72,     0,    72,    74,    75,    84,    85,
      86,    87,    88,    89,    90,    91,    73,    82,    83,    25,
      26,     0,     0,     0,     0,     0,     0,     0,    63,    52,
       0,     0,     0,    70,    71,     0,    66,     0,    53,     0,
      60,    92,    92,    92,    92,    92,     0,    92,    49,     0,
      65,     0,     0,     0,    27,    28,    29,     0,    31,     0,
       0,     0,    32,     0,     0,    72,    67,     0,    72,    92,
      92,    79,    77,    78,    80,    81,     0,     0,    92,    51,
       0,     0,    61,    30,     0,     0,    43,     0,    68,    72,
      92,    44,     0,     0,    50,     0,    33,    69,    92,    76
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    41,    42,   172,   173,    79,    85,    86,    87,
     112,    64,    65,    66,    80,    82,   113,   145,   146,    91,
     168,   169,   182,   183,   126,   127,   128,    88,    77,    38
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -178
static const yytype_int16 yypact[] =
{
     122,     3,  -178,   -16,   -16,   -16,   -16,   -16,   -16,   -16,
     -16,   -16,   -16,   -16,   -16,   -16,   -16,    32,   122,  -178,
      -9,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,    -1,  -178,
       7,     9,   -16,     9,     9,     9,     9,     9,     9,     9,
       9,    28,    -6,    13,   -22,  -178,  -178,  -178,  -178,  -178,
    -178,     0,     4,     4,    12,  -178,    -6,  -178,    14,    16,
      18,    19,    21,    34,    44,    45,  -178,    -6,    13,  -178,
    -178,     4,  -178,  -178,  -178,  -178,  -178,  -178,    23,     8,
      54,  -178,  -178,   -35,  -178,   -35,   -35,   -35,   -35,   -35,
     -35,   -35,   -35,  -178,     2,  -178,  -178,  -178,     4,   -35,
      30,    11,    10,     4,    46,     4,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,    47,    52,    53,    56,    57,    58,    59,  -178,  -178,
      42,    25,    78,  -178,  -178,    63,    61,    91,  -178,    97,
    -178,   -35,   -35,   -35,   -35,   -35,   108,   -35,  -178,    73,
    -178,    11,    75,    90,  -178,  -178,  -178,    94,  -178,    95,
      26,    96,  -178,   114,   115,     4,   116,   120,     4,   -35,
     -35,  -178,  -178,  -178,  -178,  -178,   142,   134,   -35,  -178,
      11,   125,  -178,  -178,   129,   127,  -178,   131,   132,     4,
     -35,  -178,   108,    11,  -178,   133,  -178,  -178,   -35,  -178
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -178,   153,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,   112,  -178,   -30,  -178,    98,   -91,  -178,    64,
    -178,   113,  -178,  -178,   110,    99,  -178,  -178,  -149,   -63,
    -178,  -177,  -178,  -178,  -178,    15,    17,  -108,  -178,  -178
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -39
static const yytype_int16 yytable[] =
{
      92,   141,   129,   194,   130,   131,   132,   133,   134,   135,
     136,   137,   176,   -38,    39,    61,   114,   115,   105,    62,
      83,    84,    40,   205,   143,   144,    58,   106,   107,   106,
     107,   209,    56,    83,    84,    59,    60,    78,    89,   181,
      76,   198,    90,    63,    81,   139,   138,   170,   147,    93,
     148,    95,   150,    96,   207,    97,    98,   108,    99,   108,
     164,   165,   166,   167,   109,   110,   174,   110,   111,   142,
     111,   100,   170,   118,   119,   120,   121,   122,   123,   124,
     125,   101,   102,   158,   151,   149,   116,   117,   193,   152,
     153,   159,   170,   154,   155,   156,   157,   197,   161,   162,
     170,   118,   119,   120,   121,   122,   123,   124,   125,   160,
     163,   171,   189,   175,   177,   192,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,     1,
     178,   179,   180,   191,     2,   186,   204,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,   187,   188,   190,    67,   195,    68,    69,    70,    71,
      72,    73,    74,    75,   196,   199,   200,   201,   202,   203,
     208,    57,   206,   140,     0,   103,    94,   104,     0,     0,
       0,     0,     0,     0,     0,   184,     0,   185
};

static const yytype_int16 yycheck[] =
{
      63,   109,    93,   180,    95,    96,    97,    98,    99,   100,
     101,   102,   161,    35,    11,     6,     8,     9,    81,    10,
      55,    56,    38,   200,    13,    14,    35,     4,     5,     4,
       5,   208,     0,    55,    56,    36,    29,    43,    38,    13,
      12,   190,    38,    34,    31,   108,    44,   155,    38,    37,
     113,    37,   115,    37,   203,    37,    37,    34,    37,    34,
     151,   152,   153,   154,    41,    42,   157,    42,    45,    39,
      45,    37,   180,    47,    48,    49,    50,    51,    52,    53,
      54,    37,    37,    41,    37,    39,    32,    33,   179,    37,
      37,    13,   200,    37,    37,    37,    37,   188,    37,     8,
     208,    47,    48,    49,    50,    51,    52,    53,    54,    46,
      13,     3,   175,    40,    39,   178,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,     7,
      40,    37,    37,    13,    12,    39,   199,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    37,    37,    37,    42,    13,    43,    44,    45,    46,
      47,    48,    49,    50,    30,    40,    37,    40,    37,    37,
      37,    18,   202,   109,    -1,    77,    66,    78,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   170,    -1,   170
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    12,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,   106,    11,
      38,    79,    80,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,     0,    58,    35,    36,
      29,     6,    10,    34,    88,    89,    90,    79,    88,    88,
      88,    88,    88,    88,    88,    88,    12,   105,    43,    83,
      91,    31,    92,    55,    56,    84,    85,    86,   104,    38,
      38,    96,    96,    37,    91,    37,    37,    37,    37,    37,
      37,    37,    37,    83,    92,    96,     4,     5,    34,    41,
      42,    45,    87,    93,     8,     9,    32,    33,    47,    48,
      49,    50,    51,    52,    53,    54,   101,   102,   103,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    44,    96,
      86,   104,    39,    13,    14,    94,    95,    38,    96,    39,
      96,    37,    37,    37,    37,    37,    37,    37,    41,    13,
      46,    37,     8,    13,    84,    84,    84,    84,    97,    98,
     104,     3,    81,    82,    84,    40,    95,    39,    40,    37,
      37,    13,    99,   100,   102,   103,    39,    37,    37,    96,
      37,    13,    96,    84,    98,    13,    30,    84,    95,    40,
      37,    40,    37,    37,    96,    98,    81,    95,    37,    98
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
#line 57 "nvgp4ASM.y"
    {
			if (shaderType == 0)
				t_program.VSinstructionPool.push_back(t_inst);
			else
				t_program.FSinstructionPool.push_back(t_inst);
				
			t_inst.init();
			t_operand.init();
			operandPool.clear();
		;}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 71 "nvgp4ASM.y"
    {shaderType = (yyvsp[(2) - (2)].ival);;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 102 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (5)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
	;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 108 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (5)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
	;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 114 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
		t_inst.src1 = operandPool[2];
	;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 121 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
		t_inst.src1 = operandPool[2];
	;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 128 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
		t_inst.src1 = operandPool[2];
	;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 135 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (9)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
		t_inst.src1 = operandPool[2];
		t_inst.src2 = operandPool[3];
	;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 143 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
	;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 149 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
	;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 155 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (11)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
		t_inst.src1 = operandPool[2];
		t_inst.src2 = operandPool[3];
	;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 181 "nvgp4ASM.y"
    {t_inst.opModifiers.push_back((yyvsp[(2) - (2)].ival));;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 183 "nvgp4ASM.y"
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

  case 44:

/* Line 1464 of yacc.c  */
#line 196 "nvgp4ASM.y"
    {(yyval.ival) = (yyvsp[(3) - (4)].ival);;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 204 "nvgp4ASM.y"
    {operandPool.push_back(t_operand);;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 205 "nvgp4ASM.y"
    {operandPool.push_back(t_operand);;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 208 "nvgp4ASM.y"
    {t_operand.abs = true;;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 211 "nvgp4ASM.y"
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

  case 51:

/* Line 1464 of yacc.c  */
#line 221 "nvgp4ASM.y"
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

  case 52:

/* Line 1464 of yacc.c  */
#line 236 "nvgp4ASM.y"
    {
			t_operand.id = (yyvsp[(2) - (3)].ival);
			t_operand.type = INST_REG;
			strncpy(t_operand.modifier, (yyvsp[(3) - (3)].sval), 5);
			if ((yyvsp[(1) - (3)].sval)[0] == '-')
				t_operand.inverse = true;
		;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 243 "nvgp4ASM.y"
    {
			t_operand.type = INST_CONSTANT;
			strncpy(t_operand.modifier, (yyvsp[(3) - (3)].sval), 5);
			if ((yyvsp[(1) - (3)].sval)[0] == '-')
				t_operand.inverse = true;
		;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 258 "nvgp4ASM.y"
    {operandPool.push_back(t_operand);;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 264 "nvgp4ASM.y"
    {
			t_operand.id = (yyvsp[(1) - (2)].ival);
			t_operand.type = INST_REG;
			strncpy(t_operand.modifier, (yyvsp[(2) - (2)].sval), 5);
		;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 269 "nvgp4ASM.y"
    {
			t_operand.id = 0;
			t_operand.type = INST_ATTRIB;
			strncpy(t_operand.modifier, (yyvsp[(4) - (4)].sval), 5);
		;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 274 "nvgp4ASM.y"
    {
			t_operand.id = (yyvsp[(5) - (7)].ival) + 1;
			t_operand.type = INST_ATTRIB;
			strncpy(t_operand.modifier, (yyvsp[(7) - (7)].sval), 5);
		;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 279 "nvgp4ASM.y"
    {
			t_operand.type = INST_COLOR;
			strncpy(t_operand.modifier, (yyvsp[(2) - (2)].sval), 5);
		;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 292 "nvgp4ASM.y"
    {
			t_operand.val[0] = t_operand.val[1] =
			t_operand.val[2] = t_operand.val[3] = (yyvsp[(1) - (1)].fval);
		;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 296 "nvgp4ASM.y"
    {
			t_operand.val[0] = (yyvsp[(1) - (3)].fval);
			t_operand.val[1] = t_operand.val[2] = t_operand.val[3] = (yyvsp[(3) - (3)].fval);
		;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 300 "nvgp4ASM.y"
    {
			t_operand.val[0] = (yyvsp[(1) - (5)].fval);
			t_operand.val[1] = (yyvsp[(3) - (5)].fval);
			t_operand.val[2] = t_operand.val[3] = (yyvsp[(5) - (5)].fval);
		;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 305 "nvgp4ASM.y"
    {
			t_operand.val[0] = (yyvsp[(1) - (7)].fval);
			t_operand.val[1] = (yyvsp[(3) - (7)].fval);
			t_operand.val[2] = (yyvsp[(5) - (7)].fval);
			t_operand.val[3] = (yyvsp[(7) - (7)].fval);
		;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 314 "nvgp4ASM.y"
    {(yyval.fval) = (yyvsp[(1) - (1)].ival);;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 315 "nvgp4ASM.y"
    {(yyval.fval) = (yyvsp[(1) - (1)].fval);;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 319 "nvgp4ASM.y"
    {strcpy((yyval.sval), "xyzw");;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 320 "nvgp4ASM.y"
    {strcpy((yyval.sval), (yyvsp[(2) - (2)].sval));;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 321 "nvgp4ASM.y"
    {strcpy((yyval.sval), (yyvsp[(2) - (2)].sval));;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 322 "nvgp4ASM.y"
    {strcpy((yyval.sval), (yyvsp[(2) - (2)].sval));;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 340 "nvgp4ASM.y"
    {strcpy((yyval.sval), (yyvsp[(1) - (1)].sval));;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 341 "nvgp4ASM.y"
    {strcpy((yyval.sval), (yyvsp[(1) - (1)].sval));;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 345 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'x'; (yyval.sval)[1] = '\0';;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 346 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'y'; (yyval.sval)[1] = '\0';;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 347 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'z'; (yyval.sval)[1] = '\0';;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 348 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'w'; (yyval.sval)[1] = '\0';;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 352 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'r'; (yyval.sval)[1] = '\0';;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 353 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'g'; (yyval.sval)[1] = '\0';;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 354 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'b'; (yyval.sval)[1] = '\0';;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 355 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'a'; (yyval.sval)[1] = '\0';;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 358 "nvgp4ASM.y"
    {(yyval.sval)[0] = '\0';;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 359 "nvgp4ASM.y"
    {(yyval.sval)[0] = '-'; (yyval.sval)[1] = '\0';;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 360 "nvgp4ASM.y"
    {(yyval.sval)[0] = '+'; (yyval.sval)[1] = '\0';;}
    break;



/* Line 1464 of yacc.c  */
#line 2045 "nvgp4ASM.tab.c"
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
#line 366 "nvgp4ASM.y"



