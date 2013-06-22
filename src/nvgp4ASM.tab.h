/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1685 of yacc.c  */
#line 20 "nvgp4ASM.y"

	int		ival;
	float	fval;
	char	sval[30];



/* Line 1685 of yacc.c  */
#line 93 "nvgp4ASM.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE nvgp4ASM_lval;


