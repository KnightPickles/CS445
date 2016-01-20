/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "c-.y"

// c-.y CS445 Zachary Yama

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <getopt.h>
#include "util.h"
#include "tokenClass.h"
#define YYERROR_VERBOSE

extern int yylineno;
extern int yylex();
extern FILE *yyin;

static char *assignName;
static int lineno;
static TreeNode *syntaxTree;

void yyerror(const char *msg) {
    printf("Line %i: %s\n", yylineno, msg);
    exit(-1);
}

// Check length of specific chars in the most brutal way possible. 
void charerror(const char *rtxt) {
    int len = strlen(rtxt);
    if(len == 4 && rtxt[1] == '\\') {
        len -= 1;
    }
    if(len - 2 != 1) {
        printf("ERROR(%u): character is %u characters and not a single character: %s\n", yylineno, (unsigned)strlen(rtxt) - 2, rtxt);
    } 
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 38 "c-.y"
{
    Token token; 
    TreeNode *treeNode;
    DeclType integer;
    char *string;
}
/* Line 193 of yacc.c.  */
#line 242 "c-.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 255 "c-.tab.c"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   215

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNRULES -- Number of states.  */
#define YYNSTATES  172

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    18,    22,
      26,    28,    30,    34,    36,    41,    44,    46,    48,    50,
      52,    59,    65,    67,    68,    72,    74,    77,    81,    83,
      85,    89,    91,    93,    95,    97,    99,   101,   103,   105,
     107,   109,   114,   117,   118,   121,   122,   125,   127,   135,
     143,   149,   155,   163,   169,   177,   180,   184,   187,   191,
     195,   199,   203,   207,   210,   213,   215,   219,   221,   225,
     227,   230,   232,   236,   238,   240,   242,   244,   246,   248,
     250,   254,   256,   258,   260,   264,   266,   268,   270,   272,
     275,   277,   279,   281,   283,   285,   287,   289,   294,   298,
     300,   302,   307,   309,   310,   314,   316,   318,   320,   322
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      53,     0,    -1,    54,    -1,    54,    55,    -1,    55,    -1,
      56,    -1,    63,    -1,    62,    58,    46,    -1,    61,    58,
      46,    -1,    58,    44,    59,    -1,    59,    -1,    60,    -1,
      60,    45,    83,    -1,     3,    -1,     3,    42,     4,    43,
      -1,    19,    62,    -1,    62,    -1,    17,    -1,    10,    -1,
      12,    -1,    62,     3,    38,    64,    39,    69,    -1,     3,
      38,    64,    39,    69,    -1,    65,    -1,    -1,    65,    46,
      66,    -1,    66,    -1,    62,    67,    -1,    67,    44,    68,
      -1,    68,    -1,     3,    -1,     3,    42,    43,    -1,    71,
      -1,    70,    -1,    76,    -1,    78,    -1,    75,    -1,    72,
      -1,    80,    -1,    81,    -1,    77,    -1,    79,    -1,    40,
      73,    74,    41,    -1,    73,    57,    -1,    -1,    74,    69,
      -1,    -1,    82,    46,    -1,    46,    -1,    15,    38,    83,
      39,    70,    13,    70,    -1,    15,    38,    83,    39,    70,
      13,    71,    -1,    15,    38,    83,    39,    69,    -1,    20,
      38,    83,    39,    70,    -1,    14,    38,    95,    16,    83,
      39,    70,    -1,    20,    38,    83,    39,    71,    -1,    14,
      38,    95,    16,    83,    39,    71,    -1,    18,    46,    -1,
      18,    82,    46,    -1,    11,    46,    -1,    95,    21,    82,
      -1,    95,    30,    82,    -1,    95,    32,    82,    -1,    95,
      34,    82,    -1,    95,    36,    82,    -1,    95,    28,    -1,
      95,    29,    -1,    83,    -1,    83,    50,    84,    -1,    84,
      -1,    84,    49,    85,    -1,    85,    -1,    51,    85,    -1,
      86,    -1,    88,    87,    88,    -1,    88,    -1,    24,    -1,
      25,    -1,    27,    -1,    26,    -1,    23,    -1,    22,    -1,
      88,    89,    90,    -1,    90,    -1,    31,    -1,    33,    -1,
      90,    91,    92,    -1,    92,    -1,    35,    -1,    37,    -1,
      47,    -1,    93,    92,    -1,    94,    -1,    33,    -1,    35,
      -1,    48,    -1,    96,    -1,    95,    -1,     3,    -1,     3,
      42,    82,    43,    -1,    38,    82,    39,    -1,    97,    -1,
     100,    -1,     3,    38,    98,    39,    -1,    99,    -1,    -1,
      99,    44,    82,    -1,    82,    -1,     4,    -1,     6,    -1,
       5,    -1,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   117,   117,   122,   132,   135,   136,   141,   156,   171,
     181,   184,   185,   191,   195,   203,   208,   214,   215,   216,
     220,   229,   239,   240,   243,   253,   256,   270,   280,   283,
     287,   296,   297,   300,   301,   302,   303,   304,   305,   308,
     309,   312,   320,   330,   333,   343,   346,   347,   350,   360,
     368,   377,   384,   394,   401,   411,   415,   422,   430,   436,
     442,   448,   454,   460,   465,   470,   473,   479,   482,   488,
     491,   496,   499,   505,   508,   509,   510,   511,   512,   513,
     516,   522,   525,   526,   529,   535,   538,   539,   540,   543,
     548,   551,   552,   553,   556,   557,   560,   564,   571,   572,
     573,   576,   583,   584,   587,   597,   600,   605,   610,   615
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "NUMCONST", "STRINGCONST",
  "CHARCONST", "BOOLCONST", "OP", "ERROR", "BOOL", "BREAK", "CHAR", "ELSE",
  "FOREACH", "IF", "IN", "INT", "RETURN", "STATIC", "WHILE", "ASSIGN",
  "NOTEQ", "EQ", "LESSEQ", "LESS", "GRTEQ", "GRT", "INC", "DEC", "ADDASS",
  "ADD", "SUBASS", "SUB", "MULASS", "MUL", "DIVASS", "DIV", "OPAREN",
  "CPAREN", "OBRACE", "CBRACE", "OBRAK", "CBRAK", "COMMA", "COLON", "SEMI",
  "MOD", "QUE", "AND", "OR", "NOT", "$accept", "program",
  "declaration_list", "declaration", "var_declaration",
  "scoped_var_declaration", "var_decl_list", "var_decl_initialize",
  "var_decl_id", "scoped_type_specifier", "type_specifier",
  "fun_declaration", "params", "param_list", "param_type_list",
  "param_id_list", "param_id", "statement", "matched", "unmatched",
  "compound_stmt", "local_declarations", "statement_list",
  "expression_stmt", "matched_selection", "unmatched_selection",
  "matched_iteration", "unmatched_iteration", "return_stmt", "break_stmt",
  "expression", "simple_expression", "and_expression",
  "unary_rel_expression", "rel_expression", "relop", "sum_expression",
  "sumop", "term", "mulop", "unary_expression", "unaryop", "factor",
  "mutable", "immutable", "call", "args", "arg_list", "constant", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    54,    54,    55,    55,    56,    57,    58,
      58,    59,    59,    60,    60,    61,    61,    62,    62,    62,
      63,    63,    64,    64,    65,    65,    66,    67,    67,    68,
      68,    69,    69,    70,    70,    70,    70,    70,    70,    71,
      71,    72,    73,    73,    74,    74,    75,    75,    76,    77,
      77,    78,    78,    79,    79,    80,    80,    81,    82,    82,
      82,    82,    82,    82,    82,    82,    83,    83,    84,    84,
      85,    85,    86,    86,    87,    87,    87,    87,    87,    87,
      88,    88,    89,    89,    90,    90,    91,    91,    91,    92,
      92,    93,    93,    93,    94,    94,    95,    95,    96,    96,
      96,    97,    98,    98,    99,    99,   100,   100,   100,   100
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     3,     3,
       1,     1,     3,     1,     4,     2,     1,     1,     1,     1,
       6,     5,     1,     0,     3,     1,     2,     3,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     2,     0,     2,     0,     2,     1,     7,     7,
       5,     5,     7,     5,     7,     2,     3,     2,     3,     3,
       3,     3,     3,     2,     2,     1,     3,     1,     3,     1,
       2,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     3,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     4,     3,     1,
       1,     4,     1,     0,     3,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    18,    19,    17,     0,     2,     4,     5,     0,
       6,    23,     1,     3,    13,     0,    10,    11,     0,     0,
      22,    25,    23,     0,     0,     7,     0,    29,    26,    28,
       0,     0,     0,     0,    13,     9,    96,   106,   108,   107,
     109,    91,    92,     0,    93,     0,    12,    67,    69,    71,
      73,    81,    85,     0,    90,    95,    94,    99,   100,     0,
       0,     0,     0,     0,     0,     0,    43,    47,    21,    32,
      31,    36,    35,    33,    39,    34,    40,    37,    38,     0,
      65,    95,    24,     0,    14,   103,     0,     0,    70,     0,
       0,    79,    78,    74,    75,    77,    76,    82,    83,     0,
       0,    86,    87,    88,     0,    89,    30,    27,    57,     0,
       0,    55,     0,     0,    45,    46,     0,    63,    64,     0,
       0,     0,     0,    20,   105,     0,   102,     0,    98,    66,
      68,    72,    80,    84,    96,     0,     0,    56,     0,     0,
      42,     0,    16,     0,    58,    59,    60,    61,    62,   101,
       0,    97,     0,     0,     0,    15,     0,    41,    44,   104,
       0,    50,    32,    51,    53,     8,     0,     0,    52,    54,
      48,    49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,     7,     8,   140,    15,    16,    17,   141,
      18,    10,    19,    20,    21,    28,    29,    68,    69,    70,
      71,   114,   143,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    47,    48,    49,    99,    50,   100,    51,   104,
      52,    53,    54,    81,    56,    57,   125,   126,    58
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -114
static const yytype_int16 yypact[] =
{
      23,    -9,  -114,  -114,  -114,    13,    23,  -114,  -114,    11,
    -114,    81,  -114,  -114,   -21,    50,  -114,    -2,    48,    21,
      26,  -114,    81,    72,    84,  -114,   153,    53,    56,  -114,
      98,    81,    68,    67,    77,  -114,    29,  -114,  -114,  -114,
    -114,  -114,  -114,   153,  -114,   153,    76,    83,  -114,  -114,
     154,    31,  -114,   167,  -114,  -114,  -114,  -114,  -114,    82,
      48,    88,    91,    92,   117,    97,  -114,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,    94,
      76,     2,  -114,    98,  -114,   153,   153,   102,  -114,   153,
     153,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,   167,
     167,  -114,  -114,  -114,   167,  -114,  -114,  -114,  -114,   134,
     153,  -114,    96,   153,    80,  -114,   153,  -114,  -114,   153,
     153,   153,   153,  -114,  -114,   104,   101,   105,  -114,    83,
    -114,    75,    31,  -114,   109,   131,   -23,  -114,    19,    81,
    -114,    84,  -114,     4,  -114,  -114,  -114,  -114,  -114,  -114,
     153,  -114,   153,    98,    98,  -114,    71,  -114,  -114,  -114,
      20,  -114,   140,  -114,  -114,  -114,    98,    98,  -114,  -114,
    -114,  -114
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -114,  -114,  -114,   148,  -114,  -114,    25,   137,  -114,  -114,
       0,  -114,   142,  -114,   136,  -114,   115,   -80,  -105,  -113,
    -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,  -114,
     -39,   -24,    73,   -33,  -114,  -114,    70,  -114,    89,  -114,
     -48,  -114,  -114,   -25,  -114,  -114,  -114,  -114,  -114
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
       9,    55,    46,   123,    87,   105,     9,    36,    37,    38,
      39,    40,    88,    12,    14,    61,   153,    22,    62,    63,
      55,    23,    64,   116,    65,   112,     1,    89,    55,    11,
     117,   118,   119,     2,   120,     3,   121,    41,   122,    42,
       4,   164,    43,    26,    66,   157,   124,   127,   162,   163,
      67,    27,    44,   169,   171,    45,   133,   130,   154,   166,
      30,   168,   170,   158,    55,    55,   101,    85,   102,    89,
      89,    86,    31,   161,    55,    55,    33,   144,   103,    55,
     145,   146,   147,   148,   135,    55,   136,    34,    55,   138,
       2,     2,     3,     3,    24,    59,    25,     4,     4,   139,
      60,    36,    37,    38,    39,    40,    97,    83,    98,    61,
      84,   159,    62,    63,   142,    24,    64,   165,    65,    23,
      36,    37,    38,    39,    40,   106,    89,    55,   160,   109,
     110,    41,    90,    42,   108,   113,    43,   134,    66,   155,
     115,   128,   137,   149,    67,   150,    44,   152,   151,    45,
      41,    86,    42,   167,    13,    43,    36,    37,    38,    39,
      40,    35,   129,   111,    32,    44,   156,    82,    45,   131,
      36,    37,    38,    39,    40,   107,    91,    92,    93,    94,
      95,    96,     0,     0,     0,    97,    41,    98,    42,   132,
       0,    43,     0,     0,     0,     0,     0,     0,     0,     0,
      41,    44,    42,     0,    45,    43,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    44
};

static const yytype_int16 yycheck[] =
{
       0,    26,    26,    83,    43,    53,     6,     3,     4,     5,
       6,     7,    45,     0,     3,    11,    39,    38,    14,    15,
      45,    42,    18,    21,    20,    64,     3,    50,    53,    38,
      28,    29,    30,    10,    32,    12,    34,    33,    36,    35,
      17,   154,    38,    45,    40,    41,    85,    86,   153,   154,
      46,     3,    48,   166,   167,    51,   104,    90,    39,    39,
      39,   166,   167,   143,    89,    90,    35,    38,    37,    50,
      50,    42,    46,   153,    99,   100,     4,   116,    47,   104,
     119,   120,   121,   122,   109,   110,   110,     3,   113,   113,
      10,    10,    12,    12,    44,    42,    46,    17,    17,    19,
      44,     3,     4,     5,     6,     7,    31,    39,    33,    11,
      43,   150,    14,    15,   114,    44,    18,    46,    20,    42,
       3,     4,     5,     6,     7,    43,    50,   152,   152,    38,
      38,    33,    49,    35,    46,    38,    38,     3,    40,   139,
      46,    39,    46,    39,    46,    44,    48,    16,    43,    51,
      33,    42,    35,    13,     6,    38,     3,     4,     5,     6,
       7,    24,    89,    46,    22,    48,   141,    31,    51,    99,
       3,     4,     5,     6,     7,    60,    22,    23,    24,    25,
      26,    27,    -1,    -1,    -1,    31,    33,    33,    35,   100,
      -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    48,    35,    -1,    51,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    10,    12,    17,    53,    54,    55,    56,    62,
      63,    38,     0,    55,     3,    58,    59,    60,    62,    64,
      65,    66,    38,    42,    44,    46,    45,     3,    67,    68,
      39,    46,    64,     4,     3,    59,     3,     4,     5,     6,
       7,    33,    35,    38,    48,    51,    83,    84,    85,    86,
      88,    90,    92,    93,    94,    95,    96,    97,   100,    42,
      44,    11,    14,    15,    18,    20,    40,    46,    69,    70,
      71,    72,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    95,    66,    39,    43,    38,    42,    82,    85,    50,
      49,    22,    23,    24,    25,    26,    27,    31,    33,    87,
      89,    35,    37,    47,    91,    92,    43,    68,    46,    38,
      38,    46,    82,    38,    73,    46,    21,    28,    29,    30,
      32,    34,    36,    69,    82,    98,    99,    82,    39,    84,
      85,    88,    90,    92,     3,    95,    83,    46,    83,    19,
      57,    61,    62,    74,    82,    82,    82,    82,    82,    39,
      44,    43,    16,    39,    39,    62,    58,    41,    69,    82,
      83,    69,    70,    70,    71,    46,    39,    13,    70,    71,
      70,    71
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
        case 2:
#line 117 "c-.y"
    { 
                                syntaxTree = (yyvsp[(1) - (1)].treeNode);
                            ;}
    break;

  case 3:
#line 122 "c-.y"
    {
                               TreeNode *trav = (yyvsp[(1) - (2)].treeNode);
                               if(trav != NULL) {
                                   while (trav -> sibling != NULL) trav = trav -> sibling;
                                   trav -> sibling = (yyvsp[(2) - (2)].treeNode);
                                   (yyval.treeNode) = (yyvsp[(1) - (2)].treeNode);
                               } else {
                                   (yyval.treeNode) = (yyvsp[(2) - (2)].treeNode);
                               }
                            ;}
    break;

  case 4:
#line 132 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 5:
#line 135 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 6:
#line 136 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 7:
#line 141 "c-.y"
    {
                                TreeNode *complete = (yyvsp[(2) - (3)].treeNode);
                                if(complete != NULL) {
                                    do {
                                        complete -> declType = (yyvsp[(1) - (3)].integer);
                                        complete = complete -> sibling;

                                    } while(complete != NULL);
                                    (yyval.treeNode) = (yyvsp[(2) - (3)].treeNode);
                                } else {
                                    (yyval.treeNode) = NULL;
                                }
                            ;}
    break;

  case 8:
#line 156 "c-.y"
    {
                                TreeNode *complete = (yyvsp[(2) - (3)].treeNode);
                                if(complete != NULL) {
                                    do {
                                        complete -> declType = (yyvsp[(1) - (3)].treeNode) -> declType;
                                        complete -> isStatic = (yyvsp[(1) - (3)].treeNode) -> isStatic;
                                        complete = complete -> sibling;
                                    } while(complete != NULL); 
                                    (yyval.treeNode) = (yyvsp[(2) - (3)].treeNode);
                                } else {
                                    (yyval.treeNode) = NULL;
                                }
                            ;}
    break;

  case 9:
#line 171 "c-.y"
    {
                               TreeNode *trav = (yyvsp[(1) - (3)].treeNode);
                               if(trav != NULL) {
                                    while(trav -> sibling != NULL) trav = trav -> sibling;
                                    trav -> sibling = (yyvsp[(3) - (3)].treeNode); 
                                    (yyval.treeNode) = (yyvsp[(1) - (3)].treeNode); 
                                } else {
                                    (yyval.treeNode) = (yyvsp[(3) - (3)].treeNode);
                                }
                            ;}
    break;

  case 10:
#line 181 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 11:
#line 184 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 12:
#line 185 "c-.y"
    {
                                (yyvsp[(1) - (3)].treeNode) -> child[0] = (yyvsp[(3) - (3)].treeNode); // <- NOT NULL, SHOULD BE $3
                                (yyval.treeNode) = (yyvsp[(1) - (3)].treeNode);  
                            ;}
    break;

  case 13:
#line 191 "c-.y"
    { 
                                (yyval.treeNode) = newDeclNode(VarK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(1) - (1)].token.value.sval);
                            ;}
    break;

  case 14:
#line 195 "c-.y"
    {
                                (yyval.treeNode) = newDeclNode(VarK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(1) - (4)].token.value.sval); 
                                (yyval.treeNode) -> isArray = true;
                                (yyval.treeNode) -> arrayLen = (yyvsp[(3) - (4)].token.value.ival);
                            ;}
    break;

  case 15:
