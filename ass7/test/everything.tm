* C- compiler version C-F20
* Built: Nov 19, 2020
* Author: Robert B. Heckendorn
* File compiled:  everything.c-
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
* FUNCTION wallace
 39:     ST  3,-1(1)	Store return address 
* COMPOUND
* Compound Body
* EXPRESSION
 40:     LD  3,-4(1)	Load variable close
* EXPRESSION
 41:     LD  3,-5(1)	Load variable shave
 42:     ST  3,-4(1)	Store variable close
* EXPRESSION
 43:     LD  3,-3(1)	Load variable trousers
 44:     ST  3,-6(1)	Push left side 
 45:    LDC  3,666(6)	Load integer constant 
 46:     ST  3,-7(1)	Push left side 
 47:     LD  3,-2(1)	Load variable wrong
 48:     LD  4,-7(1)	Pop left into ac1 
 49:    DIV  3,4,3	Op / 
 50:     LD  4,-6(1)	Pop left into ac1 
 51:    MOD  3,4,3	Op % 
 52:     ST  3,-2(1)	Store variable wrong
* EXPRESSION
 53:     LD  3,-2(1)	Load variable wrong
 54:     ST  3,-6(1)	Push left side 
 55:     LD  3,-3(1)	Load variable trousers
 56:     LD  4,-6(1)	Pop left into ac1 
 57:    MUL  3,4,3	Op * 
 58:     ST  3,-6(1)	Push left side 
 59:     LD  3,0(0)	Load variable gromit
 60:     LD  4,-6(1)	Pop left into ac1 
 61:    SUB  3,4,3	Op - 
 62:     ST  3,-6(1)	Push left side 
 63:    LDC  3,42(6)	Load integer constant 
 64:    NEG  3,3,3	Op unary - 
 65:     LD  4,-6(1)	Pop left into ac1 
 66:    ADD  3,4,3	Op + 
 67:     ST  3,0(0)	Store variable gromit
* EXPRESSION
 68:    LDC  3,27182818(6)	Load integer constant 
 69:     LD  4,0(0)	load lhs variable gromit
 70:    ADD  3,4,3	op += 
 71:     ST  3,0(0)	Store variable gromit
* EXPRESSION
 72:    LDC  3,31415927(6)	Load integer constant 
 73:     LD  4,0(0)	load lhs variable gromit
 74:    SUB  3,4,3	op -= 
 75:     ST  3,0(0)	Store variable gromit
* EXPRESSION
 76:     LD  3,-2(1)	Load variable wrong
 77:     ST  3,-6(1)	Push left side 
 78:     LD  3,-3(1)	Load variable trousers
 79:     LD  4,-6(1)	Pop left into ac1 
 80:    TLT  3,4,3	Op < 
 81:     ST  3,-6(1)	Push left side 
 82:     LD  3,-3(1)	Load variable trousers
 83:     ST  3,-7(1)	Push left side 
 84:     LD  3,0(0)	Load variable gromit
 85:     LD  4,-7(1)	Pop left into ac1 
 86:    TLE  3,4,3	Op <= 
 87:     LD  4,-6(1)	Pop left into ac1 
 88:    AND  3,4,3	Op AND 
 89:     ST  3,-4(1)	Store variable close
* EXPRESSION
 90:     LD  3,-2(1)	Load variable wrong
 91:     ST  3,-6(1)	Push left side 
 92:     LD  3,-3(1)	Load variable trousers
 93:     LD  4,-6(1)	Pop left into ac1 
 94:    TGT  3,4,3	Op > 
 95:     ST  3,-6(1)	Push left side 
 96:     LD  3,-3(1)	Load variable trousers
 97:     ST  3,-7(1)	Push left side 
 98:     LD  3,0(0)	Load variable gromit
 99:     LD  4,-7(1)	Pop left into ac1 
