%{

#include <cstdio>
#include "c-.tab.h"

%}

%option noyywrap
%option yylineno

%%

[ \n\t]         ;
[0-9]+          { yylval.ival = atoi(yytext); return NUMCONST; }
'(.)*'          { yylval.cval = yytext[1]; return CHARCONST; }
\"(.)*\"        { yylval.sval = strdup(yytext); return STRINGCONST; }
"true"          { yylval.ival = 1; return BOOLCONST; }
"false"         { yylval.ival = 0; return BOOLCONST; }
[a-zA-Z]+[0-9]* { yylval.sval = strdup(yytext); return ID; }
.               ;
%%