#line 203 "c-.y"
    {
                                (yyval.treeNode) = newDeclNode(VarK);
                                (yyval.treeNode) -> isStatic = true;
                                (yyval.treeNode) -> declType = (yyvsp[(2) - (2)].integer);
                            ;}
    break;

  case 16:
#line 208 "c-.y"
    {
                                (yyval.treeNode) = newDeclNode(VarK);
                                (yyval.treeNode) -> declType = (yyvsp[(1) - (1)].integer);
                            ;}
    break;

  case 17:
#line 214 "c-.y"
    { (yyval.integer) = Int; ;}
    break;

  case 18:
#line 215 "c-.y"
    { (yyval.integer) = Bool; ;}
    break;

  case 19:
#line 216 "c-.y"
    { (yyval.integer) = Char; ;}
    break;

  case 20:
#line 220 "c-.y"
    {
                                (yyval.treeNode) = newDeclNode(FuncK);
                                (yyval.treeNode) -> declType = (yyvsp[(1) - (6)].integer);  
                                (yyval.treeNode) -> attr.name = (yyvsp[(2) - (6)].token.value.sval);
                                (yyval.treeNode) -> child[0] = (yyvsp[(4) - (6)].treeNode);
                                (yyval.treeNode) -> child[1] = (yyvsp[(6) - (6)].treeNode); 
                                (yyval.treeNode) -> lineno = (yyvsp[(3) - (6)].token.value.ival); // Allows for correct line no
                            ;}
    break;

  case 21:
