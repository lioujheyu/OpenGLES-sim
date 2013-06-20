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

/* Line 1685 of yacc.c  */
#line 17 "nvgp4ASM.y"

	int		ival;
	float	fval;
	char	sval[30];



/* Line 1685 of yacc.c  */
#line 92 "nvgp4ASM.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE nvgp4ASM_lval;


