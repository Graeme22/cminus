* C- compiler version C-F20
* Built: Nov 19, 2020
* Author: Robert B. Heckendorn
* File compiled:  overlayTmp3.c-
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
* FUNCTION dog
 39:     ST  3,-1(1)	Store return address 
* RETURN
 40:     LD  3,-2(1)	Load variable pig
 41:    LDA  2,0(3)	Copy result to return register 
 42:     LD  3,-1(1)	Load return address 
 43:     LD  1,0(1)	Adjust fp 
 44:    JMP  7,0(3)	Return 
* Add standard closing in case there is no return statement
 45:    LDC  2,0(6)	Set return value to 0 
 46:     LD  3,-1(1)	Load return address 
 47:     LD  1,0(1)	Adjust fp 
 48:    JMP  7,0(3)	Return 
* END FUNCTION dog
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION main
 49:     ST  3,-1(1)	Store return address 
* IF
 50:    LDC  3,1(6)	Load Boolean constant 
* THEN
* COMPOUND
* Compound Body
* EXPRESSION
 52:    LDC  3,111(6)	Load integer constant 
 53:     ST  3,-3(1)	Store variable z
* COMPOUND
* Compound Body
* EXPRESSION
 54:    LDC  3,222(6)	Load integer constant 
 55:     ST  3,-4(1)	Store variable x
* EXPRESSION
 56:    LDC  3,666(6)	Load integer constant 
 57:     ST  3,-5(1)	Push left side 
* CALL dog
 58:     ST  1,-6(1)	Store fp in ghost frame for dog
* Param 1
 59:     LD  3,-4(1)	Load variable x
 60:     ST  3,-8(1)	Push parameter 
* Param end dog
 61:    LDA  1,-6(1)	Load address of new frame 
 62:    LDA  3,1(7)	Return address in ac 
 63:    JMP  7,-25(7)	CALL dog
 64:    LDA  3,0(2)	Save the result in ac 
* Call end dog
 65:     LD  4,-5(1)	Pop left into ac1 
 66:    ADD  3,4,3	Op + 
 67:     ST  3,-4(1)	Store variable x
* EXPRESSION
* CALL output
 68:     ST  1,-5(1)	Store fp in ghost frame for output
* Param 1
 69:     LD  3,-4(1)	Load variable x
 70:     ST  3,-7(1)	Push parameter 
* Param end output
 71:    LDA  1,-5(1)	Load address of new frame 
 72:    LDA  3,1(7)	Return address in ac 
 73:    JMP  7,-58(7)	CALL output
 74:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL outnl
 75:     ST  1,-5(1)	Store fp in ghost frame for outnl
* Param end outnl
 76:    LDA  1,-5(1)	Load address of new frame 
 77:    LDA  3,1(7)	Return address in ac 
 78:    JMP  7,-45(7)	CALL outnl
 79:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* END COMPOUND
* COMPOUND
* Compound Body
* EXPRESSION
 80:    LDC  3,333(6)	Load integer constant 
 81:     ST  3,-4(1)	Store variable y
* EXPRESSION
 82:    LDC  3,666(6)	Load integer constant 
 83:     ST  3,-5(1)	Push left side 
* CALL dog
 84:     ST  1,-6(1)	Store fp in ghost frame for dog
* Param 1
 85:     LD  3,-4(1)	Load variable y
 86:     ST  3,-8(1)	Push parameter 
* Param end dog
 87:    LDA  1,-6(1)	Load address of new frame 
 88:    LDA  3,1(7)	Return address in ac 
 89:    JMP  7,-51(7)	CALL dog
 90:    LDA  3,0(2)	Save the result in ac 
* Call end dog
 91:     LD  4,-5(1)	Pop left into ac1 
 92:    ADD  3,4,3	Op + 
 93:     ST  3,-4(1)	Store variable y
* EXPRESSION
* CALL output
 94:     ST  1,-5(1)	Store fp in ghost frame for output
* Param 1
 95:     LD  3,-4(1)	Load variable y
 96:     ST  3,-7(1)	Push parameter 
* Param end output
 97:    LDA  1,-5(1)	Load address of new frame 
 98:    LDA  3,1(7)	Return address in ac 
 99:    JMP  7,-84(7)	CALL output
100:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL outnl
101:     ST  1,-5(1)	Store fp in ghost frame for outnl
* Param end outnl
102:    LDA  1,-5(1)	Load address of new frame 
103:    LDA  3,1(7)	Return address in ac 
104:    JMP  7,-71(7)	CALL outnl
105:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* END COMPOUND
* EXPRESSION
106:    LDC  3,666(6)	Load integer constant 
107:     ST  3,-4(1)	Push left side 
* CALL dog
108:     ST  1,-5(1)	Store fp in ghost frame for dog
* Param 1
109:     LD  3,-3(1)	Load variable z
110:     ST  3,-7(1)	Push parameter 
* Param end dog
111:    LDA  1,-5(1)	Load address of new frame 
112:    LDA  3,1(7)	Return address in ac 
113:    JMP  7,-75(7)	CALL dog
114:    LDA  3,0(2)	Save the result in ac 
* Call end dog
115:     LD  4,-4(1)	Pop left into ac1 
116:    ADD  3,4,3	Op + 
117:     ST  3,-3(1)	Store variable z
* EXPRESSION
* CALL output
118:     ST  1,-4(1)	Store fp in ghost frame for output
* Param 1
119:     LD  3,-3(1)	Load variable z
120:     ST  3,-6(1)	Push parameter 
* Param end output
121:    LDA  1,-4(1)	Load address of new frame 
122:    LDA  3,1(7)	Return address in ac 
123:    JMP  7,-108(7)	CALL output
124:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL outnl
125:     ST  1,-4(1)	Store fp in ghost frame for outnl
* Param end outnl
126:    LDA  1,-4(1)	Load address of new frame 
127:    LDA  3,1(7)	Return address in ac 
128:    JMP  7,-95(7)	CALL outnl
129:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* END COMPOUND
 51:    JZR  3,78(7)	Jump around the THEN if false [backpatch] 
* END IF
* Add standard closing in case there is no return statement
130:    LDC  2,0(6)	Set return value to 0 
131:     LD  3,-1(1)	Load return address 
132:     LD  1,0(1)	Adjust fp 
133:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,133(7)	Jump to init [backpatch] 
* INIT
134:     LD  0,0(0)	Set the global pointer 
135:    LDA  1,0(0)	set first frame at end of globals 
136:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
137:    LDA  3,1(7)	Return address in ac 
138:    JMP  7,-90(7)	Jump to main 
139:   HALT  0,0,0	DONE! 
* END INIT
