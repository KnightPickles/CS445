%{
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

%}

%union {
    Token token; 
    TreeNode *treeNode;
    DeclType integer;
    char *string;
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
                        matched_selection
                        unmatched_selection
                        matched_iteration
                        unmatched_iteration
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

%type <string>          unaryop 
                        relop 
                        mulop 
                        sumop

%type <integer>         type_specifier 
                        

%token <token.value.sval> ID
%token <token.value.ival> NUMCONST
%token <token.value.sval> STRINGCONST
%token <token.value.cval> CHARCONST
%token <token.value.ival> BOOLCONST
%token <token.value.sval> OP
%token <token.value.cval> ERROR 
%token <token.value.sval> BOOL BREAK CHAR ELSE FOREACH IF IN INT RETURN STATIC WHILE
%token <token.value.sval> ASSIGN NOTEQ EQ LESSEQ LESS GRTEQ GRT INC DEC ADDASS ADD SUBASS SUB MULASS MUL DIVASS DIV
%token <token.value.ival> OPAREN CPAREN OBRACE CBRACE OBRAK CBRAK
%token <token.value.sval> COMMA COLON SEMI MOD QUE AND OR NOT
%%
program                 : declaration_list { 
                                syntaxTree = $1;
                            }    
                        ;

declaration_list        : declaration_list declaration {
                               TreeNode *trav = $1;
                               if(trav != NULL) {
                                   while (trav -> sibling != NULL) trav = trav -> sibling;
                                   trav -> sibling = $2;
                                   $$ = $1;
                               } else {
                                   $$ = $2;
                               }
                            }
                        | declaration { $$ = $1; }
                        ;

declaration             : var_declaration { $$ = $1; }
                        | fun_declaration { $$ = $1; }//$$ = $1; }
                        ;

// Variable Declaration

var_declaration         : type_specifier var_decl_list SEMI {
                                TreeNode *complete = $2;
                                if(complete != NULL) {
                                    do {
                                        complete -> declType = $1;
                                        complete = complete -> sibling;

                                    } while(complete != NULL);
                                    $$ = $2;
                                } else {
                                    $$ = NULL;
                                }
                            }
                        ;

scoped_var_declaration  : scoped_type_specifier var_decl_list SEMI {
                                TreeNode *complete = $2;
                                if(complete != NULL) {
                                    do {
                                        complete -> declType = $1 -> declType;
                                        complete -> isStatic = $1 -> isStatic;
                                        complete = complete -> sibling;
                                    } while(complete != NULL); 
                                    $$ = $2;
                                } else {
                                    $$ = NULL;
                                }
                            }
                        ;

var_decl_list           : var_decl_list COMMA var_decl_initialize {
                               TreeNode *trav = $1;
                               if(trav != NULL) {
                                    while(trav -> sibling != NULL) trav = trav -> sibling;
                                    trav -> sibling = $3; 
                                    $$ = $1; 
                                } else {
                                    $$ = $3;
                                }
                            }
                        | var_decl_initialize { $$ = $1; }
                        ;

var_decl_initialize     : var_decl_id { $$ = $1; }
                        | var_decl_id COLON simple_expression {
                                $1 -> child[0] = $3; // <- NOT NULL, SHOULD BE $3
                                $$ = $1;  
                            }
                        ;

var_decl_id             : ID { 
                                $$ = newDeclNode(VarK);
                                $$ -> attr.name = $1;
                            }
                        | ID OBRAK NUMCONST CBRAK {
                                $$ = newDeclNode(VarK);
                                $$ -> attr.name = $1; 
                                $$ -> isArray = true;
                                $$ -> arrayLen = $3;
                            }
                        ;

scoped_type_specifier   : STATIC type_specifier {
                                $$ = newDeclNode(VarK);
                                $$ -> isStatic = true;
                                $$ -> declType = $2;
                            }
                        | type_specifier {
                                $$ = newDeclNode(VarK);
                                $$ -> declType = $1;
                            }
                        ;

type_specifier          : INT { $$ = Int; }
                        | BOOL { $$ = Bool; }
                        | CHAR { $$ = Char; }
                        ;
// Function Declaration

fun_declaration         : type_specifier ID OPAREN params CPAREN statement {
                                $$ = newDeclNode(FuncK);
                                $$ -> declType = $1;  
                                $$ -> attr.name = $2;
                                $$ -> child[0] = $4;
                                $$ -> child[1] = $6; 
                                $$ -> lineno = $3; // Allows for correct line no
                            }

                        | ID OPAREN params CPAREN statement {
                               $$ = newDeclNode(FuncK);
                               $$ -> declType = Void;
                               $$ -> attr.name = $1;
                               $$ -> child[0] = $3;
                               $$ -> child[1] = $5; 
                               $$ -> lineno = $2;
                            }
                        ;

params                  : param_list { $$ = $1; }
                        | { $$ = NULL; }
                        ;

param_list              : param_list SEMI param_type_list {
                                TreeNode *trav = $1;
                                if(trav != NULL) {
                                    while(trav -> sibling != NULL) trav = trav -> sibling;
                                    trav -> sibling = $3;
                                    $$ = $1;
                                } else {
                                    $$ = $3; 
                                }
                            }
                        | param_type_list { $$ = $1; }
                        ;

param_type_list         : type_specifier param_id_list {
                                TreeNode *complete = $2;
                                if(complete != NULL) {
                                    do {
                                        complete -> declType = $1;
                                        complete = complete -> sibling;
                                    } while(complete != NULL);
                                    $$ = $2;
                                } else {
                                    $$ = NULL;
                                }
                            }
                        ;

param_id_list           : param_id_list COMMA param_id {
                               TreeNode *trav = $1; 
                               if(trav != NULL) {
                                   while(trav -> sibling != NULL) trav = trav -> sibling;
                                   trav -> sibling = $3;
                                   $$ = $1;
                               } else { 
                                   $$ = $3;
                               }
                            }
                        | param_id { $$ = $1; }
                        ;

param_id                : ID { 
                               $$ = newDeclNode(ParamK);
                               $$ -> attr.name = $1;
                            }
                        | ID OBRAK CBRAK {
                               $$ = newDeclNode(ParamK);
                               $$ -> attr.name = $1;
                               $$ -> isArray = true;
                            }
                        ;

// Statement

statement               : unmatched { $$ = $1; }
                        | matched { $$ = $1; }
                        ;

matched                 : matched_selection { $$ = $1; }
                        | matched_iteration { $$ = $1; }
                        | expression_stmt { $$ = $1; }
                        | compound_stmt { $$ = $1; }
                        | return_stmt { $$ = $1; }
                        | break_stmt { $$ = $1; }
                        ;

unmatched               : unmatched_selection { $$ = $1; }
                        | unmatched_iteration { $$ = $1; }
                        ;

compound_stmt           : OBRACE local_declarations statement_list CBRACE {
                               $$ = newStmtNode(CompK); 
                               $$ -> child[0] = $2;
                               $$ -> child[1] = $3; 
                               $$ -> lineno = $1;
                            }
                        ;

local_declarations      : local_declarations scoped_var_declaration {
                                TreeNode *trav = $1; 
                                if(trav != NULL) {
                                    while(trav -> sibling != NULL) trav = trav -> sibling;
                                    trav -> sibling = $2;
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
                                    while(trav -> sibling != NULL) trav = trav -> sibling;
                                    trav -> sibling = $2;
                                    $$ = $1;
                                } else {
                                    $$ = $2;
                                }
                            }
                        | { $$ = NULL; }
                        ;

expression_stmt         : expression SEMI { $$ = $1; }
                        | SEMI { $$ = NULL; }
                        ;

matched_selection       : IF OPAREN simple_expression CPAREN matched ELSE matched {
                                $$ = newStmtNode(IfK);
                                $$ -> attr.name = $1;
                                $$ -> child[0] = $3;
                                $$ -> child[1] = $5;
                                $$ -> child[2] = $7;
                                $$ -> lineno = $2;
                            }
                        ;

unmatched_selection     : IF OPAREN simple_expression CPAREN matched ELSE unmatched {
                                $$ = newStmtNode(IfK);
                                $$ -> attr.name = $1;
                                $$ -> child[0] = $3;
                                $$ -> child[1] = $5;
                                $$ -> child[2] = $7;
                                $$ -> lineno = $2;
                            }
                        | IF OPAREN simple_expression CPAREN statement {
                                $$ = newStmtNode(IfK);
                                $$ -> attr.name = $1;
                                $$ -> child[0] = $3;
                                $$ -> child[1] = $5;
                                $$ -> lineno = $2;
                            }
                        ;

matched_iteration       : WHILE OPAREN simple_expression CPAREN matched {
                                $$ = newStmtNode(WhileK);
                                $$ -> attr.name = $1;
                                $$ -> child[0] = $3;
                                $$ -> child[1] = $5;
                                $$ -> lineno = $2;
                            }
                        | FOREACH OPAREN mutable IN simple_expression CPAREN matched {
                                $$ = newStmtNode(ForK);
                                $$ -> attr.name = $1;
                                $$ -> child[0] = $3;
                                $$ -> child[1] = $5;
                                $$ -> child[2] = $7;
                                $$ -> lineno = $2;
                            }
                        ;

unmatched_iteration     : WHILE OPAREN simple_expression CPAREN unmatched {
                                $$ = newStmtNode(WhileK);
                                $$ -> attr.name = $1;
                                $$ -> child[0] = $3;
                                $$ -> child[1] = $5;
                                $$ -> lineno = $2;
                            }
                        | FOREACH OPAREN mutable IN simple_expression CPAREN unmatched {
                                $$ = newStmtNode(ForK);
                                $$ -> attr.name = $1;
                                $$ -> child[0] = $3; 
                                $$ -> child[1] = $5;
                                $$ -> child[2] = $7;
                                $$ -> lineno = $2;
                            }
                        ;

return_stmt             : RETURN SEMI { 
                                $$ = newStmtNode(ReturnK);
                                $$ -> attr.name = $1;
                            }
                        | RETURN expression SEMI {
                                $$ = newStmtNode(ReturnK);
                                $$ -> attr.name = $1;
                                $$ -> child[0] = $2;
                            }
                        ;

break_stmt              : BREAK SEMI { 
                                $$ = newStmtNode(BreakK);
                                $$ -> attr.name = $1;
                            }
                        ;

// Expression

expression              : mutable ASSIGN expression {
                                $$ = newExprNode(AssignK);
                                $$ -> attr.name = $2;
                                $$ -> child[0] = $1;
                                $$ -> child[1] = $3;
                            }
                        | mutable ADDASS expression {
                                $$ = newExprNode(AssignK);
                                $$ -> attr.name = $2;
                                $$ -> child[0] = $1;
                                $$ -> child[1] = $3;
                            }
                        | mutable SUBASS expression {
                                $$ = newExprNode(AssignK);
                                $$ -> attr.name = $2;
                                $$ -> child[0] = $1;
                                $$ -> child[1] = $3;
                            }
                        | mutable MULASS expression {
                                $$ = newExprNode(AssignK);
                                $$ -> attr.name = $2;
                                $$ -> child[0] = $1;
                                $$ -> child[1] = $3;
                            }
                        | mutable DIVASS expression { 
                                $$ = newExprNode(AssignK);
                                $$ -> attr.name = $2;
                                $$ -> child[0] = $1;
                                $$ -> child[1] = $3;
                            }
                        | mutable INC {
                                $$ = newExprNode(AssignK);
                                $$ -> attr.name = $2;
                                $$ -> child[0] = $1;
                            }
                        | mutable DEC {
                                $$ = newExprNode(AssignK);
                                $$ -> attr.name = $2;
                                $$ -> child[0] = $1;
                            }
                        | simple_expression { $$ = $1; } 
                        ;

simple_expression       : simple_expression OR and_expression {
                                $$ = newExprNode(OpK);
                                $$ -> attr.name = $2;
                                $$ -> child[0] = $1;
                                $$ -> child[1] = $3;
                            }
                        | and_expression { $$ = $1; }
                        ;

and_expression          : and_expression AND unary_rel_expression {
                                $$ = newExprNode(OpK);
                                $$ -> attr.name = $2;
                                $$ -> child[0] = $1;
                                $$ -> child[1] = $3; 
                            }
                        | unary_rel_expression { $$ = $1; }
                        ;

unary_rel_expression    : NOT unary_rel_expression {
                                $$ = newExprNode(OpK);
                                $$ -> attr.name = $1;
                                $$ -> child[0] = $2;
                            }
                        | rel_expression { $$ = $1; }
                        ;

rel_expression          : sum_expression relop sum_expression {
                               $$ = newExprNode(OpK);
                               $$ -> attr.name = $2;
                               $$ -> child[0] = $1;
                               $$ -> child[1] = $3;
                            }
                        | sum_expression { $$ = $1; }
                        ;

relop                   : LESSEQ { $$ = $1; }
                        | LESS { $$ = $1; }
                        | GRT { $$ = $1; }
                        | GRTEQ { $$ = $1; }
                        | EQ { $$ = $1; }
                        | NOTEQ { $$ = $1; }
                        ;

sum_expression          : sum_expression sumop term {
                                $$ = newExprNode(OpK);
                                $$ -> attr.name = $2;
                                $$ -> child[0] = $1;
                                $$ -> child[1] = $3;
                            }
                        | term { $$ = $1; }
                        ;

sumop                   : ADD { $$ = $1; }
                        | SUB { $$ = $1; }
                        ;

term                    : term mulop unary_expression {
                                $$ = newExprNode(OpK);
                                $$ -> attr.name = $2;
                                $$ -> child[0] = $1;
                                $$ -> child[1] = $3;
                            }
                        | unary_expression { $$ = $1; }
                        ;

mulop                   : MUL { $$ = $1; } 
                        | DIV { $$ = $1; }
                        | MOD { $$ = $1; }
                        ;

unary_expression        : unaryop unary_expression {
                                $$ = newExprNode(OpK);
                                $$ -> attr.name = $1;
                                $$ -> child[0] = $2;
                            }
                        | factor { $$ = $1; }
                        ;

unaryop                 : SUB { $$ = $1; }
                        | MUL { $$ = $1; }
                        | QUE { $$ = $1; }
                        ;

factor                  : immutable { $$ = $1; } 
                        | mutable { $$ = $1; }
                        ;

mutable                 : ID {
                               $$ = newExprNode(IdK); 
                               $$ -> attr.name = $1;
                            } 
                        | ID OBRAK expression CBRAK {
                               $$ = newExprNode(IdK);
                               $$ -> attr.name = $1;
                               $$ -> child[0] = $3;
                            }
                        ;
        
immutable               : OPAREN expression CPAREN { $$ = $2; }
                        | call { $$ = $1; }
                        | constant { $$ = $1; }
                        ;

call                    : ID OPAREN args CPAREN {
                               $$ = newExprNode(CallK);
                               $$ -> attr.name = $1;
                               $$ -> child[0] = $3;
                            }
                        ;

args                    : arg_list { $$ = $1; }
                        | { $$ = NULL; }
                        ;

arg_list                : arg_list COMMA expression {
                                TreeNode *trav = $1; 
                                if(trav != NULL) {
                                    while(trav -> sibling != NULL) trav = trav -> sibling;
                                    trav -> sibling = $3;
                                    $$ = $1;
                                } else {
                                    $$ = $3;
                                }
                            }
                        | expression { $$ = $1; }
                        ;

constant                : NUMCONST {
                                $$ = newExprNode(ConstK); 
                                $$ -> attr.ivalue = $1; 
                                $$ -> declType = Int;
                            }
                        | CHARCONST { 
                                $$ = newExprNode(ConstK); 
                                $$ -> attr.cvalue = $1;
                                $$ -> declType = Char;
                            }
                        | STRINGCONST { 
                               $$ = newExprNode(ConstK); 
                               $$ -> attr.svalue = $1; 
                               $$ -> declType = String; 
                            }
                        | BOOLCONST { 
                               $$ = newExprNode(ConstK); 
                               $$ -> attr.ivalue = $1; 
                               $$ -> declType = Bool;
                            }
                        ;

%%
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
