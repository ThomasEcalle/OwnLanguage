/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

#ifndef YY_YY_MINIPSEUD_TAB_H_INCLUDED
# define YY_YY_MINIPSEUD_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

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
     PRINTLIST = 262,
     PLUS = 263,
     MIN = 264,
     MULT = 265,
     DIV = 266,
     POW = 267,
     AFF = 268,
     IF = 269,
     ELSE = 270,
     DOUBLEEQUAL = 271,
     WHILE = 272,
     DIFFERENT = 273,
     INF = 274,
     SUP = 275,
     INFOREQUAL = 276,
     SUPOREQUAL = 277,
     FOR = 278,
     FUNCTION = 279,
     COMA = 280,
     OP_PAR = 281,
     CL_PAR = 282,
     OP_BRACKET = 283,
     CL_BRACKET = 284,
     COLON = 285,
     EOL = 286,
     OR = 287,
     AND = 288,
     NEQ = 289,
     EQ = 290,
     LET = 291,
     GET = 292,
     LT = 293,
     GT = 294,
     NOT = 295,
     NEG = 296
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 17 "minipseud.y"

	struct Node *node;


/* Line 2058 of yacc.c  */
#line 103 "minipseud.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_MINIPSEUD_TAB_H_INCLUDED  */
