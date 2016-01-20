struct Token {
    union Value {
        int ival;
        char cval;
        char* sval;
    } value;

    char* rtxt;
    int slen;
};
