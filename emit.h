#ifndef EMIT_H
#define EMIT_H

//
//  Special register defines for optional use in calling the 
//  routines below.
//

#define GP   0  //  The global pointer
#define FP   1  //  The local frame pointer
#define RT   2  //  Return value
#define AC   3  //  Accumulator
#define AC1  4  //  Accumulator
#define AC2  5  //  Accumulator
#define AC3  6  //  Accumulator
#define PC   7  //  The program counter

//  No comment please...
#define NO_COMMENT (char *)""

//  We always trace the code
#define TraceCode   1

#include <string>
using namespace std;

enum inst {HALT,NOP,IN,OUT,INB,OUTB,INC,OUTC,OUTNL,ADD,SUB,MUL,DIV,AND,OR,XOR,NOT,SWP,RND, 
    LDC,LDA,LD,LDL,LDI,ST,STI,JNZ,JZR,TLT,TLE,TEQ,TNE,TGE,TGT,MOV,SET,CMP,CPI};

//  The following functions were borrowed from Tiny compiler code generator
int emitSkip(int howMany); //this one
void emitBackup(int loc);
void emitRestore();

void emitComment(string c); //this one
void emitComment(char *c, char *cc);

void emitGoto(int d, int s, char *c);
void emitGoto(int d, int s, char *c, char *cc);
void emitGotoAbs(int a, char *c);
void emitGotoAbs(int a, char *c, char *cc);

void emit(inst op, int r, int s, int t, string c);

void emitRM(string op, int r, int d, int s, string c); //this one with ()
void emitRM(char *op, int r, int d, int s, char *c, char *cc);
void emitRMAbs(char *op, int r, int a, char *c);
void emitRMAbs(char *op, int r, int a, char *c, char *cc);

void emitRO(string op, int r, int s, int t, string c); //this oen without ()
void emitRO(char *op, int r, int s, int t, char *c, char *cc);

void backPatchAJumpToHere(int addr, char *comment);
void backPatchAJumpToHere(char *cmd, int reg, int addr, char *comment);

void emitLit(char *s);

#endif
