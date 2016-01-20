%{
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

%}

%union {
    Token token; 
    TreeNode *treeNode;
    DeclType declType;
    char *cstring;
}

%type <treeNode>        program
                        declaration
                        declaration_list
                       
                        /* Declarations */
                        var_declaration
                        scoped_type_specifier
                        scoped_var_declaration
                        var_decl_list
                        var_decl_initialize
                        var_decl_id
                        
                        /* Functions (Declarations) */
                        fun_declaration
                        params
                        param_list
                        param_type_list
                        param_id_list
                        param_id

                        /* Statements */
                        statement
                        matched
                        unmatched
                        compound_stmt
                        local_declarations
                        statement_list
                        expression_stmt
                        matched_conditional
                        unmatched_conditional
                        return_stmt
                        break_stmt
                        
                        /* Expressions */
                        expression
                        simple_expression
                        and_expression
                        unary_rel_expression
                        rel_expression
                        sum_expression
                        term
                        unary_expression
                        factor
                        mutable
                        immutable
                        call 
                        args
                        arg_list
                        constant

%type <declType> type_specifier 

%type <token>   unaryop 
                relop 
                mulop 
                sumop
                binary_assign
                unary_assign
                        
%token <token>  ID
                NUMCONST
                STRINGCONST
                CHARCONST
                BOOLCONST
                BOOL BREAK CHAR ELSE FOREACH IF IN INT RETURN STATIC WHILE
                NOTEQ EQ LESSEQ GRTEQ INC DEC ADDASS SUBASS MULASS DIVASS
                '=' '<' '>' '+' '-' '*' '/'
                '(' ')' '{' '}' '[' ']'
                ',' ':' ';' '%' '?' '&' '|' '!'
%%
program                 : declaration_list { syntaxTree = $1; }    
                        ;

declaration_list        : declaration_list declaration {
                               TreeNode *trav = $1;
                               if(trav != NULL) {
                                   while (trav->sibling != NULL) trav = trav->sibling;
                                   trav->sibling = $2;
                                   $$ = $1;
                               } else {
                                   $$ = $2;
                               }
                            }
                        | declaration { $$ = $1; }
                        ;

declaration             : var_declaration { $$ = $1; }
                        | fun_declaration { $$ = $1; }
                        | error { $$ = NULL; }
                        ;

// Variable Declaration

var_declaration         : type_specifier var_decl_list ';' {
                                yyerrok;
                                TreeNode *complete = $2;
                                if(complete != NULL) {
                                    do {
                                        complete->declType = $1;
                                        complete = complete->sibling;

                                    } while(complete != NULL);
                                    $$ = $2;
                                } else {
                                    $$ = NULL;
                                }
                            }
                        | error ';' { yyerrok; $$ = NULL; }
                        ;

scoped_var_declaration  : scoped_type_specifier var_decl_list ';' {
                                yyerrok;
                                TreeNode *complete = $2;
                                if(complete != NULL) {
                                    do {
                                        complete->declType = $1->declType;
                                        complete->isStatic = $1->isStatic;
                                        complete = complete->sibling;
                                    } while(complete != NULL); 
                                    $$ = $2;
                                } else {
                                    $$ = NULL;
                                }
                            }
                        | error { yyerrok; $$ = NULL; }
                        | scoped_type_specifier error  { $$ = NULL; }
                        ;

var_decl_list           : var_decl_list ',' var_decl_initialize {
                               TreeNode *trav = $1;
                               if(trav != NULL) {
                                    while(trav->sibling != NULL) trav = trav->sibling;
                                    trav->sibling = $3; 
                                    $$ = $1; 
                                } else {
                                    $$ = $3;
                                }
                            }
                        | var_decl_initialize { $$ = $1; }
                        | error ',' var_decl_initialize { yyerrok; $$ = NULL; }
                        | var_decl_list ',' error { $$ = NULL; }
                        ;