#line 229 "c-.y"
    {
                               (yyval.treeNode) = newDeclNode(FuncK);
                               (yyval.treeNode) -> declType = Void;
                               (yyval.treeNode) -> attr.name = (yyvsp[(1) - (5)].token.value.sval);
                               (yyval.treeNode) -> child[0] = (yyvsp[(3) - (5)].treeNode);
                               (yyval.treeNode) -> child[1] = (yyvsp[(5) - (5)].treeNode); 
                               (yyval.treeNode) -> lineno = (yyvsp[(2) - (5)].token.value.ival);
                            ;}
    break;

  case 22:
#line 239 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 23:
#line 240 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 24:
#line 243 "c-.y"
    {
                                TreeNode *trav = (yyvsp[(1) - (3)].treeNode);
                                if(trav != NULL) {
                                    while(trav -> sibling != NULL) trav = trav -> sibling;
                                    trav -> sibling = (yyvsp[(3) - (3)].treeNode);
                                    (yyval.treeNode) = (yyvsp[(1) - (3)].treeNode);
                                } else {
                                    (yyval.treeNode) = (yyvsp[(3) - (3)].treeNode); 
                                }
                            ;}
    break;

  case 25:
#line 253 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 26:
#line 256 "c-.y"
    {
                                TreeNode *complete = (yyvsp[(2) - (2)].treeNode);
                                if(complete != NULL) {
                                    do {
                                        complete -> declType = (yyvsp[(1) - (2)].integer);
                                        complete = complete -> sibling;
                                    } while(complete != NULL);
                                    (yyval.treeNode) = (yyvsp[(2) - (2)].treeNode);
                                } else {
                                    (yyval.treeNode) = NULL;
                                }
                            ;}
    break;

  case 27:
