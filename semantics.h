// semantics.h
// Zachary Yama 

#ifndef SEMANTICS_H
#define SEMANTICS_H

#include "globals.h"
#include "symbolTable.h"
#include "util.h"

SymbolTable returnSymbolTable();
void printSemantics();
void printTable();
void printError(int code, int lineno, int explineno, char* s1, char* s2, char* s3, double d1);
void IOLibrary(TreeNode*& t);
void semantics(TreeNode* tree, int& numerrors, int& numwarnings);
void scopeAndType(TreeNode* tree, int& numerrors, int& numwarnings);
void processMisc(TreeNode* t, int& numerrors, int& numwarnings);
void processDecl(TreeNode* t, int& numerrors, int& numwarnings);
void processStmt(TreeNode* t, int& numerrors, int& numwarnings);
void processExpr(TreeNode* t, int& numerrors, int& numwarnings);
void exprTypes(const char* s, bool isBin, bool &singleSidedErrors, DeclType &lhs, DeclType &rhs, DeclType &rt);
char* getTypeStr(DeclType declType);

#endif
