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

#include <string>
#include <cstdio>
#include "context_link_def.h"
#include "context.h"

int nvgp4ASM_lex(void);
void nvgp4ASM_error(char *s);
void nvgp4ASM_str_in(const char *s);

instruction t_inst;
operand t_operand;
std::vector<operand> operandPool;
std::vector<instruction> instructionPool;


/* Line 189 of yacc.c  */
#line 97 "nvgp4ASM.tab.c"

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
     ATTRIB = 262,
     POSITION = 263,
     RESULT_COLOR0 = 264,
     TYPE = 265,
     IDENTIFIER = 266,
     INTEGER = 267,
     FLOAT = 268,
     VECTOROP = 269,
     SCALAROP = 270,
     BINSCOP = 271,
     VECSCAOP = 272,
     BINOP = 273,
     TRIOP = 274,
     SWZOP = 275,
     TEXOP = 276,
     TXDOP = 277,
     BRAOP = 278,
     FLOWCCOP = 279,
     IFOP = 280,
     REPOP = 281,
     ENDFLOWOP = 282,
     OPMODIFIER = 283,
     TEXTARGET = 284,
     CCMASKRULE = 285,
     XYZW_SWIZZLE = 286,
     RGBA_SWIZZLE = 287,
     REG = 288
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 17 "nvgp4ASM.y"

	int		ival;
	float	fval;
	char	sval[30];



