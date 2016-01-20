%{
// c-.l CS445 Zachary Yama

#include <stdio.h>
#include "tokenClass.h"
#include "util.h"
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
    char* resize = (char*)malloc(j * sizeof(char));
    strncpy(resize, esced, j);
    free(esced);
    yylval.token.slen = j;
    return resize;
}

void charerror(char* str) {
    int len = strlen(str);
    if(len == 4 && str[1] == '\\') {
        len -= 1;
    }
    if(len - 2 != 1) {
        printf("ERROR(%u): character is %u characters and not a single character: %s\n", yylineno, (unsigned)strlen(str) - 2, str);
    }
}

%}
%option noyywrap
%option yylineno
%%
[ \t\n]                         ;
(\/\/(.)*\n)                    ;
['"@#^_~]                       { printf("ERROR(%u): Invalid input character: \"%c\"\n", yylineno, yytext[0]); }
[0-9]+                          { yylval.token.rtxt = strdup(yytext); yylval.token.value.ival = atoi(yytext); return NUMCONST; }
'(.)*'                          { charerror(strdup(yytext)); yylval.token.rtxt = strdup(yytext); yylval.token.value.cval = escstr(yytext)[0]; return CHARCONST; }
\"(.)*\"                        { yylval.token.rtxt = strdup(yytext); yylval.token.value.sval = escstr(yytext); return STRINGCONST; }
"true"                          { yylval.token.value.ival = 1; yylval.token.rtxt = strdup(yytext); return BOOLCONST; }
"false"                         { yylval.token.value.ival = 0; yylval.token.rtxt = strdup(yytext); return BOOLCONST; }
"bool"                          { yylval.token.value.sval = strdup(yytext); return BOOL; }
"break"                         { yylval.token.value.sval = strdup(yytext); return BREAK; }
"char"                          { yylval.token.value.sval = strdup(yytext); return CHAR; }
"else"                          { yylval.token.value.sval = strdup(yytext); return ELSE; }
"foreach"                       { yylval.token.value.sval = strdup(yytext); return FOREACH; }
"if"                            { yylval.token.value.sval = strdup(yytext); return IF; }
"in"                            { yylval.token.value.sval = strdup(yytext); return IN; }
"int"                           { yylval.token.value.sval = strdup(yytext); return INT; }
"return"                        { yylval.token.value.sval = strdup(yytext); return RETURN; }
"static"                        { yylval.token.value.sval = strdup(yytext); return STATIC; }
"while"                         { yylval.token.value.sval = strdup(yytext); return WHILE; }
"!="                            { yylval.token.value.sval = strdup(yytext); return NOTEQ; }
"<="                            { yylval.token.value.sval = strdup(yytext); return LESSEQ; }
">="                            { yylval.token.value.sval = strdup(yytext); return GRTEQ; }
"=="                            { yylval.token.value.sval = strdup(yytext); return EQ; }
"++"                            { yylval.token.value.sval = strdup(yytext); return INC; }
"--"                            { yylval.token.value.sval = strdup(yytext); return DEC; }
"+="                            { yylval.token.value.sval = strdup(yytext); return ADDASS; }
"-="                            { yylval.token.value.sval = strdup(yytext); return SUBASS; }
"*="                            { yylval.token.value.sval = strdup(yytext); return MULASS; }
"/="                            { yylval.token.value.sval = strdup(yytext); return DIVASS; }
"="                             { yylval.token.value.sval = strdup(yytext); return ASSIGN; }
"<"                             { yylval.token.value.sval = strdup(yytext); return LESS; }
">"                             { yylval.token.value.sval = strdup(yytext); return GRT; }
"+"                             { yylval.token.value.sval = strdup(yytext); return ADD; }
"-"                             { yylval.token.value.sval = strdup(yytext); return SUB; }
"*"                             { yylval.token.value.sval = strdup(yytext); return MUL; }
"/"                             { yylval.token.value.sval = strdup(yytext); return DIV; }
"%"                             { yylval.token.value.sval = strdup(yytext); return MOD; }
"&"                             { yylval.token.value.sval = strdup(yytext); return AND; }
"|"                             { yylval.token.value.sval = strdup(yytext); return OR;  }
"!"                             { yylval.token.value.sval = strdup(yytext); return NOT; }
"?"                             { yylval.token.value.sval = strdup(yytext); return QUE; }
"("                             { yylval.token.value.ival = yylineno; return OPAREN; }
")"                             { yylval.token.value.ival = yylineno; return CPAREN; }
"{"                             { yylval.token.value.ival = yylineno; return OBRACE; }
"}"                             { yylval.token.value.ival = yylineno; return CBRACE; }
"["                             { yylval.token.value.ival = yylineno; return OBRAK; }
"]"                             { yylval.token.value.ival = yylineno; return CBRAK; }
";"                             { yylval.token.value.sval = strdup(yytext); return SEMI; }
":"                             { yylval.token.value.sval = strdup(yytext); return COLON; }
","                             { yylval.token.value.sval = strdup(yytext); return COMMA; }
[a-zA-Z]+([0-9]*[a-zA-Z]*)*     { yylval.token.value.sval = strdup(yytext); return ID; }
.                               { yylval.token.lineno = yylineno; yylval.token.rtxt = strdup(yytext); return yytext[0]; }
%%
