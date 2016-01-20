%{
// c-.y CS445 Zachary Yama
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "tokenClass.h"
#define YYERROR_VERBOSE

extern int yylineno;
extern int yylex();
extern FILE *yyin;

void yyerror(const char *msg) {
    printf("PARSER ERROR: %s\n", msg);
    exit(-1);
}

// Length check character input 
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
    struct Token token; 
}

%token <token.value.sval> ID
%token <token.value.ival> NUMCONST
%token <token.value.sval> STRINGCONST
%token <token.value.cval> CHARCONST
%token <token.value.ival> BOOLCONST
%token <token.value.sval> OP
%token <token.value.cval> ERROR 
%token BOOL BREAK CHAR ELSE FOREACH IF IN INT RETURN STATIC WHILE
%token NOTEQ EQ LESSEQ GRTEQ INC DEC ADDASS SUBASS MULASS DIVASS

%%
fake            : fake ERROR         { printf("ERROR(%u): Invalid input character: \"%c\"\n", yylineno, $2); }
                | fake ID            { printf("Line %u Token: ID Value: %s\n", yylineno, $2); }
                | fake NUMCONST      { printf("Line %u Token: NUMCONST Value: %i  Input: %s\n", yylineno, $2, yylval.token.rtxt); }
                | fake STRINGCONST   { printf("Line %u Token: STRINGCONST Value of length %i: \"%s\"  Input: %s\n", yylineno, yylval.token.slen, $2, yylval.token.rtxt); }
                | fake CHARCONST     { charerror(yylval.token.rtxt); printf("Line %u Token: CHARCONST Value: '%c'  Input: %s\n", yylineno, $2, yylval.token.rtxt); }
                | fake BOOLCONST     { printf("Line %u Token: BOOLCONST Value: %i  Input: %s\n", yylineno, $2, yylval.token.rtxt); } 
                | fake BOOL          { printf("Line %u Token: BOOL\n", yylineno); }
                | fake NOTEQ         { printf("Line %u Token: NOTEQ\n", yylineno); }
                | fake EQ            { printf("Line %u Token: EQ\n", yylineno); }
                | fake LESSEQ        { printf("Line %u Token: LESSEQ\n", yylineno); }
                | fake GRTEQ         { printf("Line %u Token: GRTEQ\n", yylineno); }
                | fake INC           { printf("Line %u Token: INC\n", yylineno); }
                | fake DEC           { printf("Line %u Token: DEC\n", yylineno); }
                | fake ADDASS        { printf("Line %u Token: ADDASS\n", yylineno); }
                | fake SUBASS        { printf("Line %u Token: SUBASS\n", yylineno); }
                | fake MULASS        { printf("Line %u Token: MULASS\n", yylineno); }
                | fake DIVASS        { printf("Line %u Token: DIVASS\n", yylineno); }
                | fake BREAK         { printf("Line %u Token: BREAK\n", yylineno); }
                | fake CHAR          { printf("Line %u Token: CHAR\n", yylineno); }
                | fake ELSE          { printf("Line %u Token: ELSE\n", yylineno); }
                | fake FOREACH       { printf("Line %u Token: FOREACH\n", yylineno); }
                | fake IF            { printf("Line %u Token: IF\n", yylineno); } 
                | fake IN            { printf("Line %u Token: IN\n", yylineno); }
                | fake INT           { printf("Line %u Token: INT\n", yylineno); }
                | fake RETURN        { printf("Line %u Token: RETURN\n", yylineno); }
                | fake STATIC        { printf("Line %u Token: STATIC\n", yylineno); }
                | fake WHILE         { printf("Line %u Token: WHILE\n", yylineno); }
                | fake OP            { printf("Line %u Token: %s\n", yylineno, $2); }
                |
                ;
%%
int main(int argc, char** argv) {
    if(argc == 2) {
        FILE *iFile;
        iFile = fopen(argv[1], "r");
        if(!iFile) {
            printf("File not found: %s\n", argv[1]);
            exit(-1);
        }
        yyin = iFile;
    }
    
    do {
        yyparse();
    } while(!feof(yyin));
    
    return 0;
}
