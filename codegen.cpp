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
bool doInit = false;
bool doStore = false;
bool opLoad = false;
bool opStore = false;
inst opCode;
bool unary = false;
int staticCounter = 1;
int compSize = 0;
int parCounter = 0;
int tempIndex = 0;
int breakLoc = 0;
string opName;

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
            doStore = false;

            // doInit is an initializer override that only allows init of globals and statics
            if((!t->isStatic && !t->isGlobal) || ((t->isStatic || t->isGlobal) && doInit)) {
                if(t->isArray) {
                    emit(LDC, AC, t->memSize - 1, 6, "load size of array " + name);
                    emit(ST, AC, t->memOffset + 1, FP, "save size of array " + name);
                } else {
                    // if init'd variable decl
                    if(t->child[0] != NULL) {
                        emitBegin(t->child[0]);
                        emit(ST, AC, t->memOffset, FP, "Store variable " + name);
                    }
                }
            }
            break;
        case FuncK:
            // Set tempIndex based on params if there is no defined compK child
            TreeNode* sibCnt = t->child[0];
            int n;
            if(sibCnt != NULL) {
                for(n = 0; sibCnt != NULL; n++) sibCnt = sibCnt->sibling;
                if(!(t->child[1]->nodekind == StmtK && t->child[1]->kind.stmt == CompK)) {
                    tempIndex -= n + 2;
                }
            }

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
            tempIndex = 0;
            break;
    }
}

