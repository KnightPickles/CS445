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




/* Copy the first part of user declarations.  */
#line 1 "c-.y"

// c-.y CS445 Zachary Yama

#include <iostream>
#include <getopt.h>
#include <string>
#include "util.h"
#include "token.h"
#include "semantics.h"
#include "symbolTable.h"
#include "codegen.h"
#define YYERROR_VERBOSE

using namespace std;

extern int gOffset;
extern int numwarnings;
extern int numerrors;
extern int yylineno;
extern int yylex();
extern char *yytext;
extern FILE *yyin;
extern void initTokenMaps();

static TreeNode *syntaxTree;
static std::map<std::string , char *> niceTokenNameMap;    // use an ordered map (not as fast as unordered)

int split(char *s, char *strs[], char breakchar)
{
    int num;
    
    strs[0] = s;
    num = 1;
    for (char *p = s; *p; p++) {
        if (*p==breakchar) {
            strs[num++] = p+1;
            *p = '\0';
        }
    }
    strs[num] = NULL;
    
    return num;
}


// trim off the last character
void trim(char *s)
{
    s[strlen(s)-1] = '\0';
}


// WARNING: this routine must be called to initialize mapping of
// (strings returned as error message) --> (human readable strings)
//
void initTokenMaps() {
    niceTokenNameMap["NOTEQ"] = (char *)"'!='";
    niceTokenNameMap["MULASS"] = (char *)"'*='";
    niceTokenNameMap["INC"] = (char *)"'++'";
    niceTokenNameMap["ADDASS"] = (char *)"'+='";
    niceTokenNameMap["DEC"] = (char *)"'--'";
    niceTokenNameMap["SUBASS"] = (char *)"'-='";
    niceTokenNameMap["DIVASS"] = (char *)"'/='";
    niceTokenNameMap["LESSEQ"] = (char *)"'<='";
    niceTokenNameMap["EQ"] = (char *)"'=='";
    niceTokenNameMap["GRTEQ"] = (char *)"'>='";
    niceTokenNameMap["BOOL"] = (char *)"bool";
    niceTokenNameMap["BREAK"] = (char *)"break";
    niceTokenNameMap["CHAR"] = (char *)"char";
    niceTokenNameMap["ELSE"] = (char *)"else";
    niceTokenNameMap["FOREACH"] = (char *)"foreach";
    niceTokenNameMap["IF"] = (char *)"if";
    niceTokenNameMap["IN"] = (char *)"in";
    niceTokenNameMap["INT"] = (char *)"int";
    niceTokenNameMap["RETURN"] = (char *)"return";
    niceTokenNameMap["STATIC"] = (char *)"static";
    niceTokenNameMap["WHILE"] = (char *)"while";
    niceTokenNameMap["BOOLCONST"] = (char *)"Boolean constant";
    niceTokenNameMap["NUMCONST"] = (char *)"numeric constant";
    niceTokenNameMap["ID"] = (char *)"identifier";
    niceTokenNameMap["CHARCONST"] = (char *)"character constant";
    niceTokenNameMap["STRINGCONST"] = (char *)"string constant";
    niceTokenNameMap["$end"] = (char *)"end of input";
}


// looks of pretty printed words for tokens that are
// not already in single quotes.  It uses the niceTokenNameMap table.
char *niceTokenStr(char *tokenName ) {
    if (tokenName[0] == '\'') return tokenName;
    if (niceTokenNameMap.find(tokenName) == niceTokenNameMap.end()) {
        printf("ERROR(SYSTEM): niceTokenStr fails to find string '%s'\n", tokenName); 
        fflush(stdout);
        exit(1);
    }
    return niceTokenNameMap[tokenName];
}


// Is this a message that we need to elaborate with the current parsed token.
// This elaboration is some what of a crap shoot since the token could
// be already overwritten with a look ahead token.   But probably not.
bool elaborate(char *s)
{
    return (strstr(s, "constant") || strstr(s, "identifier"));
}


// A tiny sort routine for SMALL NUMBERS of
// of char * elements.  num is the total length
// of the array but only every step elements will
// be sorted.  The "up" flag is direction of sort.
// For example:
//    tinySort(str, i, 2, direction);      // sorts even number elements in array
//    tinySort(str+1, i-1, 2, direction);  // sorts odd number elements in array
//    tinySort(str, i, 1, direction);      // sorts all elements in array
//
void tinySort(char *base[], int num, int step, bool up)
{
    for (int i=step; i<num; i+=step) {
        for (int j=0; j<i; j+=step) {
            if (up ^ (strcmp(base[i], base[j])>0)) {
                char *tmp;
                tmp = base[i]; base[i] = base[j]; base[j] = tmp;
            }
        }
    }
}


