* C- compiler version C-F15
* Built: date
* Author: Zachary M. Yama
* File compiled: ./test/tinyCall.c-
* FUNCTION input
  1:     ST  3,-1(1)	Store return address 
  2:     IN  2,2,2	Grab int input 
  3:     LD  3,-1(1)	Load return address 
  4:     LD  1,0(1)	Adjust fp 
  5:    LDA  7,0(3)	Return 
* END FUNCTION input
* FUNCTION output
  6:     ST  3,-1(1)	Store return address 
  7:     LD  3,-2(1)	Load paramater 
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
 19:     LD  3,-2(1)	Load paramater 
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
 31:     LD  3,-2(1)	Load paramater 
 32:   OUTC  3,3,3	Output char 
 33:    LDC  2,0(6)	Set return to 0 
 34:     LD  3,-1(1)	Load return address 
 35:     LD  1,0(1)	Adjust fp 
 36:    LDA  7,0(3)	Return 
* END FUNCTION outputc
* FUNCTION outnl
 37:     ST  3,-1(1)	Store return address 
 38:  OUTNL  2,2,2	Output a newline 
 39:     LD  3,-1(1)	Load return address 
 40:     LD  1,0(1)	Adjust fp 
 41:    LDA  7,0(3)	Return 
* END FUNCTION outnl
* FUNCTION cheyenne
 42:     ST  3,-1(1)	Store return address 
* Add standard closing in case there is no return statement
 43:    LDC  2,0(6)	Set return value to 0 
 44:     LD  3,-1(1)	Load return address 
 45:     LD  1,0(1)	Adjust fp 
 46:    LDA  7,0(3)	Return 
* END FUNCTION cheyenne
* FUNCTION sioux
 47:     ST  3,-1(1)	Store return address 
* Add standard closing in case there is no return statement
 48:    LDC  2,0(6)	Set return value to 0 
 49:     LD  3,-1(1)	Load return address 
 50:     LD  1,0(1)	Adjust fp 
 51:    LDA  7,0(3)	Return 
* END FUNCTION sioux
* FUNCTION comanche
 52:     ST  3,-1(1)	Store return address 
* Add standard closing in case there is no return statement
 53:    LDC  2,0(6)	Set return value to 0 
 54:     LD  3,-1(1)	Load return address 
 55:     LD  1,0(1)	Adjust fp 
 56:    LDA  7,0(3)	Return 
* END FUNCTION comanche
* FUNCTION main
 57:     ST  3,-1(1)	Store return address 
* Add standard closing in case there is no return statement
 58:    LDC  2,0(6)	Set return value to 0 
 59:     LD  3,-1(1)	Load return address 
 60:     LD  1,0(1)	Adjust fp 
 61:    LDA  7,0(3)	Return 
* END FUNCTION main
  0:    LDA  7,61(7)	Jump to init [backpatch] 
* INIT
 63:     LD  0,0(0)	Set the global pointer 
 64:    LDA  1,0(0)	set first frame at end of globals 
 65:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
 66:    LDC  3,5(6)	load size of array ga 
 67:     ST  3,0(6)	save size of array ga 
 68:    LDC  3,6(6)	load size of array gb 
 69:     ST  3,-6(6)	save size of array gb 
 70:    LDC  3,7(6)	load size of array gc 
 71:     ST  3,-13(6)	save size of array gc 
 72:    LDC  3,5(6)	load size of array 1 
 73:     ST  3,-21(6)	save size of array 1 
 74:    LDC  3,6(6)	load size of array 2 
 75:     ST  3,-27(6)	save size of array 2 
 76:    LDC  3,7(6)	load size of array 3 
 77:     ST  3,-34(6)	save size of array 3 
* END INIT GLOBALS AND STATICS
 78:    LDA  3,1(2)	Return address in AC 
 79:    LDA  7,22(7)	Jump to main 
 80:   HALT  0,0,0	DONE! 
* END INIT
