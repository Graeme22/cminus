* C- compiler version C-F20
* Built: Nov 19, 2020
* Author: Robert B. Heckendorn
* File compiled:  sort.c-
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
* FUNCTION minloc
 39:     ST  3,-1(1)	Store return address 
* COMPOUND
* Compound Body
* EXPRESSION
 40:     LD  3,-3(1)	Load variable low
 41:     ST  3,-7(1)	Store variable k
* EXPRESSION
 42:     LD  3,-2(1)	Load address of base of array a
 43:     ST  3,-8(1)	Push left side 
 44:     LD  3,-3(1)	Load variable low
 45:     LD  4,-8(1)	Pop left into ac1 
 46:    SUB  3,4,3	compute location from index 
 47:     LD  3,0(3)	Load array element 
 48:     ST  3,-6(1)	Store variable x
* EXPRESSION
 49:     LD  3,-3(1)	Load variable low
 50:     ST  3,-8(1)	Push left side 
 51:    LDC  3,1(6)	Load integer constant 
 52:     LD  4,-8(1)	Pop left into ac1 
 53:    ADD  3,4,3	Op + 
 54:     ST  3,-5(1)	Store variable i
* WHILE
 55:     LD  3,-5(1)	Load variable i
 56:     ST  3,-8(1)	Push left side 
 57:     LD  3,-4(1)	Load variable high
 58:     LD  4,-8(1)	Pop left into ac1 
 59:    TLT  3,4,3	Op < 
 60:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* IF
 62:     LD  3,-2(1)	Load address of base of array a
 63:     ST  3,-8(1)	Push left side 
 64:     LD  3,-5(1)	Load variable i
 65:     LD  4,-8(1)	Pop left into ac1 
 66:    SUB  3,4,3	compute location from index 
 67:     LD  3,0(3)	Load array element 
 68:     ST  3,-8(1)	Push left side 
 69:     LD  3,-6(1)	Load variable x
 70:     LD  4,-8(1)	Pop left into ac1 
 71:    TLT  3,4,3	Op < 
* THEN
* COMPOUND
* Compound Body
* EXPRESSION
 73:     LD  3,-2(1)	Load address of base of array a
 74:     ST  3,-8(1)	Push left side 
 75:     LD  3,-5(1)	Load variable i
 76:     LD  4,-8(1)	Pop left into ac1 
 77:    SUB  3,4,3	compute location from index 
 78:     LD  3,0(3)	Load array element 
 79:     ST  3,-6(1)	Store variable x
* EXPRESSION
 80:     LD  3,-5(1)	Load variable i
 81:     ST  3,-7(1)	Store variable k
* END COMPOUND
 72:    JZR  3,9(7)	Jump around the THEN if false [backpatch] 
* END IF
* EXPRESSION
 82:     LD  3,-5(1)	load lhs variable i
 83:    LDA  3,1(3)	increment value of i
 84:     ST  3,-5(1)	Store variable i
* END COMPOUND
 85:    JMP  7,-31(7)	go to beginning of loop 
 61:    JMP  7,24(7)	Jump past loop [backpatch] 
* END WHILE
* RETURN
 86:     LD  3,-7(1)	Load variable k
 87:    LDA  2,0(3)	Copy result to return register 
 88:     LD  3,-1(1)	Load return address 
 89:     LD  1,0(1)	Adjust fp 
 90:    JMP  7,0(3)	Return 
* END COMPOUND
* Add standard closing in case there is no return statement
 91:    LDC  2,0(6)	Set return value to 0 
 92:     LD  3,-1(1)	Load return address 
 93:     LD  1,0(1)	Adjust fp 
 94:    JMP  7,0(3)	Return 
* END FUNCTION minloc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION sort
 95:     ST  3,-1(1)	Store return address 
* COMPOUND
* Compound Body
* EXPRESSION
 96:     LD  3,-3(1)	Load variable low
 97:     ST  3,-5(1)	Store variable i
