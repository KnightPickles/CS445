/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     ID = 258,
     NUMCONST = 259,
     STRINGCONST = 260,
     CHARCONST = 261,
     BOOLCONST = 262,
     BOOL = 263,
     BREAK = 264,
     CHAR = 265,
     ELSE = 266,
     FOREACH = 267,
     IF = 268,
     IN = 269,
     INT = 270,
     RETURN = 271,
     STATIC = 272,
     WHILE = 273,
     NOTEQ = 274,
     EQ = 275,
     LESSEQ = 276,
     GRTEQ = 277,
     INC = 278,
     DEC = 279,
     ADDASS = 280,
     SUBASS = 281,
     MULASS = 282,
     DIVASS = 283
   };
#endif
/* Tokens.  */
#define ID 258
#define NUMCONST 259
#define STRINGCONST 260
#define CHARCONST 261
#define BOOLCONST 262
#define BOOL 263
#define BREAK 264
#define CHAR 265
#define ELSE 266
#define FOREACH 267
#define IF 268
#define IN 269
#define INT 270
#define RETURN 271
#define STATIC 272
#define WHILE 273
#define NOTEQ 274
#define EQ 275
#define LESSEQ 276
#define GRTEQ 277
#define INC 278
#define DEC 279
#define ADDASS 280
#define SUBASS 281
#define MULASS 282
#define DIVASS 283




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 172 "c-.y"
{
    Token token; 
    TreeNode *treeNode;
    DeclType declType;
    char *cstring;
}
/* Line 1529 of yacc.c.  */
#line 112 "c-.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

