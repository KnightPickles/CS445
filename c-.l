%{
// c-.l CS445 Zachary Yama

#include <cstdio>
#include "tokenClass.h"
#include "c-.tab.h"

// Take in yytext containing "\0", "\n", "\." and return a string with '\0', '\n', '.'.
char* escstr(char* str) {
    int j = 0;
    char* esced = (char*)malloc(strlen(str) * sizeof(char)); 
    for(int i = 1; i < strlen(str) - 1; i++) {
        if(str[i] == '\\') {
            char eschar = str[i + 1];
            switch(eschar) {
                default : esced[j] = str[i + 1]; break;
                case 'n': esced[j] = '\n'; break;
                case '0': esced[j] = '\0'; break;
            }
            i++;
        } else {
            esced[j] = str[i];
        }
        j++;
    }
    yylval.token.slen = j;
    return esced;
}

%}
%option noyywrap
%option yylineno
%x START_COMMENT
%x START_COMMENT_BLOK
%%
[ \t\n]                         ;
"//"                            { BEGIN(START_COMMENT); }
<START_COMMENT>.                ;
<START_COMMENT>"\n"             { BEGIN(INITIAL); }
"/*"                            { BEGIN(START_COMMENT_BLOK); }
<START_COMMENT_BLOK>.           ;
<START_COMMENT_BLOK>"*/"        { BEGIN(INITIAL); }
['"@#^_~]                       { yylval.token.rtxt = strdup(yytext); yylval.token.value.cval = yytext[0]; return ERROR; }
[0-9]+                          { yylval.token.rtxt = strdup(yytext); yylval.token.value.ival = atoi(yytext); return NUMCONST; }
'(.)*'                          { yylval.token.rtxt = strdup(yytext); yylval.token.value.cval = escstr(yytext)[0]; return CHARCONST; }
\"(.)*\"                        { yylval.token.rtxt = strdup(yytext); yylval.token.value.sval = escstr(yytext); return STRINGCONST; }
"true"                          { yylval.token.value.ival = 1; yylval.token.rtxt = strdup(yytext); return BOOLCONST; }
"false"                         { yylval.token.value.ival = 0; yylval.token.rtxt = strdup(yytext); return BOOLCONST; }
"bool"                          { return BOOL; }
"break"                         { return BREAK; }
"char"                          { return CHAR; }
"else"                          { return ELSE; }
"foreach"                       { return FOREACH; }
"if"                            { return IF; }
"in"                            { return IN; }
"int"                           { return INT; }
"return"                        { return RETURN; }
"static"                        { return STATIC; }
"while"                         { return WHILE; }
"!="                            { return NOTEQ; }
"<="                            { return LESSEQ; }
">="                            { return GRTEQ; }
"=="                            { return EQ; }
"++"                            { return INC; }
"--"                            { return DEC; }
"+="                            { return ADDASS; }
"-="                            { return SUBASS; }
"*="                            { return MULASS; }
"/="                            { return DIVASS; }
[a-zA-Z]+[0-9]*                 { yylval.token.value.sval = strdup(yytext); return ID; }
.                               { yylval.token.value.sval = strdup(yytext); return OP; }
%%