// This is the yyerror called by the bison parser for errors.
// It only does errors and not warnings.   
void yyerror(const char *msg)
{
    char *space;
    char *strs[100];
    int numstrs;

    // make a copy of msg string
    space = strdup(msg);

    // split out components
    numstrs = split(space, strs, ' ');
    if (numstrs>4) trim(strs[3]);

    // translate components
    for (int i=3; i<numstrs; i+=2) {
        strs[i] = niceTokenStr(strs[i]);
    }

    // print components
    printf("ERROR(%d): Syntax error, unexpected %s", yylineno, strs[3]);
    if (elaborate(strs[3])) {
        if (yytext[0]=='\'' || yytext[0]=='"') printf(" %s", yytext); 
        else printf(" \'%s\'", yytext);
    }
    if (numstrs>4) printf(",");
    tinySort(strs+5, numstrs-5, 2, true); 
    for (int i=4; i<numstrs; i++) {
        printf(" %s", strs[i]);
    }
    printf(".\n");
    fflush(stdout);   // force a dump of the error

    numerrors++;

    free(space);
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
#line 172 "c-.y"
{
    Token token; 
    TreeNode *treeNode;
    DeclType declType;
    char *cstring;
}
/* Line 193 of yacc.c.  */
#line 330 "c-.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 343 "c-.tab.c"

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
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   963

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  170
/* YYNRULES -- Number of states.  */
#define YYNSTATES  252

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,     2,     2,    45,    47,     2,
      36,    37,    34,    32,    42,    33,     2,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    43,    44,
      30,    28,    31,    46,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    40,     2,    41,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,    48,    39,     2,     2,     2,     2,
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
      25,    26,    27,    29
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    20,
      23,    27,    29,    32,    36,    38,    42,    46,    48,    52,
      56,    60,    62,    64,    69,    73,    76,    79,    81,    83,
      85,    87,    94,   100,   103,   108,   115,   121,   125,   127,
     128,   132,   134,   138,   142,   145,   148,   152,   154,   158,
     162,   164,   168,   170,   172,   174,   176,   178,   180,   182,
     184,   186,   194,   200,   208,   216,   222,   228,   230,   238,
     244,   250,   258,   266,   272,   278,   284,   289,   294,   299,
     302,   303,   306,   307,   310,   313,   315,   318,   321,   325,
     328,   332,   335,   337,   340,   344,   348,   352,   354,   356,
     358,   360,   362,   364,   366,   370,   372,   376,   380,   384,
     388,   390,   394,   398,   402,   405,   407,   410,   414,   416,
     420,   424,   428,   430,   432,   434,   436,   438,   440,   444,
     446,   450,   454,   458,   460,   462,   466,   468,   472,   476,
     480,   482,   484,   486,   489,   491,   494,   496,   498,   500,
     502,   504,   506,   511,   515,   518,   522,   524,   526,   529,
     534,   538,   540,   541,   545,   547,   551,   555,   557,   559,
     561
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      51,     0,    -1,    52,    -1,    52,    53,    -1,    53,    -1,
      54,    -1,    61,    -1,     1,    -1,    60,    56,    44,    -1,
       1,    44,    -1,    59,    56,    44,    -1,     1,    -1,    59,
       1,    -1,    56,    42,    57,    -1,    57,    -1,     1,    42,
      57,    -1,    56,    42,     1,    -1,    58,    -1,    58,    43,
      81,    -1,     1,    43,    81,    -1,    58,    43,     1,    -1,
       1,    -1,     3,    -1,     3,    40,     4,    41,    -1,     3,
      40,     1,    -1,     1,    41,    -1,    17,    60,    -1,    60,
      -1,    15,    -1,     8,    -1,    10,    -1,    60,     3,    36,
      62,    37,    67,    -1,     3,    36,    62,    37,    67,    -1,
      60,     1,    -1,    60,     3,    36,     1,    -1,    60,     3,
      36,    62,    37,     1,    -1,     3,    36,    62,    37,     1,
      -1,     3,    36,     1,    -1,    63,    -1,    -1,    63,    44,
      64,    -1,    64,    -1,     1,    44,    64,    -1,    63,    44,
       1,    -1,    60,    65,    -1,    60,     1,    -1,    65,    42,
      66,    -1,    66,    -1,     1,    42,    66,    -1,    65,    42,
       1,    -1,     3,    -1,     3,    40,    41,    -1,     1,    -1,
      69,    -1,    68,    -1,    70,    -1,    75,    -1,    72,    -1,
      76,    -1,    77,    -1,    71,    -1,    13,    36,    81,    37,
      68,    11,    68,    -1,    18,    36,    81,    37,    68,    -1,
      12,    36,    93,    14,    81,    37,    68,    -1,    13,    36,
       1,    37,    68,    11,    68,    -1,    18,    36,     1,    37,
      68,    -1,    12,    36,     1,    37,    68,    -1,     1,    -1,
      13,    36,    81,    37,    68,    11,    69,    -1,    13,    36,
      81,    37,    67,    -1,    18,    36,    81,    37,    69,    -1,
      12,    36,    93,    14,    81,    37,    69,    -1,    13,    36,
       1,    37,    68,    11,    69,    -1,    13,    36,     1,    37,
      67,    -1,    18,    36,     1,    37,    69,    -1,    12,    36,
       1,    37,    69,    -1,    38,    73,    74,    39,    -1,    38,
      73,     1,    39,    -1,    38,     1,    74,    39,    -1,    73,
      55,    -1,    -1,    74,    67,    -1,    -1,    74,     1,    -1,
      78,    44,    -1,    44,    -1,     1,    44,    -1,    16,    44,
      -1,    16,    78,    44,    -1,     9,    44,    -1,    93,    79,
      78,    -1,    93,    80,    -1,    81,    -1,     1,    80,    -1,
       1,    79,    78,    -1,    93,    79,     1,    -1,     1,    79,
       1,    -1,    28,    -1,    25,    -1,    26,    -1,    27,    -1,
      29,    -1,    23,    -1,    24,    -1,    81,    48,    82,    -1,
      82,    -1,     1,    48,    82,    -1,    81,    48,     1,    -1,
       1,    48,     1,    -1,    82,    47,    83,    -1,    83,    -1,
       1,    47,    83,    -1,    82,    47,     1,    -1,     1,    47,
       1,    -1,    49,    83,    -1,    84,    -1,    49,     1,    -1,
      86,    85,    86,    -1,    86,    -1,     1,    85,    86,    -1,
      86,    85,     1,    -1,     1,    85,     1,    -1,    21,    -1,
      30,    -1,    31,    -1,    22,    -1,    20,    -1,    19,    -1,
      86,    87,    88,    -1,    88,    -1,     1,    87,    88,    -1,
      86,    87,     1,    -1,     1,    87,     1,    -1,    32,    -1,
      33,    -1,    88,    89,    90,    -1,    90,    -1,     1,    89,
      90,    -1,    88,    89,     1,    -1,     1,    89,     1,    -1,
      34,    -1,    35,    -1,    45,    -1,    91,    90,    -1,    92,
      -1,    91,     1,    -1,    33,    -1,    34,    -1,    46,    -1,
      94,    -1,    93,    -1,     3,    -1,     3,    40,    78,    41,
      -1,     3,    40,     1,    -1,     1,    41,    -1,    36,    78,
      37,    -1,    95,    -1,    98,    -1,    36,     1,    -1,     3,
      36,    96,    37,    -1,     3,    36,     1,    -1,    97,    -1,
      -1,    97,    42,    78,    -1,    78,    -1,     1,    42,    78,
      -1,    97,    42,     1,    -1,     4,    -1,     6,    -1,     5,
      -1,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   249,   249,   252,   262,   265,   266,   267,   272,   286,
     289,   303,   304,   307,   317,   318,   319,   323,   324,   328,
     329,   330,   333,   339,   347,   348,   351,   356,   362,   363,
     364,   368,   377,   385,   386,   387,   388,   389,   392,   393,
     396,   407,   408,   409,   412,   424,   427,   438,   439,   440,
     443,   448,   454,   459,   460,   463,   464,   465,   466,   467,
     470,   473,   481,   488,   496,   497,   498,   499,   502,   510,
     517,   524,   532,   533,   534,   535,   538,   545,   546,   549,
     559,   562,   572,   573,   576,   577,   578,   582,   588,   597,
     607,   614,   621,   622,   623,   624,   625,   628,   629,   630,
     631,   632,   635,   636,   639,   645,   646,   647,   648,   651,
     657,   658,   659,   660,   663,   668,   669,   672,   678,   679,
     680,   681,   684,   685,   686,   687,   688,   689,   692,   698,
     699,   700,   701,   704,   705,   708,   715,   716,   717,   718,
     721,   722,   723,   726,   731,   732,   735,   736,   737,   740,
     741,   744,   749,   755,   756,   759,   760,   761,   762,   765,
     771,   774,   775,   778,   789,   790,   791,   794,   800,   806,
     813
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "NUMCONST", "STRINGCONST",
  "CHARCONST", "BOOLCONST", "BOOL", "BREAK", "CHAR", "ELSE", "FOREACH",
  "IF", "IN", "INT", "RETURN", "STATIC", "WHILE", "NOTEQ", "EQ", "LESSEQ",
  "GRTEQ", "INC", "DEC", "ADDASS", "SUBASS", "MULASS", "'='", "DIVASS",
  "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'('", "')'", "'{'", "'}'",
  "'['", "']'", "','", "':'", "';'", "'%'", "'?'", "'&'", "'|'", "'!'",
  "$accept", "program", "declaration_list", "declaration",
  "var_declaration", "scoped_var_declaration", "var_decl_list",
  "var_decl_initialize", "var_decl_id", "scoped_type_specifier",
  "type_specifier", "fun_declaration", "params", "param_list",
  "param_type_list", "param_id_list", "param_id", "statement", "matched",
  "unmatched", "matched_conditional", "unmatched_conditional",
  "compound_stmt", "local_declarations", "statement_list",
  "expression_stmt", "return_stmt", "break_stmt", "expression",
  "binary_assign", "unary_assign", "simple_expression", "and_expression",
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
     275,   276,   277,   278,   279,   280,   281,   282,    61,   283,
      60,    62,    43,    45,    42,    47,    40,    41,   123,   125,
      91,    93,    44,    58,    59,    37,    63,    38,   124,    33
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    53,    54,    54,
      55,    55,    55,    56,    56,    56,    56,    57,    57,    57,
      57,    57,    58,    58,    58,    58,    59,    59,    60,    60,
      60,    61,    61,    61,    61,    61,    61,    61,    62,    62,
      63,    63,    63,    63,    64,    64,    65,    65,    65,    65,
      66,    66,    66,    67,    67,    68,    68,    68,    68,    68,
      69,    70,    70,    70,    70,    70,    70,    70,    71,    71,
      71,    71,    71,    71,    71,    71,    72,    72,    72,    73,
      73,    74,    74,    74,    75,    75,    75,    76,    76,    77,
      78,    78,    78,    78,    78,    78,    78,    79,    79,    79,
      79,    79,    80,    80,    81,    81,    81,    81,    81,    82,
      82,    82,    82,    82,    83,    83,    83,    84,    84,    84,
      84,    84,    85,    85,    85,    85,    85,    85,    86,    86,
      86,    86,    86,    87,    87,    88,    88,    88,    88,    88,
      89,    89,    89,    90,    90,    90,    91,    91,    91,    92,
      92,    93,    93,    93,    93,    94,    94,    94,    94,    95,
      95,    96,    96,    97,    97,    97,    97,    98,    98,    98,
      98
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     3,     2,
       3,     1,     2,     3,     1,     3,     3,     1,     3,     3,
       3,     1,     1,     4,     3,     2,     2,     1,     1,     1,
       1,     6,     5,     2,     4,     6,     5,     3,     1,     0,
       3,     1,     3,     3,     2,     2,     3,     1,     3,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     7,     5,     7,     7,     5,     5,     1,     7,     5,
       5,     7,     7,     5,     5,     5,     4,     4,     4,     2,
       0,     2,     0,     2,     2,     1,     2,     2,     3,     2,
       3,     2,     1,     2,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     3,     2,     1,     2,     3,     1,     3,
       3,     3,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     3,     3,     1,     1,     3,     1,     3,     3,     3,
       1,     1,     1,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     4,     3,     2,     3,     1,     1,     2,     4,
       3,     1,     0,     3,     1,     3,     3,     1,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,     0,    29,    30,    28,     0,     0,     4,     5,
       0,     6,     9,     0,     1,     3,    33,    22,     0,    14,
      17,    37,     0,     0,    38,    41,    25,     0,     0,     0,
       0,     0,     8,     0,     0,    45,    50,    44,    47,     0,
       0,    21,    22,    15,     0,   151,   167,   169,   168,   170,
     146,   147,     0,   148,     0,    19,   105,   110,   115,   118,
     129,   136,     0,   144,   150,   149,   156,   157,    34,     0,
      24,     0,    16,    13,    20,    18,    42,     0,     0,     0,
      36,     0,     0,     0,     0,     0,     0,    85,    32,    54,
      53,    55,    60,    57,    56,    58,    59,     0,    92,   150,
      43,    40,   127,   126,   122,   125,   123,   124,   133,   134,
     140,   141,   154,   142,     0,     0,     0,     0,     0,     0,
       0,   158,     0,   116,   114,     0,     0,     0,     0,     0,
     145,   143,     0,    23,    52,    48,    51,    49,    46,   102,
     103,    98,    99,   100,    97,   101,    86,     0,    93,    89,
       0,     0,     0,    87,     0,     0,    82,     0,    84,     0,
      91,   113,   111,   108,   106,   121,   119,   132,   130,   139,
     137,   160,   164,     0,   161,   153,     0,   155,   107,   104,
     112,   109,   120,   117,   131,   128,   138,   135,    35,    31,
      96,    94,     0,   151,     0,     0,     0,    88,     0,     0,
       0,    11,     0,    79,     0,    27,     0,    95,    90,     0,
     159,     0,   152,     0,     0,     0,     0,     0,     0,    67,
      78,    81,    77,    26,    12,     0,    76,   165,   166,   163,
      67,    66,    75,     0,    73,    54,    69,    54,    65,    74,
      62,    70,    10,     0,     0,     0,    63,    71,    64,    72,
      61,    68
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,   203,    18,    19,    20,   204,
      22,    11,    23,    24,    25,    37,    38,   221,    89,    90,
      91,    92,    93,   157,   200,    94,    95,    96,    97,   147,
     148,    98,    56,    57,    58,   116,    59,   117,    60,   118,
      61,    62,    63,    99,    65,    66,   173,   174,    67
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -164
static const yytype_int16 yypact[] =
{
     105,    -8,    47,  -164,  -164,  -164,    86,   700,  -164,  -164,
     118,  -164,  -164,    55,  -164,  -164,   121,     4,    83,  -164,
      51,    65,   130,    85,    91,  -164,  -164,   135,   344,    95,
      60,   180,  -164,   393,    58,   108,   107,   113,  -164,   253,
     233,   143,   116,  -164,   870,    57,  -164,  -164,  -164,  -164,
    -164,  -164,   402,  -164,   410,   125,   129,  -164,  -164,   876,
       3,  -164,   618,  -164,  -164,  -164,  -164,  -164,    65,   140,
    -164,   157,   143,  -164,   870,   125,  -164,   194,   160,   203,
     720,   164,   181,   202,   337,   210,    13,  -164,  -164,  -164,
    -164,  -164,  -164,  -164,  -164,  -164,  -164,   207,   125,   395,
    -164,  -164,  -164,  -164,  -164,  -164,  -164,  -164,  -164,  -164,
    -164,  -164,  -164,  -164,   427,   461,   625,   632,   641,   355,
     478,   780,   216,   918,  -164,   485,   499,   678,   685,   692,
     220,  -164,   272,  -164,  -164,  -164,  -164,  -164,  -164,  -164,
    -164,  -164,  -164,  -164,  -164,  -164,  -164,   535,  -164,  -164,
     213,   546,   780,  -164,   219,   553,  -164,   136,  -164,   560,
    -164,   918,  -164,   900,   129,   126,    42,    -2,     3,   220,
    -164,   750,  -164,   227,   225,   780,   231,  -164,   900,   129,
     918,  -164,   126,    42,    -2,     3,   220,  -164,   720,  -164,
     780,  -164,    70,   228,   256,   810,   -24,  -164,   840,    -3,
     187,   235,    58,  -164,   229,  -164,   206,   780,  -164,   571,
    -164,   607,  -164,   319,   344,   319,   319,   319,   319,   720,
    -164,  -164,  -164,  -164,   186,   193,  -164,  -164,   780,  -164,
     720,  -164,  -164,     5,  -164,   269,  -164,   271,  -164,  -164,
    -164,  -164,  -164,   319,   319,   319,  -164,  -164,  -164,  -164,
    -164,  -164
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -164,  -164,  -164,   276,  -164,  -164,    88,    87,  -164,  -164,
       0,  -164,   264,  -164,    45,  -164,   170,   -37,   489,  -163,
    -164,  -164,  -164,  -164,   137,  -164,  -164,  -164,   -43,   196,
     197,   -25,  -110,   -42,  -164,   239,   -58,   -49,   -57,   -56,
     -51,  -164,  -164,   -27,  -164,  -164,  -164,  -164,  -164
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -163
static const yytype_int16 yytable[] =
{
      10,    64,    88,    55,   129,   164,    64,    10,    75,   122,
     128,   131,   124,   216,   156,   179,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   125,   -80,   -80,    64,   -80,   -80,
     -80,   -80,   110,   111,   218,    64,    12,   110,   111,   112,
      29,   154,   243,   113,    30,   125,   -80,   -80,   113,   -80,
     232,   -80,   -80,   125,   239,   241,    21,   -80,   166,   -80,
     168,    70,   -80,     3,    71,     4,     3,   170,     4,   183,
       5,   185,   162,     5,   108,   109,   172,   176,   187,    76,
     247,   249,   251,    13,   181,   101,    14,    64,    64,    64,
      64,    64,   -39,   119,    33,   189,    68,   120,    64,    64,
      64,    64,    64,     3,   191,     4,     1,   213,     2,    34,
       5,   112,   129,     3,    43,     4,   208,   128,    73,    16,
       5,    17,    39,   194,    64,    31,   196,    32,    64,   129,
     199,    35,   -39,    36,   128,    40,    41,   201,    42,   -82,
     -82,   -82,   -82,   -82,     3,   -82,     4,    78,   -82,   -82,
      77,     5,   -82,   202,   -82,    79,    30,   205,   108,   109,
     110,   111,    26,    27,    28,   -21,   227,   112,   229,   -82,
     -82,   113,   -82,   125,   -82,   -82,   126,   132,   234,   236,
     -82,    72,   -82,    42,    26,   -82,    28,    64,   219,   233,
      45,    46,    47,    48,    49,   134,    81,    36,   133,    82,
      83,   136,   223,    84,   137,    85,    36,   219,   149,    45,
      46,    47,    48,    49,   192,    81,   193,   150,    82,    83,
      50,    51,    84,    52,    85,    86,   220,    26,    27,    28,
     224,    87,    42,    53,   100,    31,    54,   242,   151,    50,
      51,     3,    52,     4,    86,   226,   155,   135,     5,   138,
      87,   158,    53,   177,    80,    54,    45,    46,    47,    48,
      49,   112,    81,   197,   210,    82,    83,   211,   120,    84,
     214,    85,   212,   188,   222,    45,    46,    47,    48,    49,
     244,    81,   245,    15,    82,    83,    50,    51,    84,    52,
      85,    86,   225,    69,   206,   159,   160,    87,   127,    53,
       0,     0,    54,     0,     0,    50,    51,     0,    52,     0,
      86,     0,     0,     0,     0,     0,    87,     0,    53,     0,
     230,    54,    45,    46,    47,    48,    49,     0,    81,     0,
       0,    82,    83,     0,     0,    84,     0,    85,   152,     0,
      45,    46,    47,    48,    49,    44,     0,    45,    46,    47,
      48,    49,    50,    51,     0,    52,   171,    86,    45,    46,
      47,    48,    49,    87,     0,    53,     0,     0,    54,     0,
      50,    51,     0,    52,     0,     0,     0,    50,    51,     0,
      52,   153,     0,    53,     0,     0,    54,     0,    50,    51,
      53,    52,  -162,    54,    74,     0,    45,    46,    47,    48,
      49,    53,     0,   121,    54,    45,    46,    47,    48,    49,
       0,   123,     0,    45,    46,    47,    48,    49,   139,   140,
     141,   142,   143,   144,   145,     0,    50,    51,   161,    52,
      45,    46,    47,    48,    49,    50,    51,     0,    52,    53,
       0,     0,    54,    50,    51,     0,    52,     0,    53,     0,
       0,    54,     0,     0,     0,     0,    53,     0,     0,    54,
      50,    51,   163,    52,    45,    46,    47,    48,    49,     0,
       0,     0,     0,    53,     0,     0,    54,     0,     0,   175,
       0,    45,    46,    47,    48,    49,   178,     0,    45,    46,
      47,    48,    49,     0,    50,    51,     0,    52,     0,     0,
     180,     0,    45,    46,    47,    48,    49,    53,     0,     0,
      54,    50,    51,     0,    52,     0,     0,     0,    50,    51,
       0,    52,     0,     0,    53,     0,     0,    54,     0,     0,
       0,    53,    50,    51,    54,    52,   190,     0,    45,    46,
      47,    48,    49,     0,     0,    53,     0,   195,    54,    45,
      46,    47,    48,    49,   198,     0,    45,    46,    47,    48,
      49,   207,     0,    45,    46,    47,    48,    49,    50,    51,
       0,    52,   152,     0,    45,    46,    47,    48,    49,    50,
      51,    53,    52,     0,    54,     0,    50,    51,     0,    52,
       0,     0,    53,    50,    51,    54,    52,     0,     0,    53,
       0,     0,    54,     0,    50,    51,    53,    52,   228,    54,
      45,    46,    47,    48,    49,     0,     0,    53,     0,   130,
      54,    45,    46,    47,    48,    49,   165,     0,    45,    46,
      47,    48,    49,   167,     0,    45,    46,    47,    48,    49,
      50,    51,   169,    52,    45,    46,    47,    48,    49,     0,
       0,    50,    51,    53,    52,     0,    54,     0,    50,    51,
       0,    52,     0,     0,    53,    50,    51,     0,    52,     0,
       0,    53,     0,     0,    50,    51,     0,    52,    53,   182,
       0,    45,    46,    47,    48,    49,   184,    53,    45,    46,
      47,    48,    49,   186,     0,    45,    46,    47,    48,    49,
      -2,     1,   231,     2,   235,   237,   238,   240,     3,     0,
       4,    50,    51,     0,    52,     5,     0,     0,    50,    51,
       0,    52,     0,     0,    53,    50,    51,     0,    52,     0,
       0,    53,   246,   248,   250,     0,     0,     0,    53,   102,
     103,   104,   105,   139,   140,   141,   142,   143,   144,   145,
     106,   107,   108,   109,   110,   111,     0,     0,     0,     0,
       0,   112,     0,     0,   146,   113,     0,   114,   115,   102,
     103,   104,   105,   139,   140,   141,   142,   143,   144,   145,
     106,   107,   108,   109,   110,   111,     0,     0,     0,     0,
       0,   112,   209,     0,     0,   113,     0,   114,   115,   102,
     103,   104,   105,   139,   140,   141,   142,   143,   144,   145,
     106,   107,   108,   109,   110,   111,     0,     0,     0,     0,
       0,   112,     0,     0,     0,   113,     0,   114,   115,   102,
     103,   104,   105,     0,     0,     0,     0,     0,     0,     0,
     106,   107,   108,   109,   110,   111,     0,   215,     0,     0,
       0,   112,     0,     0,     0,   113,     0,   114,   115,   102,
     103,   104,   105,     0,     0,     0,     0,     0,     0,     0,
     106,   107,   108,   109,   110,   111,     0,   217,     0,     0,
       0,   112,     0,     0,     0,   113,     0,   114,   115,   102,
     103,   104,   105,     0,     0,   102,   103,   104,   105,     0,
     106,   107,   108,   109,   110,   111,   106,   107,   108,   109,
       0,   112,     0,     0,     0,   113,     0,   114,   115,   102,
     103,   104,   105,     0,     0,     0,     0,     0,     0,     0,
     106,   107,   108,   109,   110,   111,     0,   102,   103,   104,
     105,   112,     0,     0,     0,   113,     0,   114,   106,   107,
     108,   109,   110,   111,     0,     0,     0,     0,     0,   112,
       0,     0,     0,   113
};

static const yytype_int16 yycheck[] =
{
       0,    28,    39,    28,    60,   115,    33,     7,    33,    52,
      59,    62,    54,    37,     1,   125,     3,     4,     5,     6,
       7,     8,     9,    10,    48,    12,    13,    54,    15,    16,
      17,    18,    34,    35,    37,    62,    44,    34,    35,    41,
      36,    84,    37,    45,    40,    48,    33,    34,    45,    36,
     213,    38,    39,    48,   217,   218,     1,    44,   116,    46,
     117,     1,    49,     8,     4,    10,     8,   118,    10,   127,
      15,   128,   114,    15,    32,    33,   119,   120,   129,    34,
     243,   244,   245,    36,   126,    40,     0,   114,   115,   116,
     117,   118,    37,    36,    43,   132,     1,    40,   125,   126,
     127,   128,   129,     8,   147,    10,     1,    37,     3,    44,
      15,    41,   168,     8,    27,    10,   159,   166,    31,     1,
      15,     3,    37,   150,   151,    42,   151,    44,   155,   185,
     155,     1,    37,     3,   183,    44,     1,     1,     3,     3,
       4,     5,     6,     7,     8,     9,    10,    40,    12,    13,
      42,    15,    16,    17,    18,    42,    40,   157,    32,    33,
      34,    35,    41,    42,    43,    44,   209,    41,   211,    33,
      34,    45,    36,    48,    38,    39,    47,    37,   215,   216,
      44,     1,    46,     3,    41,    49,    43,   214,     1,   214,
       3,     4,     5,     6,     7,     1,     9,     3,    41,    12,
      13,    41,   202,    16,     1,    18,     3,     1,    44,     3,
       4,     5,     6,     7,     1,     9,     3,    36,    12,    13,
      33,    34,    16,    36,    18,    38,    39,    41,    42,    43,
       1,    44,     3,    46,     1,    42,    49,    44,    36,    33,
      34,     8,    36,    10,    38,    39,    36,    77,    15,    79,
      44,    44,    46,    37,     1,    49,     3,     4,     5,     6,
       7,    41,     9,    44,    37,    12,    13,    42,    40,    16,
      14,    18,    41,     1,    39,     3,     4,     5,     6,     7,
      11,     9,    11,     7,    12,    13,    33,    34,    16,    36,
      18,    38,   204,    29,   157,    99,    99,    44,    59,    46,
      -1,    -1,    49,    -1,    -1,    33,    34,    -1,    36,    -1,
      38,    -1,    -1,    -1,    -1,    -1,    44,    -1,    46,    -1,
       1,    49,     3,     4,     5,     6,     7,    -1,     9,    -1,
      -1,    12,    13,    -1,    -1,    16,    -1,    18,     1,    -1,
       3,     4,     5,     6,     7,     1,    -1,     3,     4,     5,
       6,     7,    33,    34,    -1,    36,     1,    38,     3,     4,
       5,     6,     7,    44,    -1,    46,    -1,    -1,    49,    -1,
      33,    34,    -1,    36,    -1,    -1,    -1,    33,    34,    -1,
      36,    44,    -1,    46,    -1,    -1,    49,    -1,    33,    34,
      46,    36,    37,    49,     1,    -1,     3,     4,     5,     6,
       7,    46,    -1,     1,    49,     3,     4,     5,     6,     7,
      -1,     1,    -1,     3,     4,     5,     6,     7,    23,    24,
      25,    26,    27,    28,    29,    -1,    33,    34,     1,    36,
       3,     4,     5,     6,     7,    33,    34,    -1,    36,    46,
      -1,    -1,    49,    33,    34,    -1,    36,    -1,    46,    -1,
      -1,    49,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,
      33,    34,     1,    36,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    49,    -1,    -1,     1,
      -1,     3,     4,     5,     6,     7,     1,    -1,     3,     4,
       5,     6,     7,    -1,    33,    34,    -1,    36,    -1,    -1,
       1,    -1,     3,     4,     5,     6,     7,    46,    -1,    -1,
      49,    33,    34,    -1,    36,    -1,    -1,    -1,    33,    34,
      -1,    36,    -1,    -1,    46,    -1,    -1,    49,    -1,    -1,
      -1,    46,    33,    34,    49,    36,     1,    -1,     3,     4,
       5,     6,     7,    -1,    -1,    46,    -1,     1,    49,     3,
       4,     5,     6,     7,     1,    -1,     3,     4,     5,     6,
       7,     1,    -1,     3,     4,     5,     6,     7,    33,    34,
      -1,    36,     1,    -1,     3,     4,     5,     6,     7,    33,
      34,    46,    36,    -1,    49,    -1,    33,    34,    -1,    36,
      -1,    -1,    46,    33,    34,    49,    36,    -1,    -1,    46,
      -1,    -1,    49,    -1,    33,    34,    46,    36,     1,    49,
       3,     4,     5,     6,     7,    -1,    -1,    46,    -1,     1,
      49,     3,     4,     5,     6,     7,     1,    -1,     3,     4,
       5,     6,     7,     1,    -1,     3,     4,     5,     6,     7,
      33,    34,     1,    36,     3,     4,     5,     6,     7,    -1,
      -1,    33,    34,    46,    36,    -1,    49,    -1,    33,    34,
      -1,    36,    -1,    -1,    46,    33,    34,    -1,    36,    -1,
      -1,    46,    -1,    -1,    33,    34,    -1,    36,    46,     1,
      -1,     3,     4,     5,     6,     7,     1,    46,     3,     4,
       5,     6,     7,     1,    -1,     3,     4,     5,     6,     7,
       0,     1,   213,     3,   215,   216,   217,   218,     8,    -1,
      10,    33,    34,    -1,    36,    15,    -1,    -1,    33,    34,
      -1,    36,    -1,    -1,    46,    33,    34,    -1,    36,    -1,
      -1,    46,   243,   244,   245,    -1,    -1,    -1,    46,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    41,    -1,    -1,    44,    45,    -1,    47,    48,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    45,    -1,    47,    48,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    41,    -1,    -1,    -1,    45,    -1,    47,    48,    19,
      20,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    37,    -1,    -1,
      -1,    41,    -1,    -1,    -1,    45,    -1,    47,    48,    19,
      20,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    37,    -1,    -1,
      -1,    41,    -1,    -1,    -1,    45,    -1,    47,    48,    19,
      20,    21,    22,    -1,    -1,    19,    20,    21,    22,    -1,
      30,    31,    32,    33,    34,    35,    30,    31,    32,    33,
      -1,    41,    -1,    -1,    -1,    45,    -1,    47,    48,    19,
      20,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    19,    20,    21,
      22,    41,    -1,    -1,    -1,    45,    -1,    47,    30,    31,
      32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,    41,
      -1,    -1,    -1,    45
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     8,    10,    15,    51,    52,    53,    54,
      60,    61,    44,    36,     0,    53,     1,     3,    56,    57,
      58,     1,    60,    62,    63,    64,    41,    42,    43,    36,
      40,    42,    44,    43,    44,     1,     3,    65,    66,    37,
      44,     1,     3,    57,     1,     3,     4,     5,     6,     7,
      33,    34,    36,    46,    49,    81,    82,    83,    84,    86,
      88,    90,    91,    92,    93,    94,    95,    98,     1,    62,
       1,     4,     1,    57,     1,    81,    64,    42,    40,    42,
       1,     9,    12,    13,    16,    18,    38,    44,    67,    68,
      69,    70,    71,    72,    75,    76,    77,    78,    81,    93,
       1,    64,    19,    20,    21,    22,    30,    31,    32,    33,
      34,    35,    41,    45,    47,    48,    85,    87,    89,    36,
      40,     1,    78,     1,    83,    48,    47,    85,    87,    89,
       1,    90,    37,    41,     1,    66,    41,     1,    66,    23,
      24,    25,    26,    27,    28,    29,    44,    79,    80,    44,
      36,    36,     1,    44,    78,    36,     1,    73,    44,    79,
      80,     1,    83,     1,    82,     1,    86,     1,    88,     1,
      90,     1,    78,    96,    97,     1,    78,    37,     1,    82,
       1,    83,     1,    86,     1,    88,     1,    90,     1,    67,
       1,    78,     1,     3,    93,     1,    81,    44,     1,    81,
      74,     1,    17,    55,    59,    60,    74,     1,    78,    42,
      37,    42,    41,    37,    14,    37,    37,    37,    37,     1,
      39,    67,    39,    60,     1,    56,    39,    78,     1,    78,
       1,    68,    69,    81,    67,    68,    67,    68,    68,    69,
      68,    69,    44,    37,    11,    11,    68,    69,    68,    69,
      68,    69
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
#line 249 "c-.y"
    { syntaxTree = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 3:
#line 252 "c-.y"
    {
                               TreeNode *trav = (yyvsp[(1) - (2)].treeNode);
                               if(trav != NULL) {
                                   while (trav->sibling != NULL) trav = trav->sibling;
                                   trav->sibling = (yyvsp[(2) - (2)].treeNode);
                                   (yyval.treeNode) = (yyvsp[(1) - (2)].treeNode);
                               } else {
                                   (yyval.treeNode) = (yyvsp[(2) - (2)].treeNode);
                               }
                            ;}
    break;

  case 4:
#line 262 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 5:
#line 265 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 6:
#line 266 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 7:
#line 267 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 8:
#line 272 "c-.y"
    {
                                yyerrok;
                                TreeNode *complete = (yyvsp[(2) - (3)].treeNode);
                                if(complete != NULL) {
                                    do {
                                        complete->declType = (yyvsp[(1) - (3)].declType);
                                        complete = complete->sibling;

                                    } while(complete != NULL);
                                    (yyval.treeNode) = (yyvsp[(2) - (3)].treeNode);
                                } else {
                                    (yyval.treeNode) = NULL;
                                }
                            ;}
    break;

  case 9:
#line 286 "c-.y"
    { yyerrok; (yyval.treeNode) = NULL; ;}
    break;

  case 10:
#line 289 "c-.y"
    {
                                yyerrok;
                                TreeNode *complete = (yyvsp[(2) - (3)].treeNode);
                                if(complete != NULL) {
                                    do {
                                        complete->declType = (yyvsp[(1) - (3)].treeNode)->declType;
                                        complete->isStatic = (yyvsp[(1) - (3)].treeNode)->isStatic;
                                        complete = complete->sibling;
                                    } while(complete != NULL); 
                                    (yyval.treeNode) = (yyvsp[(2) - (3)].treeNode);
                                } else {
                                    (yyval.treeNode) = NULL;
                                }
                            ;}
    break;

  case 11:
#line 303 "c-.y"
    { yyerrok; (yyval.treeNode) = NULL; ;}
    break;

  case 12:
#line 304 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 13:
#line 307 "c-.y"
    {
                               TreeNode *trav = (yyvsp[(1) - (3)].treeNode);
                               if(trav != NULL) {
                                    while(trav->sibling != NULL) trav = trav->sibling;
                                    trav->sibling = (yyvsp[(3) - (3)].treeNode); 
                                    (yyval.treeNode) = (yyvsp[(1) - (3)].treeNode); 
                                } else {
                                    (yyval.treeNode) = (yyvsp[(3) - (3)].treeNode);
                                }
                            ;}
    break;

  case 14:
#line 317 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 15:
#line 318 "c-.y"
    { yyerrok; (yyval.treeNode) = NULL; ;}
    break;

  case 16:
#line 319 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 17:
#line 323 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 18:
#line 324 "c-.y"
    {
                                (yyvsp[(1) - (3)].treeNode)->child[0] = (yyvsp[(3) - (3)].treeNode); // <- NOT NULL, SHOULD BE $3
                                (yyval.treeNode) = (yyvsp[(1) - (3)].treeNode);  
                            ;}
    break;

  case 19:
#line 328 "c-.y"
    { yyerrok; (yyval.treeNode) = NULL; ;}
    break;

  case 20:
#line 329 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 21:
#line 330 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 22:
#line 333 "c-.y"
    {
                                yyerrok;
                                (yyval.treeNode) = newDeclNode(VarK);
                                (yyval.treeNode)->attr.name = (yyvsp[(1) - (1)].token).value.sval;
                                (yyval.treeNode)->lineno = (yyvsp[(1) - (1)].token).lineno;
                            ;}
    break;

  case 23:
#line 339 "c-.y"
    {
                                yyerrok;
                                (yyval.treeNode) = newDeclNode(VarK);
                                (yyval.treeNode)->attr.name = (yyvsp[(1) - (4)].token).value.sval; 
                                (yyval.treeNode)->isArray = true;
                                (yyval.treeNode)->arrayLen = (yyvsp[(3) - (4)].token).value.ival;
                                (yyval.treeNode)->lineno = (yyvsp[(1) - (4)].token).lineno;
                            ;}
    break;

  case 24:
#line 347 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 25:
#line 348 "c-.y"
    { yyerrok; (yyval.treeNode) = NULL; ;}
    break;

  case 26:
#line 351 "c-.y"
    {
                                (yyval.treeNode) = newDeclNode(VarK);
                                (yyval.treeNode)->isStatic = true;
                                (yyval.treeNode)->declType = (yyvsp[(2) - (2)].declType);
                            ;}
    break;

  case 27:
#line 356 "c-.y"
    {
                                (yyval.treeNode) = newDeclNode(VarK);
                                (yyval.treeNode)->declType = (yyvsp[(1) - (1)].declType);
                            ;}
    break;

  case 28:
#line 362 "c-.y"
    { (yyval.declType) = Int; ;}
    break;

  case 29:
#line 363 "c-.y"
    { (yyval.declType) = Bool; ;}
    break;

  case 30:
#line 364 "c-.y"
    { (yyval.declType) = Char; ;}
    break;

  case 31:
#line 368 "c-.y"
    {
                                (yyval.treeNode) = newDeclNode(FuncK);
                                (yyval.treeNode)->declType = (yyvsp[(1) - (6)].declType);  
                                (yyval.treeNode)->attr.name = (yyvsp[(2) - (6)].token).value.sval;
                                (yyval.treeNode)->child[0] = (yyvsp[(4) - (6)].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[(6) - (6)].treeNode); 
                                (yyval.treeNode)->lineno = (yyvsp[(2) - (6)].token).lineno; // Allows for correct line no
                            ;}
    break;

  case 32:
#line 377 "c-.y"
    {
                               (yyval.treeNode) = newDeclNode(FuncK);
                               (yyval.treeNode)->declType = Void;
                               (yyval.treeNode)->attr.name = (yyvsp[(1) - (5)].token).value.sval;
                               (yyval.treeNode)->child[0] = (yyvsp[(3) - (5)].treeNode);
                               (yyval.treeNode)->child[1] = (yyvsp[(5) - (5)].treeNode); 
                               (yyval.treeNode)->lineno = (yyvsp[(1) - (5)].token).lineno;
                            ;}
    break;

  case 33:
#line 385 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 34:
#line 386 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 35:
#line 387 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 36:
#line 388 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 37:
#line 389 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 38:
#line 392 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 39:
#line 393 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 40:
#line 396 "c-.y"
    {
                                yyerrok;
                                TreeNode *trav = (yyvsp[(1) - (3)].treeNode);
                                if(trav != NULL) {
                                    while(trav->sibling != NULL) trav = trav->sibling;
                                    trav->sibling = (yyvsp[(3) - (3)].treeNode);
                                    (yyval.treeNode) = (yyvsp[(1) - (3)].treeNode);
                                } else {
                                    (yyval.treeNode) = (yyvsp[(3) - (3)].treeNode); 
                                }
                            ;}
    break;

  case 41:
#line 407 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 42:
#line 408 "c-.y"
    { yyerrok; (yyval.treeNode) = NULL; ;}
    break;

  case 43:
#line 409 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 44:
#line 412 "c-.y"
    {
                                TreeNode *complete = (yyvsp[(2) - (2)].treeNode);
                                if(complete != NULL) {
                                    do {
                                        complete->declType = (yyvsp[(1) - (2)].declType);
                                        complete = complete->sibling;
                                    } while(complete != NULL);
                                    (yyval.treeNode) = (yyvsp[(2) - (2)].treeNode);
                                } else {
                                    (yyval.treeNode) = NULL;
                                }
                            ;}
    break;

  case 45:
#line 424 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 46:
#line 427 "c-.y"
    {
                                yyerrok; 
                                TreeNode *trav = (yyvsp[(1) - (3)].treeNode); 
                                if(trav != NULL) {
                                    while(trav->sibling != NULL) trav = trav->sibling;
                                    trav->sibling = (yyvsp[(3) - (3)].treeNode);
                                    (yyval.treeNode) = (yyvsp[(1) - (3)].treeNode);
                                } else { 
                                    (yyval.treeNode) = (yyvsp[(3) - (3)].treeNode);
                                }
                            ;}
    break;

  case 47:
#line 438 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 48:
#line 439 "c-.y"
    { yyerrok; (yyval.treeNode) = NULL; ;}
    break;

  case 49:
#line 440 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 50:
#line 443 "c-.y"
    {
                                yyerrok;
                                (yyval.treeNode) = newDeclNode(ParamK);
                                (yyval.treeNode)->attr.name = (yyvsp[(1) - (1)].token).value.sval;
                            ;}
    break;

  case 51:
#line 448 "c-.y"
    {
                                yyerrok;
                                (yyval.treeNode) = newDeclNode(ParamK);
                                (yyval.treeNode)->attr.name = (yyvsp[(1) - (3)].token).value.sval;
                                (yyval.treeNode)->isArray = true;
                            ;}
    break;

  case 52:
#line 454 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 53:
#line 459 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 54:
#line 460 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 55:
#line 463 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 56:
#line 464 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 57:
#line 465 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 58:
#line 466 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 59:
#line 467 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 60:
#line 470 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 61:
#line 473 "c-.y"
    {
                                (yyval.treeNode) = newStmtNode(IfK);
                                (yyval.treeNode)->attr.name = (yyvsp[(1) - (7)].token).rtxt;
                                (yyval.treeNode)->child[0] = (yyvsp[(3) - (7)].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[(5) - (7)].treeNode);
                                (yyval.treeNode)->child[2] = (yyvsp[(7) - (7)].treeNode);
                                (yyval.treeNode)->lineno = (yyvsp[(1) - (7)].token).lineno;
                            ;}
    break;

  case 62:
#line 481 "c-.y"
    {
                                (yyval.treeNode) = newStmtNode(WhileK);
                                (yyval.treeNode)->attr.name = (yyvsp[(1) - (5)].token).rtxt;
                                (yyval.treeNode)->child[0] = (yyvsp[(3) - (5)].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[(5) - (5)].treeNode);
                                (yyval.treeNode)->lineno = (yyvsp[(1) - (5)].token).lineno;
                            ;}
    break;

  case 63:
#line 488 "c-.y"
    {
                                (yyval.treeNode) = newStmtNode(ForK);
                                (yyval.treeNode)->attr.name = (yyvsp[(1) - (7)].token).rtxt;
                                (yyval.treeNode)->child[0] = (yyvsp[(3) - (7)].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[(5) - (7)].treeNode);
                                (yyval.treeNode)->child[2] = (yyvsp[(7) - (7)].treeNode);
                                (yyval.treeNode)->lineno = (yyvsp[(1) - (7)].token).lineno;
                            ;}
    break;

  case 64:
#line 496 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 65:
#line 497 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 66:
#line 498 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 67:
#line 499 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 68:
#line 502 "c-.y"
    {
                                (yyval.treeNode) = newStmtNode(IfK);
                                (yyval.treeNode)->attr.name = (yyvsp[(1) - (7)].token).rtxt;
                                (yyval.treeNode)->child[0] = (yyvsp[(3) - (7)].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[(5) - (7)].treeNode);
                                (yyval.treeNode)->child[2] = (yyvsp[(7) - (7)].treeNode);
                                (yyval.treeNode)->lineno = (yyvsp[(1) - (7)].token).lineno;
                            ;}
    break;

  case 69:
#line 510 "c-.y"
    {
                                (yyval.treeNode) = newStmtNode(IfK);
                                (yyval.treeNode)->attr.name = (yyvsp[(1) - (5)].token).rtxt;
                                (yyval.treeNode)->child[0] = (yyvsp[(3) - (5)].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[(5) - (5)].treeNode);
                                (yyval.treeNode)->lineno = (yyvsp[(1) - (5)].token).lineno;
                            ;}
    break;

  case 70:
#line 517 "c-.y"
    {
                                (yyval.treeNode) = newStmtNode(WhileK);
                                (yyval.treeNode)->attr.name = (yyvsp[(1) - (5)].token).rtxt;
                                (yyval.treeNode)->child[0] = (yyvsp[(3) - (5)].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[(5) - (5)].treeNode);
                                (yyval.treeNode)->lineno = (yyvsp[(1) - (5)].token).lineno;
                            ;}
    break;

  case 71:
#line 524 "c-.y"
    {
                                (yyval.treeNode) = newStmtNode(ForK);
                                (yyval.treeNode)->attr.name = (yyvsp[(1) - (7)].token).rtxt;
                                (yyval.treeNode)->child[0] = (yyvsp[(3) - (7)].treeNode); 
                                (yyval.treeNode)->child[1] = (yyvsp[(5) - (7)].treeNode);
                                (yyval.treeNode)->child[2] = (yyvsp[(7) - (7)].treeNode);
                                (yyval.treeNode)->lineno = (yyvsp[(1) - (7)].token).lineno;
                            ;}
    break;

  case 72:
#line 532 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 73:
#line 533 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 74:
#line 534 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 75:
#line 535 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 76:
#line 538 "c-.y"
    {
                               yyerrok;
                               (yyval.treeNode) = newStmtNode(CompK); 
                               (yyval.treeNode)->child[0] = (yyvsp[(2) - (4)].treeNode);
                               (yyval.treeNode)->child[1] = (yyvsp[(3) - (4)].treeNode); 
                               (yyval.treeNode)->lineno = (yyvsp[(1) - (4)].token).lineno;
                            ;}
    break;

  case 77:
#line 545 "c-.y"
    { yyerrok; (yyval.treeNode) = NULL; ;}
    break;

  case 78:
#line 546 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 79:
#line 549 "c-.y"
    {
                                TreeNode *trav = (yyvsp[(1) - (2)].treeNode); 
                                if(trav != NULL) {
                                    while(trav->sibling != NULL) trav = trav->sibling;
                                    trav->sibling = (yyvsp[(2) - (2)].treeNode);
                                    (yyval.treeNode) = (yyvsp[(1) - (2)].treeNode);
                                } else {
                                    (yyval.treeNode) = (yyvsp[(2) - (2)].treeNode); 
                                }
                            ;}
    break;

  case 80:
#line 559 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 81:
#line 562 "c-.y"
    {
                                TreeNode *trav = (yyvsp[(1) - (2)].treeNode); 
                                if(trav != NULL) {
                                    while(trav->sibling != NULL) trav = trav->sibling;
                                    trav->sibling = (yyvsp[(2) - (2)].treeNode);
                                    (yyval.treeNode) = (yyvsp[(1) - (2)].treeNode);
                                } else {
                                    (yyval.treeNode) = (yyvsp[(2) - (2)].treeNode);
                                }
                            ;}
    break;

  case 82:
#line 572 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 83:
#line 573 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 84:
#line 576 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (2)].treeNode); yyerrok; ;}
    break;

  case 85:
#line 577 "c-.y"
    { (yyval.treeNode) = NULL; yyerrok; ;}
    break;

  case 86:
#line 578 "c-.y"
    { yyerrok; (yyval.treeNode) = NULL; ;}
    break;

  case 87:
#line 582 "c-.y"
    { 
                                yyerrok;
                                (yyval.treeNode) = newStmtNode(ReturnK);
                                (yyval.treeNode)->attr.name = (yyvsp[(1) - (2)].token).rtxt;
                                (yyval.treeNode)->lineno = (yyvsp[(1) - (2)].token).lineno;
                            ;}
    break;

  case 88:
#line 588 "c-.y"
    {
                                yyerrok;
                                (yyval.treeNode) = newStmtNode(ReturnK);
                                (yyval.treeNode)->attr.name = (yyvsp[(1) - (3)].token).rtxt;
                                (yyval.treeNode)->child[0] = (yyvsp[(2) - (3)].treeNode);
                                (yyval.treeNode)->lineno = (yyvsp[(1) - (3)].token).lineno;
                            ;}
    break;

  case 89:
#line 597 "c-.y"
    { 
                                yyerrok;
                                (yyval.treeNode) = newStmtNode(BreakK);
                                (yyval.treeNode)->attr.name = (yyvsp[(1) - (2)].token).rtxt;
                            ;}
    break;

  case 90:
#line 607 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(AssignK);
                                (yyval.treeNode)->attr.name = (yyvsp[(2) - (3)].token).rtxt;
                                (yyval.treeNode)->child[0] = (yyvsp[(1) - (3)].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[(3) - (3)].treeNode);
                                (yyval.treeNode)->lineno = (yyvsp[(2) - (3)].token).lineno;
                            ;}
    break;

  case 91:
#line 614 "c-.y"
    {
                                yyerrok;
                                (yyval.treeNode) = newExprNode(AssignK);
                                (yyval.treeNode)->attr.name = (yyvsp[(2) - (2)].token).rtxt;
                                (yyval.treeNode)->child[0] = (yyvsp[(1) - (2)].treeNode);
                                (yyval.treeNode)->lineno = (yyvsp[(2) - (2)].token).lineno;
                            ;}
    break;

  case 92:
#line 621 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 93:
#line 622 "c-.y"
    { yyerrok; (yyval.treeNode) = NULL; ;}
    break;

  case 94:
#line 623 "c-.y"
    { yyerrok; (yyval.treeNode) = NULL; ;}
    break;

  case 95:
#line 624 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 96:
#line 625 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 97:
#line 628 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 98:
#line 629 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 99:
#line 630 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 100:
#line 631 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 101:
#line 632 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 102:
#line 635 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 103:
#line 636 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 104:
#line 639 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(OpK);
                                (yyval.treeNode)->attr.name = (yyvsp[(2) - (3)].token).rtxt;
                                (yyval.treeNode)->child[0] = (yyvsp[(1) - (3)].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[(3) - (3)].treeNode);
                            ;}
    break;

  case 105:
#line 645 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 106:
#line 646 "c-.y"
    { yyerrok; (yyval.treeNode) = NULL; ;}
    break;

  case 107:
#line 647 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 108:
#line 648 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 109:
#line 651 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(OpK);
                                (yyval.treeNode)->attr.name = (yyvsp[(2) - (3)].token).rtxt;
                                (yyval.treeNode)->child[0] = (yyvsp[(1) - (3)].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[(3) - (3)].treeNode); 
                            ;}
    break;

  case 110:
#line 657 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 111:
#line 658 "c-.y"
    { yyerrok; (yyval.treeNode) = NULL; ;}
    break;

  case 112:
#line 659 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 113:
#line 660 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 114:
#line 663 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(OpK);
                                (yyval.treeNode)->attr.name = (yyvsp[(1) - (2)].token).rtxt;
                                (yyval.treeNode)->child[0] = (yyvsp[(2) - (2)].treeNode);
                            ;}
    break;

  case 115:
