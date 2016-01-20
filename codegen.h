// codegen.h

#ifndef CODEGEN_H
#define CODEGEN_H

#include "globals.h"
#include "symbolTable.h"

void generateCode(TreeNode* tree, SymbolTable symbolTable, char* outfile, char* infile);
void emitHeader(char* filename);
void emitIOLib(TreeNode* tree);
void emitBegin(TreeNode* tree);
void emitInput(TreeNode* tree);
void emitInit(TreeNode* tree);
void emitGlobalsAndStatics(TreeNode* tree);
void emitDecl(TreeNode* tree);
void emitExpr(TreeNode* tree);
void emitStmt(TreeNode* tree);

#endif
