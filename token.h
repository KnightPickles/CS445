#ifndef TOKEN_H
#define TOKEN_H
typedef struct token {
    union Value {
        int ival;
        char cval;
        char* sval;
    } value;

    char* rtxt;
    int slen;
    int lineno;
} Token;
#endif
