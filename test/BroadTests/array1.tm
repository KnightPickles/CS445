* C- compiler version C-F15
* Built: Dec 1, 2015
* Author: Robert B. Heckendorn
* File compiled:  array1.c-
* FUNCTION input
  1:     ST  3,-1(1)	Store return address 
  2:     IN  2,2,2	Grab int input 
  3:     LD  3,-1(1)	Load return address 
  4:     LD  1,0(1)	Adjust fp 
  5:    LDA  7,0(3)	Return 
* END FUNCTION input
* FUNCTION output
  6:     ST  3,-1(1)	Store return address 
  7:     LD  3,-2(1)	Load parameter 
  8:    OUT  3,3,3	Output integer 
  9:    LDC  2,0(6)	Set return to 0 
 10:     LD  3,-1(1)	Load return address 
 11:     LD  1,0(1)	Adjust fp 
 12:    LDA  7,0(3)	Return 
* END FUNCTION output
* FUNCTION inputb
 13:     ST  3,-1(1)	Store return address 
 14:    INB  2,2,2	Grab bool input 
 15:     LD  3,-1(1)	Load return address 
 16:     LD  1,0(1)	Adjust fp 
 17:    LDA  7,0(3)	Return 
* END FUNCTION inputb
* FUNCTION outputb
 18:     ST  3,-1(1)	Store return address 
 19:     LD  3,-2(1)	Load parameter 
 20:   OUTB  3,3,3	Output bool 
 21:    LDC  2,0(6)	Set return to 0 
 22:     LD  3,-1(1)	Load return address 
 23:     LD  1,0(1)	Adjust fp 
 24:    LDA  7,0(3)	Return 
* END FUNCTION outputb
* FUNCTION inputc
 25:     ST  3,-1(1)	Store return address 
 26:    INC  2,2,2	Grab char input 
 27:     LD  3,-1(1)	Load return address 
 28:     LD  1,0(1)	Adjust fp 
 29:    LDA  7,0(3)	Return 
* END FUNCTION inputc
* FUNCTION outputc
 30:     ST  3,-1(1)	Store return address 
 31:     LD  3,-2(1)	Load parameter 
 32:   OUTC  3,3,3	Output char 
 33:    LDC  2,0(6)	Set return to 0 
 34:     LD  3,-1(1)	Load return address 
 35:     LD  1,0(1)	Adjust fp 
 36:    LDA  7,0(3)	Return 
* END FUNCTION outputc
* FUNCTION outnl
 37:     ST  3,-1(1)	Store return address 
 38:  OUTNL  3,3,3	Output a newline 
 39:     LD  3,-1(1)	Load return address 
 40:     LD  1,0(1)	Adjust fp 
 41:    LDA  7,0(3)	Return 
* END FUNCTION outnl
* FUNCTION ford
 42:     ST  3,-1(1)	Store return address. 
* COMPOUND
 43:    LDC  3,22(6)	load size of array z
 44:     ST  3,-4(1)	save size of array z
* EXPRESSION
 45:     LD  3,-2(1)	Load address of base of array x
 46:     LD  3,1(3)	Load array size 
* EXPRESSION
 47:    LDC  3,11(6)	Load integer constant 
 48:     ST  3,-27(1)	Save index 
 49:    LDC  3,3(6)	Load integer constant 
 50:     LD  4,-2(1)	Load address of base of array x
 51:    SUB  3,4,3	Compute offset of value 
 52:     LD  3,0(3)	Load the value 
 53:     LD  4,-27(1)	Restore index 
 54:    LDA  5,-5(1)	Load address of base of array z
 55:    SUB  5,5,4	Compute offset of value 
 56:     ST  3,0(5)	Store variable z
* EXPRESSION
 57:    LDC  3,3(6)	Load integer constant 
 58:     ST  3,-27(1)	Save index 
 59:    LDC  3,777(6)	Load integer constant 
 60:     LD  4,-27(1)	Restore index 
 61:     LD  5,-2(1)	Load address of base of array x
 62:    SUB  5,5,4	Compute offset of value 
 63:     ST  3,0(5)	Store variable x
* END COMPOUND
* Add standard closing in case there is no return statement
 64:    LDC  2,0(6)	Set return value to 0 
 65:     LD  3,-1(1)	Load return address 
 66:     LD  1,0(1)	Adjust fp 
 67:    LDA  7,0(3)	Return 
* END FUNCTION ford
* FUNCTION main
 68:     ST  3,-1(1)	Store return address. 
* COMPOUND
 69:    LDC  3,33(6)	load size of array y
 70:     ST  3,-2(1)	save size of array y
* EXPRESSION
 71:    LDC  3,3(6)	Load integer constant 
 72:     ST  3,-36(1)	Save index 
 73:    LDC  3,666(6)	Load integer constant 
 74:     LD  4,-36(1)	Restore index 
 75:    LDA  5,-3(1)	Load address of base of array y
 76:    SUB  5,5,4	Compute offset of value 
 77:     ST  3,0(5)	Store variable y
* EXPRESSION
*                       Begin call to  ford
 78:     ST  1,-36(1)	Store old fp in ghost frame 
*                       Load param 1
 79:    LDA  3,-3(1)	Load address of base of array y
 80:     ST  3,-38(1)	Store parameter 
*                       Load param 2
 81:    LDA  3,-3(1)	Load address of base of array y
 82:     ST  3,-39(1)	Store parameter 
*                       Jump to ford
 83:    LDA  1,-36(1)	Load address of new frame 
 84:    LDA  3,1(7)	Return address in ac 
 85:    LDA  7,-44(7)	CALL ford
 86:    LDA  3,0(2)	Save the result in ac 
*                       End call to ford
* EXPRESSION
*                       Begin call to  output
 87:     ST  1,-36(1)	Store old fp in ghost frame 
*                       Load param 1
 88:    LDC  3,3(6)	Load integer constant 
 89:    LDA  4,-3(1)	Load address of base of array y
 90:    SUB  3,4,3	Compute offset of value 
 91:     LD  3,0(3)	Load the value 
 92:     ST  3,-38(1)	Store parameter 
*                       Jump to output
 93:    LDA  1,-36(1)	Load address of new frame 
 94:    LDA  3,1(7)	Return address in ac 
 95:    LDA  7,-90(7)	CALL output
 96:    LDA  3,0(2)	Save the result in ac 
*                       End call to output
* EXPRESSION
*                       Begin call to  outnl
 97:     ST  1,-36(1)	Store old fp in ghost frame 
*                       Jump to outnl
 98:    LDA  1,-36(1)	Load address of new frame 
 99:    LDA  3,1(7)	Return address in ac 
100:    LDA  7,-64(7)	CALL outnl
101:    LDA  3,0(2)	Save the result in ac 
*                       End call to outnl
* END COMPOUND
* Add standard closing in case there is no return statement
102:    LDC  2,0(6)	Set return value to 0 
103:     LD  3,-1(1)	Load return address 
104:     LD  1,0(1)	Adjust fp 
105:    LDA  7,0(3)	Return 
* END FUNCTION main
  0:    LDA  7,105(7)	Jump to init [backpatch] 
* INIT
106:     LD  0,0(0)	Set the global pointer 
107:    LDA  1,0(0)	set first frame at end of globals 
108:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
109:    LDA  3,1(7)	Return address in ac 
110:    LDA  7,-43(7)	Jump to main 
111:   HALT  0,0,0	DONE! 
* END INIT
