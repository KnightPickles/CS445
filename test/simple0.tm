* C- compiler version C-F15
* Built: Oct 14, 2015
* Author: Robert B. Heckendorn
* File compiled:  simple0.c-
* FUNCTION input
  1:     ST  3,-1(1)	 
  2:     IN  2,2,2	 
  3:     LD  3,-1(1)	 
  4:     LD  1,0(1)	 
  5:    LDA  7,0(3)	 
* END FUNCTION input
* FUNCTION output
  6:     ST  3,-1(1)	 
  7:     LD  3,-2(1)	 
  8:    OUT  3,3,3	
  9:    LDC  2,0(6)	 
 10:     LD  3,-1(1)	 
 11:     LD  1,0(1)	 
 12:    LDA  7,0(3)	 
* END FUNCTION output
* FUNCTION inputb
 13:     ST  3,-1(1)	 
 14:    INB  2,2,2	 
 15:     LD  3,-1(1)	 
 16:     LD  1,0(1)	 
 17:    LDA  7,0(3)	
* END FUNCTION inputb
* FUNCTION outputb
 18:     ST  3,-1(1)	 
 19:     LD  3,-2(1)	 
 20:   OUTB  3,3,3	 
 21:    LDC  2,0(6)	 
 22:     LD  3,-1(1)	 
 23:     LD  1,0(1)	 
 24:    LDA  7,0(3)	 
* END FUNCTION outputb
* FUNCTION inputc
 25:     ST  3,-1(1)	 
 26:    INC  2,2,2	 
 27:     LD  3,-1(1)	 
 28:     LD  1,0(1)	 
 29:    LDA  7,0(3)	 
* END FUNCTION inputc
* FUNCTION outputc
 30:     ST  3,-1(1)	 
 31:     LD  3,-2(1)	
 32:   OUTC  3,3,3	 
 33:    LDC  2,0(6)	 
 34:     LD  3,-1(1)	 
 35:     LD  1,0(1)	 
 36:    LDA  7,0(3)	 
* END FUNCTION outputc
* FUNCTION outnl
 37:     ST  3,-1(1)	 
 38:  OUTNL  3,3,3	 
 39:     LD  3,-1(1)	 
 40:     LD  1,0(1)	 
 41:    LDA  7,0(3)	 
* END FUNCTION outnl
* FUNCTION main
 42:     ST  3,-1(1)	 
* COMPOUND
* EXPRESSION
*                       
 43:     ST  1,-2(1)	 
*                       
 44:    LDC  3,666(6)	 
 45:     ST  3,-4(1)	 
*                       
 46:    LDA  1,-2(1)	 
 47:    LDA  3,1(7)	 
 48:    LDA  7,-43(7)
 49:    LDA  3,0(2)	 
*                       
* EXPRESSION
*                       
 50:     ST  1,-2(1)	 
*                     
 51:    LDA  1,-2(1)	 
 52:    LDA  3,1(7)	 
 53:    LDA  7,-17(7)	
 54:    LDA  3,0(2)	 
*                       
* END COMPOUND
* Add standard closing in case there is no return statement
 55:    LDC  2,0(6)	 
 56:     LD  3,-1(1)	 
 57:     LD  1,0(1)	 
 58:    LDA  7,0(3)	
* END FUNCTION main
  0:    LDA  7,58(7)	 
* INIT
 59:     LD  0,0(0)	 
 60:    LDA  1,0(0)	
 61:     ST  1,0(1)	 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
 62:    LDA  3,1(7)	 
 63:    LDA  7,-22(7)	 
 64:   HALT  0,0,0	 
* END INIT
