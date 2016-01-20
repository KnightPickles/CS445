// codegen.cpp

#include <string>
#include "codegen.h"
#include "emit.h"

//int emitSkip(int howMany); // returns the space where we want to skip and makes whitespace 
//void emitBackup(int loc); // jumps to a line and allows for overwriting
//emitComment(char *c);
//void emit(char *op, int r, int d, int s, char *c); //this one with ()
//void emit(char *op, int r, int s, int t, char *c); //this oen without ()

using namespace std;

extern int gOffset;
extern int lOffset;

FILE* code;
SymbolTable table;
bool isReturn = false;
bool isLHS = true;
bool doStore = false;
int staticCounter = 1;
int compSize = 0;
int parCounter = 0;
int compC = 2;
int tempIndex = 0;

void generateCode(TreeNode* tree, SymbolTable st, char* outfile, char* infile) {
    table = st;
    if(strcmp(outfile, "-") == 0) { 
        code = stdout; 
    } else code = fopen(outfile, "w");
    emitHeader(infile);
    emitIOLib(tree);
    emitInput(tree);
    emitInit(tree);
    fclose(code);
}

void emitHeader(char* filename) {
    emitComment("C- compiler version C-F15");
    emitComment("Built: date");
    emitComment("Author: Zachary M. Yama");
    string file(filename);
    emitComment("File compiled: " + file);
    emitSkip(1);
}

void emitInput(TreeNode* tree) {
    for(int i = 0; i < 7; i++) tree = tree->sibling; 
    emitBegin(tree);
}


void emitInit(TreeNode* tree) {
    TreeNode* main = (TreeNode*)table.lookup("main");
    int restore = emitSkip(0);
    emitBackup(0);
    emit(LDA, PC, restore - 1, PC, "Jump to init [backpatch] "); 
    emitSkip(restore - 1);
    emitComment("INIT");
    emit(LD, GP, 0, 0, "Set the global pointer ");
    emit(LDA, FP, gOffset, GP, "set first frame at end of globals ");
    emit(ST, FP, 0, FP, "store old fp (point to self) ");
    emitComment("INIT GLOBALS AND STATICS");
    emitGlobalsAndStatics(tree);
    emitComment("END INIT GLOBALS AND STATICS");
    emit(LDA, AC, FP, PC, "Return address in ac ");
    emit(LDA, PC, main->emitLoc - emitSkip(0), PC, "Jump to main ");
    emit(HALT, 0, 0, 0, "DONE! ");
    emitComment("END INIT");
}

void emitIOLib(TreeNode* tree) {
    TreeNode* t = tree;
    inst instructions[] = {IN, OUT, INB, OUTB, INC, OUTC, OUTNL};
    string instructStr[] = {"int", "integer", "bool", "bool", "char", "char", "a newline "};
    for(int i = 0; i < 7; i++) {
        t->emitLoc = emitSkip(0) - 1;
        string name(t->attr.name);
        emitComment((char*)("FUNCTION " + name).c_str());
        emit(ST, AC, -1, FP, "Store return address ");
        if(i % 2 == 0) {
            int s = 2;
            string com = "Grab ";
            string com2 = " input ";
            if(i == 6) { 
                s = 3;
                com = "Output ";
                com2 = "";
            }
            emit(instructions[i], s, s, s, com + instructStr[i] + com2);
        } else {
            emit(LD, AC, -2, FP, "Load parameter ");
            emit(instructions[i], 3, 3, 3, "Output " + instructStr[i] + " ");
            emit(LDC, RT, 0, 6, "Set return to 0 ");
        }
        emit(LD, AC, -1, FP, "Load return address ");
        emit(LD, FP, 0, FP, "Adjust fp ");
        emit(LDA, PC, 0, AC, "Return ");
        emitComment((char*)("END FUNCTION " + name).c_str());
        t = t->sibling;
    }
}

void emitConstant(TreeNode* node) {
    if(node == NULL) return;
    if(node->nodekind == ExprK && node->kind.expr == ConstK) { 
        switch(node->declType) {
            default: break;
            case Int:
                emit(LDC, AC, node->attr.ivalue, 6, "Load integer constant ");
                break;
            case Bool:
                emit(LDC, AC, node->attr.ivalue, 6, "Load Boolean constant ");
                break;
            case Char:
                if(node->isArray) break;
                emit(LDC, AC, node->attr.cvalue, 6, "Load char constant ");
                break;
        }
    }
}

