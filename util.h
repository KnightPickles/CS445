#ifndef UTIL_H
#define UTIL_H

#include "globals.h"
//#include "util.h"

void printToken(TokenType, const char *);

void printTree(TreeNode *tree, int);
void printSpaces();
TreeNode *newStmtNode(StmtKind);
TreeNode *newExprNode(ExprKind);
TreeNode *newDeclNode(DeclKind);
#endif
