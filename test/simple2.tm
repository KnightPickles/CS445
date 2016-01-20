* C- compiler version C-F15
* Built: Oct 14, 2015
* Author: Robert B. Heckendorn
* File compiled:  simple2.c-
* FUNCTION input
  1:     ST  3,-1(1)    Store return address 
  2:     IN  2,2,2      Grab int input 
  3:     LD  3,-1(1)    Load return address 
  4:     LD  1,0(1)     Adjust fp 
  5:    LDA  7,0(3)     Return 
* END FUNCTION input
* FUNCTION output
  6:     ST  3,-1(1)    Store return address 
  7:     LD  3,-2(1)    Load parameter 
  8:    OUT  3,3,3      Output integer 
  9:    LDC  2,0(6)     Set return to 0 
 10:     LD  3,-1(1)    Load return address 
 11:     LD  1,0(1)     Adjust fp 
 12:    LDA  7,0(3)     Return 
* END FUNCTION output
* FUNCTION inputb
 13:     ST  3,-1(1)    Store return address 
 14:    INB  2,2,2      Grab bool input 
 15:     LD  3,-1(1)    Load return address 
 16:     LD  1,0(1)     Adjust fp 
 17:    LDA  7,0(3)     Return 
* END FUNCTION inputb
* FUNCTION outputb
 18:     ST  3,-1(1)    Store return address 
 19:     LD  3,-2(1)    Load parameter 
 20:   OUTB  3,3,3      Output bool 
 21:    LDC  2,0(6)     Set return to 0 
 22:     LD  3,-1(1)    Load return address 
 23:     LD  1,0(1)     Adjust fp 
 24:    LDA  7,0(3)     Return 
* END FUNCTION outputb
* FUNCTION inputc
 25:     ST  3,-1(1)    Store return address 
 26:    INC  2,2,2      Grab char input 
 27:     LD  3,-1(1)    Load return address 
 28:     LD  1,0(1)     Adjust fp 
 29:    LDA  7,0(3)     Return 
* END FUNCTION inputc
* FUNCTION outputc
 30:     ST  3,-1(1)    Store return address 
 31:     LD  3,-2(1)    Load parameter 
 32:   OUTC  3,3,3      Output char 
 33:    LDC  2,0(6)     Set return to 0 
 34:     LD  3,-1(1)    Load return address 
 35:     LD  1,0(1)     Adjust fp 
 36:    LDA  7,0(3)     Return 
* END FUNCTION outputc
* FUNCTION outnl
 37:     ST  3,-1(1)    Store return address 
 38:  OUTNL  3,3,3      Output a newline 
 39:     LD  3,-1(1)    Load return address 
 40:     LD  1,0(1)     Adjust fp 
 41:    LDA  7,0(3)     Return 
* END FUNCTION outnl
* FUNCTION dog
 42:     ST  3,-1(1)    Store return address. 
* COMPOUND
* EXPRESSION
 43:     LD  3,-2(1)    Load variable cat
 44:     ST  3,-4(1)    Save left side 
 45:    LDC  3,1000(6)  Load constant 
 46:     LD  4,-4(1)    Load left into ac1 
 47:    MUL  3,4,3      Op * 
 48:     ST  3,-3(1)    Store variable tmp
* RETURN
 49:     LD  3,-3(1)    Load variable tmp
 50:    LDA  2,0(3)     Copy result to rt register 
 51:     LD  3,-1(1)    Load return address 
 52:     LD  1,0(1)     Adjust fp 
 53:    LDA  7,0(3)     Return 
* END COMPOUND
* Add standard closing in case there is no return statement
 54:    LDC  2,0(6)     Set return value to 0 
 55:     LD  3,-1(1)    Load return address 
 56:     LD  1,0(1)     Adjust fp 
 57:    LDA  7,0(3)     Return 
* END FUNCTION dog
* FUNCTION main
 58:     ST  3,-1(1)    Store return address. 
* COMPOUND
* EXPRESSION
 59:    LDC  3,666(6)   Load constant 
 60:     ST  3,-2(1)    Store variable x
* EXPRESSION
 61:    LDC  3,777(6)   Load constant 
 62:     ST  3,0(0)     Store variable g
* EXPRESSION
*                       Begin call to  dog
 63:     ST  1,-4(1)    Store old fp in ghost frame 
*                       Load param 1
 64:     LD  3,-2(1)    Load variable x
 65:     ST  3,-6(1)    Store parameter 
*                       Jump to dog
 66:    LDA  1,-4(1)    Load address of new frame 
 67:    LDA  3,1(7)     Return address in ac 
 68:    LDA  7,-27(7)   CALL dog
 69:    LDA  3,0(2)     Save the result in ac 
*                       End call to dog
 70:     ST  3,-3(1)    Store variable y
* EXPRESSION
*                       Begin call to  dog
 71:     ST  1,-4(1)    Store old fp in ghost frame 
*                       Load param 1
 72:     LD  3,0(0)     Load variable g
 73:     ST  3,-6(1)    Store parameter 
*                       Jump to dog
 74:    LDA  1,-4(1)    Load address of new frame 
 75:    LDA  3,1(7)     Return address in ac 
 76:    LDA  7,-35(7)   CALL dog
 77:    LDA  3,0(2)     Save the result in ac 
*                       End call to dog
 78:     ST  3,-3(1)    Store variable y
* EXPRESSION
*                       Begin call to  output
 79:     ST  1,-4(1)    Store old fp in ghost frame 
*                       Load param 1
 80:     LD  3,-3(1)    Load variable y
 81:     ST  3,-6(1)    Store parameter 
*                       Jump to output
 82:    LDA  1,-4(1)    Load address of new frame 
 83:    LDA  3,1(7)     Return address in ac 
 84:    LDA  7,-79(7)   CALL output
 85:    LDA  3,0(2)     Save the result in ac 
*                       End call to output
* EXPRESSION
*                       Begin call to  outnl
 86:     ST  1,-4(1)    Store old fp in ghost frame 
*                       Jump to outnl
 87:    LDA  1,-4(1)    Load address of new frame 
 88:    LDA  3,1(7)     Return address in ac 
 89:    LDA  7,-53(7)   CALL outnl
 90:    LDA  3,0(2)     Save the result in ac 
*                       End call to outnl
* END COMPOUND
* Add standard closing in case there is no return statement
 91:    LDC  2,0(6)     Set return value to 0 
 92:     LD  3,-1(1)    Load return address 
 93:     LD  1,0(1)     Adjust fp 
 94:    LDA  7,0(3)     Return 
* END FUNCTION main
  0:    LDA  7,94(7)    Jump to init [backpatch] 
* INIT
 95:     LD  0,0(0)     Set the global pointer 
* INIT GLOBALS AND STATICS
 96:    LDC  3,555(6)   Load constant 
 97:     ST  3,0(0)     Store variable g
* END INIT GLOBALS AND STATICS
 98:    LDA  1,-1(0)    set first frame at end of globals 
 99:     ST  1,0(1)     store old fp (point to self) 
100:    LDA  3,1(7)     Return address in ac 
101:    LDA  7,-44(7)   Jump to main 
102:   HALT  0,0,0      DONE! 
* END INIT
