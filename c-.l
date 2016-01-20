%{
// c-.l CS445 Zachary Yama

#include <cstdio>
#include "token.h"
#include "util.h"
#include "c-.tab.h"

int numerrors = 0;
int numwarnings = 0;

// Perform default token assignemnts
void initialize() {
    yylval.token.lineno = yylineno;
    yylval.token.rtxt = strdup(yytext);
}

void initialize(char* sval) {
    initialize();
    yylval.token.value.sval = sval;
}

void initialize(char cval) {
    initialize();
    yylval.token.value.cval = cval;
}

void initialize(int ival) {
    initialize();
    yylval.token.value.ival = ival;
}

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

// Returns true if there was a char length error
bool charerror(char* str) {
    int len = strlen(str);
    if(len == 4 && str[1] == '\\') {
        len -= 1;
    }
    if(len - 2 != 1) {
        numwarnings++;
        printf("WARNING(%u): character is %u characters and not a single character: %s\n", yylineno, (unsigned)strlen(str) - 2, str);
        return true;
    }
    return false;
}

%}
%option noyywrap
%option yylineno
%%
[ \t\n]                         ;
(\/\/(.)*\n)                    ;
[0-9]+                          { initialize(atoi(yytext)); return NUMCONST; }
'((\\\')|[^\'\n])*\'            { initialize(escstr(yytext)[0]); charerror(strdup(yytext)); return CHARCONST; }
\"((\\\")|[^\"\n])*\"           { initialize(escstr(yytext)); return STRINGCONST; }
"true"                          { initialize(1); return BOOLCONST; }
"false"                         { initialize(0); return BOOLCONST; }
"bool"                          { initialize(strdup(yytext)); return BOOL; }
"break"                         { initialize(strdup(yytext)); return BREAK; }
"char"                          { initialize(strdup(yytext)); return CHAR; }
"else"                          { initialize(strdup(yytext)); return ELSE; }
"foreach"                       { initialize(strdup(yytext)); return FOREACH; }
"if"                            { initialize(strdup(yytext)); return IF; }
"in"                            { initialize(strdup(yytext)); return IN; }
"int"                           { initialize(strdup(yytext)); return INT; }
"return"                        { initialize(strdup(yytext)); return RETURN; }
"static"                        { initialize(strdup(yytext)); return STATIC; }
"while"                         { initialize(strdup(yytext)); return WHILE; }
"!="                            { initialize(strdup(yytext)); return NOTEQ; }
"<="                            { initialize(strdup(yytext)); return LESSEQ; }
">="                            { initialize(strdup(yytext)); return GRTEQ; }
"=="                            { initialize(strdup(yytext)); return EQ; }
"++"                            { initialize(strdup(yytext)); return INC; }
"--"                            { initialize(strdup(yytext)); return DEC; }
"+="                            { initialize(strdup(yytext)); return ADDASS; }
"-="                            { initialize(strdup(yytext)); return SUBASS; }
"*="                            { initialize(strdup(yytext)); return MULASS; }
"/="                            { initialize(strdup(yytext)); return DIVASS; }
[\=\>\<\+\-\*\/\%\&\|\!\?]      { initialize(yytext[0]); return yytext[0]; }
[\(\)\{\}\[\]\;\:\,]            { initialize(yytext[0]); return yytext[0]; }
[a-zA-Z]+[0-9a-zA-Z]*           { initialize(strdup(yytext)); return ID; }
.                               { numwarnings++; printf("WARNING(%u): Invalid input character: \'%c\'. Character ignored.\n", yylineno, yytext[0]); }
%%