// Missing error on linbad on line 107 unexpected a
var_decl_initialize     : var_decl_id { $$ = $1; }
                        | var_decl_id ':' simple_expression {
                                $1->child[0] = $3; // <- NOT NULL, SHOULD BE $3
                                $$ = $1;  
                            }
                        | error ':' simple_expression { yyerrok; $$ = NULL; }
                        | var_decl_id ':' error { $$ = NULL; }
                        | error { $$ = NULL; }
                        ;

var_decl_id             : ID {
                                yyerrok;
                                $$ = newDeclNode(VarK);
                                $$->attr.name = $1.value.sval;
                                $$->lineno = $1.lineno;
                            }
                        | ID '[' NUMCONST ']' {
                                yyerrok;
                                $$ = newDeclNode(VarK);
                                $$->attr.name = $1.value.sval; 
                                $$->isArray = true;
                                $$->arrayLen = $3.value.ival;
                                $$->lineno = $1.lineno;
                            }
                        | ID '[' error { $$ = NULL; }
                        | error ']' { yyerrok; $$ = NULL; }
                        ;

scoped_type_specifier   : STATIC type_specifier {
                                $$ = newDeclNode(VarK);
                                $$->isStatic = true;
                                $$->declType = $2;
                            }
                        | type_specifier {
                                $$ = newDeclNode(VarK);
                                $$->declType = $1;
                            }
                        ;

type_specifier          : INT { $$ = Int; }
                        | BOOL { $$ = Bool; }
                        | CHAR { $$ = Char; }
                        ;
// Function Declaration

fun_declaration         : type_specifier ID '(' params ')' statement {
                                $$ = newDeclNode(FuncK);
                                $$->declType = $1;  
                                $$->attr.name = $2.value.sval;
                                $$->child[0] = $4;
                                $$->child[1] = $6; 
                                $$->lineno = $2.lineno; // Allows for correct line no
                            }

                        | ID '(' params ')' statement {
                               $$ = newDeclNode(FuncK);
                               $$->declType = Void;
                               $$->attr.name = $1.value.sval;
                               $$->child[0] = $3;
                               $$->child[1] = $5; 
                               $$->lineno = $1.lineno;
                            }
                        | type_specifier error { $$ = NULL; }
                        | type_specifier ID '(' error { $$ = NULL; }
                        | type_specifier ID '(' params ')' error { $$ = NULL; }
                        | ID '(' params ')' error { $$ = NULL; } 
                        | ID '(' error { $$ = NULL; }
                        ;

params                  : param_list { $$ = $1; }
                        | { $$ = NULL; }
                        ;

param_list              : param_list ';' param_type_list {
                                yyerrok;
                                TreeNode *trav = $1;
                                if(trav != NULL) {
                                    while(trav->sibling != NULL) trav = trav->sibling;
                                    trav->sibling = $3;
                                    $$ = $1;
                                } else {
                                    $$ = $3; 
                                }
                            }
                        | param_type_list { $$ = $1; }
                        | error ';' param_type_list { yyerrok; $$ = NULL; }
                        | param_list ';' error { $$ = NULL; } 
                        ;

param_type_list         : type_specifier param_id_list {
                                TreeNode *complete = $2;
                                if(complete != NULL) {
                                    do {
                                        complete->declType = $1;
                                        complete = complete->sibling;
                                    } while(complete != NULL);
                                    $$ = $2;
                                } else {
                                    $$ = NULL;
                                }
                            }
                        | type_specifier error { $$ = NULL; }
                        ;

param_id_list           : param_id_list ',' param_id {
                                yyerrok; 
                                TreeNode *trav = $1; 
                                if(trav != NULL) {
                                    while(trav->sibling != NULL) trav = trav->sibling;
                                    trav->sibling = $3;
                                    $$ = $1;
                                } else { 
                                    $$ = $3;
                                }
                            }
                        | param_id { $$ = $1; }
                        | error ',' param_id { yyerrok; $$ = NULL; }
                        | param_id_list ',' error { $$ = NULL; }
                        ;

param_id                : ID {
                                yyerrok;
                                $$ = newDeclNode(ParamK);
                                $$->attr.name = $1.value.sval;
                            }
                        | ID '[' ']' {
                                yyerrok;
                                $$ = newDeclNode(ParamK);
                                $$->attr.name = $1.value.sval;
                                $$->isArray = true;
                            }
                        | error { $$ = NULL; }
                        ;

