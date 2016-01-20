%{
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define YYERROR_VERBOSE

extern int yylinno;
extern int yylex();
extern FILE *yyin;

void yyerror(const char *s) {
    printf("%s\n", s);
    exit(-1);
}
%}

%union {
    int ival;
    char cval;
    char* sval;
}

%token <ival> NUMCONST
%token <ival> BOOLCONST
%token <cval> CHARCONST
%token <sval> STRINGCONST
%token <sval> ID

%%

grammar         : grammar NUMCONST      { printf("Numconst\n"); }
                | grammar BOOLCONST     { printf("Boolconst\n"); }
                | grammar CHARCONST     { printf("Charconst\n"); }
                | grammar STRINGCONST   { printf("stringconst\n"); }
                | grammar ID            { printf("ID\n");}
                |
                ;

%%

int main(int argc, char** argv) {
    if(argc == 2) {
        FILE *iFile;
        iFile = fopen(argv[1], "r");
        if(!iFile) {
            printf("FNF %s\n", argv[1]);
            exit(-1);
        }
        yyin = iFile;
    }
    
    do {
        yyparse();
    } while(!feof(yyin));

    return 0;
}
