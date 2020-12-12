* C- compiler version C-F20
* Built: Nov 19, 2020
* Author: Robert B. Heckendorn
* File compiled:  i0c.c-
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION input
  1:     ST  3,-1(1)	Store return address 
  2:     IN  2,2,2	Grab int input 
  3:     LD  3,-1(1)	Load return address 
  4:     LD  1,0(1)	Adjust fp 
  5:    JMP  7,0(3)	Return 
* END FUNCTION input
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputb
  6:     ST  3,-1(1)	Store return address 
  7:    INB  2,2,2	Grab bool input 
  8:     LD  3,-1(1)	Load return address 
  9:     LD  1,0(1)	Adjust fp 
 10:    JMP  7,0(3)	Return 
* END FUNCTION inputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputc
 11:     ST  3,-1(1)	Store return address 
 12:    INC  2,2,2	Grab char input 
 13:     LD  3,-1(1)	Load return address 
 14:     LD  1,0(1)	Adjust fp 
 15:    JMP  7,0(3)	Return 
* END FUNCTION inputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION output
 16:     ST  3,-1(1)	Store return address 
 17:     LD  3,-2(1)	Load parameter 
 18:    OUT  3,3,3	Output integer 
 19:     LD  3,-1(1)	Load return address 
 20:     LD  1,0(1)	Adjust fp 
 21:    JMP  7,0(3)	Return 
* END FUNCTION output
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputb
 22:     ST  3,-1(1)	Store return address 
 23:     LD  3,-2(1)	Load parameter 
 24:   OUTB  3,3,3	Output bool 
 25:     LD  3,-1(1)	Load return address 
 26:     LD  1,0(1)	Adjust fp 
 27:    JMP  7,0(3)	Return 
* END FUNCTION outputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputc
 28:     ST  3,-1(1)	Store return address 
 29:     LD  3,-2(1)	Load parameter 
 30:   OUTC  3,3,3	Output char 
 31:     LD  3,-1(1)	Load return address 
 32:     LD  1,0(1)	Adjust fp 
 33:    JMP  7,0(3)	Return 
* END FUNCTION outputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outnl
 34:     ST  3,-1(1)	Store return address 
 35:  OUTNL  3,3,3	Output a newline 
 36:     LD  3,-1(1)	Load return address 
 37:     LD  1,0(1)	Adjust fp 
 38:    JMP  7,0(3)	Return 
* END FUNCTION outnl
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION main
 39:     ST  3,-1(1)	Store return address 
* COMPOUND
* Compound Body
* COMPOUND
 40:    LDC  3,1(6)	Load Boolean constant 
 41:    LDC  4,1(6)	Load 1 
 42:    XOR  3,3,4	Op XOR to get logical not 
 43:     ST  3,-2(1)	Store variable ss
* Compound Body
* EXPRESSION
* CALL outputb
 44:     ST  1,-3(1)	Store fp in ghost frame for outputb
* Param 1
 45:     LD  3,-2(1)	Load variable ss
 46:     ST  3,-5(1)	Push parameter 
* Param end outputb
 47:    LDA  1,-3(1)	Load address of new frame 
 48:    LDA  3,1(7)	Return address in ac 
 49:    JMP  7,-28(7)	CALL outputb
 50:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* END COMPOUND
* END COMPOUND
* Add standard closing in case there is no return statement
 51:    LDC  2,0(6)	Set return value to 0 
 52:     LD  3,-1(1)	Load return address 
 53:     LD  1,0(1)	Adjust fp 
 54:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,54(7)	Jump to init [backpatch] 
* INIT
 55:     LD  0,0(0)	Set the global pointer 
 56:    LDA  1,0(0)	set first frame at end of globals 
 57:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
 58:    LDA  3,1(7)	Return address in ac 
 59:    JMP  7,-21(7)	Jump to main 
 60:   HALT  0,0,0	DONE! 
* END INIT
