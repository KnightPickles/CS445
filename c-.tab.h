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
     OP = 263,
     ERROR = 264,
     BOOL = 265,
     BREAK = 266,
     CHAR = 267,
     ELSE = 268,
     FOREACH = 269,
     IF = 270,
     IN = 271,
     INT = 272,
     RETURN = 273,
     STATIC = 274,
     WHILE = 275,
     ASSIGN = 276,
     NOTEQ = 277,
     EQ = 278,
     LESSEQ = 279,
     LESS = 280,
     GRTEQ = 281,
     GRT = 282,
     INC = 283,
     DEC = 284,
     ADDASS = 285,
     ADD = 286,
     SUBASS = 287,
     SUB = 288,
     MULASS = 289,
     MUL = 290,
     DIVASS = 291,
     DIV = 292,
     OPAREN = 293,
     CPAREN = 294,
     OBRACE = 295,
     CBRACE = 296,
     OBRAK = 297,
     CBRAK = 298,
     COMMA = 299,
     COLON = 300,
     SEMI = 301,
     MOD = 302,
     QUE = 303,
     AND = 304,
     OR = 305,
     NOT = 306
   };
#endif
/* Tokens.  */
#define ID 258
#define NUMCONST 259
#define STRINGCONST 260
#define CHARCONST 261
#define BOOLCONST 262
#define OP 263
#define ERROR 264
#define BOOL 265
#define BREAK 266
#define CHAR 267
#define ELSE 268
#define FOREACH 269
#define IF 270
#define IN 271
#define INT 272
#define RETURN 273
#define STATIC 274
#define WHILE 275
#define ASSIGN 276
#define NOTEQ 277
#define EQ 278
#define LESSEQ 279
#define LESS 280
#define GRTEQ 281
#define GRT 282
#define INC 283
#define DEC 284
#define ADDASS 285
#define ADD 286
#define SUBASS 287
#define SUB 288
#define MULASS 289
#define MUL 290
#define DIVASS 291
#define DIV 292
#define OPAREN 293
#define CPAREN 294
#define OBRACE 295
#define CBRACE 296
#define OBRAK 297
#define CBRAK 298
#define COMMA 299
#define COLON 300
#define SEMI 301
#define MOD 302
#define QUE 303
#define AND 304
#define OR 305
#define NOT 306




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 38 "c-.y"
{
    Token token; 
    TreeNode *treeNode;
    DeclType integer;
    char *string;
}
/* Line 1529 of yacc.c.  */
#line 158 "c-.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

