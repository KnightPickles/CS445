// codegen.h
// Zachary Yama
#ifndef CODEGEN_H
#define CODEGEN_H

#include "globals.h"

void generateCode(TreeNode* syntaxTree, char* outfile);
TreeNode* transIOLibTM(TreeNode* syntaxTree);
void transInputTM(TreeNode* syntaxTree);

#endif
