* C- compiler version C-F20
* Built: Nov 19, 2020
* Author: Robert B. Heckendorn
* File compiled:  init.c-
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
 40:    LDC  3,666(6)	Load integer constant 
 41:     ST  3,-2(1)	Store variable i
 42:    LDC  3,97(6)	Load char constant 
 43:     ST  3,-3(1)	Store variable y
 44:    LDC  3,1(6)	Load Boolean constant 
 45:     ST  3,-4(1)	Store variable ba
 46:    LDC  3,1(6)	Load Boolean constant 
 47:     ST  3,-37(1)	Push left side 
 48:    LDC  3,0(6)	Load Boolean constant 
 49:    LDC  4,1(6)	Load 1 
 50:    XOR  3,3,4	Op XOR to get logical not 
 51:     LD  4,-37(1)	Pop left into ac1 
 52:    AND  3,4,3	Op AND 
 53:     ST  3,-5(1)	Store variable bb
 54:    LDC  3,5(6)	Load integer constant 
 55:     ST  3,-37(1)	Push left side 
 56:    LDC  3,4(6)	Load integer constant 
 57:     LD  4,-37(1)	Pop left into ac1 
 58:    TGT  3,4,3	Op > 
 59:     ST  3,-6(1)	Store variable bc
 60:    LDC  3,10(6)	load size of array x
 61:     ST  3,-7(1)	save size of array x
 62:    LDC  3,4(6)	Load integer constant 
 63:     ST  3,-37(1)	Push left side 
 64:    LDC  3,5(6)	Load integer constant 
 65:     LD  4,-37(1)	Pop left into ac1 
 66:    MUL  3,4,3	Op * 
 67:     ST  3,-37(1)	Push left side 
 68:    LDC  3,3(6)	Load integer constant 
 69:     ST  3,-38(1)	Push left side 
 70:    LDC  3,2(6)	Load integer constant 
 71:     LD  4,-38(1)	Pop left into ac1 
 72:    MUL  3,4,3	Op * 
 73:     LD  4,-37(1)	Pop left into ac1 
 74:    ADD  3,4,3	Op + 
 75:     ST  3,-18(1)	Store variable k
 76:    LDC  3,46(6)	Load integer constant 
 77:    NEG  3,3,3	Op unary - 
 78:     ST  3,-19(1)	Store variable l
 79:    LDC  3,666(6)	Load integer constant 
 80:     ST  3,-20(1)	Store variable sia
 81:    LDC  3,15(6)	load size of array sib
 82:     ST  3,-21(1)	save size of array sib
* Compound Body
* EXPRESSION
* CALL output
 83:     ST  1,-37(1)	Store fp in ghost frame for output
* Param 1
 84:     LD  3,0(0)	Load variable ga
 85:     ST  3,-39(1)	Push parameter 
* Param end output
 86:    LDA  1,-37(1)	Load address of new frame 
 87:    LDA  3,1(7)	Return address in ac 
 88:    JMP  7,-73(7)	CALL output
 89:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL outnl
 90:     ST  1,-37(1)	Store fp in ghost frame for outnl
* Param end outnl
 91:    LDA  1,-37(1)	Load address of new frame 
 92:    LDA  3,1(7)	Return address in ac 
 93:    JMP  7,-60(7)	CALL outnl
 94:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* EXPRESSION
* CALL outputb
 95:     ST  1,-37(1)	Store fp in ghost frame for outputb
* Param 1
 96:     LD  3,-1(0)	Load variable gb
 97:     ST  3,-39(1)	Push parameter 
* Param end outputb
 98:    LDA  1,-37(1)	Load address of new frame 
 99:    LDA  3,1(7)	Return address in ac 
