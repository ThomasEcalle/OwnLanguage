
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
     NUM = 258,
     VAR = 259,
     STRING = 260,
     PRINT = 261,
     PLUS = 262,
     MIN = 263,
     MULT = 264,
     DIV = 265,
     POW = 266,
     AFF = 267,
     IF = 268,
     ELSE = 269,
     DOUBLEEQUAL = 270,
     WHILE = 271,
     DIFFERENT = 272,
     INF = 273,
     SUP = 274,
     INFOREQUAL = 275,
     SUPOREQUAL = 276,
     FOR = 277,
     FUNCTION = 278,
     COMA = 279,
     OP_PAR = 280,
     CL_PAR = 281,
     OP_BRACKET = 282,
     CL_BRACKET = 283,
     COLON = 284,
     EOL = 285,
     OR = 286,
     AND = 287,
     NEQ = 288,
     EQ = 289,
     LET = 290,
     GET = 291,
     LT = 292,
     GT = 293,
     NOT = 294,
     NEG = 295
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 17 "minipseud.y"

	struct Node *node;



/* Line 1676 of yacc.c  */
#line 98 "minipseud.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