// Statement

statement               : unmatched { $$ = $1; }
                        | matched { $$ = $1; }
                        ;

matched                 : matched_conditional { $$ = $1; }
                        | expression_stmt { $$ = $1; }
                        | compound_stmt { $$ = $1; }
                        | return_stmt { $$ = $1; }
                        | break_stmt { $$ = $1; }
                        ;

unmatched               : unmatched_conditional { $$ = $1; }
                        ;

matched_conditional     : IF '(' simple_expression ')' matched ELSE matched {
                                $$ = newStmtNode(IfK);
                                $$->attr.name = $1.rtxt;
                                $$->child[0] = $3;
                                $$->child[1] = $5;
                                $$->child[2] = $7;
                                $$->lineno = $1.lineno;
                            }
                        | WHILE '(' simple_expression ')' matched {
                                $$ = newStmtNode(WhileK);
                                $$->attr.name = $1.rtxt;
                                $$->child[0] = $3;
                                $$->child[1] = $5;
                                $$->lineno = $1.lineno;
                            }
                        | FOREACH '(' mutable IN simple_expression ')' matched {
                                $$ = newStmtNode(ForK);
                                $$->attr.name = $1.rtxt;
                                $$->child[0] = $3;
                                $$->child[1] = $5;
                                $$->child[2] = $7;
                                $$->lineno = $1.lineno;
                            }
                        | IF '(' error ')' matched ELSE matched { $$ = NULL; }
                        | WHILE '(' error ')' matched { $$ = NULL; }
                        | FOREACH '(' error ')' matched { $$ = NULL; }
                        | error { $$ = NULL; }
                        ;

unmatched_conditional   : IF '(' simple_expression ')' matched ELSE unmatched {
                                $$ = newStmtNode(IfK);
                                $$->attr.name = $1.rtxt;
                                $$->child[0] = $3;
                                $$->child[1] = $5;
                                $$->child[2] = $7;
                                $$->lineno = $1.lineno;
                            }
                        | IF '(' simple_expression ')' statement {
                                $$ = newStmtNode(IfK);
                                $$->attr.name = $1.rtxt;
                                $$->child[0] = $3;
                                $$->child[1] = $5;
                                $$->lineno = $1.lineno;
                            }
                        | WHILE '(' simple_expression ')' unmatched {
                                $$ = newStmtNode(WhileK);
                                $$->attr.name = $1.rtxt;
                                $$->child[0] = $3;
                                $$->child[1] = $5;
                                $$->lineno = $1.lineno;
                            }
                        | FOREACH '(' mutable IN simple_expression ')' unmatched {
                                $$ = newStmtNode(ForK);
                                $$->attr.name = $1.rtxt;
                                $$->child[0] = $3; 
                                $$->child[1] = $5;
                                $$->child[2] = $7;
                                $$->lineno = $1.lineno;
                            }
                        | IF '(' error ')' matched ELSE unmatched { $$ = NULL; }
                        | IF '(' error ')' statement { $$ = NULL; }
                        | WHILE '(' error ')' unmatched { $$ = NULL; }
                        | FOREACH '(' error ')' unmatched { $$ = NULL; }
                        ;

compound_stmt           : '{' local_declarations statement_list '}' {
                               yyerrok;
                               $$ = newStmtNode(CompK); 
                               $$->child[0] = $2;
                               $$->child[1] = $3; 
                               $$->lineno = $1.lineno;
                            }
                        | '{' local_declarations error '}' { yyerrok; $$ = NULL; }
                        | '{' error statement_list '}' { $$ = NULL; }
                        ;

local_declarations      : local_declarations scoped_var_declaration {
                                TreeNode *trav = $1; 
                                if(trav != NULL) {
                                    while(trav->sibling != NULL) trav = trav->sibling;
                                    trav->sibling = $2;
                                    $$ = $1;
                                } else {
                                    $$ = $2; 
                                }
                            }
                        | { $$ = NULL; }      
                        ;