#line 270 "c-.y"
    {
                               TreeNode *trav = (yyvsp[(1) - (3)].treeNode); 
                               if(trav != NULL) {
                                   while(trav -> sibling != NULL) trav = trav -> sibling;
                                   trav -> sibling = (yyvsp[(3) - (3)].treeNode);
                                   (yyval.treeNode) = (yyvsp[(1) - (3)].treeNode);
                               } else { 
                                   (yyval.treeNode) = (yyvsp[(3) - (3)].treeNode);
                               }
                            ;}
    break;

  case 28:
#line 280 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 29:
#line 283 "c-.y"
    { 
                               (yyval.treeNode) = newDeclNode(ParamK);
                               (yyval.treeNode) -> attr.name = (yyvsp[(1) - (1)].token.value.sval);
                            ;}
    break;

  case 30:
#line 287 "c-.y"
    {
                               (yyval.treeNode) = newDeclNode(ParamK);
                               (yyval.treeNode) -> attr.name = (yyvsp[(1) - (3)].token.value.sval);
                               (yyval.treeNode) -> isArray = true;
                            ;}
    break;

  case 31:
#line 296 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 32:
#line 297 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 33:
#line 300 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 34:
#line 301 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 35:
#line 302 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 36:
#line 303 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 37:
#line 304 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 38:
#line 305 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 39:
#line 308 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 40:
#line 309 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 41:
#line 312 "c-.y"
    {
                               (yyval.treeNode) = newStmtNode(CompK); 
                               (yyval.treeNode) -> child[0] = (yyvsp[(2) - (4)].treeNode);
                               (yyval.treeNode) -> child[1] = (yyvsp[(3) - (4)].treeNode); 
                               (yyval.treeNode) -> lineno = (yyvsp[(1) - (4)].token.value.ival);
                            ;}
    break;

  case 42:
#line 320 "c-.y"
    {
                                TreeNode *trav = (yyvsp[(1) - (2)].treeNode); 
                                if(trav != NULL) {
                                    while(trav -> sibling != NULL) trav = trav -> sibling;
                                    trav -> sibling = (yyvsp[(2) - (2)].treeNode);
                                    (yyval.treeNode) = (yyvsp[(1) - (2)].treeNode);
                                } else {
                                    (yyval.treeNode) = (yyvsp[(2) - (2)].treeNode); 
                                }
                            ;}
    break;

  case 43:
#line 330 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 44:
#line 333 "c-.y"
    {
                                TreeNode *trav = (yyvsp[(1) - (2)].treeNode); 
                                if(trav != NULL) {
                                    while(trav -> sibling != NULL) trav = trav -> sibling;
                                    trav -> sibling = (yyvsp[(2) - (2)].treeNode);
                                    (yyval.treeNode) = (yyvsp[(1) - (2)].treeNode);
                                } else {
                                    (yyval.treeNode) = (yyvsp[(2) - (2)].treeNode);
                                }
                            ;}
    break;

  case 45:
#line 343 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 46:
#line 346 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (2)].treeNode); ;}
    break;

  case 47:
#line 347 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 48:
#line 350 "c-.y"
    {
                                (yyval.treeNode) = newStmtNode(IfK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(1) - (7)].token.value.sval);
                                (yyval.treeNode) -> child[0] = (yyvsp[(3) - (7)].treeNode);
                                (yyval.treeNode) -> child[1] = (yyvsp[(5) - (7)].treeNode);
                                (yyval.treeNode) -> child[2] = (yyvsp[(7) - (7)].treeNode);
                                (yyval.treeNode) -> lineno = (yyvsp[(2) - (7)].token.value.ival);
                            ;}
    break;

  case 49:
#line 360 "c-.y"
    {
                                (yyval.treeNode) = newStmtNode(IfK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(1) - (7)].token.value.sval);
                                (yyval.treeNode) -> child[0] = (yyvsp[(3) - (7)].treeNode);
                                (yyval.treeNode) -> child[1] = (yyvsp[(5) - (7)].treeNode);
                                (yyval.treeNode) -> child[2] = (yyvsp[(7) - (7)].treeNode);
                                (yyval.treeNode) -> lineno = (yyvsp[(2) - (7)].token.value.ival);
                            ;}
    break;

  case 50:
#line 368 "c-.y"
    {
                                (yyval.treeNode) = newStmtNode(IfK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(1) - (5)].token.value.sval);
                                (yyval.treeNode) -> child[0] = (yyvsp[(3) - (5)].treeNode);
                                (yyval.treeNode) -> child[1] = (yyvsp[(5) - (5)].treeNode);
                                (yyval.treeNode) -> lineno = (yyvsp[(2) - (5)].token.value.ival);
                            ;}
    break;

  case 51:
#line 377 "c-.y"
    {
                                (yyval.treeNode) = newStmtNode(WhileK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(1) - (5)].token.value.sval);
                                (yyval.treeNode) -> child[0] = (yyvsp[(3) - (5)].treeNode);
                                (yyval.treeNode) -> child[1] = (yyvsp[(5) - (5)].treeNode);
                                (yyval.treeNode) -> lineno = (yyvsp[(2) - (5)].token.value.ival);
                            ;}
    break;

  case 52:
#line 384 "c-.y"
    {
                                (yyval.treeNode) = newStmtNode(ForK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(1) - (7)].token.value.sval);
                                (yyval.treeNode) -> child[0] = (yyvsp[(3) - (7)].treeNode);
                                (yyval.treeNode) -> child[1] = (yyvsp[(5) - (7)].treeNode);
                                (yyval.treeNode) -> child[2] = (yyvsp[(7) - (7)].treeNode);
                                (yyval.treeNode) -> lineno = (yyvsp[(2) - (7)].token.value.ival);
                            ;}
    break;

  case 53:
#line 394 "c-.y"
    {
                                (yyval.treeNode) = newStmtNode(WhileK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(1) - (5)].token.value.sval);
                                (yyval.treeNode) -> child[0] = (yyvsp[(3) - (5)].treeNode);
                                (yyval.treeNode) -> child[1] = (yyvsp[(5) - (5)].treeNode);
                                (yyval.treeNode) -> lineno = (yyvsp[(2) - (5)].token.value.ival);
                            ;}
    break;

  case 54:
#line 401 "c-.y"
    {
                                (yyval.treeNode) = newStmtNode(ForK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(1) - (7)].token.value.sval);
                                (yyval.treeNode) -> child[0] = (yyvsp[(3) - (7)].treeNode); 
                                (yyval.treeNode) -> child[1] = (yyvsp[(5) - (7)].treeNode);
                                (yyval.treeNode) -> child[2] = (yyvsp[(7) - (7)].treeNode);
                                (yyval.treeNode) -> lineno = (yyvsp[(2) - (7)].token.value.ival);
                            ;}
    break;

  case 55:
#line 411 "c-.y"
    { 
                                (yyval.treeNode) = newStmtNode(ReturnK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(1) - (2)].token.value.sval);
                            ;}
    break;

  case 56:
#line 415 "c-.y"
    {
                                (yyval.treeNode) = newStmtNode(ReturnK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(1) - (3)].token.value.sval);
                                (yyval.treeNode) -> child[0] = (yyvsp[(2) - (3)].treeNode);
                            ;}
    break;

  case 57:
#line 422 "c-.y"
    { 
                                (yyval.treeNode) = newStmtNode(BreakK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(1) - (2)].token.value.sval);
                            ;}
    break;

  case 58:
#line 430 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(AssignK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(2) - (3)].token.value.sval);
                                (yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
                                (yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
                            ;}
    break;

  case 59:
#line 436 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(AssignK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(2) - (3)].token.value.sval);
                                (yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
                                (yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
                            ;}
    break;

  case 60:
#line 442 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(AssignK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(2) - (3)].token.value.sval);
                                (yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
                                (yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
                            ;}
    break;

  case 61:
#line 448 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(AssignK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(2) - (3)].token.value.sval);
                                (yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
                                (yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
                            ;}
    break;

  case 62:
#line 454 "c-.y"
    { 
                                (yyval.treeNode) = newExprNode(AssignK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(2) - (3)].token.value.sval);
                                (yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
                                (yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
                            ;}
    break;

  case 63:
#line 460 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(AssignK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(2) - (2)].token.value.sval);
                                (yyval.treeNode) -> child[0] = (yyvsp[(1) - (2)].treeNode);
                            ;}
    break;

  case 64:
#line 465 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(AssignK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(2) - (2)].token.value.sval);
                                (yyval.treeNode) -> child[0] = (yyvsp[(1) - (2)].treeNode);
                            ;}
    break;

  case 65:
#line 470 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 66:
#line 473 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(OpK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(2) - (3)].token.value.sval);
                                (yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
                                (yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
                            ;}
    break;

  case 67:
#line 479 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 68:
#line 482 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(OpK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(2) - (3)].token.value.sval);
                                (yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
                                (yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode); 
                            ;}
    break;

  case 69:
#line 488 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 70:
#line 491 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(OpK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(1) - (2)].token.value.sval);
                                (yyval.treeNode) -> child[0] = (yyvsp[(2) - (2)].treeNode);
                            ;}
    break;

  case 71:
#line 496 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 72:
#line 499 "c-.y"
    {
                               (yyval.treeNode) = newExprNode(OpK);
                               (yyval.treeNode) -> attr.name = (yyvsp[(2) - (3)].string);
                               (yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
                               (yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
                            ;}
    break;

  case 73:
#line 505 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 74:
#line 508 "c-.y"
    { (yyval.string) = (yyvsp[(1) - (1)].token.value.sval); ;}
    break;

  case 75:
#line 509 "c-.y"
    { (yyval.string) = (yyvsp[(1) - (1)].token.value.sval); ;}
    break;

  case 76:
#line 510 "c-.y"
    { (yyval.string) = (yyvsp[(1) - (1)].token.value.sval); ;}
    break;

  case 77:
#line 511 "c-.y"
    { (yyval.string) = (yyvsp[(1) - (1)].token.value.sval); ;}
    break;

  case 78:
#line 512 "c-.y"
    { (yyval.string) = (yyvsp[(1) - (1)].token.value.sval); ;}
    break;

  case 79:
#line 513 "c-.y"
    { (yyval.string) = (yyvsp[(1) - (1)].token.value.sval); ;}
    break;

  case 80:
#line 516 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(OpK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(2) - (3)].string);
                                (yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
                                (yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
                            ;}
    break;

  case 81:
#line 522 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 82:
#line 525 "c-.y"
    { (yyval.string) = (yyvsp[(1) - (1)].token.value.sval); ;}
    break;

  case 83:
#line 526 "c-.y"
    { (yyval.string) = (yyvsp[(1) - (1)].token.value.sval); ;}
    break;

  case 84:
#line 529 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(OpK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(2) - (3)].string);
                                (yyval.treeNode) -> child[0] = (yyvsp[(1) - (3)].treeNode);
                                (yyval.treeNode) -> child[1] = (yyvsp[(3) - (3)].treeNode);
                            ;}
    break;

  case 85:
#line 535 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 86:
#line 538 "c-.y"
    { (yyval.string) = (yyvsp[(1) - (1)].token.value.sval); ;}
    break;

  case 87:
#line 539 "c-.y"
    { (yyval.string) = (yyvsp[(1) - (1)].token.value.sval); ;}
    break;

  case 88:
#line 540 "c-.y"
    { (yyval.string) = (yyvsp[(1) - (1)].token.value.sval); ;}
    break;

  case 89:
#line 543 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(OpK);
                                (yyval.treeNode) -> attr.name = (yyvsp[(1) - (2)].string);
                                (yyval.treeNode) -> child[0] = (yyvsp[(2) - (2)].treeNode);
                            ;}
    break;

  case 90:
#line 548 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 91:
#line 551 "c-.y"
    { (yyval.string) = (yyvsp[(1) - (1)].token.value.sval); ;}
    break;

  case 92:
#line 552 "c-.y"
    { (yyval.string) = (yyvsp[(1) - (1)].token.value.sval); ;}
    break;

  case 93:
#line 553 "c-.y"
    { (yyval.string) = (yyvsp[(1) - (1)].token.value.sval); ;}
    break;

  case 94:
#line 556 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 95:
#line 557 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 96:
#line 560 "c-.y"
    {
                               (yyval.treeNode) = newExprNode(IdK); 
                               (yyval.treeNode) -> attr.name = (yyvsp[(1) - (1)].token.value.sval);
                            ;}
    break;

  case 97:
#line 564 "c-.y"
    {
                               (yyval.treeNode) = newExprNode(IdK);
                               (yyval.treeNode) -> attr.name = (yyvsp[(1) - (4)].token.value.sval);
                               (yyval.treeNode) -> child[0] = (yyvsp[(3) - (4)].treeNode);
                            ;}
    break;

  case 98:
#line 571 "c-.y"
    { (yyval.treeNode) = (yyvsp[(2) - (3)].treeNode); ;}
    break;

  case 99:
#line 572 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 100:
#line 573 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 101:
#line 576 "c-.y"
    {
                               (yyval.treeNode) = newExprNode(CallK);
                               (yyval.treeNode) -> attr.name = (yyvsp[(1) - (4)].token.value.sval);
                               (yyval.treeNode) -> child[0] = (yyvsp[(3) - (4)].treeNode);
                            ;}
    break;

  case 102:
#line 583 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 103:
#line 584 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 104:
#line 587 "c-.y"
    {
                                TreeNode *trav = (yyvsp[(1) - (3)].treeNode); 
                                if(trav != NULL) {
                                    while(trav -> sibling != NULL) trav = trav -> sibling;
                                    trav -> sibling = (yyvsp[(3) - (3)].treeNode);
                                    (yyval.treeNode) = (yyvsp[(1) - (3)].treeNode);
                                } else {
                                    (yyval.treeNode) = (yyvsp[(3) - (3)].treeNode);
                                }
                            ;}
    break;

  case 105:
#line 597 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 106:
#line 600 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(ConstK); 
                                (yyval.treeNode) -> attr.ivalue = (yyvsp[(1) - (1)].token.value.ival); 
                                (yyval.treeNode) -> declType = Int;
                            ;}
    break;

  case 107:
#line 605 "c-.y"
    { 
                                (yyval.treeNode) = newExprNode(ConstK); 
                                (yyval.treeNode) -> attr.cvalue = (yyvsp[(1) - (1)].token.value.cval);
                                (yyval.treeNode) -> declType = Char;
                            ;}
    break;

  case 108:
#line 610 "c-.y"
    { 
                               (yyval.treeNode) = newExprNode(ConstK); 
                               (yyval.treeNode) -> attr.svalue = (yyvsp[(1) - (1)].token.value.sval); 
                               (yyval.treeNode) -> declType = String; 
                            ;}
    break;

  case 109:
#line 615 "c-.y"
    { 
                               (yyval.treeNode) = newExprNode(ConstK); 
                               (yyval.treeNode) -> attr.ivalue = (yyvsp[(1) - (1)].token.value.ival); 
                               (yyval.treeNode) -> declType = Bool;
                            ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2467 "c-.tab.c"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 622 "c-.y"

int main(int argc, char** argv) {
    // Get cmd line option arguments if they exist
    int opt;
    while((opt = getopt(argc, argv, "d")) != EOF) {
        switch(opt) { //in case we add more options
            default:
                abort();
                break;
            case 'd':
                yydebug = 1;
                break;
        }
    }
   
    // If there's a trailing argument, it must be the filename. 
    if(argc > 1) {
        FILE *iFile;
        iFile = fopen(argv[argc - 1], "r");
        if(!iFile) {
            printf("File not found: %s\n", argv[argc - 1]);
            exit(-1);
        }
        yyin = iFile;
    }
    
    // Start the scanner now that our options and yyin have been changed (or not). 
    do {
        yyparse();
    } while(!feof(yyin));
   
    printTree(syntaxTree, -1);
    printf("Number of warnings: %i\n", 0);
    printf("Number of errors: %i\n", 0);
    return 0;
}