#line 668 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 116:
#line 669 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 117:
#line 672 "c-.y"
    {
                               (yyval.treeNode) = newExprNode(OpK);
                               (yyval.treeNode)->attr.name = (yyvsp[(2) - (3)].token).rtxt;
                               (yyval.treeNode)->child[0] = (yyvsp[(1) - (3)].treeNode);
                               (yyval.treeNode)->child[1] = (yyvsp[(3) - (3)].treeNode);
                            ;}
    break;

  case 118:
#line 678 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 119:
#line 679 "c-.y"
    { yyerrok; (yyval.treeNode) = NULL; ;}
    break;

  case 120:
#line 680 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 121:
#line 681 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 122:
#line 684 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 123:
#line 685 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 124:
#line 686 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 125:
#line 687 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 126:
#line 688 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 127:
#line 689 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 128:
#line 692 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(OpK);
                                (yyval.treeNode)->attr.name = (yyvsp[(2) - (3)].token).rtxt;
                                (yyval.treeNode)->child[0] = (yyvsp[(1) - (3)].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[(3) - (3)].treeNode);
                            ;}
    break;

  case 129:
#line 698 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 130:
#line 699 "c-.y"
    { yyerrok; (yyval.treeNode) = NULL; ;}
    break;

  case 131:
#line 700 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 132:
#line 701 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 133:
#line 704 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 134:
#line 705 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 135:
#line 708 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(OpK);
                                (yyval.treeNode)->attr.name = (yyvsp[(2) - (3)].token).rtxt;
                                (yyval.treeNode)->child[0] = (yyvsp[(1) - (3)].treeNode);
                                (yyval.treeNode)->child[1] = (yyvsp[(3) - (3)].treeNode);
                                (yyval.treeNode)->lineno = (yyvsp[(2) - (3)].token).lineno;
                            ;}
    break;

  case 136:
#line 715 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 137:
#line 716 "c-.y"
    { yyerrok; (yyval.treeNode) = NULL; ;}
    break;

  case 138:
#line 717 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 139:
#line 718 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 140:
#line 721 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 141:
#line 722 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 142:
#line 723 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 143:
#line 726 "c-.y"
    {
                                (yyval.treeNode) = newExprNode(OpK);
                                (yyval.treeNode)->attr.name = (yyvsp[(1) - (2)].token).rtxt;
                                (yyval.treeNode)->child[0] = (yyvsp[(2) - (2)].treeNode);
                            ;}
    break;

  case 144:
#line 731 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 145:
#line 732 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 146:
#line 735 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 147:
#line 736 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 148:
#line 737 "c-.y"
    { (yyval.token) = (yyvsp[(1) - (1)].token); ;}
    break;

  case 149:
#line 740 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 150:
#line 741 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 151:
#line 744 "c-.y"
    {
                                yyerrok;
                                (yyval.treeNode) = newExprNode(IdK); 
                                (yyval.treeNode)->attr.name = (yyvsp[(1) - (1)].token).value.sval;
                            ;}
    break;

  case 152:
#line 749 "c-.y"
    {
                                yyerrok; 
                                (yyval.treeNode) = newExprNode(IdK);
                                (yyval.treeNode)->attr.name = (yyvsp[(1) - (4)].token).value.sval;
                                (yyval.treeNode)->child[0] = (yyvsp[(3) - (4)].treeNode);
                            ;}
    break;

  case 153:
