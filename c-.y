%{
// c-.y CS445 Zachary Yama

#include <getopt.h>
#include "util.h"
#include "token.h"
#include "semantics.h"
#define YYERROR_VERBOSE

extern int yylineno;
extern int yylex();
extern FILE *yyin;

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

%type <declType> type_specifier 

%type <token>   unaryop 
                relop 
                mulop 
                sumop
                        
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
program                 : declaration_list { 
                                syntaxTree = $1;
                            }    
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
                        ;

// Variable Declaration

var_declaration         : type_specifier var_decl_list ';' {
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
                        ;

scoped_var_declaration  : scoped_type_specifier var_decl_list ';' {
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
                        ;

var_decl_initialize     : var_decl_id { $$ = $1; }
                        | var_decl_id ':' simple_expression {
                                $1->child[0] = $3; // <- NOT NULL, SHOULD BE $3
                                $$ = $1;  
                            }
                        ;

var_decl_id             : ID { 
                                $$ = newDeclNode(VarK);
                                $$->attr.name = $1.value.sval;
                                $$->lineno = $1.lineno;
                            }
                        | ID '[' NUMCONST ']' {
                                $$ = newDeclNode(VarK);
                                $$->attr.name = $1.value.sval; 
                                $$->isArray = true;
                                $$->arrayLen = $3.value.ival;
                                $$->lineno = $1.lineno;
                            }
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
                                $$->lineno = $3.lineno; // Allows for correct line no
                            }

                        | ID '(' params ')' statement {
                               $$ = newDeclNode(FuncK);
                               $$->declType = Void;
                               $$->attr.name = $1.value.sval;
                               $$->child[0] = $3;
                               $$->child[1] = $5; 
                               $$->lineno = $2.lineno;
                            }
                        ;

params                  : param_list { $$ = $1; }
                        | { $$ = NULL; }
                        ;

param_list              : param_list ';' param_type_list {
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
                        ;

param_id_list           : param_id_list ',' param_id {
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
                        ;

param_id                : ID { 
                               $$ = newDeclNode(ParamK);
                               $$->attr.name = $1.value.sval;
                            }
                        | ID '[' ']' {
                               $$ = newDeclNode(ParamK);
                               $$->attr.name = $1.value.sval;
                               $$->isArray = true;
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

compound_stmt           : '{' local_declarations statement_list '}' {
                               $$ = newStmtNode(CompK); 
                               $$->child[0] = $2;
                               $$->child[1] = $3; 
                               $$->lineno = $1.lineno;
                            }
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
                        ;

expression_stmt         : expression ';' { $$ = $1; }
                        | ';' { $$ = NULL; }
                        ;

matched_selection       : IF '(' simple_expression ')' matched ELSE matched {
                                $$ = newStmtNode(IfK);
                                $$->attr.name = $1.rtxt;
                                $$->child[0] = $3;
                                $$->child[1] = $5;
                                $$->child[2] = $7;
                                $$->lineno = $1.lineno;
                            }
                        ;

unmatched_selection     : IF '(' simple_expression ')' matched ELSE unmatched {
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
                        ;

matched_iteration       : WHILE '(' simple_expression ')' matched {
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
                        ;

unmatched_iteration     : WHILE '(' simple_expression ')' unmatched {
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
                        ;

return_stmt             : RETURN ';' { 
                                $$ = newStmtNode(ReturnK);
                                $$->attr.name = $1.rtxt;
                                $$->lineno = $1.lineno;
                            }
                        | RETURN expression ';' {
                                $$ = newStmtNode(ReturnK);
                                $$->attr.name = $1.rtxt;
                                $$->child[0] = $2;
                                $$->lineno = $1.lineno;
                            }
                        ;

break_stmt              : BREAK ';' { 
                                $$ = newStmtNode(BreakK);
                                $$->attr.name = $1.rtxt;
                            }
                        ;

// Expression

expression              : mutable '=' expression {
                                $$ = newExprNode(AssignK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->child[1] = $3;
                                $$->lineno = $2.lineno;
                            }
                        | mutable ADDASS expression {
                                $$ = newExprNode(AssignK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->child[1] = $3;
                                $$->lineno = $2.lineno;
                            }
                        | mutable SUBASS expression {
                                $$ = newExprNode(AssignK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->child[1] = $3;
                                $$->lineno = $2.lineno;
                            }
                        | mutable MULASS expression {
                                $$ = newExprNode(AssignK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->child[1] = $3;
                                $$->lineno = $2.lineno;
                            }
                        | mutable DIVASS expression { 
                                $$ = newExprNode(AssignK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->child[1] = $3;
                                $$->lineno = $2.lineno;
                            }
                        | mutable INC {
                                $$ = newExprNode(AssignK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->lineno = $2.lineno;
                            }
                        | mutable DEC {
                                $$ = newExprNode(AssignK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->lineno = $2.lineno;
                            }
                        | simple_expression { $$ = $1; } 
                        ;

simple_expression       : simple_expression '|' and_expression {
                                $$ = newExprNode(OpK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->child[1] = $3;
                            }
                        | and_expression { $$ = $1; }
                        ;

and_expression          : and_expression '&' unary_rel_expression {
                                $$ = newExprNode(OpK);
                                $$->attr.name = $2.rtxt;
                                $$->child[0] = $1;
                                $$->child[1] = $3; 
                            }
                        | unary_rel_expression { $$ = $1; }
                        ;

unary_rel_expression    : '!' unary_rel_expression {
                                $$ = newExprNode(OpK);
                                $$->attr.name = $1.rtxt;
                                $$->child[0] = $2;
                            }
                        | rel_expression { $$ = $1; }
                        ;

rel_expression          : sum_expression relop sum_expression {
                               $$ = newExprNode(OpK);
                               $$->attr.name = $2.rtxt;
                               $$->child[0] = $1;
                               $$->child[1] = $3;
                            }
                        | sum_expression { $$ = $1; }
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
                        ;

unaryop                 : '-' { $$ = $1; }
                        | '*' { $$ = $1; }
                        | '?' { $$ = $1; }
                        ;

factor                  : immutable { $$ = $1; } 
                        | mutable { $$ = $1; }
                        ;

mutable                 : ID {
                               $$ = newExprNode(IdK); 
                               $$->attr.name = $1.value.sval;
                            } 
                        | ID '[' expression ']' {
                               $$ = newExprNode(IdK);
                               $$->attr.name = $1.value.sval;
                               $$->child[0] = $3;
                            }
                        ;
        
immutable               : '(' expression ')' { $$ = $2; }
                        | call { $$ = $1; }
                        | constant { $$ = $1; }
                        ;

call                    : ID '(' args ')' {
                               $$ = newExprNode(CallK);
                               $$->attr.name = $1.value.sval;
                               $$->child[0] = $3;
                            }
                        ;

args                    : arg_list { $$ = $1; }
                        | { $$ = NULL; }
                        ;

arg_list                : arg_list ',' expression {
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
                        ;

constant                : NUMCONST {
                                $$ = newExprNode(ConstK); 
                                $$->attr.ivalue = $1.value.ival; 
                                $$->declType = Int;
                            }
                        | CHARCONST { 
                                $$ = newExprNode(ConstK); 
                                $$->attr.cvalue = $1.value.cval;
                                $$->declType = Char;
                            }
                        | STRINGCONST { 
                                $$ = newExprNode(ConstK); 
                                $$->attr.svalue = $1.value.sval; 
                                $$->declType = Char; 
                                $$->isArray = true;
                            }
                        | BOOLCONST { 
                                $$ = newExprNode(ConstK); 
                                $$->attr.ivalue = $1.value.ival; 
                                $$->declType = Bool;
                            }
                        ;

%%
int main(int argc, char** argv) {
    // Get cmd line option arguments if they exist
    int opt;
    bool print = false;
    bool printAn = false;
    while((opt = getopt(argc, argv, "dpP")) != EOF) {
        switch(opt) { //in case we add more options
            default:
                abort();
                break;
            case 'd':
                yydebug = 1;
                break;
            case 'p':
                print = true;
                break;
            case 'P':
                printAn = true;
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
   
    int numerrors = 0;
    int numwarnings = 0;
    

    if(print) {
        printTree(syntaxTree, -1, false);
    }

    IOLibrary(syntaxTree);
    semantics(syntaxTree, numerrors, numwarnings);

    if(printAn) {
        printTree(syntaxTree, -1, true); // print annotated syntax tree
    }

    printf("Number of warnings: %i\n", numwarnings);
    printf("Number of errors: %i\n", numerrors);
    
    return 0;
}
