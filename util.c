//#include "globals.h"
#include "util.h"

static int spaces = 0;
static int chiCount = 0;
static int siblingIndex = 0;

void printToken(TokenType token, const char* tokenString) {
}

// As per the tiny compiler. Probably the most ugly way to do a print statement.
void printTree(TreeNode *tree, int sibCount) {
    bool flag = false;
    if(sibCount == -1) {
        sibCount++;
        flag = true;
    } else {
        spaces += 4;
    }
    for(TreeNode *t = tree; t != NULL; t = t -> sibling) {
        printSpaces();
        if(sibCount > 0) {
            printf("|Sibling: %i ", sibCount);
        } else if(sibCount == 0 && flag == false) {
            printf("Child: %i ", chiCount); 
        } 
        sibCount++;
        
        if(t -> nodekind == StmtK) {
            switch(t -> kind.stmt) {
                case IfK:
                    printf("If ");
                    break;
                case ForK: 
                    printf("Foreach ");
                    break;
                case WhileK:
                    printf("While ");
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
            }
        } else if(t -> nodekind == ExprK) {
            switch(t -> kind.expr) {
                case ConstK:
                    printf("Const: "); 
                    switch(t -> declType) {
                        case Int: 
                            printf("%i ", t -> attr.ivalue);
                            break;
                        case Bool:
                            if(t -> attr.ivalue == 0) {
                                printf("false ");
                            } else {
                                printf("true ");
                            }
                            break;
                        case Char:
                            printf("'%c' ", t -> attr.cvalue);
                            break;
                        case String:
                            printf("\"%s\" ", t -> attr.svalue);
                            break;
                        default:
                            break;
                    }
                    break;
                case IdK:
                    printf("Id: %s ", t -> attr.name);
                    break;
                case OpK:
                    printf("Op: %s ", t -> attr.name);
                    break;
                case AssignK:
                    printf("Assign: %s ", t -> attr.name);
                    break;
                case SimpK:
                    printf("Simp: %s ", t -> attr.name);
                    break;
                case CallK:
                    printf("Call: %s ", t -> attr.name);
                    break;
            }
        } else if(t -> nodekind == DeclK) {
            switch(t -> kind.decl) {
                case FuncK:
                    printf("Func %s returns ", t -> attr.name);
                    break;
                case VarK:
                    if(t -> isArray == true) {
                        printf("Var %s is array of ", t -> attr.name);
                    } else {
                        printf("Var %s of ", t -> attr.name);
                    }
                    break;
                case ParamK:
                    if(t -> isArray == true) {
                        printf("Param %s is array of ", t -> attr.name);
                    } else {
                        printf("Param %s of ", t -> attr.name);
                    }
                    break;
                default:
                    break;
            }
            switch(t -> declType) {
                case Void:
                    printf("type void ");
                    break;
                case Int:
                    printf("type int ");
                    break;
                case Bool:
                    printf("type bool ");
                    break;
                case Char: 
                    printf("type char ");
                    break;
                default:
                    break;
            }
        } else {
            printf("Unknown node kind.\n");
        }
        printf("[line: %d]\n", t -> lineno);
        for(int i = 0; i < MAXCHILDREN; i++) {
            chiCount = i;
            printTree(t -> child[i], 0);
            chiCount = 0;
        }
    }
    siblingIndex--;
    spaces -= 4;
}

void printSpaces() {
    for(int i = 0; i < spaces; i++) {
        if(i % 4 == 0) {
            printf("|");
        } else { 
            printf(" ");
        } 
    }
}

TreeNode *newStmtNode(StmtKind kind) {
    TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
    for(int i = 0; i < MAXCHILDREN; i++) t -> child[i] = NULL;
    t -> sibling = NULL;
    t -> nodekind = StmtK;
    t -> kind.stmt = kind;
    t -> lineno = yylineno;
    return t;
}

TreeNode *newExprNode(ExprKind kind) {
    TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
    for(int i = 0; i < MAXCHILDREN; i++) t -> child[i] = NULL;
    t -> sibling = NULL;
    t -> nodekind = ExprK;
    t -> kind.expr = kind;
    t -> lineno = yylineno;
    return t;
}

TreeNode *newDeclNode(DeclKind kind) {
    TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
    for(int i = 0; i < MAXCHILDREN; i++) t -> child[i] = NULL;
    t -> sibling = NULL;
    t -> nodekind = DeclK;
    t -> kind.decl = kind;
    t -> lineno = yylineno;
    return t;
}