100:    TGE  3,4,3	Op >= 
101:     LD  4,-6(1)	Pop left into ac1 
102:    AND  3,4,3	Op AND 
103:     ST  3,-5(1)	Store variable shave
* COMPOUND
* Compound Body
* EXPRESSION
104:     LD  3,-9(1)	Load variable out
105:     LD  4,-8(1)	load lhs variable day
106:    SUB  3,4,3	op -= 
107:     ST  3,-8(1)	Store variable day
108:     LD  4,-7(1)	load lhs variable grand
109:    ADD  3,4,3	op += 
110:     ST  3,-7(1)	Store variable grand
111:     ST  3,-6(1)	Store variable a
* END COMPOUND
* EXPRESSION
112:    LDC  3,1(6)	Load integer constant 
113:    NEG  3,3,3	Op unary - 
114:     ST  3,-6(1)	Push left side 
115:    LDC  3,2(6)	Load integer constant 
116:     LD  4,-6(1)	Pop left into ac1 
117:    MUL  3,4,3	Op * 
118:     ST  3,-6(1)	Push left side 
119:    LDC  3,3(6)	Load integer constant 
120:     LD  4,-6(1)	Pop left into ac1 
121:    ADD  3,4,3	Op + 
122:     ST  3,-6(1)	Push left side 
123:    LDC  3,4(6)	Load integer constant 
124:     ST  3,-7(1)	Push left side 
125:    LDC  3,5(6)	Load integer constant 
126:     LD  4,-7(1)	Pop left into ac1 
127:    MUL  3,4,3	Op * 
128:     LD  4,-6(1)	Pop left into ac1 
129:    TLT  3,4,3	Op < 
130:     ST  3,-6(1)	Push left side 
131:    LDC  3,6(6)	Load integer constant 
132:     ST  3,-7(1)	Push left side 
133:    LDC  3,7(6)	Load integer constant 
134:     LD  4,-7(1)	Pop left into ac1 
135:    ADD  3,4,3	Op + 
136:     ST  3,-7(1)	Push left side 
137:    LDC  3,3(6)	Load integer constant 
138:    NEG  3,3,3	Op unary - 
139:     LD  4,-7(1)	Pop left into ac1 
140:    TGT  3,4,3	Op > 
141:     LD  4,-6(1)	Pop left into ac1 
142:    AND  3,4,3	Op AND 
143:     ST  3,-4(1)	Store variable close
* EXPRESSION
144:    LDC  3,1(6)	Load Boolean constant 
145:     ST  3,-6(1)	Push left side 
146:    LDC  3,1(6)	Load integer constant 
147:     ST  3,-7(1)	Push left side 
148:    LDC  3,2(6)	Load integer constant 
149:     ST  3,-8(1)	Push left side 
150:    LDC  3,3(6)	Load integer constant 
151:     LD  4,-8(1)	Pop left into ac1 
152:    ADD  3,4,3	Op + 
153:     LD  4,-7(1)	Pop left into ac1 
154:    MUL  3,4,3	Op * 
155:    NEG  3,3,3	Op unary - 
156:     ST  3,-7(1)	Push left side 
157:    LDC  3,4(6)	Load integer constant 
158:     ST  3,-8(1)	Push left side 
159:    LDC  3,5(6)	Load integer constant 
160:     LD  4,-8(1)	Pop left into ac1 
161:    MUL  3,4,3	Op * 
162:     LD  4,-7(1)	Pop left into ac1 
163:    TLT  3,4,3	Op < 
164:     ST  3,-7(1)	Push left side 
165:    LDC  3,6(6)	Load integer constant 
166:     ST  3,-8(1)	Push left side 
167:    LDC  3,7(6)	Load integer constant 
168:     LD  4,-8(1)	Pop left into ac1 
169:    ADD  3,4,3	Op + 
170:     ST  3,-8(1)	Push left side 
171:    LDC  3,3(6)	Load integer constant 
172:    NEG  3,3,3	Op unary - 
173:     LD  4,-8(1)	Pop left into ac1 
174:    TGT  3,4,3	Op > 
175:     LD  4,-7(1)	Pop left into ac1 
176:    AND  3,4,3	Op AND 
177:     LD  4,-6(1)	Pop left into ac1 
178:     OR  3,4,3	Op OR 
179:     ST  3,-5(1)	Store variable shave
* IF
180:     LD  3,-5(1)	Load variable shave
181:     ST  3,-6(1)	Push left side 
182:     LD  3,-4(1)	Load variable close
183:     LD  4,-6(1)	Pop left into ac1 
184:    TNE  3,4,3	Op != 
* THEN
* EXPRESSION
186:     LD  3,-4(1)	Load variable close
187:    LDC  4,1(6)	Load 1 
188:    XOR  3,3,4	Op XOR to get logical not 
189:     ST  3,-5(1)	Store variable shave
185:    JZR  3,4(7)	Jump around the THEN if false [backpatch] 
* END IF
* IF
190:     LD  3,-5(1)	Load variable shave
191:     ST  3,-6(1)	Push left side 
192:     LD  3,-4(1)	Load variable close
193:     LD  4,-6(1)	Pop left into ac1 
194:    TEQ  3,4,3	Op == 
195:    LDC  4,1(6)	Load 1 
196:    XOR  3,3,4	Op XOR to get logical not 
197:     ST  3,-6(1)	Push left side 
198:     LD  3,-4(1)	Load variable close
199:    LDC  4,1(6)	Load 1 
200:    XOR  3,3,4	Op XOR to get logical not 
201:     LD  4,-6(1)	Pop left into ac1 
202:     OR  3,4,3	Op OR 
* THEN
* EXPRESSION
204:    LDC  3,1(6)	Load Boolean constant 
205:     ST  3,-5(1)	Store variable shave
203:    JZR  3,3(7)	Jump around the THEN if false [backpatch] 
* ELSE
* EXPRESSION
207:    LDC  3,0(6)	Load Boolean constant 
208:     ST  3,-4(1)	Store variable close
206:    JMP  7,2(7)	Jump around the ELSE [backpatch] 
* END IF
* WHILE
209:     LD  3,-5(1)	Load variable shave
210:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
212:    LDC  3,10(6)	load size of array sheep
213:     ST  3,-8(1)	save size of array sheep
* Compound Body
* EXPRESSION
214:    LDC  3,2(6)	Load integer constant 
215:     ST  3,-19(1)	Push index 
216:    LDC  3,1618(6)	Load integer constant 
217:     LD  4,-19(1)	Pop index 
218:    LDA  5,-9(1)	Load address of base of array sheep
219:    SUB  5,5,4	Compute offset of value 
220:     ST  3,0(5)	Store variable sheep
* IF
221:    LDA  3,-9(1)	Load address of base of array sheep
222:     ST  3,-19(1)	Push left side 
223:    LDC  3,2(6)	Load integer constant 
224:     LD  4,-19(1)	Pop left into ac1 
225:    SUB  3,4,3	compute location from index 
226:     LD  3,0(3)	Load array element 
227:     ST  3,-19(1)	Push left side 
228:    LDC  3,496(6)	Load integer constant 
229:     LD  4,-19(1)	Pop left into ac1 
230:    TLT  3,4,3	Op < 
* THEN
* BREAK
232:    JMP  7,-22(7)	break 
231:    JZR  3,1(7)	Jump around the THEN if false [backpatch] 
* END IF
* EXPRESSION
* CALL wallace
233:     ST  1,-19(1)	Store fp in ghost frame for wallace
* Param 1
234:     LD  3,0(0)	load lhs variable gromit
235:    LDA  3,-1(3)	decrement value of gromit
236:     ST  3,0(0)	Store variable gromit
237:     ST  3,-21(1)	Push parameter 
* Param 2
238:     LD  3,-6(1)	Load variable were
239:     ST  3,-22(1)	Push left side 
240:     LD  3,-7(1)	Load variable rabbit
241:     LD  4,-22(1)	Pop left into ac1 
242:    SUB  3,4,3	Op - 
243:     ST  3,-22(1)	Push parameter 
* Param end wallace
244:    LDA  1,-19(1)	Load address of new frame 
245:    LDA  3,1(7)	Return address in ac 
246:    JMP  7,-208(7)	CALL wallace
247:    LDA  3,0(2)	Save the result in ac 
* Call end wallace
* COMPOUND
* Compound Body
* EXPRESSION
248:     LD  3,-21(1)	load lhs variable trousers
249:    LDA  3,1(3)	increment value of trousers
250:     ST  3,-21(1)	Store variable trousers
251:     LD  4,-20(1)	load lhs variable wrong
252:    ADD  3,4,3	op += 
253:     ST  3,-20(1)	Store variable wrong
254:     ST  3,-19(1)	Store variable the
* IF
255:     LD  3,-6(1)	Load variable were
256:     ST  3,-22(1)	Push left side 
257:     LD  3,-7(1)	Load variable rabbit
258:     LD  4,-22(1)	Pop left into ac1 
259:    TEQ  3,4,3	Op == 
* THEN
* EXPRESSION
261:     LD  3,-20(1)	load lhs variable wrong
262:    LDA  3,-1(3)	decrement value of wrong
263:     ST  3,-20(1)	Store variable wrong
264:     ST  3,-6(1)	Store variable were
260:    JZR  3,4(7)	Jump around the THEN if false [backpatch] 
* END IF
* END COMPOUND
* END COMPOUND
265:    JMP  7,-57(7)	go to beginning of loop 
211:    JMP  7,54(7)	Jump past loop [backpatch] 
* END WHILE
* RETURN
266:     LD  3,-1(1)	Load return address 
267:     LD  1,0(1)	Adjust fp 
268:    JMP  7,0(3)	Return 
* END COMPOUND
* Add standard closing in case there is no return statement
269:    LDC  2,0(6)	Set return value to 0 
270:     LD  3,-1(1)	Load return address 
271:     LD  1,0(1)	Adjust fp 
272:    JMP  7,0(3)	Return 
* END FUNCTION wallace
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION Wendolene
273:     ST  3,-1(1)	Store return address 
* COMPOUND
* Compound Body
* RETURN
274:     LD  3,-2(1)	Load variable wool
275:     ST  3,-6(1)	Push left side 
276:     LD  3,-4(1)	Load address of base of array yarn
277:     ST  3,-7(1)	Push left side 
278:    LDC  3,0(6)	Load integer constant 
279:     LD  4,-7(1)	Pop left into ac1 
280:    SUB  3,4,3	compute location from index 
281:     LD  3,0(3)	Load array element 
282:     LD  4,-6(1)	Pop left into ac1 
283:    ADD  3,4,3	Op + 
284:     ST  3,-6(1)	Push left side 
285:     LD  3,-4(1)	Load address of base of array yarn
286:     LD  3,1(3)	Load array size 
287:     LD  4,-6(1)	Pop left into ac1 
288:    ADD  3,4,3	Op + 
289:     ST  3,-6(1)	Push left side 
290:     LD  3,-4(1)	Load address of base of array yarn
291:     ST  3,-7(1)	Push left side 
292:    LDC  3,7(6)	Load integer constant 
293:     ST  3,-8(1)	Push left side 
294:     LD  3,-2(1)	Load variable wool
295:     LD  4,-8(1)	Pop left into ac1 
296:    MUL  3,4,3	Op * 
297:     LD  4,-7(1)	Pop left into ac1 
298:    SUB  3,4,3	compute location from index 
299:     LD  3,0(3)	Load array element 
300:     LD  4,-6(1)	Pop left into ac1 
301:    ADD  3,4,3	Op + 
302:    LDA  2,0(3)	Copy result to return register 
303:     LD  3,-1(1)	Load return address 
304:     LD  1,0(1)	Adjust fp 
305:    JMP  7,0(3)	Return 
* END COMPOUND
* Add standard closing in case there is no return statement
306:    LDC  2,0(6)	Set return value to 0 
307:     LD  3,-1(1)	Load return address 
308:     LD  1,0(1)	Adjust fp 
309:    JMP  7,0(3)	Return 
* END FUNCTION Wendolene
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION ramsBottom
310:     ST  3,-1(1)	Store return address 
* COMPOUND
311:    LDC  3,2(6)	load size of array chicken
312:     ST  3,-2(1)	save size of array chicken
313:    LDC  3,3(6)	load size of array run
314:     ST  3,-5(1)	save size of array run
315:    LDC  3,2(6)	load size of array wallace
316:     ST  3,-9(1)	save size of array wallace
317:    LDC  3,3(6)	load size of array gromit
318:     ST  3,-12(1)	save size of array gromit
* Compound Body
* EXPRESSION
319:    LDC  3,42(6)	Load integer constant 
320:     ST  3,-16(1)	Push left side 
* CALL Wendolene
321:     ST  1,-17(1)	Store fp in ghost frame for Wendolene
* Param 1
322:    LDC  3,1(6)	Load integer constant 
323:     ST  3,-19(1)	Push left side 
324:    LDC  3,2(6)	Load integer constant 
325:     LD  4,-19(1)	Pop left into ac1 
326:    ADD  3,4,3	Op + 
327:     ST  3,-19(1)	Push left side 
328:    LDC  3,3(6)	Load integer constant 
329:     LD  4,-19(1)	Pop left into ac1 
330:    ADD  3,4,3	Op + 
331:     ST  3,-19(1)	Push parameter 
* Param 2
332:    LDC  3,1(6)	Load Boolean constant 
333:    LDC  4,1(6)	Load 1 
334:    XOR  3,3,4	Op XOR to get logical not 
335:     ST  3,-20(1)	Push left side 
336:    LDC  3,1(6)	Load Boolean constant 
337:     ST  3,-21(1)	Push left side 
338:    LDC  3,0(6)	Load Boolean constant 
339:     LD  4,-21(1)	Pop left into ac1 
340:    AND  3,4,3	Op AND 
341:     LD  4,-20(1)	Pop left into ac1 
342:     OR  3,4,3	Op OR 
343:     ST  3,-20(1)	Push parameter 
* Param 3
344:    LDA  3,-3(1)	Load address of base of array chicken
345:     ST  3,-21(1)	Push parameter 
* Param 4
346:    LDA  3,-6(1)	Load address of base of array run
347:     ST  3,-22(1)	Push parameter 
* Param end Wendolene
348:    LDA  1,-17(1)	Load address of new frame 
349:    LDA  3,1(7)	Return address in ac 
350:    JMP  7,-78(7)	CALL Wendolene
351:    LDA  3,0(2)	Save the result in ac 
* Call end Wendolene
352:     LD  4,-16(1)	Pop left into ac1 
353:    MUL  3,4,3	Op * 
* EXPRESSION
354:    LDA  3,-6(1)	Load address of base of array run
355:     ST  3,-16(1)	Push left side 
356:    LDA  3,-6(1)	Load address of base of array run
357:     LD  3,1(3)	Load array size 
358:     ST  3,-17(1)	Push left side 
359:    LDC  3,1(6)	Load integer constant 
360:     LD  4,-17(1)	Pop left into ac1 
361:    SUB  3,4,3	Op - 
362:     LD  4,-16(1)	Pop left into ac1 
363:    SUB  3,4,3	compute location from index 
364:     LD  3,0(3)	Load array element 
* RETURN
365:    LDA  3,-10(1)	Load address of base of array wallace
366:     ST  3,-16(1)	Push left side 
367:    LDC  3,1(6)	Load integer constant 
368:     LD  4,-16(1)	Pop left into ac1 
369:    SUB  3,4,3	compute location from index 
370:     LD  3,0(3)	Load array element 
371:     ST  3,-16(1)	Push left side 
372:    LDA  3,-13(1)	Load address of base of array gromit
373:     ST  3,-17(1)	Push left side 
374:    LDC  3,2(6)	Load integer constant 
375:     LD  4,-17(1)	Pop left into ac1 
376:    SUB  3,4,3	compute location from index 
377:     LD  3,0(3)	Load array element 
378:    NEG  3,3,3	Op unary - 
379:     ST  3,-17(1)	Push left side 
380:    LDC  3,3(6)	Load integer constant 
381:     LD  4,-17(1)	Pop left into ac1 
382:    MUL  3,4,3	Op * 
383:     LD  4,-16(1)	Pop left into ac1 
384:    TGE  3,4,3	Op >= 
385:    LDC  4,1(6)	Load 1 
386:    XOR  3,3,4	Op XOR to get logical not 
387:    LDA  2,0(3)	Copy result to return register 
388:     LD  3,-1(1)	Load return address 
389:     LD  1,0(1)	Adjust fp 
390:    JMP  7,0(3)	Return 
* END COMPOUND
* Add standard closing in case there is no return statement
391:    LDC  2,0(6)	Set return value to 0 
392:     LD  3,-1(1)	Load return address 
393:     LD  1,0(1)	Adjust fp 
394:    JMP  7,0(3)	Return 
* END FUNCTION ramsBottom
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION cheese
395:     ST  3,-1(1)	Store return address 
* WHILE
396:     LD  3,-2(1)	Load variable x
397:     ST  3,-4(1)	Push left side 
398:    LDC  3,0(6)	Load integer constant 
399:     LD  4,-4(1)	Pop left into ac1 
400:    TGT  3,4,3	Op > 
401:    JNZ  3,1(7)	Jump to while part 
* DO
* IF
403:     LD  3,-3(1)	Load variable y
404:     ST  3,-4(1)	Push left side 
405:    LDC  3,3(6)	Load integer constant 
406:     LD  4,-4(1)	Pop left into ac1 
407:    TGT  3,4,3	Op > 
* THEN
* EXPRESSION
409:     LD  3,-2(1)	load lhs variable x
410:    LDA  3,-1(3)	decrement value of x
411:     ST  3,-2(1)	Store variable x
408:    JZR  3,4(7)	Jump around the THEN if false [backpatch] 
* ELSE
* RETURN
413:     LD  3,-2(1)	Load variable x
414:     ST  3,-4(1)	Push left side 
415:     LD  3,-2(1)	Load variable x
416:     LD  4,-4(1)	Pop left into ac1 
417:    MUL  3,4,3	Op * 
418:     ST  3,-4(1)	Push left side 
419:     LD  3,-3(1)	Load variable y
420:     LD  4,-4(1)	Pop left into ac1 
421:    MOD  3,4,3	Op % 
422:    LDA  2,0(3)	Copy result to return register 
423:     LD  3,-1(1)	Load return address 
424:     LD  1,0(1)	Adjust fp 
425:    JMP  7,0(3)	Return 
412:    JMP  7,13(7)	Jump around the ELSE [backpatch] 
* END IF
426:    JMP  7,-31(7)	go to beginning of loop 
402:    JMP  7,24(7)	Jump past loop [backpatch] 
* END WHILE
* Add standard closing in case there is no return statement
427:    LDC  2,0(6)	Set return value to 0 
428:     LD  3,-1(1)	Load return address 
429:     LD  1,0(1)	Adjust fp 
430:    JMP  7,0(3)	Return 
* END FUNCTION cheese
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION Wensleydale
431:     ST  3,-1(1)	Store return address 
* RETURN
* CALL cheese
432:     ST  1,-4(1)	Store fp in ghost frame for cheese
* Param 1
433:     LD  3,-2(1)	Load variable x
434:     ST  3,-6(1)	Push parameter 
* Param 2
435:     LD  3,0(0)	Load variable gromit
436:     ST  3,-7(1)	Push parameter 
* Param end cheese
437:    LDA  1,-4(1)	Load address of new frame 
438:    LDA  3,1(7)	Return address in ac 
439:    JMP  7,-45(7)	CALL cheese
440:    LDA  3,0(2)	Save the result in ac 
* Call end cheese
441:    LDA  2,0(3)	Copy result to return register 
442:     LD  3,-1(1)	Load return address 
443:     LD  1,0(1)	Adjust fp 
444:    JMP  7,0(3)	Return 
* Add standard closing in case there is no return statement
445:    LDC  2,0(6)	Set return value to 0 
446:     LD  3,-1(1)	Load return address 
447:     LD  1,0(1)	Adjust fp 
448:    JMP  7,0(3)	Return 
* END FUNCTION Wensleydale
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION main
449:     ST  3,-1(1)	Store return address 
* COMPOUND
450:    LDC  3,113(6)	load size of array yarn
451:     ST  3,-3(1)	save size of array yarn
452:    LDC  3,22(6)	load size of array preston
453:     ST  3,-118(1)	save size of array preston
* Compound Body
* EXPRESSION
* CALL wallace
454:     ST  1,-141(1)	Store fp in ghost frame for wallace
* Param 1
* CALL cheese
455:     ST  1,-143(1)	Store fp in ghost frame for cheese
* Param 1
456:    LDC  3,62(6)	Load integer constant 
457:     ST  3,-145(1)	Push parameter 
* Param 2
458:    LDC  3,62(6)	Load integer constant 
459:     ST  3,-146(1)	Push parameter 
* Param end cheese
460:    LDA  1,-143(1)	Load address of new frame 
461:    LDA  3,1(7)	Return address in ac 
462:    JMP  7,-68(7)	CALL cheese
463:    LDA  3,0(2)	Save the result in ac 
* Call end cheese
464:     ST  3,-143(1)	Push parameter 
* Param 2
465:     LD  3,0(0)	Load variable gromit
466:     ST  3,-144(1)	Push parameter 
* Param end wallace
467:    LDA  1,-141(1)	Load address of new frame 
468:    LDA  3,1(7)	Return address in ac 
469:    JMP  7,-431(7)	CALL wallace
470:    LDA  3,0(2)	Save the result in ac 
* Call end wallace
* RETURN
* CALL Wendolene
471:     ST  1,-141(1)	Store fp in ghost frame for Wendolene
* Param 1
472:    LDA  3,-119(1)	Load address of base of array preston
473:     LD  3,1(3)	Load array size 
474:     ST  3,-143(1)	Push left side 
475:    LDA  3,-4(1)	Load address of base of array yarn
476:     LD  3,1(3)	Load array size 
477:     LD  4,-143(1)	Pop left into ac1 
478:    MUL  3,4,3	Op * 
479:     ST  3,-143(1)	Push parameter 
* Param 2
480:     LD  3,-117(1)	Load variable shawn
481:     ST  3,-144(1)	Push parameter 
* Param 3
482:    LDA  3,-4(1)	Load address of base of array yarn
483:     ST  3,-145(1)	Push parameter 
* Param 4
484:    LDA  3,-119(1)	Load address of base of array preston
485:     ST  3,-146(1)	Push parameter 
* Param end Wendolene
486:    LDA  1,-141(1)	Load address of new frame 
487:    LDA  3,1(7)	Return address in ac 
488:    JMP  7,-216(7)	CALL Wendolene
489:    LDA  3,0(2)	Save the result in ac 
* Call end Wendolene
490:    LDA  2,0(3)	Copy result to return register 
491:     LD  3,-1(1)	Load return address 
492:     LD  1,0(1)	Adjust fp 
493:    JMP  7,0(3)	Return 
* END COMPOUND
* Add standard closing in case there is no return statement
494:    LDC  2,0(6)	Set return value to 0 
495:     LD  3,-1(1)	Load return address 
496:     LD  1,0(1)	Adjust fp 
497:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,497(7)	Jump to init [backpatch] 
* INIT
498:     LD  0,0(0)	Set the global pointer 
499:    LDA  1,-1(0)	set first frame at end of globals 
500:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
501:    LDA  3,1(7)	Return address in ac 
502:    JMP  7,-54(7)	Jump to main 
503:   HALT  0,0,0	DONE! 
* END INIT
