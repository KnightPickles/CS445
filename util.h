#ifndef UTIL_H
#define UTIL_H

#include "globals.h"

void printTree(TreeNode *tree, int, bool, bool);
void printSpaces();
TreeNode *newStmtNode(StmtKind);
TreeNode *newExprNode(ExprKind);
TreeNode *newDeclNode(DeclKind);
#endif
