* C- compiler version C-F20
* Built: Nov 19, 2020
* Author: Robert B. Heckendorn
* File compiled:  permlist.c-
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
* FUNCTION put
 39:     ST  3,-1(1)	Store return address 
* COMPOUND
* Compound Body
* EXPRESSION
 40:     LD  3,-2(1)	Load address of base of array p
 41:     ST  3,-5(1)	Push left side 
 42:    LDC  3,1(6)	Load integer constant 
 43:     LD  4,-5(1)	Pop left into ac1 
 44:    SUB  3,4,3	compute location from index 
 45:     LD  3,0(3)	Load array element 
 46:     ST  3,-4(1)	Store variable sum
* EXPRESSION
 47:    LDC  3,2(6)	Load integer constant 
 48:     ST  3,-3(1)	Store variable j
* WHILE
 49:     LD  3,-3(1)	Load variable j
 50:     ST  3,-5(1)	Push left side 
 51:     LD  3,0(0)	Load variable n
 52:     LD  4,-5(1)	Pop left into ac1 
 53:    TLE  3,4,3	Op <= 
 54:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* EXPRESSION
 56:     LD  3,-4(1)	Load variable sum
 57:     ST  3,-5(1)	Push left side 
 58:    LDC  3,10(6)	Load integer constant 
 59:     LD  4,-5(1)	Pop left into ac1 
 60:    MUL  3,4,3	Op * 
 61:     ST  3,-5(1)	Push left side 
 62:     LD  3,-2(1)	Load address of base of array p
 63:     ST  3,-6(1)	Push left side 
 64:     LD  3,-3(1)	Load variable j
 65:     LD  4,-6(1)	Pop left into ac1 
 66:    SUB  3,4,3	compute location from index 
 67:     LD  3,0(3)	Load array element 
 68:     LD  4,-5(1)	Pop left into ac1 
 69:    ADD  3,4,3	Op + 
 70:     ST  3,-4(1)	Store variable sum
* EXPRESSION
 71:     LD  3,-3(1)	Load variable j
 72:     ST  3,-5(1)	Push left side 
 73:    LDC  3,1(6)	Load integer constant 
 74:     LD  4,-5(1)	Pop left into ac1 
 75:    ADD  3,4,3	Op + 
 76:     ST  3,-3(1)	Store variable j
* END COMPOUND
 77:    JMP  7,-29(7)	go to beginning of loop 
 55:    JMP  7,22(7)	Jump past loop [backpatch] 
* END WHILE
* EXPRESSION
* CALL output
 78:     ST  1,-5(1)	Store fp in ghost frame for output
* Param 1
 79:     LD  3,-4(1)	Load variable sum
 80:     ST  3,-7(1)	Push parameter 
* Param end output
 81:    LDA  1,-5(1)	Load address of new frame 
 82:    LDA  3,1(7)	Return address in ac 
 83:    JMP  7,-68(7)	CALL output
 84:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL outnl
 85:     ST  1,-5(1)	Store fp in ghost frame for outnl
* Param end outnl
 86:    LDA  1,-5(1)	Load address of new frame 
 87:    LDA  3,1(7)	Return address in ac 
 88:    JMP  7,-55(7)	CALL outnl
 89:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* END COMPOUND
* Add standard closing in case there is no return statement
 90:    LDC  2,0(6)	Set return value to 0 
 91:     LD  3,-1(1)	Load return address 
 92:     LD  1,0(1)	Adjust fp 
 93:    JMP  7,0(3)	Return 
* END FUNCTION put
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION main
 94:     ST  3,-1(1)	Store return address 
* COMPOUND
 95:    LDC  3,20(6)	load size of array p
 96:     ST  3,-2(1)	save size of array p
* Compound Body
* EXPRESSION
* CALL input
 97:     ST  1,-25(1)	Store fp in ghost frame for input
* Param end input
 98:    LDA  1,-25(1)	Load address of new frame 
 99:    LDA  3,1(7)	Return address in ac 