// Array size is 1 when the array is a 
void emitExpr(TreeNode* t) {
    string name = (t->kind.expr != ConstK) ? t->attr.name : "";
    inst OP;
    inst load = LDA;
    int tempRest = 0;
    int PTR;
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
            opName = name;
            if("+=" == name) { // Emit necessary instructions to do an op assign
                opCode = ADD;
            } else if("-=" == name) {
                opCode = SUB;
            } else if("/=" == name) {
                opCode = DIV;
            } else if("*=" == name) {
                opCode = MUL;
            } else if("++" == name) {
                opCode = LDA;
            } else if("--" == name) {
                opCode = LDA;
            }
                
            opStore = false;
            doStore = false;
            unary = false;
            opLoad = false;

            if(LHS->isArray) {
                doStore = false;
                if(LHS->child[0] != NULL) {
                    emitBegin(LHS->child[0]);
                    emit(ST, AC, compSize + tempIndex, FP, "Save index ");
                    tempIndex--;
                } 
            }
            opName = name;

            opStore = opLoad = doStore = unary = false;
            emitBegin(RHS);
            opName = name;

            if(name == "=") {
                doStore = true;
                opStore = false;
                emitBegin(LHS);
            } else {
                if(name == "--" || name == "++") {
                    unary = true;
                } else unary = false;
                doStore = opStore = opLoad = true;
                emitBegin(LHS);
            }
            opStore = false;
            opName = name;
            if(LHS->isArray && LHS->child[0] != NULL) tempIndex++;
            break;
        case OpK:
            doStore = false;
            load = LDA;
            if(LHS->isArray) load = LD;
            if(t->isStatic || t->isGlobal) PTR = GP;
            else PTR = FP;

            // Unary Ops
            if(RHS == NULL) {
                emitBegin(t->child[0]);
                if("*" == name) {
                    if(LHS->memSize == 1) load = LD;
                    emit(LD, AC, 1, AC, "Load array size ");
                } else if("?" == name) {
                    emit(RND, AC, AC, 6, "Op ? ");
                } else if("!" == name) {
                    emit(LDC, AC1, 1, 6, "Load 1 ");
                    emit(XOR, AC, AC, AC1, "Op NOT ");
                } else if("-" == name) {
                    emit(LDC, AC1, 0, 6, "Load 0 ");
                    emit(SUB, AC, AC1, AC, "Op unary - ");
                }
            } else { // Binary Ops
                emitBegin(t->child[0]);
                tempRest = tempIndex; // Save current viable temporary index  
                tempIndex--; // Increment past the index we plan to use
                emit(ST, 3, compSize + tempRest - parCounter, FP, "Save left side ");
                emitBegin(t->child[1]);
                emit(LD, AC1, compSize + tempRest - parCounter, FP, "Load left into ac1 ");
                tempIndex++; // Incrementation no longer needed
                if(">" == name) {
                    emit(TGT, AC, AC1, AC, "Op > ");
                } else if(">=" == name) {
                    emit(TGE, AC, AC1, AC, "Op >= ");
                } else if("<" == name) {
                    emit(TLT, AC, AC1, AC, "Op < "); 
                } else if("<=" == name) {
                    emit(TLE, AC, AC1, AC, "Op <= ");
                } else if("==" == name) {
                    emit(TEQ, AC, AC1, AC, "Op == ");
                } else if("!=" == name) {
                    emit(TNE, AC, AC1, AC, "Op != ");
                } else if("|" == name) {
                    emit(OR, AC, AC1, AC, "Op OR ");
                } else if("&" == name) {
                    emit(AND, AC, AC1, AC, "Op AND ");
                } else if("+" == name) {
                    emit(ADD, AC, AC1, AC, "Op + ");
                } else if("-" == name) {
                    emit(SUB, AC, AC1, AC, "Op - ");
                } else if("/" == name) {
                    emit(DIV, AC, AC1, AC, "Op / "); 
                } else if("*" == name) {
                    emit(MUL, AC, AC1, AC, "Op * ");
                } else if("%" == name) {
                    emit(DIV, AC2, AC1, AC, "Op % ");
                    emit(MUL, AC2, AC2, AC, " ");
                    emit(SUB, AC, AC1, AC2, " ");
                }
            }
            break;
        case ConstK:
            emitConstant(t);
            break;
        case IdK:
            PTR = (t->isGlobal || t->isStatic) ? 0 : 1;
            if(t->memSize == 1) load = LD;
            if(!doStore) { // Load 
                if(t->isArray) {
                    if(t->child[0] != NULL) {
                        emitBegin(t->child[0]);
                        emit(load, AC1, t->memOffset, PTR, "Load address of base of array " + name);
                        emit(SUB, AC, AC1, AC, "Compute offset of value ");
                        emit(LD, opLoad ? (unary ? AC : AC1) : AC, 0, AC, opLoad ? "Load LHS value " : "Load the value ");
                    } else {
                        emit(load, opLoad ? (unary ? AC : AC1) : AC, t->memOffset, PTR, opLoad ? "Load LHS address of base of array " : "Load address of base of array " + name);
                    }
                } else {
                    emit(LD, opLoad ? (unary ? AC : AC1) : AC, t->memOffset, PTR, (opLoad ? "load lhs variable " : "Load variable ") + name);
                }
            } else { // Store
                if(t->isArray) {
                    if(t->child[0] != NULL) {
                        emit(LD, AC1, compSize + tempIndex + 1, FP, "Restore index ");
                        emit(load, AC2, t->memOffset, PTR, "Load address of base of array " + name); 
                        emit(SUB, AC2, AC2, AC1, "Compute offset of value ");
                        if(opStore) { // Crazy array op assign insertion
                            emit(LD, opLoad ? (unary ? AC : AC1) : AC, 0, AC2, "load lhs variable " + name);
                            if(opName == "++") {
                                emit(LDA, AC, 1, AC, "increment value of " + name); 
                            } else if(opName == "--") {
                                emit(LDA, AC, -1, AC, "decrement value of " + name); 
                            } else emit(opCode, AC, AC1, AC, "op " + opName + " ");   
                        }
                        emit(ST, AC, 0, AC2, "Store variable " + name);
                    } else {
                        emit(load, AC, t->memOffset, PTR, "Load address of base of array [NONINDEX]" + name);
                    }
                } else {
                    if(opStore) { // Crazy op assign insertion
                        emit(LD, opLoad ? (unary ? AC : AC1) : AC, t->memOffset, PTR, "load lhs variable " + name);
                        if(opName == "++") {
                            emit(LDA, AC, 1, AC, "increment value of " + name); 
                        } else if(opName == "--") {
                            emit(LDA, AC, -1, AC, "decrement value of " + name); 
                        } else emit(opCode, AC, AC1, AC, "op " + opName + " ");   
                    }
                    emit(ST, AC, t->memOffset, PTR, "Store variable " + name);
                }
            }
            break;
        case CallK:
            TreeNode* found = (TreeNode*)table.lookup(t->attr.name);
            tempIndex -= 2; // For some magical reason this happens to the offsets
            
            // Temporaries to for use before and after recursion
            parCounter = 0;
            int parc = parCounter;
            bool stb = doStore;
            int tempI = tempIndex; 
            int comps = compSize;
            doStore = opLoad = false;

            // Call Begin
            emitComment("EXPRESSION");
            emitComment("                      Begin call to  " + name);
            emit(ST, FP, comps + tempI + 2, FP, "Store old fp in ghost frame "); 
            
            // Recurse
            emitBegin(t->child[0]);

            // Restore temporaries
            doStore = stb;
            parCounter = parc;
            compSize = comps;

            // Call End
            emitComment("                      Jump to " + name);
            emit(LDA, FP, compSize + tempI + 2, FP, "Load address of new frame ");
            emit(LDA, AC, FP, PC, "Return address in ac ");
            emit(LDA, PC, found->emitLoc - emitSkip(0), PC, "CALL " + name);
            emit(LDA, AC, 0, RT, "Save the result in ac ");
            emitComment("                      End call to " + name);
            
            // Reset ghost frame index
            tempIndex += 2;
            break;
    }

    if(t->isParam) {
        emit(ST, AC, compSize - parCounter + tempIndex, FP, "Store parameter ");
        parCounter++;
    }
}