* WHILE
 98:     LD  3,-5(1)	Load variable i
 99:     ST  3,-7(1)	Push left side 
100:     LD  3,-4(1)	Load variable high
101:     ST  3,-8(1)	Push left side 
102:    LDC  3,1(6)	Load integer constant 
103:     LD  4,-8(1)	Pop left into ac1 
104:    SUB  3,4,3	Op - 
105:     LD  4,-7(1)	Pop left into ac1 
106:    TLT  3,4,3	Op < 
107:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* EXPRESSION
* CALL minloc
109:     ST  1,-8(1)	Store fp in ghost frame for minloc
* Param 1
110:     LD  3,-2(1)	Load address of base of array a
111:     ST  3,-10(1)	Push parameter 
* Param 2
112:     LD  3,-5(1)	Load variable i
113:     ST  3,-11(1)	Push parameter 
* Param 3
114:     LD  3,-4(1)	Load variable high
115:     ST  3,-12(1)	Push parameter 
* Param end minloc
116:    LDA  1,-8(1)	Load address of new frame 
117:    LDA  3,1(7)	Return address in ac 
118:    JMP  7,-80(7)	CALL minloc
119:    LDA  3,0(2)	Save the result in ac 
* Call end minloc
120:     ST  3,-6(1)	Store variable k
* EXPRESSION
121:     LD  3,-2(1)	Load address of base of array a
122:     ST  3,-8(1)	Push left side 
123:     LD  3,-6(1)	Load variable k
124:     LD  4,-8(1)	Pop left into ac1 
125:    SUB  3,4,3	compute location from index 
126:     LD  3,0(3)	Load array element 
127:     ST  3,-7(1)	Store variable t
* EXPRESSION
128:     LD  3,-6(1)	Load variable k
129:     ST  3,-8(1)	Push index 
130:     LD  3,-2(1)	Load address of base of array a
131:     ST  3,-9(1)	Push left side 
132:     LD  3,-5(1)	Load variable i
133:     LD  4,-9(1)	Pop left into ac1 
134:    SUB  3,4,3	compute location from index 
135:     LD  3,0(3)	Load array element 
136:     LD  4,-8(1)	Pop index 
137:     LD  5,-2(1)	Load address of base of array a
138:    SUB  5,5,4	Compute offset of value 
139:     ST  3,0(5)	Store variable a
* EXPRESSION
140:     LD  3,-5(1)	Load variable i
141:     ST  3,-8(1)	Push index 
142:     LD  3,-7(1)	Load variable t
143:     LD  4,-8(1)	Pop index 
144:     LD  5,-2(1)	Load address of base of array a
145:    SUB  5,5,4	Compute offset of value 
146:     ST  3,0(5)	Store variable a
* EXPRESSION
147:     LD  3,-5(1)	load lhs variable i
148:    LDA  3,1(3)	increment value of i
149:     ST  3,-5(1)	Store variable i
* END COMPOUND
150:    JMP  7,-53(7)	go to beginning of loop 
108:    JMP  7,42(7)	Jump past loop [backpatch] 
* END WHILE
* END COMPOUND
* Add standard closing in case there is no return statement
151:    LDC  2,0(6)	Set return value to 0 
152:     LD  3,-1(1)	Load return address 
153:     LD  1,0(1)	Adjust fp 
154:    JMP  7,0(3)	Return 
* END FUNCTION sort
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION main
155:     ST  3,-1(1)	Store return address 
* COMPOUND
* Compound Body
* EXPRESSION
156:    LDC  3,0(6)	Load integer constant 
157:     ST  3,-2(1)	Store variable i
* WHILE
158:     LD  3,-2(1)	Load variable i
159:     ST  3,-3(1)	Push left side 
160:    LDC  3,10(6)	Load integer constant 
161:     LD  4,-3(1)	Pop left into ac1 
162:    TLT  3,4,3	Op < 
163:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* EXPRESSION
165:     LD  3,-2(1)	Load variable i
166:     ST  3,-3(1)	Push index 
* CALL input
167:     ST  1,-4(1)	Store fp in ghost frame for input
* Param end input
168:    LDA  1,-4(1)	Load address of new frame 
169:    LDA  3,1(7)	Return address in ac 
170:    JMP  7,-170(7)	CALL input
171:    LDA  3,0(2)	Save the result in ac 
* Call end input
172:     LD  4,-3(1)	Pop index 
173:    LDA  5,-1(0)	Load address of base of array x
174:    SUB  5,5,4	Compute offset of value 
175:     ST  3,0(5)	Store variable x
* EXPRESSION
176:     LD  3,-2(1)	load lhs variable i
177:    LDA  3,1(3)	increment value of i
178:     ST  3,-2(1)	Store variable i
* END COMPOUND
179:    JMP  7,-22(7)	go to beginning of loop 
164:    JMP  7,15(7)	Jump past loop [backpatch] 
* END WHILE
* EXPRESSION
* CALL sort
180:     ST  1,-3(1)	Store fp in ghost frame for sort
* Param 1
181:    LDA  3,-1(0)	Load address of base of array x
182:     ST  3,-5(1)	Push parameter 
* Param 2
183:    LDC  3,0(6)	Load integer constant 
184:     ST  3,-6(1)	Push parameter 
* Param 3
185:    LDC  3,10(6)	Load integer constant 
186:     ST  3,-7(1)	Push parameter 
* Param end sort
187:    LDA  1,-3(1)	Load address of new frame 
188:    LDA  3,1(7)	Return address in ac 
189:    JMP  7,-95(7)	CALL sort
190:    LDA  3,0(2)	Save the result in ac 
* Call end sort
* EXPRESSION
191:    LDC  3,0(6)	Load integer constant 
192:     ST  3,-2(1)	Store variable i
* WHILE
193:     LD  3,-2(1)	Load variable i
194:     ST  3,-3(1)	Push left side 
195:    LDC  3,10(6)	Load integer constant 
196:     LD  4,-3(1)	Pop left into ac1 
197:    TLT  3,4,3	Op < 
198:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* EXPRESSION
* CALL output
200:     ST  1,-3(1)	Store fp in ghost frame for output
* Param 1
201:    LDA  3,-1(0)	Load address of base of array x
202:     ST  3,-5(1)	Push left side 
203:     LD  3,-2(1)	Load variable i
204:     LD  4,-5(1)	Pop left into ac1 
205:    SUB  3,4,3	compute location from index 
206:     LD  3,0(3)	Load array element 
207:     ST  3,-5(1)	Push parameter 
* Param end output
208:    LDA  1,-3(1)	Load address of new frame 
209:    LDA  3,1(7)	Return address in ac 
210:    JMP  7,-195(7)	CALL output
211:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
212:     LD  3,-2(1)	load lhs variable i
213:    LDA  3,1(3)	increment value of i
214:     ST  3,-2(1)	Store variable i
* END COMPOUND
215:    JMP  7,-23(7)	go to beginning of loop 
199:    JMP  7,16(7)	Jump past loop [backpatch] 
* END WHILE
* END COMPOUND
* Add standard closing in case there is no return statement
216:    LDC  2,0(6)	Set return value to 0 
217:     LD  3,-1(1)	Load return address 
218:     LD  1,0(1)	Adjust fp 
219:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,219(7)	Jump to init [backpatch] 
* INIT
220:     LD  0,0(0)	Set the global pointer 
221:    LDA  1,-11(0)	set first frame at end of globals 
222:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
223:    LDC  3,10(6)	load size of array x
224:     ST  3,0(0)	save size of array x
* END INIT GLOBALS AND STATICS
225:    LDA  3,1(7)	Return address in ac 
226:    JMP  7,-72(7)	Jump to main 
227:   HALT  0,0,0	DONE! 
* END INIT