100:    JMP  7,-100(7)	CALL input
101:    LDA  3,0(2)	Save the result in ac 
* Call end input
102:     ST  3,0(0)	Store variable n
* EXPRESSION
103:    LDC  3,0(6)	Load integer constant 
104:     ST  3,-24(1)	Store variable j
* WHILE
105:     LD  3,-24(1)	Load variable j
106:     ST  3,-25(1)	Push left side 
107:     LD  3,0(0)	Load variable n
108:     LD  4,-25(1)	Pop left into ac1 
109:    TLE  3,4,3	Op <= 
110:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* EXPRESSION
112:     LD  3,-24(1)	Load variable j
113:     ST  3,-25(1)	Push index 
114:     LD  3,-24(1)	Load variable j
115:     LD  4,-25(1)	Pop index 
116:    LDA  5,-3(1)	Load address of base of array p
117:    SUB  5,5,4	Compute offset of value 
118:     ST  3,0(5)	Store variable p
* EXPRESSION
119:     LD  3,-24(1)	Load variable j
120:     ST  3,-25(1)	Push left side 
121:    LDC  3,1(6)	Load integer constant 
122:     LD  4,-25(1)	Pop left into ac1 
123:    ADD  3,4,3	Op + 
124:     ST  3,-24(1)	Store variable j
* END COMPOUND
125:    JMP  7,-21(7)	go to beginning of loop 
111:    JMP  7,14(7)	Jump past loop [backpatch] 
* END WHILE
* EXPRESSION
126:    LDC  3,1(6)	Load integer constant 
127:     ST  3,-23(1)	Store variable i
* WHILE
128:     LD  3,-23(1)	Load variable i
129:     ST  3,-25(1)	Push left side 
130:    LDC  3,0(6)	Load integer constant 
131:     LD  4,-25(1)	Pop left into ac1 
132:    TGT  3,4,3	Op > 
133:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* EXPRESSION
* CALL put
135:     ST  1,-28(1)	Store fp in ghost frame for put
* Param 1
136:    LDA  3,-3(1)	Load address of base of array p
137:     ST  3,-30(1)	Push parameter 
* Param end put
138:    LDA  1,-28(1)	Load address of new frame 
139:    LDA  3,1(7)	Return address in ac 
140:    JMP  7,-102(7)	CALL put
141:    LDA  3,0(2)	Save the result in ac 
* Call end put
* EXPRESSION
142:     LD  3,0(0)	Load variable n
143:     ST  3,-28(1)	Push left side 
144:    LDC  3,1(6)	Load integer constant 
145:     LD  4,-28(1)	Pop left into ac1 
146:    SUB  3,4,3	Op - 
147:     ST  3,-23(1)	Store variable i
* WHILE
148:    LDA  3,-3(1)	Load address of base of array p
149:     ST  3,-28(1)	Push left side 
150:     LD  3,-23(1)	Load variable i
151:     LD  4,-28(1)	Pop left into ac1 
152:    SUB  3,4,3	compute location from index 
153:     LD  3,0(3)	Load array element 
154:     ST  3,-28(1)	Push left side 
155:    LDA  3,-3(1)	Load address of base of array p
156:     ST  3,-29(1)	Push left side 
157:     LD  3,-23(1)	Load variable i
158:     ST  3,-30(1)	Push left side 
159:    LDC  3,1(6)	Load integer constant 
160:     LD  4,-30(1)	Pop left into ac1 
161:    ADD  3,4,3	Op + 
162:     LD  4,-29(1)	Pop left into ac1 
163:    SUB  3,4,3	compute location from index 
164:     LD  3,0(3)	Load array element 
165:     LD  4,-28(1)	Pop left into ac1 
166:    TGT  3,4,3	Op > 
167:    JNZ  3,1(7)	Jump to while part 
* DO
* EXPRESSION
169:     LD  3,-23(1)	Load variable i
170:     ST  3,-28(1)	Push left side 
171:    LDC  3,1(6)	Load integer constant 
172:     LD  4,-28(1)	Pop left into ac1 
173:    SUB  3,4,3	Op - 
174:     ST  3,-23(1)	Store variable i
175:    JMP  7,-28(7)	go to beginning of loop 
168:    JMP  7,7(7)	Jump past loop [backpatch] 
* END WHILE
* EXPRESSION
176:     LD  3,0(0)	Load variable n
177:     ST  3,-24(1)	Store variable j
* WHILE
178:    LDA  3,-3(1)	Load address of base of array p
179:     ST  3,-28(1)	Push left side 
180:     LD  3,-23(1)	Load variable i
181:     LD  4,-28(1)	Pop left into ac1 
182:    SUB  3,4,3	compute location from index 
183:     LD  3,0(3)	Load array element 
184:     ST  3,-28(1)	Push left side 
185:    LDA  3,-3(1)	Load address of base of array p
186:     ST  3,-29(1)	Push left side 
187:     LD  3,-24(1)	Load variable j
188:     LD  4,-29(1)	Pop left into ac1 
189:    SUB  3,4,3	compute location from index 
190:     LD  3,0(3)	Load array element 
191:     LD  4,-28(1)	Pop left into ac1 
192:    TGT  3,4,3	Op > 
193:    JNZ  3,1(7)	Jump to while part 
* DO
* EXPRESSION
195:     LD  3,-24(1)	Load variable j
196:     ST  3,-28(1)	Push left side 
197:    LDC  3,1(6)	Load integer constant 
198:     LD  4,-28(1)	Pop left into ac1 
199:    SUB  3,4,3	Op - 
200:     ST  3,-24(1)	Store variable j
201:    JMP  7,-24(7)	go to beginning of loop 
194:    JMP  7,7(7)	Jump past loop [backpatch] 
* END WHILE
* EXPRESSION
202:    LDA  3,-3(1)	Load address of base of array p
203:     ST  3,-28(1)	Push left side 
204:     LD  3,-23(1)	Load variable i
205:     LD  4,-28(1)	Pop left into ac1 
206:    SUB  3,4,3	compute location from index 
207:     LD  3,0(3)	Load array element 
208:     ST  3,-27(1)	Store variable tmp
* EXPRESSION
209:     LD  3,-23(1)	Load variable i
210:     ST  3,-28(1)	Push index 
211:    LDA  3,-3(1)	Load address of base of array p
212:     ST  3,-29(1)	Push left side 
213:     LD  3,-24(1)	Load variable j
214:     LD  4,-29(1)	Pop left into ac1 
215:    SUB  3,4,3	compute location from index 
216:     LD  3,0(3)	Load array element 
217:     LD  4,-28(1)	Pop index 
218:    LDA  5,-3(1)	Load address of base of array p
219:    SUB  5,5,4	Compute offset of value 
220:     ST  3,0(5)	Store variable p
* EXPRESSION
221:     LD  3,-24(1)	Load variable j
222:     ST  3,-28(1)	Push index 
223:     LD  3,-27(1)	Load variable tmp
224:     LD  4,-28(1)	Pop index 
225:    LDA  5,-3(1)	Load address of base of array p
226:    SUB  5,5,4	Compute offset of value 
227:     ST  3,0(5)	Store variable p
* EXPRESSION
228:     LD  3,0(0)	Load variable n
229:     ST  3,-25(1)	Store variable r
* EXPRESSION
230:     LD  3,-23(1)	Load variable i
231:     ST  3,-28(1)	Push left side 
232:    LDC  3,1(6)	Load integer constant 
233:     LD  4,-28(1)	Pop left into ac1 
234:    ADD  3,4,3	Op + 
235:     ST  3,-26(1)	Store variable s
* WHILE
236:     LD  3,-25(1)	Load variable r
237:     ST  3,-28(1)	Push left side 
238:     LD  3,-26(1)	Load variable s
239:     LD  4,-28(1)	Pop left into ac1 
240:    TGT  3,4,3	Op > 
241:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* EXPRESSION
243:    LDA  3,-3(1)	Load address of base of array p
244:     ST  3,-28(1)	Push left side 
245:     LD  3,-25(1)	Load variable r
246:     LD  4,-28(1)	Pop left into ac1 
247:    SUB  3,4,3	compute location from index 
248:     LD  3,0(3)	Load array element 
249:     ST  3,-27(1)	Store variable tmp
* EXPRESSION
250:     LD  3,-25(1)	Load variable r
251:     ST  3,-28(1)	Push index 
252:    LDA  3,-3(1)	Load address of base of array p
253:     ST  3,-29(1)	Push left side 
254:     LD  3,-26(1)	Load variable s
255:     LD  4,-29(1)	Pop left into ac1 
256:    SUB  3,4,3	compute location from index 
257:     LD  3,0(3)	Load array element 
258:     LD  4,-28(1)	Pop index 
259:    LDA  5,-3(1)	Load address of base of array p
260:    SUB  5,5,4	Compute offset of value 
261:     ST  3,0(5)	Store variable p
* EXPRESSION
262:     LD  3,-26(1)	Load variable s
263:     ST  3,-28(1)	Push index 
264:     LD  3,-27(1)	Load variable tmp
265:     LD  4,-28(1)	Pop index 
266:    LDA  5,-3(1)	Load address of base of array p
267:    SUB  5,5,4	Compute offset of value 
268:     ST  3,0(5)	Store variable p
* EXPRESSION
269:     LD  3,-25(1)	Load variable r
270:     ST  3,-28(1)	Push left side 
271:    LDC  3,1(6)	Load integer constant 
272:     LD  4,-28(1)	Pop left into ac1 
273:    SUB  3,4,3	Op - 
274:     ST  3,-25(1)	Store variable r
* EXPRESSION
275:     LD  3,-26(1)	Load variable s
276:     ST  3,-28(1)	Push left side 
277:    LDC  3,1(6)	Load integer constant 
278:     LD  4,-28(1)	Pop left into ac1 
279:    ADD  3,4,3	Op + 
280:     ST  3,-26(1)	Store variable s
* END COMPOUND
281:    JMP  7,-46(7)	go to beginning of loop 
242:    JMP  7,39(7)	Jump past loop [backpatch] 
* END WHILE
* END COMPOUND
282:    JMP  7,-155(7)	go to beginning of loop 
134:    JMP  7,148(7)	Jump past loop [backpatch] 
* END WHILE
* END COMPOUND
* Add standard closing in case there is no return statement
283:    LDC  2,0(6)	Set return value to 0 
284:     LD  3,-1(1)	Load return address 
285:     LD  1,0(1)	Adjust fp 
286:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,286(7)	Jump to init [backpatch] 
* INIT
287:     LD  0,0(0)	Set the global pointer 
288:    LDA  1,-1(0)	set first frame at end of globals 
289:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
290:    LDA  3,1(7)	Return address in ac 
291:    JMP  7,-198(7)	Jump to main 
292:   HALT  0,0,0	DONE! 
* END INIT