#line 755 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 154:
#line 756 "c-.y"
    { yyerrok; (yyval.treeNode) = NULL; ;}
    break;

  case 155:
#line 759 "c-.y"
    { yyerrok; (yyval.treeNode) = (yyvsp[(2) - (3)].treeNode); ;}
    break;

  case 156:
#line 760 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 157:
#line 761 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 158:
#line 762 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 159:
#line 765 "c-.y"
    {
                                yyerrok; 
                                (yyval.treeNode) = newExprNode(CallK);
                                (yyval.treeNode)->attr.name = (yyvsp[(1) - (4)].token).value.sval;
                                (yyval.treeNode)->child[0] = (yyvsp[(3) - (4)].treeNode);
                            ;}
    break;

  case 160:
#line 771 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 161:
#line 774 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 162:
#line 775 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 163:
#line 778 "c-.y"
    {
                                yyerrok;
                                TreeNode *trav = (yyvsp[(1) - (3)].treeNode); 
                                if(trav != NULL) {
                                    while(trav->sibling != NULL) trav = trav->sibling;
                                    trav->sibling = (yyvsp[(3) - (3)].treeNode);
                                    (yyval.treeNode) = (yyvsp[(1) - (3)].treeNode);
                                } else {
                                    (yyval.treeNode) = (yyvsp[(3) - (3)].treeNode);
                                }
                            ;}
    break;

  case 164:
#line 789 "c-.y"
    { (yyval.treeNode) = (yyvsp[(1) - (1)].treeNode); ;}
    break;

  case 165:
#line 790 "c-.y"
    { yyerrok; (yyval.treeNode) = NULL; ;}
    break;

  case 166:
#line 791 "c-.y"
    { (yyval.treeNode) = NULL; ;}
    break;

  case 167:
#line 794 "c-.y"
    {
                                yyerrok;
                                (yyval.treeNode) = newExprNode(ConstK); 
                                (yyval.treeNode)->attr.ivalue = (yyvsp[(1) - (1)].token).value.ival; 
                                (yyval.treeNode)->declType = Int;
                            ;}
    break;

  case 168:
#line 800 "c-.y"
    { 
                                yyerrok;
                                (yyval.treeNode) = newExprNode(ConstK); 
                                (yyval.treeNode)->attr.cvalue = (yyvsp[(1) - (1)].token).value.cval;
                                (yyval.treeNode)->declType = Char;
                            ;}
    break;

  case 169:
#line 806 "c-.y"
    { 
                                yyerrok;
                                (yyval.treeNode) = newExprNode(ConstK); 
                                (yyval.treeNode)->attr.svalue = (yyvsp[(1) - (1)].token).value.sval; 
                                (yyval.treeNode)->declType = Char; 
                                (yyval.treeNode)->isArray = true;
                            ;}
    break;

  case 170:
