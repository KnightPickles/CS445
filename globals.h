// globals.h as per the Tiny compiler dictates

#ifndef GLOBALS_H
#define GLOBALS_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 0
#endif

#define MAXRESERVED 8

extern int yylineno;

typedef int TokenType;
typedef enum {DeclK, StmtK, ExprK} NodeKind;
typedef enum {FuncK, VarK, ParamK} DeclKind;
typedef enum {IfK, ForK, WhileK, CompK, ReturnK, BreakK} StmtKind;
typedef enum {ConstK, IdK, OpK, AssignK, CallK} ExprKind;
typedef enum {Void, Int, Bool, Char, IntChar, Undefined} DeclType;

#define MAXCHILDREN 3

typedef struct treeNode {
    // connectivity in the tree
    struct treeNode *child[MAXCHILDREN];   // children of the node
    struct treeNode *sibling;              // siblings for the node

    // what kind of node
    int lineno;                            // linenum relevant to this node
    NodeKind nodekind;                     // type of node
    union {                                // subtype of type
        DeclKind decl;                     // used when DeclK
        StmtKind stmt;                     // used when StmtK
        ExprKind expr;                       // used when ExpK
    } kind;
    
    // extra properties about the node depending on type of the node
    union {                                // relevant data to type -> attr
        int ivalue;                         // used when an integer constant or boolean
        unsigned char cvalue;              // used when a character
        char *svalue;                      // used when a string constant
        char *name;                         // used when IdK
    } attr;                                 
    DeclType declType;                       // used when ExpK for type checking
    bool isStatic;                         // is staticly allocated?
    bool isArray;                          // is this an array
    int arrayLen;
    // only applies to decl nodes
    bool isGlobal;      // Is this variable declared in local or global space?
    int memSize;        // How much memory does it take up? i.e. array size
    int memOffset;         // How far is it offest from address 9999 moving towards 0?
} TreeNode;
#endif
