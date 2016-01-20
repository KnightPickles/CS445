// codegen.cpp
// Zachary Yama
#ifndef CODEGEN_CPP
#define CODEGEN_CPP

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "codegen.h"

using namespace std;

int pc = 1; 
ofstream tmo;

enum instruction { HALT, NOP,IN,OUT,INB,OUTB,INC,OUTC,OUTLN,ADD,SUB,MUL,DIV,AND,OR,XOR,NOT,SWP,RND,LDC,LDA,LD,LDL,LDI,ST,STI,JNZ,JZR,TLT,TLE,TEQ,TNE,TGE,TGT,MOV,SET,CMP,CPI };
string instString[] = { "HALT", "NOP", "IN", "OUT", "INB", "OUTB", "INC", "OUTC", "OUTLN", "ADD", "SUB", "MUL", "DIV", 
    "AND", "OR", "XOR", "NOT", "SWP", "RND", "LDC", "LDA", "LD", "LDL", "LDI", "ST", "STI", "JNZ", "JZR", "TLT", "TLE", "TEQ", "TNE", "TGE", "TGE", "TGT", "MOV", "SET", "CMP", "CPI" };

void args(int r, int s, int t) {
    tmo << left << " " << r << "," << s << "," << t; 
}

void argsParen(int r, int s, int t) {
    tmo << left << " " << r << "," << s << "(" << t << ")"; 
}

void comment(string s) {
    tmo << s << endl;
}

void emit(instruction inst, int r, int s, int t, string com) {
    tmo << right << setw(4) << pc << setw(12) << instString[inst];
    switch(inst) {
        case OUTLN: case HALT:
        case NOP: case IN: case OUT: case INB: case OUTB: case INC: case OUTC: case ADD: case SUB:
        case MUL: case DIV: case AND: case OR: case XOR: case NOT: case SWP: case RND: case TLT:
        case TLE: case TEQ: case TNE: case TGE: case TGT: case MOV: case SET: case CMP: case CPI: 
            args(r, s, t); comment(com); break; 
        case LDC: case LDA: case LD: case LDL: case LDI: case ST: case STI: case JNZ: case JZR: 
            argsParen(r, s, t); comment(com); break; 
        default: break;
    }
    pc++;
}

void generateCode(TreeNode* syntaxTree, char* outfile) {
    tmo.open(outfile);
    TreeNode* t = syntaxTree;
    TreeNode* contFromIO = transIOLibTM(t);
    transInputTM(contFromIO);
    tmo.close();
}

TreeNode* transIOLibTM(TreeNode* syntaxTree) {
    char* s = syntaxTree->attr.name;
    if(strcmp("input", s) == 0) {
        emit(ST, 3, -1, 1, "Store return address");
        emit(IN, 2, 2, 2, "Grab int input");
        emit(LD, 3, -1, 1, "Load return address");
        emit(LD, 1, 0, 1, "Adjust fp");
        emit(LDA, 7, 0, 3, "Return");
    } else if(strcmp("output", s) == 0) {
        emit(ST, 3, -1, 1, "Store return address");        
    } else if(strcmp("inputb", s) == 0) {

    } else if(strcmp("outputb", s) == 0) {

    } else if(strcmp("inputc", s) == 0) {

    } else if(strcmp("outputc", s) == 0) {

    } else if(strcmp("outln", s) == 0) {

    } else {
        // Return where we left off 
        return syntaxTree;
    }
    if(syntaxTree->sibling != NULL) transInputTM(syntaxTree->sibling);
    return NULL;
}

void transInputTM(TreeNode* syntaxTree) {
    
    if(syntaxTree->sibling != NULL) transInputTM(syntaxTree->sibling);
}

#endif