/* Line 214 of yacc.c  */
#line 174 "nvgp4ASM.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 186 "nvgp4ASM.tab.c"

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
#define YYFINAL  53
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   185

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNRULES -- Number of states.  */
#define YYNSTATES  207

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      42,    43,     2,    55,    36,    54,    37,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    35,    34,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    38,     2,    39,     2,     2,     2,    53,    52,    41,
       2,     2,     2,    51,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    50,     2,     2,     2,     2,    49,
      46,    47,    48,    44,    40,    45,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,    10,    13,    15,    17,    19,
      21,    23,    25,    27,    29,    31,    33,    35,    37,    39,
      41,    43,    45,    47,    53,    59,    67,    75,    83,    93,
     101,   109,   121,   126,   130,   134,   138,   141,   144,   145,
     148,   151,   155,   160,   161,   163,   165,   167,   172,   181,
     188,   192,   196,   198,   200,   202,   204,   207,   210,   215,
     223,   226,   230,   233,   237,   239,   243,   249,   257,   259,
     261,   262,   265,   268,   271,   279,   282,   285,   287,   289,
     291,   293,   295,   297,   299,   301,   303,   305,   307,   309,
     311,   312,   314,   316,   318
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      57,     0,    -1,    58,    57,    -1,    -1,    59,    34,    -1,
     104,    35,    -1,    60,    -1,    61,    -1,    62,    -1,    63,
      -1,    64,    -1,    65,    -1,    67,    -1,    66,    -1,    68,
      -1,    69,    -1,    70,    -1,    71,    -1,    72,    -1,    73,
      -1,    74,    -1,    75,    -1,    76,    -1,    14,    77,    86,
      36,    82,    -1,    15,    77,    86,    36,    82,    -1,    16,
      77,    86,    36,    82,    36,    82,    -1,    17,    77,    86,
      36,    82,    36,    82,    -1,    18,    77,    86,    36,    82,
      36,    82,    -1,    19,    77,    86,    36,    82,    36,    82,
      36,    82,    -1,    20,    77,    86,    36,    82,    36,    95,
      -1,    21,    77,    86,    36,    82,    36,    79,    -1,    22,
      77,    86,    36,    82,    36,    82,    36,    82,    36,    79,
      -1,    23,    77,   103,    81,    -1,    24,    77,    81,    -1,
      25,    77,    90,    -1,    26,    77,    82,    -1,    26,    77,
      -1,    27,    77,    -1,    -1,    78,    77,    -1,    37,    28,
      -1,    80,    36,    29,    -1,     3,    38,    12,    39,    -1,
      -1,    89,    -1,    83,    -1,    84,    -1,   102,    40,    84,
      40,    -1,   102,    85,    37,     7,    38,    12,    39,    94,
      -1,   102,    41,    38,    12,    39,    94,    -1,   102,    33,
      94,    -1,   102,    91,    94,    -1,     5,    -1,     4,    -1,
      87,    -1,    88,    -1,    88,    89,    -1,    33,    94,    -1,
       6,    37,     8,    94,    -1,     6,    37,     7,    38,    12,
      39,    94,    -1,     9,    94,    -1,    42,    90,    43,    -1,
      30,    94,    -1,    44,    92,    45,    -1,    93,    -1,    93,
      36,    93,    -1,    93,    36,    93,    36,    93,    -1,    93,
      36,    93,    36,    93,    36,    93,    -1,    12,    -1,    13,
      -1,    -1,    37,    99,    -1,    37,    31,    -1,    37,    32,
      -1,    96,    36,    96,    36,    96,    36,    96,    -1,   102,
      97,    -1,   102,    98,    -1,    12,    -1,   100,    -1,   101,
      -1,   100,    -1,   101,    -1,    46,    -1,    47,    -1,    48,
      -1,    49,    -1,    50,    -1,    51,    -1,    52,    -1,    53,
      -1,    -1,    54,    -1,    55,    -1,    11,    -1,    11,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    50,    50,    51,    54,    59,    64,    65,    66,    70,
      71,    72,    73,    74,    75,    76,    80,    81,    85,    86,
      87,    88,    89,    92,   100,   108,   117,   126,   135,   145,
     153,   162,   164,   166,   168,   171,   172,   175,   177,   179,
     182,   184,   191,   193,   195,   199,   200,   203,   206,   213,
     220,   227,   236,   237,   241,   242,   245,   248,   253,   257,
     262,   268,   270,   272,   275,   279,   283,   288,   297,   298,
     302,   303,   304,   305,   308,   311,   312,   316,   317,   320,
     323,   324,   328,   329,   330,   331,   335,   336,   337,   338,
     341,   342,   343,   345,   347
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TEXTURE", "VERTEX", "FRAGMENT",
  "RESULT", "ATTRIB", "POSITION", "RESULT_COLOR0", "TYPE", "IDENTIFIER",
  "INTEGER", "FLOAT", "VECTOROP", "SCALAROP", "BINSCOP", "VECSCAOP",
  "BINOP", "TRIOP", "SWZOP", "TEXOP", "TXDOP", "BRAOP", "FLOWCCOP", "IFOP",
  "REPOP", "ENDFLOWOP", "OPMODIFIER", "TEXTARGET", "CCMASKRULE",
  "XYZW_SWIZZLE", "RGBA_SWIZZLE", "REG", "';'", "':'", "','", "'.'", "'['",
  "']'", "'|'", "'c'", "'('", "')'", "'{'", "'}'", "'x'", "'y'", "'z'",
  "'w'", "'r'", "'g'", "'b'", "'a'", "'-'", "'+'", "$accept", "input",
  "line", "instruction", "ALUInstruction", "TexInstruction",
  "FlowInstruction", "VECTORop_instruction", "SCALARop_instruction",
  "BINSCop_instruction", "VECSCAop_instruction", "BINop_instruction",
  "TRIop_instruction", "SWZop_instruction", "TEXop_instruction",
  "TXDop_instruction", "BRAop_instruction", "FLOWCCop_instruction",
  "IFop_instruction", "REPop_instruction", "ENDFLOWop_instruction",
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
     285,   286,   287,   288,    59,    58,    44,    46,    91,    93,
     124,    99,    40,    41,   123,   125,   120,   121,   122,   119,
     114,   103,    98,    97,    45,    43
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    57,    58,    58,    59,    59,    59,    60,
      60,    60,    60,    60,    60,    60,    61,    61,    62,    62,
      62,    62,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    75,    76,    77,    77,
      78,    79,    80,    81,    81,    82,    82,    83,    84,    84,
      84,    84,    85,    85,    86,    86,    87,    88,    88,    88,
      88,    89,    90,    91,    92,    92,    92,    92,    93,    93,
      94,    94,    94,    94,    95,    96,    96,    97,    97,    98,
      99,    99,   100,   100,   100,   100,   101,   101,   101,   101,
     102,   102,   102,   103,   104
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     5,     7,     7,     7,     9,     7,
       7,    11,     4,     3,     3,     3,     2,     2,     0,     2,
       2,     3,     4,     0,     1,     1,     1,     4,     8,     6,
       3,     3,     1,     1,     1,     1,     2,     2,     4,     7,
       2,     3,     2,     3,     1,     3,     5,     7,     1,     1,
       0,     2,     2,     2,     7,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    94,    38,    38,    38,    38,    38,    38,    38,    38,
      38,    38,    38,    38,    38,    38,     0,     3,     0,     6,
       7,     8,     9,    10,    11,    13,    12,    14,    15,    16,
      17,    18,    19,    20,    21,    22,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    43,
       0,    90,    37,     1,     2,     4,     5,    40,     0,    70,
      70,     0,    54,    55,    39,     0,     0,     0,     0,     0,
       0,     0,     0,    93,    43,     0,    33,    44,    70,    34,
      91,    92,    35,    45,    46,     0,     0,     0,    60,    57,
      90,    56,    90,    90,    90,    90,    90,    90,    90,    90,
      32,     0,    62,    53,    52,    70,    90,     0,     0,     0,
      70,     0,    70,    72,    73,    82,    83,    84,    85,    86,
      87,    88,    89,    71,    80,    81,    23,    24,     0,     0,
       0,     0,     0,     0,     0,    61,    50,     0,     0,     0,
      68,    69,     0,    64,     0,    51,     0,    58,    90,    90,
      90,    90,    90,     0,    90,    47,     0,    63,     0,     0,
       0,    25,    26,    27,     0,    29,     0,     0,     0,    30,
       0,     0,    70,    65,     0,    70,    90,    90,    77,    75,
      76,    78,    79,     0,     0,    90,    49,     0,     0,    59,
      28,     0,     0,    41,     0,    66,    70,    90,    42,     0,
       0,    48,     0,    31,    67,    90,    74
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    38,    39,   169,   170,    76,    82,    83,    84,   109,
      61,    62,    63,    77,    79,   110,   142,   143,    88,   165,
     166,   179,   180,   123,   124,   125,    85,    74,    36
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -175
static const yytype_int16 yypact[] =
{
     123,  -175,   -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,
     -22,   -22,   -22,   -22,   -22,   -22,    17,   123,    -8,  -175,
    -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,  -175,    -5,    -1,     7,   -22,
       7,     7,     7,     7,     7,     7,     7,     7,    25,    -4,
      12,   -20,  -175,  -175,  -175,  -175,  -175,  -175,     0,     6,
       6,     8,  -175,    -4,  -175,    10,    13,    22,    28,    31,
      33,    34,    35,  -175,    -4,    12,  -175,  -175,     6,  -175,
    -175,  -175,  -175,  -175,  -175,    15,    14,    55,  -175,  -175,
     -30,  -175,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,
    -175,    38,  -175,  -175,  -175,     6,   -30,    44,    20,    16,
       6,    45,     6,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,    48,    49,
      53,    54,    57,    58,    59,  -175,  -175,    11,    24,    79,
    -175,  -175,    51,    62,    92,  -175,    97,  -175,   -30,   -30,
     -30,   -30,   -30,   107,   -30,  -175,    72,  -175,    20,    75,
      90,  -175,  -175,  -175,    78,  -175,    94,    27,    93,  -175,
      96,    99,     6,   115,   121,     6,   -30,   -30,  -175,  -175,
    -175,  -175,  -175,   141,   133,   -30,  -175,    20,   124,  -175,
    -175,   128,   126,  -175,   130,   131,     6,   -30,  -175,   107,
      20,  -175,   132,  -175,  -175,   -30,  -175
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -175,   152,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,  -175,
    -175,   113,  -175,   -29,  -175,    98,   -88,  -175,    65,  -175,
     114,  -175,  -175,   110,   100,  -175,  -175,  -146,   -60,  -175,
    -174,  -175,  -175,  -175,     9,    18,  -105,  -175,  -175
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -37
static const yytype_int16 yytable[] =
{
      89,   138,   126,   191,   127,   128,   129,   130,   131,   132,
     133,   134,   173,    58,   -36,    37,    59,    53,   102,   103,
     104,   111,   112,   202,    80,    81,    55,    57,   103,   104,
      56,   206,   140,   141,    80,    81,    73,    86,    75,   178,
      60,   195,    78,    87,    90,   136,    92,   167,   105,    93,
     145,   155,   147,   144,   204,   106,   107,   105,    94,   108,
     161,   162,   163,   164,    95,   107,   171,    96,   108,    97,
      98,    99,   167,   115,   116,   117,   118,   119,   120,   121,
     122,   135,   139,   146,   148,   149,   113,   114,   190,   150,
     151,   156,   167,   152,   153,   154,   157,   194,   158,   159,
     167,   115,   116,   117,   118,   119,   120,   121,   122,   160,
     168,   172,   186,   174,   176,   189,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,   175,
     177,   183,   184,   188,     1,   185,   201,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,   187,    64,   192,    65,    66,    67,    68,    69,    70,
      71,    72,   193,   196,   197,   198,   199,   200,   205,    54,
     203,   137,   100,    91,     0,   101,   181,     0,     0,     0,
       0,     0,     0,     0,     0,   182
};

static const yytype_int16 yycheck[] =
{
      60,   106,    90,   177,    92,    93,    94,    95,    96,    97,
      98,    99,   158,     6,    34,    37,     9,     0,    78,     4,
       5,     7,     8,   197,    54,    55,    34,    28,     4,     5,
      35,   205,    12,    13,    54,    55,    11,    37,    42,    12,
      33,   187,    30,    37,    36,   105,    36,   152,    33,    36,
     110,    40,   112,    37,   200,    40,    41,    33,    36,    44,
     148,   149,   150,   151,    36,    41,   154,    36,    44,    36,
      36,    36,   177,    46,    47,    48,    49,    50,    51,    52,
      53,    43,    38,    38,    36,    36,    31,    32,   176,    36,
      36,    12,   197,    36,    36,    36,    45,   185,    36,     7,
     205,    46,    47,    48,    49,    50,    51,    52,    53,    12,
       3,    39,   172,    38,    36,   175,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    39,
      36,    38,    36,    12,    11,    36,   196,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    36,    39,    12,    40,    41,    42,    43,    44,    45,
      46,    47,    29,    39,    36,    39,    36,    36,    36,    17,
     199,   106,    74,    63,    -1,    75,   167,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   167
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    11,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,   104,    37,    77,    78,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,     0,    57,    34,    35,    28,     6,     9,
      33,    86,    87,    88,    77,    86,    86,    86,    86,    86,
      86,    86,    86,    11,   103,    42,    81,    89,    30,    90,
      54,    55,    82,    83,    84,   102,    37,    37,    94,    94,
      36,    89,    36,    36,    36,    36,    36,    36,    36,    36,
      81,    90,    94,     4,     5,    33,    40,    41,    44,    85,
      91,     7,     8,    31,    32,    46,    47,    48,    49,    50,
      51,    52,    53,    99,   100,   101,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    43,    94,    84,   102,    38,
      12,    13,    92,    93,    37,    94,    38,    94,    36,    36,
      36,    36,    36,    36,    36,    40,    12,    45,    36,     7,
      12,    82,    82,    82,    82,    95,    96,   102,     3,    79,
      80,    82,    39,    93,    38,    39,    36,    36,    12,    97,
      98,   100,   101,    38,    36,    36,    94,    36,    12,    94,
      82,    96,    12,    29,    82,    93,    39,    36,    39,    36,
      36,    94,    96,    79,    93,    36,    96
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
        case 4:

/* Line 1464 of yacc.c  */
#line 54 "nvgp4ASM.y"
    {
			t_inst.init();
			t_operand.init();
			operandPool.clear();
		;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 92 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (5)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];

		t_inst.print();
	;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 100 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (5)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];

		t_inst.print();
	;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 108 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
		t_inst.src1 = operandPool[2];

		t_inst.print();
	;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 117 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
		t_inst.src1 = operandPool[2];

		t_inst.print();
	;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 126 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
		t_inst.src1 = operandPool[2];

		t_inst.print();
	;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 135 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (9)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
		t_inst.src1 = operandPool[2];
		t_inst.src2 = operandPool[3];

		t_inst.print();
	;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 145 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];

		t_inst.print();
	;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 153 "nvgp4ASM.y"
    {
		t_inst.op = (yyvsp[(1) - (7)].ival);
		t_inst.dst = operandPool[0];
		t_inst.src0 = operandPool[1];
		t_inst.src1 = operandPool[2];

		t_inst.print();
	;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 182 "nvgp4ASM.y"
    {t_inst.opModifiers.push_back((yyvsp[(2) - (2)].ival));;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 184 "nvgp4ASM.y"
    {
		t_operand.id = (yyvsp[(1) - (3)].ival);
		t_operand.type = INST_TEXTURE;
		t_operand.val[0] = (yyvsp[(3) - (3)].ival);
		operandPool.push_back(t_operand);
	;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 191 "nvgp4ASM.y"
    {(yyval.ival) = (yyvsp[(3) - (4)].ival);;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 199 "nvgp4ASM.y"
    {operandPool.push_back(t_operand);;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 200 "nvgp4ASM.y"
    {operandPool.push_back(t_operand);;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 203 "nvgp4ASM.y"
    {t_operand.abs = true;;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 206 "nvgp4ASM.y"
    {
			t_operand.id = (yyvsp[(6) - (8)].ival);
			t_operand.type = INST_ATTRIB;
			strncpy(t_operand.modifier, (yyvsp[(8) - (8)].sval), 5);
			if ((yyvsp[(1) - (8)].sval)[0] == '-')
				t_operand.inverse = true;
		;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 213 "nvgp4ASM.y"
    {
			t_operand.id = (yyvsp[(4) - (6)].ival);
			t_operand.type = INST_UNIFORM;
			strncpy(t_operand.modifier, (yyvsp[(6) - (6)].sval), 5);
			if ((yyvsp[(1) - (6)].sval)[0] == '-')
				t_operand.inverse = true;
		;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 220 "nvgp4ASM.y"
    {
			t_operand.id = (yyvsp[(2) - (3)].ival);
			t_operand.type = INST_REG;
			strncpy(t_operand.modifier, (yyvsp[(3) - (3)].sval), 5);
			if ((yyvsp[(1) - (3)].sval)[0] == '-')
				t_operand.inverse = true;
		;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 227 "nvgp4ASM.y"
    {
			t_operand.type = INST_CONSTANT;
			strncpy(t_operand.modifier, (yyvsp[(3) - (3)].sval), 5);
			if ((yyvsp[(1) - (3)].sval)[0] == '-')
				t_operand.inverse = true;
		;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 242 "nvgp4ASM.y"
    {operandPool.push_back(t_operand);;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 248 "nvgp4ASM.y"
    {
			t_operand.id = (yyvsp[(1) - (2)].ival);
			t_operand.type = INST_REG;
			strncpy(t_operand.modifier, (yyvsp[(2) - (2)].sval), 5);
		;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 253 "nvgp4ASM.y"
    {
			t_operand.type = INST_POSITION;
			strncpy(t_operand.modifier, (yyvsp[(4) - (4)].sval), 5);
		;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 257 "nvgp4ASM.y"
    {
			t_operand.id = (yyvsp[(5) - (7)].ival);
			t_operand.type = INST_ATTRIB;
			strncpy(t_operand.modifier, (yyvsp[(7) - (7)].sval), 5);
		;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 262 "nvgp4ASM.y"
    {
			t_operand.type = INST_COLOR;
			strncpy(t_operand.modifier, (yyvsp[(2) - (2)].sval), 5);
		;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 275 "nvgp4ASM.y"
    {
			t_operand.val[0] = t_operand.val[1] =
			t_operand.val[2] = t_operand.val[3] = (yyvsp[(1) - (1)].fval);
		;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 279 "nvgp4ASM.y"
    {
			t_operand.val[0] = (yyvsp[(1) - (3)].fval);
			t_operand.val[1] = t_operand.val[2] = t_operand.val[3] = (yyvsp[(3) - (3)].fval);
		;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 283 "nvgp4ASM.y"
    {
			t_operand.val[0] = (yyvsp[(1) - (5)].fval);
			t_operand.val[1] = (yyvsp[(3) - (5)].fval);
			t_operand.val[2] = t_operand.val[3] = (yyvsp[(5) - (5)].fval);
		;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 288 "nvgp4ASM.y"
    {
			t_operand.val[0] = (yyvsp[(1) - (7)].fval);
			t_operand.val[1] = (yyvsp[(3) - (7)].fval);
			t_operand.val[2] = (yyvsp[(5) - (7)].fval);
			t_operand.val[3] = (yyvsp[(7) - (7)].fval);
		;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 297 "nvgp4ASM.y"
    {(yyval.fval) = (yyvsp[(1) - (1)].ival);;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 298 "nvgp4ASM.y"
    {(yyval.fval) = (yyvsp[(1) - (1)].fval);;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 302 "nvgp4ASM.y"
    {strcpy((yyval.sval), "xyzw");;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 303 "nvgp4ASM.y"
    {strcpy((yyval.sval), (yyvsp[(2) - (2)].sval));;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 304 "nvgp4ASM.y"
    {strcpy((yyval.sval), (yyvsp[(2) - (2)].sval));;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 305 "nvgp4ASM.y"
    {strcpy((yyval.sval), (yyvsp[(2) - (2)].sval));;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 323 "nvgp4ASM.y"
    {strcpy((yyval.sval), (yyvsp[(1) - (1)].sval));;}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 324 "nvgp4ASM.y"
    {strcpy((yyval.sval), (yyvsp[(1) - (1)].sval));;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 328 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'x'; (yyval.sval)[1] = '\0';;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 329 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'y'; (yyval.sval)[1] = '\0';;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 330 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'z'; (yyval.sval)[1] = '\0';;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 331 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'w'; (yyval.sval)[1] = '\0';;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 335 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'r'; (yyval.sval)[1] = '\0';;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 336 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'g'; (yyval.sval)[1] = '\0';;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 337 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'b'; (yyval.sval)[1] = '\0';;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 338 "nvgp4ASM.y"
    {(yyval.sval)[0] = 'a'; (yyval.sval)[1] = '\0';;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 341 "nvgp4ASM.y"
    {(yyval.sval)[0] = '\0';;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 342 "nvgp4ASM.y"
    {(yyval.sval)[0] = '-'; (yyval.sval)[1] = '\0';;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 343 "nvgp4ASM.y"
    {(yyval.sval)[0] = '+'; (yyval.sval)[1] = '\0';;}
    break;



/* Line 1464 of yacc.c  */
#line 2014 "nvgp4ASM.tab.c"
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
#line 349 "nvgp4ASM.y"