100:    JMP  7,-79(7)	CALL outputb
101:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outnl
102:     ST  1,-37(1)	Store fp in ghost frame for outnl
* Param end outnl
103:    LDA  1,-37(1)	Load address of new frame 
104:    LDA  3,1(7)	Return address in ac 
105:    JMP  7,-72(7)	CALL outnl
106:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* EXPRESSION
* CALL output
107:     ST  1,-37(1)	Store fp in ghost frame for output
* Param 1
108:    LDA  3,-3(0)	Load address of base of array gc
109:     LD  3,1(3)	Load array size 
110:     ST  3,-39(1)	Push parameter 
* Param end output
111:    LDA  1,-37(1)	Load address of new frame 
112:    LDA  3,1(7)	Return address in ac 
113:    JMP  7,-98(7)	CALL output
114:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL outnl
115:     ST  1,-37(1)	Store fp in ghost frame for outnl
* Param end outnl
116:    LDA  1,-37(1)	Load address of new frame 
117:    LDA  3,1(7)	Return address in ac 
118:    JMP  7,-85(7)	CALL outnl
119:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* EXPRESSION
* CALL output
120:     ST  1,-37(1)	Store fp in ghost frame for output
* Param 1
121:     LD  3,-2(1)	Load variable i
122:     ST  3,-39(1)	Push parameter 
* Param end output
123:    LDA  1,-37(1)	Load address of new frame 
124:    LDA  3,1(7)	Return address in ac 
125:    JMP  7,-110(7)	CALL output
126:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL outnl
127:     ST  1,-37(1)	Store fp in ghost frame for outnl
* Param end outnl
128:    LDA  1,-37(1)	Load address of new frame 
129:    LDA  3,1(7)	Return address in ac 
130:    JMP  7,-97(7)	CALL outnl
131:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* EXPRESSION
* CALL outputc
132:     ST  1,-37(1)	Store fp in ghost frame for outputc
* Param 1
133:     LD  3,-3(1)	Load variable y
134:     ST  3,-39(1)	Push parameter 
* Param end outputc
135:    LDA  1,-37(1)	Load address of new frame 
136:    LDA  3,1(7)	Return address in ac 
137:    JMP  7,-110(7)	CALL outputc
138:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* EXPRESSION
* CALL outnl
139:     ST  1,-37(1)	Store fp in ghost frame for outnl
* Param end outnl
140:    LDA  1,-37(1)	Load address of new frame 
141:    LDA  3,1(7)	Return address in ac 
142:    JMP  7,-109(7)	CALL outnl
143:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* EXPRESSION
* CALL outputb
144:     ST  1,-37(1)	Store fp in ghost frame for outputb
* Param 1
145:     LD  3,-4(1)	Load variable ba
146:     ST  3,-39(1)	Push parameter 
* Param end outputb
147:    LDA  1,-37(1)	Load address of new frame 
148:    LDA  3,1(7)	Return address in ac 
149:    JMP  7,-128(7)	CALL outputb
150:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outnl
151:     ST  1,-37(1)	Store fp in ghost frame for outnl
* Param end outnl
152:    LDA  1,-37(1)	Load address of new frame 
153:    LDA  3,1(7)	Return address in ac 
154:    JMP  7,-121(7)	CALL outnl
155:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* EXPRESSION
* CALL outputb
156:     ST  1,-37(1)	Store fp in ghost frame for outputb
* Param 1
157:     LD  3,-5(1)	Load variable bb
158:     ST  3,-39(1)	Push parameter 
* Param end outputb
159:    LDA  1,-37(1)	Load address of new frame 
160:    LDA  3,1(7)	Return address in ac 
161:    JMP  7,-140(7)	CALL outputb
162:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outnl
163:     ST  1,-37(1)	Store fp in ghost frame for outnl
* Param end outnl
164:    LDA  1,-37(1)	Load address of new frame 
165:    LDA  3,1(7)	Return address in ac 
166:    JMP  7,-133(7)	CALL outnl
167:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* EXPRESSION
* CALL outputb
168:     ST  1,-37(1)	Store fp in ghost frame for outputb
* Param 1
169:     LD  3,-6(1)	Load variable bc
170:     ST  3,-39(1)	Push parameter 
* Param end outputb
171:    LDA  1,-37(1)	Load address of new frame 
172:    LDA  3,1(7)	Return address in ac 
173:    JMP  7,-152(7)	CALL outputb
174:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outnl
175:     ST  1,-37(1)	Store fp in ghost frame for outnl
* Param end outnl
176:    LDA  1,-37(1)	Load address of new frame 
177:    LDA  3,1(7)	Return address in ac 
178:    JMP  7,-145(7)	CALL outnl
179:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* EXPRESSION
* CALL output
180:     ST  1,-37(1)	Store fp in ghost frame for output
* Param 1
181:    LDA  3,-8(1)	Load address of base of array x
182:     LD  3,1(3)	Load array size 
183:     ST  3,-39(1)	Push parameter 
* Param end output
184:    LDA  1,-37(1)	Load address of new frame 
185:    LDA  3,1(7)	Return address in ac 
186:    JMP  7,-171(7)	CALL output
187:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL outnl
188:     ST  1,-37(1)	Store fp in ghost frame for outnl
* Param end outnl
189:    LDA  1,-37(1)	Load address of new frame 
190:    LDA  3,1(7)	Return address in ac 
191:    JMP  7,-158(7)	CALL outnl
192:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* EXPRESSION
* CALL output
193:     ST  1,-37(1)	Store fp in ghost frame for output
* Param 1
194:     LD  3,-18(1)	Load variable k
195:     ST  3,-39(1)	Push parameter 
* Param end output
196:    LDA  1,-37(1)	Load address of new frame 
197:    LDA  3,1(7)	Return address in ac 
198:    JMP  7,-183(7)	CALL output
199:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL outnl
200:     ST  1,-37(1)	Store fp in ghost frame for outnl
* Param end outnl
201:    LDA  1,-37(1)	Load address of new frame 
202:    LDA  3,1(7)	Return address in ac 
203:    JMP  7,-170(7)	CALL outnl
204:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* EXPRESSION
* CALL output
205:     ST  1,-37(1)	Store fp in ghost frame for output
* Param 1
206:     LD  3,-19(1)	Load variable l
207:     ST  3,-39(1)	Push parameter 
* Param end output
208:    LDA  1,-37(1)	Load address of new frame 
209:    LDA  3,1(7)	Return address in ac 
210:    JMP  7,-195(7)	CALL output
211:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL outnl
212:     ST  1,-37(1)	Store fp in ghost frame for outnl
* Param end outnl
213:    LDA  1,-37(1)	Load address of new frame 
214:    LDA  3,1(7)	Return address in ac 
215:    JMP  7,-182(7)	CALL outnl
216:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* EXPRESSION
* CALL output
217:     ST  1,-37(1)	Store fp in ghost frame for output
* Param 1
218:     LD  3,-20(1)	Load variable sia
219:     ST  3,-39(1)	Push parameter 
* Param end output
220:    LDA  1,-37(1)	Load address of new frame 
221:    LDA  3,1(7)	Return address in ac 
222:    JMP  7,-207(7)	CALL output
223:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL outnl
224:     ST  1,-37(1)	Store fp in ghost frame for outnl
* Param end outnl
225:    LDA  1,-37(1)	Load address of new frame 
226:    LDA  3,1(7)	Return address in ac 
227:    JMP  7,-194(7)	CALL outnl
228:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* EXPRESSION
* CALL output
229:     ST  1,-37(1)	Store fp in ghost frame for output
* Param 1
230:    LDA  3,-22(1)	Load address of base of array sib
231:     LD  3,1(3)	Load array size 
232:     ST  3,-39(1)	Push parameter 
* Param end output
233:    LDA  1,-37(1)	Load address of new frame 
234:    LDA  3,1(7)	Return address in ac 
235:    JMP  7,-220(7)	CALL output
236:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL outnl
237:     ST  1,-37(1)	Store fp in ghost frame for outnl
* Param end outnl
238:    LDA  1,-37(1)	Load address of new frame 
239:    LDA  3,1(7)	Return address in ac 
240:    JMP  7,-207(7)	CALL outnl
241:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* COMPOUND
242:    LDC  3,20(6)	load size of array y
243:     ST  3,-37(1)	save size of array y
244:    LDC  3,1(6)	Load Boolean constant 
245:    LDC  4,1(6)	Load 1 
246:    XOR  3,3,4	Op XOR to get logical not 
247:     ST  3,-58(1)	Store variable t
* Compound Body
* EXPRESSION
* CALL output
248:     ST  1,-59(1)	Store fp in ghost frame for output
* Param 1
249:    LDA  3,-38(1)	Load address of base of array y
250:     LD  3,1(3)	Load array size 
251:     ST  3,-61(1)	Push parameter 
* Param end output
252:    LDA  1,-59(1)	Load address of new frame 
253:    LDA  3,1(7)	Return address in ac 
254:    JMP  7,-239(7)	CALL output
255:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL outnl
256:     ST  1,-59(1)	Store fp in ghost frame for outnl
* Param end outnl
257:    LDA  1,-59(1)	Load address of new frame 
258:    LDA  3,1(7)	Return address in ac 
259:    JMP  7,-226(7)	CALL outnl
260:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* EXPRESSION
* CALL outputb
261:     ST  1,-59(1)	Store fp in ghost frame for outputb
* Param 1
262:     LD  3,-58(1)	Load variable t
263:     ST  3,-61(1)	Push parameter 
* Param end outputb
264:    LDA  1,-59(1)	Load address of new frame 
265:    LDA  3,1(7)	Return address in ac 
266:    JMP  7,-245(7)	CALL outputb
267:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outnl
268:     ST  1,-59(1)	Store fp in ghost frame for outnl
* Param end outnl
269:    LDA  1,-59(1)	Load address of new frame 
270:    LDA  3,1(7)	Return address in ac 
271:    JMP  7,-238(7)	CALL outnl
272:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* END COMPOUND
* END COMPOUND
* Add standard closing in case there is no return statement
273:    LDC  2,0(6)	Set return value to 0 
274:     LD  3,-1(1)	Load return address 
275:     LD  1,0(1)	Adjust fp 
276:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,276(7)	Jump to init [backpatch] 
* INIT
277:     LD  0,0(0)	Set the global pointer 
278:    LDA  1,-16(0)	set first frame at end of globals 
279:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
280:    LDC  3,111(6)	Load integer constant 
281:     ST  3,0(0)	Store variable ga
282:    LDC  3,1(6)	Load Boolean constant 
283:     ST  3,-1(0)	Store variable gb
284:    LDC  3,13(6)	load size of array gc
285:     ST  3,-2(0)	save size of array gc
* END INIT GLOBALS AND STATICS
286:    LDA  3,1(7)	Return address in ac 
287:    JMP  7,-249(7)	Jump to main 
288:   HALT  0,0,0	DONE! 
* END INIT