void emitStmt(TreeNode* t) {
    int ifSkip, ifLoc, whileSkip, whileLoc, brkLoc;
    switch(t->kind.stmt) {
        case IfK:
            emitComment("IF");
            doStore = opLoad = false;
            emitBegin(t->child[0]);
            ifLoc = emitSkip(1);
            emitComment("THEN");
            emitComment("EXPRESSION");
            emitBegin(t->child[1]);
            ifSkip = emitSkip(0);

            emitBackup(ifLoc);
            if(t->child[2] != NULL) ifSkip++;
            emit(JZR, AC, ifSkip - emitSkip(0) - 1, PC, "Jump around the THEN if false [backpatch] ");
            emitRestore();

            if(t->child[2] != NULL) {
                emitComment("ELSE");
                emitComment("EXPRESSION");
                ifLoc = emitSkip(1);
                emitBegin(t->child[2]);
                ifSkip = emitSkip(0);
                emitBackup(ifLoc);
                emit(LDA, PC, ifSkip - emitSkip(0) - 1, PC, "Jump around the ELSE [backpatch] ");
                emitRestore();
            }

            emitComment("ENDIF");
            break;
        case WhileK:
            doStore = opLoad = false;
            whileLoc = emitSkip(0);
            emitComment("WHILE");
            emitBegin(t->child[0]);
            emit(JNZ, AC, 1, PC, "Jump to while part ");
            whileSkip = emitSkip(1);
            brkLoc = breakLoc;
            breakLoc = emitSkip(0); 

            emitComment("DO");
            emitBegin(t->child[1]);
            
            emit(LDA, PC, whileLoc - emitSkip(0) - 1, PC, "go to beginning of loop ");
            whileLoc = emitSkip(0);
            emitBackup(whileSkip);
            emit(LDA, PC, whileLoc - whileSkip - 1, PC, "Jump past loop [backpatch] "); 
            emitRestore();

            breakLoc = brkLoc;
            emitComment("ENDWHILE");
            break;
        case ForK:
            emitComment("FOR");
            for(int i = 0; i < 3; i++) emitBegin(t->child[i]);
            emitComment("ENDFOR");
            break;
        case ReturnK:
            emitComment("RETURN");
            doStore = opLoad = false;
            emitBegin(t->child[0]);
            if(t->child[0] != NULL) {
                emit(LDA, RT, 0, AC, "Copy result to rt register ");
            }
            emit(LD, AC, -1, FP, "Load return address ");
            emit(LD, FP, 0, FP, "Adjust fp ");
            emit(LDA, PC, 0, AC, "Return ");
            break;
        case BreakK:
            emitComment("BREAK");
            emit(LDA, PC, breakLoc - emitSkip(0) - 2, PC, "break ");
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
    doInit = true;
    compSize = -2;
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
                    emitBegin(t->child[0]);
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
