#include<stdio.h>
#include<stdlib.h>
#include"globals.h"
#include"tree.h"
#include"struct.h"

int numWarnings = 0, numErrors = 0;

TreeNode * newStmtNode(StmtKind kind, int lineNum) {
    TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if(t == NULL)
        printf("Out of memory error at line\n");
    else {
        for(i = 0; i < MAXCHILDREN; i++) t -> child[i] = NULL;
        t -> sibling = NULL;
        t -> nodekind = StmtK;
        t -> kind.stmt = kind;
        t -> lineNum = lineNum;
    }
    return t;
}

TreeNode * newExpNode(ExpKind kind, int lineNum) {
    TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if(t == NULL)
        printf("Out of memory error at line\n");
    else {
        for(i = 0; i < MAXCHILDREN; i++) t -> child[i] = NULL;
        t -> sibling = NULL;
        t -> nodekind = ExpK;
        t -> kind.exp = kind;
        t -> lineNum = lineNum;
  //      t -> type = Void;
    }
    return t;
}

TreeNode * newDeclNode(DeclKind kind, int lineNum) {
    TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;
    if(t == NULL)
        printf("Out of memory error at line\n");
    else {
        for(i = 0; i < MAXCHILDREN; i++) t -> child[i] = NULL;
        t -> sibling = NULL;
        t -> nodekind = DeclK;
        t -> kind.decl = kind;
        t -> lineNum = lineNum;
//        t -> type = Void;
    }
    return t;
}

void printTree(FILE* stdout, TreeNode *tree) {
	while(tree != NULL) {
		if(tree -> nodekind == StmtK) {
			switch(tree -> kind.stmt) {
				case IfK:
					printf("If ");
					break;
				case WhileK:
					printf("While ");
					break;
				case ForeachK:
					printf("Foreach ");
					break;
				case CompK:
					printf("Compound ");
					break;
				case ReturnK:
					printf("Return ");
					break;
				case BreakK:
					printf("Break ");
					break;
				default:
					printf("I don't know what kind of statement this is.\n");
					break;
			}
		}
		else if(tree -> nodekind == ExpK) {
			switch(tree -> kind.exp) {
				case OpK:
					printf("Op: c ");
					break; 	
				case ConstK:
					printf("Const: d ");
					break; 
				case IdK:
					printf("Id: s ");
					break;
				case CallK:
					printf("Call: s ");
					break;
				case AssignK:
					printf("Assign: s ");
					break;
			} 
		}
		else if(tree -> nodekind == DeclK) {
			switch(tree -> kind.decl) {
				case VarK:
					printf("Var %s ", tree -> attr.name);
					if(tree -> isArray == 1)
						printf("is array ");
					printf("of type ");
					if(tree -> type == 0) 
						printf("void ");
					else if(tree -> type == 1) 
						printf("int ");
					else if(tree -> type == 2) 
						printf("bool ");
					else if(tree -> type == 3) 
						printf("char ");
					break;
				case FunK:
					printf("Func %s returns type ", tree -> attr.name);
					if(tree -> type == 0) 
						printf("void ");
					else if(tree -> type == 1) 
						printf("int ");
					else if(tree -> type == 2) 
						printf("bool ");
					else if(tree -> type == 3) 
						printf("char ");
					break;	
			}
		}
		//for(int i = 0; i < MAXCHILDREN; i++) { printTree(stdout, tree -> child[i]); }
		printf("[line: %d]\n", tree -> lineNum);
		tree = tree -> sibling;
	}
	printf("Number of warnings: %d\nNumber of errors: %d\n", numWarnings, numErrors);
}