statement_list          : statement_list statement {
                                TreeNode *trav = $1; 
                                if(trav != NULL) {
                                    while(trav->sibling != NULL) trav = trav->sibling;
                                    trav->sibling = $2;
                                    $$ = $1;
                                } else {
                                    $$ = $2;
                                }
                            }
                        | { $$ = NULL; }
                        | statement_list error { $$ = NULL; }
                        ;

expression_stmt         : expression ';' { $$ = $1; yyerrok; }
                        | ';' { $$ = NULL; yyerrok; }
                        | error ';' { yyerrok; $$ = NULL; }
                        ;


return_stmt             : RETURN ';' { 
                                yyerrok;
                                $$ = newStmtNode(ReturnK);
                                $$->attr.name = $1.rtxt;
                                $$->lineno = $1.lineno;
                            }
                        | RETURN expression ';' {
                                yyerrok;
                                $$ = newStmtNode(ReturnK);
                                $$->attr.name = $1.rtxt;
                                $$->child[0] = $2;
                                $$->lineno = $1.lineno;
                            }
                        ;

break_stmt              : BREAK ';' { 
                                yyerrok;
                                $$ = newStmtNode(BreakK);
                                $$->attr.name = $1.rtxt;
                            }
                        ;

// Expression

// Questioning the validity of error binary yyerrok and 
expression              : mutable binary_assign expression {
                                $$ = newExprNode(AssignK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->child[1] = $3;
                                $$->lineno = $2.lineno;
                            }
                        | mutable unary_assign {
                                yyerrok;
                                $$ = newExprNode(AssignK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->lineno = $2.lineno;
                            }
                        | simple_expression { $$ = $1; }
                        | error unary_assign { yyerrok; $$ = NULL; }
                        | error binary_assign expression { yyerrok; $$ = NULL; }
                        | mutable binary_assign error { $$ = NULL; }
                        | error binary_assign error { $$ = NULL; }
                        ;

binary_assign           : '=' { $$ = $1; }
                        | ADDASS { $$ = $1; }
                        | SUBASS { $$ = $1; }
                        | MULASS { $$ = $1; }
                        | DIVASS { $$ = $1; }
                        ;

unary_assign            : INC { $$ = $1; }
                        | DEC { $$ = $1; }
                        ;

simple_expression       : simple_expression '|' and_expression {
                                $$ = newExprNode(OpK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->child[1] = $3;
                            }
                        | and_expression { $$ = $1; }
                        | error '|' and_expression { yyerrok; $$ = NULL; }
                        | simple_expression '|' error { $$ = NULL; }
                        | error '|' error { $$ = NULL; }
                        ;

and_expression          : and_expression '&' unary_rel_expression {
                                $$ = newExprNode(OpK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->child[1] = $3; 
                            }
                        | unary_rel_expression { $$ = $1; }
                        | error '&' unary_rel_expression { yyerrok; $$ = NULL; }
                        | and_expression '&' error { $$ = NULL; }
                        | error '&' error { $$ = NULL; } 
                        ;

unary_rel_expression    : '!' unary_rel_expression {
                                $$ = newExprNode(OpK);
                                $$->attr.name = $1.rtxt;
                                $$->child[0] = $2;
                            }
                        | rel_expression { $$ = $1; }
                        | '!' error { $$ = NULL; }
                        ;

rel_expression          : sum_expression relop sum_expression {
                               $$ = newExprNode(OpK);
                               $$->attr.name = $2.rtxt;
                               $$->child[0] = $1;
                               $$->child[1] = $3;
                            }
                        | sum_expression { $$ = $1; }
                        | error relop sum_expression { yyerrok; $$ = NULL; }
                        | sum_expression relop error { $$ = NULL; }
                        | error relop error { $$ = NULL; }
                        ;

relop                   : LESSEQ { $$ = $1; }
                        | '<' { $$ = $1; }
                        | '>' { $$ = $1; }
                        | GRTEQ { $$ = $1; }
                        | EQ { $$ = $1; }
                        | NOTEQ { $$ = $1; }
                        ;

sum_expression          : sum_expression sumop term {
                                $$ = newExprNode(OpK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->child[1] = $3;
                            }
                        | term { $$ = $1; }
                        | error sumop term { yyerrok; $$ = NULL; }
                        | sum_expression sumop error { $$ = NULL; }
                        | error sumop error { $$ = NULL; } 
                        ;

sumop                   : '+' { $$ = $1; }
                        | '-' { $$ = $1; }
                        ;

term                    : term mulop unary_expression {
                                $$ = newExprNode(OpK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->child[1] = $3;
                                $$->lineno = $2.lineno;
                            }
                        | unary_expression { $$ = $1; }
                        | error mulop unary_expression { yyerrok; $$ = NULL; }
                        | term mulop error { $$ = NULL; }
                        | error mulop error { $$ = NULL; } 
                        ;

mulop                   : '*' { $$ = $1; } 
                        | '/' { $$ = $1; }
                        | '%' { $$ = $1; }
                        ;

unary_expression        : unaryop unary_expression {
                                $$ = newExprNode(OpK);
                                $$->attr.name = $1.rtxt;
                                $$->child[0] = $2;
                            }
                        | factor { $$ = $1; }
                        | unaryop error { $$ = NULL; }
                        ;

unaryop                 : '-' { $$ = $1; }
                        | '*' { $$ = $1; }
                        | '?' { $$ = $1; }
                        ;

factor                  : immutable { $$ = $1; } 
                        | mutable { $$ = $1; }
                        ;

mutable                 : ID {
                                yyerrok;
                                $$ = newExprNode(IdK); 
                                $$->attr.name = $1.value.sval;
                            } 
                        | ID '[' expression ']' {
                                yyerrok; 
                                $$ = newExprNode(IdK);
                                $$->attr.name = $1.value.sval;
                                $$->child[0] = $3;
                            }
                        | ID '[' error { $$ = NULL; }
                        | error ']' { yyerrok; $$ = NULL; } 
                        ;
        
immutable               : '(' expression ')' { yyerrok; $$ = $2; }
                        | call { $$ = $1; }
                        | constant { $$ = $1; }
                        | '(' error { $$ = NULL; } 
                        ;

call                    : ID '(' args ')' {
                                yyerrok; 
                                $$ = newExprNode(CallK);
                                $$->attr.name = $1.value.sval;
                                $$->child[0] = $3;
                            }
                        | ID '(' error { $$ = NULL; }
                        ;

args                    : arg_list { $$ = $1; }
                        | { $$ = NULL; }
                        ;

arg_list                : arg_list ',' expression {
                                yyerrok;
                                TreeNode *trav = $1; 
                                if(trav != NULL) {
                                    while(trav->sibling != NULL) trav = trav->sibling;
                                    trav->sibling = $3;
                                    $$ = $1;
                                } else {
                                    $$ = $3;
                                }
                            }
                        | expression { $$ = $1; }
                        | error ',' expression { yyerrok; $$ = NULL; }
                        | arg_list ',' error { $$ = NULL; } 
                        ;

constant                : NUMCONST {
                                yyerrok;
                                $$ = newExprNode(ConstK); 
                                $$->attr.ivalue = $1.value.ival; 
                                $$->declType = Int;
                            }
                        | CHARCONST { 
                                yyerrok;
                                $$ = newExprNode(ConstK); 
                                $$->attr.cvalue = $1.value.cval;
                                $$->declType = Char;
                            }
                        | STRINGCONST { 
                                yyerrok;
                                $$ = newExprNode(ConstK); 
                                $$->attr.svalue = $1.value.sval; 
                                $$->declType = Char; 
                                $$->isArray = true;
                            }
                        | BOOLCONST { 
                                yyerrok;
                                $$ = newExprNode(ConstK); 
                                $$->attr.ivalue = $1.value.ival; 
                                $$->declType = Bool;
                            }
                        ;

%%
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
    
    if(numerrors == 0 && numwarnings == 0) {
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