void emitBegin(TreeNode* tree) {
    if(tree == NULL) return;
    switch(tree->nodekind) {
        case DeclK: emitDecl(tree); break;
        case ExprK: emitExpr(tree); break;
        case StmtK: emitStmt(tree); break;
    }
    emitBegin(tree->sibling);
}

void emitDecl(TreeNode* t) {
    string name = t->attr.name;
    switch(t->kind.decl) {
        case ParamK:
            for(int i = 0; i < 3; i++) emitBegin(t->child[i]);
            break;
        case VarK:
            name = t->attr.name;
            if(!t->isGlobal && !t->isStatic) {
                if(t->isArray) {
                    emit(LDC, AC, t->memSize - 1, 6, "load size of array " + name);
                    emit(ST, AC, t->memOffset + 1, FP, "save size of array " + name);
                } else {
                    // if init'd variable decl
                    if(t->child[0] != NULL) {
                        emitConstant(t->child[0]);
                        emit(ST, AC, t->memOffset, FP, "Store variable " + name);
                    }
                }
            }
            break;
        case FuncK:
            t->emitLoc = emitSkip(0) - 1; // allows function tracking for calls

            emitComment("FUNCTION " + name);
            emit(ST, AC, -1, FP, "Store return address. ");
            
            for(int i = 0; i < 3; i++) emitBegin(t->child[i]);

            // Add return in case there isn't one
            emitComment("Add standard closing in case there is no return statement");
            emit(LDC, RT, 0, 6, "Set return value to 0 ");
            emit(LD, AC, -1, FP, "Load return address ");
            emit(LD, FP, 0, FP, "Adjust fp ");
            emit(LDA, PC, 0, AC, "Return "); 

            emitComment("END FUNCTION " + name);
            break;
    }
}

// Array size is 1 when the array is a 
void emitExpr(TreeNode* t) {
    string name;
    inst load = LDA;
    TreeNode* LHS = t->child[0];
    TreeNode* RHS = t->child[1];

    if(t->isParam) {
        char parCStr[10];
        sprintf(parCStr, "%i", parCounter + 1);
        emitComment("                      Load param " + (string)parCStr);
    }
    
    switch(t->kind.expr) {
        case AssignK: 
            emitComment("EXPRESSION");

            if(!LHS->isArray) {
                doStore = false;
                emitBegin(RHS);
                doStore = true;
                emitBegin(LHS);
            } else {
                doStore = false;
                if(LHS->child[0] != NULL) {
                    emitBegin(LHS->child[0]);
                    emit(ST, AC, compSize, FP, "Save index ");
                }
                doStore = false;
                emitBegin(RHS);
                doStore = true;
                emitBegin(LHS);
            }
            break;
        case OpK:
            for(int i = 0; i < 3; i++) emitBegin(t->child[i]);
            if(strcmp(t->attr.name, "*") == 0) {
                if(t->child[0]->memSize == 1) load = LD;
                emit(LD, AC, 1, AC, "Load array size ");
            }
            break;
        case ConstK:
            emitConstant(t);
            break;
        case IdK:
            name = t->attr.name;
            if(t->memSize == 1) load = LD;
            if(!doStore) { // Load 
                if(t->isArray) {
                    if(t->child[0] != NULL) {
                        emitBegin(t->child[0]);
                        emit(load, AC1, t->memOffset, t->isStatic ? GP : (t->isGlobal ? GP : FP), "Load address of base of array " + name);
                        emit(SUB, AC, AC1, AC, "Compute offset of value ");
                        emit(LD, AC, 0, AC, "Load the value ");
                    } else {
                        emit(load, AC, t->memOffset, t->isStatic ? GP : (t->isGlobal ? GP : FP), "Load address of base of array " + name);
                    }
                } else {
                    emit(LD, AC, t->memOffset, t->isStatic ? GP : (t->isGlobal ? GP : FP), "Load variable " + name);
                }
            } else { // Store
                if(t->isArray) {
                    if(t->child[0] != NULL) {
                        emit(LD, AC1, compSize, FP, "Restore index ");
                        emit(load, AC2, t->memOffset, t->isStatic ? GP : (t->isGlobal ? GP : FP), "Load address of base of array " + name); 
                        emit(SUB, AC2, AC2, AC1, "Compute offset of value ");
                        emit(ST, AC, 0, AC2, "Store variable " + name);
                    } else {
                        emit(load, AC, t->memOffset, t->isStatic ? GP : (t->isGlobal ? GP : FP), "Load address of base of array [NONINDEX]" + name);
                    }
                } else {
                    emit(ST, AC, t->memOffset, t->isStatic ? GP : (t->isGlobal ? GP : FP), "Store variable " + name);
                }
            }
            break;
        case CallK:
            TreeNode* found = (TreeNode*)table.lookup(t->attr.name);
            int comps = compSize;
            compC-=2;
            emitComment("EXPRESSION");
            // do global comp size
            name = t->attr.name;
            emitComment("                      Begin call to  " + name);
            emit(ST, FP, comps + compC, FP, "Store old fp in ghost frame ");
           
            parCounter = 0;
            int parc = parCounter;
            bool stb = doStore;
            doStore = false;
            emitBegin(t->child[0]);
            doStore = stb;
            parCounter = parc;
            compSize = comps;

            emitComment("                      Jump to " + name);
            emit(LDA, FP, compSize + compC, FP, "Load address of new frame ");
            emit(LDA, AC, FP, PC, "Return address in ac ");
            emit(LDA, PC, found->emitLoc - emitSkip(0), PC, "CALL " + name);
            emit(LDA, AC, 0, RT, "Save the result in ac ");
            emitComment("                      End call to " + name);
            compC+=2;

            break;
    }

    if(t->isParam) {
        emit(ST, AC, compSize - 2 - parCounter + compC, FP, "Store parameter ");
        parCounter++;
    }
}