#line 813 "c-.y"
    { 
                                yyerrok;
                                (yyval.treeNode) = newExprNode(ConstK); 
                                (yyval.treeNode)->attr.ivalue = (yyvsp[(1) - (1)].token).value.ival; 
                                (yyval.treeNode)->declType = Bool;
                            ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3085 "c-.tab.c"
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


#line 821 "c-.y"

int main(int argc, char** argv) {
    initTokenMaps(); // Used for verbose error checking

    // Get cmd line option arguments if they exist
    int opt;
    bool print = false;
    bool printAn = false;
    char* outfile = NULL;
    char* infile = NULL;
    while(optind < argc) {
        if((opt = getopt(argc, argv, "dpPo:")) != EOF) {
            switch(opt) { //in case we add more options
                default:
                    abort(); break;
                case 'd':
                    yydebug = 1;
                    break;
                case 'p':
                    print = true;
                    break;
                case 'P':
                    printAn = true;
                    break;
                case 'o':
                    outfile = optarg; 
                    break;
            }
        } else { // If EOF, we hit an unexpected argument. It's the input file. 
            infile = argv[optind];
            optind++;
        }
    }

    //printf("in %s out %s\n", infile, outfile);

    // If there's a trailing argument, it must be the filename. 
    if(argc > 1) {
        FILE *iFile;
        iFile = fopen(infile, "r");
        if(!iFile) {
            printf("File not found: %s\n", infile);
            exit(-1);
        }
        yyin = iFile;
    }
    
    // Start the scanner now that our options and yyin have been changed (or not). 
    do {
        yyparse();
    } while(!feof(yyin)); 

    if(print && numerrors == 0) {
        printTree(syntaxTree, -1, false, false);
    }

    if(numerrors == 0 && numwarnings == 0) {
        IOLibrary(syntaxTree);
        semantics(syntaxTree, numerrors, numwarnings);
    }

    if(numerrors == 0 && numwarnings == 0 && printAn) {
        printTree(syntaxTree, -1, true, true); // print annotated syntax tree
    }

    if(printAn) printf("Offset for end of global space: %i\n", gOffset);
    printf("Number of warnings: %i\n", numwarnings);
    printf("Number of errors: %i\n", numerrors);
    
    if(numerrors == 0) {
        if(outfile == NULL) {
            // No file argument:
            string nofilearg = infile;
            while(nofilearg.find("/", 0) != string::npos) {
                nofilearg = nofilearg.substr(nofilearg.find("/", 0) + 1, nofilearg.length());
            }
            nofilearg = nofilearg.substr(0, nofilearg.length() - 2);
            nofilearg += "tm";
            generateCode(syntaxTree, returnSymbolTable(), (char *)nofilearg.c_str(), infile);
        } else if(strcmp(outfile, "-") == 0) {
            // Do that one -o - to stdout thing. 
            generateCode(syntaxTree, returnSymbolTable(), outfile, infile);
        } else if(outfile != NULL) {
            //outfile++;
            string outfiletm = outfile;
            //outfiletm += ".tm";
            // We have an output file argument so make the a.out be filename.out from -o filename
            generateCode(syntaxTree, returnSymbolTable(), (char *)outfiletm.c_str(), infile);
        }
    }

    return 0;
}