void emitStmt(TreeNode* t) {
    switch(t->kind.stmt) {
        case IfK:
            for(int i = 0; i < 3; i++) emitBegin(t->child[i]);
            break;
        case WhileK:
            for(int i = 0; i < 3; i++) emitBegin(t->child[i]);
            break;
        case ForK:
            for(int i = 0; i < 3; i++) emitBegin(t->child[i]);
            break;
        case ReturnK:
            emitComment("RETURN");
            isReturn = true;
            emitBegin(t->child[0]);
            isReturn = false;
            if(t->child[0] != NULL) {
                emit(LDA, RT, 0, AC, "Copy result to rt register ");
            }
            emit(LD, AC, -1, FP, "Load return address ");
            emit(LD, FP, 0, FP, "Adjust fp ");
            emit(LDA, PC, 0, AC, "Return ");
            break;
        case BreakK:
            for(int i = 0; i < 3; i++) emitBegin(t->child[i]);
            break;
        case CompK:
            compSize = t->memSize;
            emitComment("COMPOUND");
            for(int i = 0; i < 3; i++) emitBegin(t->child[i]);
            emitComment("END COMPOUND");
            break;
    }
}

void emitGlobalsAndStatics(TreeNode* t) {
    if(t == NULL) return;

    if(t->nodekind == DeclK && t->kind.decl == VarK) {
        if(t->isGlobal || t->isStatic) {
            string name(t->attr.name);
            char str[10];
            sprintf(str, "%i", staticCounter);
            string statstr;
            statstr = t->isStatic ? "-" + (string)str : "";

            if(t->isArray) {
                emit(LDC, AC, t->memSize - 1, 6, "load size of array " + name + statstr);
                emit(ST, AC, t->memOffset + 1, 0, "save size of array " + name + statstr);
            } else {
                if(t->child[0] != NULL) {
                    emitConstant(t->child[0]);
                    emit(ST, AC, t->memOffset, GP, "Store variable " + name + statstr);
                }
            }
            if(t->isStatic) { 
                t->staticIndex = staticCounter;
                staticCounter++;
            }
        }
    }
    for(int i = 0; i < 3; i++) emitGlobalsAndStatics(t->child[i]);
    emitGlobalsAndStatics(t->sibling);
}
