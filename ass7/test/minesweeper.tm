* C- compiler version C-F20
* Built: Nov 19, 2020
* Author: Robert B. Heckendorn
* File compiled:  minesweeper.c-
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
* FUNCTION Random
 39:     ST  3,-1(1)	Store return address 
* COMPOUND
* Compound Body
* EXPRESSION
 40:     LD  3,0(0)	Load variable seed
 41:     ST  3,-3(1)	Push left side 
 42:    LDC  3,333331(6)	Load integer constant 
 43:     LD  4,-3(1)	Pop left into ac1 
 44:    MUL  3,4,3	Op * 
 45:     ST  3,-3(1)	Push left side 
 46:    LDC  3,3331(6)	Load integer constant 
 47:     LD  4,-3(1)	Pop left into ac1 
 48:    ADD  3,4,3	Op + 
 49:     ST  3,0(0)	Store variable seed
* IF
 50:     LD  3,0(0)	Load variable seed
 51:     ST  3,-3(1)	Push left side 
 52:    LDC  3,0(6)	Load integer constant 
 53:     LD  4,-3(1)	Pop left into ac1 
 54:    TLT  3,4,3	Op < 
* THEN
* RETURN
 56:     LD  3,0(0)	Load variable seed
 57:    NEG  3,3,3	Op unary - 
 58:     ST  3,-3(1)	Push left side 
 59:    LDC  3,100(6)	Load integer constant 
 60:     LD  4,-3(1)	Pop left into ac1 
 61:    MOD  3,4,3	Op % 
 62:    LDA  2,0(3)	Copy result to return register 
 63:     LD  3,-1(1)	Load return address 
 64:     LD  1,0(1)	Adjust fp 
 65:    JMP  7,0(3)	Return 
 55:    JZR  3,11(7)	Jump around the THEN if false [backpatch] 
* ELSE
* RETURN
 67:     LD  3,0(0)	Load variable seed
 68:     ST  3,-3(1)	Push left side 
 69:    LDC  3,100(6)	Load integer constant 
 70:     LD  4,-3(1)	Pop left into ac1 
 71:    MOD  3,4,3	Op % 
 72:    LDA  2,0(3)	Copy result to return register 
 73:     LD  3,-1(1)	Load return address 
 74:     LD  1,0(1)	Adjust fp 
 75:    JMP  7,0(3)	Return 
 66:    JMP  7,9(7)	Jump around the ELSE [backpatch] 
* END IF
* END COMPOUND
* Add standard closing in case there is no return statement
 76:    LDC  2,0(6)	Set return value to 0 
 77:     LD  3,-1(1)	Load return address 
 78:     LD  1,0(1)	Adjust fp 
 79:    JMP  7,0(3)	Return 
* END FUNCTION Random
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION CreateBoard
 80:     ST  3,-1(1)	Store return address 
* COMPOUND
* Compound Body
* EXPRESSION
 81:    LDC  3,0(6)	Load integer constant 
 82:     ST  3,-2(1)	Store variable i
* WHILE
 83:     LD  3,-2(1)	Load variable i
 84:     ST  3,-4(1)	Push left side 
 85:    LDC  3,100(6)	Load integer constant 
 86:     LD  4,-4(1)	Pop left into ac1 
 87:    TLT  3,4,3	Op < 
 88:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* EXPRESSION
 90:     LD  3,-2(1)	Load variable i
 91:     ST  3,-4(1)	Push index 
 92:    LDC  3,0(6)	Load Boolean constant 
 93:     LD  4,-4(1)	Pop index 
 94:    LDA  5,-103(0)	Load address of base of array guess
 95:    SUB  5,5,4	Compute offset of value 
 96:     ST  3,0(5)	Store variable guess
* EXPRESSION
 97:    LDC  3,1(6)	Load integer constant 
 98:     LD  4,-2(1)	load lhs variable i
 99:    ADD  3,4,3	op += 
100:     ST  3,-2(1)	Store variable i
* END COMPOUND
101:    JMP  7,-19(7)	go to beginning of loop 
 89:    JMP  7,12(7)	Jump past loop [backpatch] 
* END WHILE
* EXPRESSION
102:    LDC  3,0(6)	Load integer constant 
103:     ST  3,-2(1)	Store variable i
* WHILE
104:     LD  3,-2(1)	Load variable i
105:     ST  3,-4(1)	Push left side 
106:    LDC  3,100(6)	Load integer constant 
107:     LD  4,-4(1)	Pop left into ac1 
108:    TLT  3,4,3	Op < 
109:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* EXPRESSION
111:     LD  3,-2(1)	Load variable i
112:     ST  3,-4(1)	Push index 
113:    LDC  3,0(6)	Load integer constant 
114:     LD  4,-4(1)	Pop index 
115:    LDA  5,-2(0)	Load address of base of array board
116:    SUB  5,5,4	Compute offset of value 
117:     ST  3,0(5)	Store variable board
* EXPRESSION
118:    LDC  3,1(6)	Load integer constant 
119:     LD  4,-2(1)	load lhs variable i
120:    ADD  3,4,3	op += 
121:     ST  3,-2(1)	Store variable i
* END COMPOUND
122:    JMP  7,-19(7)	go to beginning of loop 
110:    JMP  7,12(7)	Jump past loop [backpatch] 
* END WHILE
* EXPRESSION
123:    LDC  3,0(6)	Load integer constant 
124:     ST  3,-2(1)	Store variable i
* WHILE
125:     LD  3,-2(1)	Load variable i
126:     ST  3,-4(1)	Push left side 
127:    LDC  3,15(6)	Load integer constant 
128:     LD  4,-4(1)	Pop left into ac1 
129:    TLE  3,4,3	Op <= 
130:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* WHILE
132:    LDC  3,1(6)	Load Boolean constant 
133:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* EXPRESSION
* CALL Random
135:     ST  1,-5(1)	Store fp in ghost frame for Random
* Param end Random
136:    LDA  1,-5(1)	Load address of new frame 
137:    LDA  3,1(7)	Return address in ac 
138:    JMP  7,-100(7)	CALL Random
139:    LDA  3,0(2)	Save the result in ac 
* Call end Random
140:     ST  3,-4(1)	Store variable rand
* IF
141:    LDA  3,-2(0)	Load address of base of array board
142:     ST  3,-5(1)	Push left side 
143:     LD  3,-4(1)	Load variable rand
144:     LD  4,-5(1)	Pop left into ac1 
145:    SUB  3,4,3	compute location from index 
146:     LD  3,0(3)	Load array element 
147:     ST  3,-5(1)	Push left side 
148:    LDC  3,1(6)	Load integer constant 
149:    NEG  3,3,3	Op unary - 
150:     LD  4,-5(1)	Pop left into ac1 
151:    TNE  3,4,3	Op != 
* THEN
* COMPOUND
* Compound Body
* EXPRESSION
153:     LD  3,-4(1)	Load variable rand
154:     ST  3,-5(1)	Push index 
155:    LDC  3,1(6)	Load integer constant 
156:    NEG  3,3,3	Op unary - 
157:     LD  4,-5(1)	Pop index 
158:    LDA  5,-2(0)	Load address of base of array board
159:    SUB  5,5,4	Compute offset of value 
160:     ST  3,0(5)	Store variable board
* IF
161:     LD  3,-4(1)	Load variable rand
162:     ST  3,-5(1)	Push left side 
163:    LDC  3,10(6)	Load integer constant 
164:     LD  4,-5(1)	Pop left into ac1 
165:    MOD  3,4,3	Op % 
166:     ST  3,-5(1)	Push left side 
167:    LDC  3,0(6)	Load integer constant 
168:     LD  4,-5(1)	Pop left into ac1 
169:    TNE  3,4,3	Op != 
170:     ST  3,-5(1)	Push left side 
171:     LD  3,-4(1)	Load variable rand
172:     ST  3,-6(1)	Push left side 
173:    LDC  3,9(6)	Load integer constant 
174:     LD  4,-6(1)	Pop left into ac1 
175:    TGT  3,4,3	Op > 
176:     LD  4,-5(1)	Pop left into ac1 
177:    AND  3,4,3	Op AND 
* THEN
* IF
179:    LDA  3,-2(0)	Load address of base of array board
180:     ST  3,-5(1)	Push left side 
181:     LD  3,-4(1)	Load variable rand
182:     ST  3,-6(1)	Push left side 
183:    LDC  3,11(6)	Load integer constant 
184:     LD  4,-6(1)	Pop left into ac1 
185:    SUB  3,4,3	Op - 
186:     LD  4,-5(1)	Pop left into ac1 
187:    SUB  3,4,3	compute location from index 
188:     LD  3,0(3)	Load array element 
189:     ST  3,-5(1)	Push left side 
190:    LDC  3,1(6)	Load integer constant 
191:    NEG  3,3,3	Op unary - 
192:     LD  4,-5(1)	Pop left into ac1 
193:    TNE  3,4,3	Op != 
* THEN
* EXPRESSION
195:     LD  3,-4(1)	Load variable rand
196:     ST  3,-5(1)	Push left side 
197:    LDC  3,11(6)	Load integer constant 
198:     LD  4,-5(1)	Pop left into ac1 
199:    SUB  3,4,3	Op - 
200:     ST  3,-5(1)	Push index 
201:    LDC  3,1(6)	Load integer constant 
202:     LD  4,-5(1)	Pop index 
203:    LDA  5,-2(0)	Load address of base of array board
204:    SUB  5,5,4	Compute offset of value 
205:     LD  4,0(5)	load lhs variable board
206:    ADD  3,4,3	op += 
207:     ST  3,0(5)	Store variable board
194:    JZR  3,13(7)	Jump around the THEN if false [backpatch] 
* END IF
178:    JZR  3,29(7)	Jump around the THEN if false [backpatch] 
* END IF
* IF
208:     LD  3,-4(1)	Load variable rand
209:     ST  3,-5(1)	Push left side 
210:    LDC  3,9(6)	Load integer constant 
211:     LD  4,-5(1)	Pop left into ac1 
212:    TGT  3,4,3	Op > 
* THEN
* IF
214:    LDA  3,-2(0)	Load address of base of array board
215:     ST  3,-5(1)	Push left side 
216:     LD  3,-4(1)	Load variable rand
217:     ST  3,-6(1)	Push left side 
218:    LDC  3,10(6)	Load integer constant 
219:     LD  4,-6(1)	Pop left into ac1 
220:    SUB  3,4,3	Op - 
221:     LD  4,-5(1)	Pop left into ac1 
222:    SUB  3,4,3	compute location from index 
223:     LD  3,0(3)	Load array element 
224:     ST  3,-5(1)	Push left side 
225:    LDC  3,1(6)	Load integer constant 
226:    NEG  3,3,3	Op unary - 
227:     LD  4,-5(1)	Pop left into ac1 
228:    TNE  3,4,3	Op != 
* THEN
* EXPRESSION
230:     LD  3,-4(1)	Load variable rand
231:     ST  3,-5(1)	Push left side 
232:    LDC  3,10(6)	Load integer constant 
233:     LD  4,-5(1)	Pop left into ac1 
234:    SUB  3,4,3	Op - 
235:     ST  3,-5(1)	Push index 
236:    LDC  3,1(6)	Load integer constant 
237:     LD  4,-5(1)	Pop index 
238:    LDA  5,-2(0)	Load address of base of array board
239:    SUB  5,5,4	Compute offset of value 
240:     LD  4,0(5)	load lhs variable board
241:    ADD  3,4,3	op += 
242:     ST  3,0(5)	Store variable board
229:    JZR  3,13(7)	Jump around the THEN if false [backpatch] 
* END IF
213:    JZR  3,29(7)	Jump around the THEN if false [backpatch] 
* END IF
* IF
243:     LD  3,-4(1)	Load variable rand
244:     ST  3,-5(1)	Push left side 
245:    LDC  3,9(6)	Load integer constant 
246:     LD  4,-5(1)	Pop left into ac1 
247:    MOD  3,4,3	Op % 
248:     ST  3,-5(1)	Push left side 
249:    LDC  3,0(6)	Load integer constant 
250:     LD  4,-5(1)	Pop left into ac1 
251:    TNE  3,4,3	Op != 
252:     ST  3,-5(1)	Push left side 
253:     LD  3,-4(1)	Load variable rand
254:     ST  3,-6(1)	Push left side 
255:    LDC  3,9(6)	Load integer constant 
256:     LD  4,-6(1)	Pop left into ac1 
257:    TGT  3,4,3	Op > 
258:     LD  4,-5(1)	Pop left into ac1 
259:    AND  3,4,3	Op AND 
* THEN
* IF
261:    LDA  3,-2(0)	Load address of base of array board
262:     ST  3,-5(1)	Push left side 
263:     LD  3,-4(1)	Load variable rand
264:     ST  3,-6(1)	Push left side 
265:    LDC  3,9(6)	Load integer constant 
266:     LD  4,-6(1)	Pop left into ac1 
267:    SUB  3,4,3	Op - 
268:     LD  4,-5(1)	Pop left into ac1 
269:    SUB  3,4,3	compute location from index 
270:     LD  3,0(3)	Load array element 
271:     ST  3,-5(1)	Push left side 
272:    LDC  3,1(6)	Load integer constant 
273:    NEG  3,3,3	Op unary - 
274:     LD  4,-5(1)	Pop left into ac1 
275:    TNE  3,4,3	Op != 
* THEN
* EXPRESSION
277:     LD  3,-4(1)	Load variable rand
278:     ST  3,-5(1)	Push left side 
279:    LDC  3,9(6)	Load integer constant 
280:     LD  4,-5(1)	Pop left into ac1 
281:    SUB  3,4,3	Op - 
282:     ST  3,-5(1)	Push index 
283:    LDC  3,1(6)	Load integer constant 
284:     LD  4,-5(1)	Pop index 
285:    LDA  5,-2(0)	Load address of base of array board
286:    SUB  5,5,4	Compute offset of value 
287:     LD  4,0(5)	load lhs variable board
288:    ADD  3,4,3	op += 
289:     ST  3,0(5)	Store variable board
276:    JZR  3,13(7)	Jump around the THEN if false [backpatch] 
* END IF
260:    JZR  3,29(7)	Jump around the THEN if false [backpatch] 
* END IF
* IF
290:     LD  3,-4(1)	Load variable rand
291:     ST  3,-5(1)	Push left side 
292:    LDC  3,10(6)	Load integer constant 
293:     LD  4,-5(1)	Pop left into ac1 
294:    MOD  3,4,3	Op % 
295:     ST  3,-5(1)	Push left side 
296:    LDC  3,0(6)	Load integer constant 
297:     LD  4,-5(1)	Pop left into ac1 
298:    TNE  3,4,3	Op != 
* THEN
* IF
300:    LDA  3,-2(0)	Load address of base of array board
301:     ST  3,-5(1)	Push left side 
302:     LD  3,-4(1)	Load variable rand
303:     ST  3,-6(1)	Push left side 
304:    LDC  3,1(6)	Load integer constant 
305:     LD  4,-6(1)	Pop left into ac1 
306:    SUB  3,4,3	Op - 
307:     LD  4,-5(1)	Pop left into ac1 
308:    SUB  3,4,3	compute location from index 
309:     LD  3,0(3)	Load array element 
310:     ST  3,-5(1)	Push left side 
311:    LDC  3,1(6)	Load integer constant 
312:    NEG  3,3,3	Op unary - 
313:     LD  4,-5(1)	Pop left into ac1 
314:    TNE  3,4,3	Op != 
* THEN
* EXPRESSION
316:     LD  3,-4(1)	Load variable rand
317:     ST  3,-5(1)	Push left side 
318:    LDC  3,1(6)	Load integer constant 
319:     LD  4,-5(1)	Pop left into ac1 
320:    SUB  3,4,3	Op - 
321:     ST  3,-5(1)	Push index 
322:    LDC  3,1(6)	Load integer constant 
323:     LD  4,-5(1)	Pop index 
324:    LDA  5,-2(0)	Load address of base of array board
325:    SUB  5,5,4	Compute offset of value 
326:     LD  4,0(5)	load lhs variable board
327:    ADD  3,4,3	op += 
328:     ST  3,0(5)	Store variable board
315:    JZR  3,13(7)	Jump around the THEN if false [backpatch] 
* END IF
299:    JZR  3,29(7)	Jump around the THEN if false [backpatch] 
* END IF
* IF
329:     LD  3,-4(1)	Load variable rand
330:     ST  3,-5(1)	Push left side 
331:    LDC  3,9(6)	Load integer constant 
332:     LD  4,-5(1)	Pop left into ac1 
333:    MOD  3,4,3	Op % 
334:     ST  3,-5(1)	Push left side 
335:    LDC  3,0(6)	Load integer constant 
336:     LD  4,-5(1)	Pop left into ac1 
337:    TNE  3,4,3	Op != 
338:     ST  3,-5(1)	Push left side 
339:     LD  3,-4(1)	Load variable rand
340:     ST  3,-6(1)	Push left side 
341:    LDC  3,0(6)	Load integer constant 
342:     LD  4,-6(1)	Pop left into ac1 
343:    TEQ  3,4,3	Op == 
344:     LD  4,-5(1)	Pop left into ac1 
345:     OR  3,4,3	Op OR 
* THEN
* IF
347:    LDA  3,-2(0)	Load address of base of array board
348:     ST  3,-5(1)	Push left side 
349:     LD  3,-4(1)	Load variable rand
350:     ST  3,-6(1)	Push left side 
351:    LDC  3,1(6)	Load integer constant 
352:     LD  4,-6(1)	Pop left into ac1 
353:    ADD  3,4,3	Op + 
354:     LD  4,-5(1)	Pop left into ac1 
355:    SUB  3,4,3	compute location from index 
356:     LD  3,0(3)	Load array element 
357:     ST  3,-5(1)	Push left side 
358:    LDC  3,1(6)	Load integer constant 
359:    NEG  3,3,3	Op unary - 
360:     LD  4,-5(1)	Pop left into ac1 
361:    TNE  3,4,3	Op != 
* THEN
* EXPRESSION
363:     LD  3,-4(1)	Load variable rand
364:     ST  3,-5(1)	Push left side 
365:    LDC  3,1(6)	Load integer constant 
366:     LD  4,-5(1)	Pop left into ac1 
367:    ADD  3,4,3	Op + 
368:     ST  3,-5(1)	Push index 
369:    LDC  3,1(6)	Load integer constant 
370:     LD  4,-5(1)	Pop index 
371:    LDA  5,-2(0)	Load address of base of array board
372:    SUB  5,5,4	Compute offset of value 
373:     LD  4,0(5)	load lhs variable board
374:    ADD  3,4,3	op += 
375:     ST  3,0(5)	Store variable board
362:    JZR  3,13(7)	Jump around the THEN if false [backpatch] 
* END IF
346:    JZR  3,29(7)	Jump around the THEN if false [backpatch] 
* END IF
* IF
376:     LD  3,-4(1)	Load variable rand
377:     ST  3,-5(1)	Push left side 
378:    LDC  3,10(6)	Load integer constant 
379:     LD  4,-5(1)	Pop left into ac1 
380:    MOD  3,4,3	Op % 
381:     ST  3,-5(1)	Push left side 
382:    LDC  3,0(6)	Load integer constant 
383:     LD  4,-5(1)	Pop left into ac1 
384:    TNE  3,4,3	Op != 
385:     ST  3,-5(1)	Push left side 
386:     LD  3,-4(1)	Load variable rand
387:     ST  3,-6(1)	Push left side 
388:    LDC  3,90(6)	Load integer constant 
389:     LD  4,-6(1)	Pop left into ac1 
390:    TLT  3,4,3	Op < 
391:     LD  4,-5(1)	Pop left into ac1 
392:    AND  3,4,3	Op AND 
* THEN
* IF
394:    LDA  3,-2(0)	Load address of base of array board
395:     ST  3,-5(1)	Push left side 
396:     LD  3,-4(1)	Load variable rand
397:     ST  3,-6(1)	Push left side 
398:    LDC  3,9(6)	Load integer constant 
399:     LD  4,-6(1)	Pop left into ac1 
400:    ADD  3,4,3	Op + 
401:     LD  4,-5(1)	Pop left into ac1 
402:    SUB  3,4,3	compute location from index 
403:     LD  3,0(3)	Load array element 
404:     ST  3,-5(1)	Push left side 
405:    LDC  3,1(6)	Load integer constant 
406:    NEG  3,3,3	Op unary - 
407:     LD  4,-5(1)	Pop left into ac1 
408:    TNE  3,4,3	Op != 
* THEN
* EXPRESSION
410:     LD  3,-4(1)	Load variable rand
411:     ST  3,-5(1)	Push left side 
412:    LDC  3,9(6)	Load integer constant 
413:     LD  4,-5(1)	Pop left into ac1 
414:    ADD  3,4,3	Op + 
415:     ST  3,-5(1)	Push index 
416:    LDC  3,1(6)	Load integer constant 
417:     LD  4,-5(1)	Pop index 
418:    LDA  5,-2(0)	Load address of base of array board
419:    SUB  5,5,4	Compute offset of value 
420:     LD  4,0(5)	load lhs variable board
421:    ADD  3,4,3	op += 
422:     ST  3,0(5)	Store variable board
409:    JZR  3,13(7)	Jump around the THEN if false [backpatch] 
* END IF
393:    JZR  3,29(7)	Jump around the THEN if false [backpatch] 
* END IF
* IF
423:     LD  3,-4(1)	Load variable rand
424:     ST  3,-5(1)	Push left side 
425:    LDC  3,90(6)	Load integer constant 
426:     LD  4,-5(1)	Pop left into ac1 
427:    TLT  3,4,3	Op < 
* THEN
* IF
429:    LDA  3,-2(0)	Load address of base of array board
430:     ST  3,-5(1)	Push left side 
431:     LD  3,-4(1)	Load variable rand
432:     ST  3,-6(1)	Push left side 
433:    LDC  3,10(6)	Load integer constant 
434:     LD  4,-6(1)	Pop left into ac1 
435:    ADD  3,4,3	Op + 
436:     LD  4,-5(1)	Pop left into ac1 
437:    SUB  3,4,3	compute location from index 
438:     LD  3,0(3)	Load array element 
439:     ST  3,-5(1)	Push left side 
440:    LDC  3,1(6)	Load integer constant 
441:    NEG  3,3,3	Op unary - 
442:     LD  4,-5(1)	Pop left into ac1 
443:    TNE  3,4,3	Op != 
* THEN
* EXPRESSION
445:     LD  3,-4(1)	Load variable rand
446:     ST  3,-5(1)	Push left side 
447:    LDC  3,10(6)	Load integer constant 
448:     LD  4,-5(1)	Pop left into ac1 
449:    ADD  3,4,3	Op + 
450:     ST  3,-5(1)	Push index 
451:    LDC  3,1(6)	Load integer constant 
452:     LD  4,-5(1)	Pop index 
453:    LDA  5,-2(0)	Load address of base of array board
454:    SUB  5,5,4	Compute offset of value 
455:     LD  4,0(5)	load lhs variable board
456:    ADD  3,4,3	op += 
457:     ST  3,0(5)	Store variable board
444:    JZR  3,13(7)	Jump around the THEN if false [backpatch] 
* END IF
428:    JZR  3,29(7)	Jump around the THEN if false [backpatch] 
* END IF
* IF
458:     LD  3,-4(1)	Load variable rand
459:     ST  3,-5(1)	Push left side 
460:    LDC  3,9(6)	Load integer constant 
461:     LD  4,-5(1)	Pop left into ac1 
462:    MOD  3,4,3	Op % 
463:     ST  3,-5(1)	Push left side 
464:    LDC  3,0(6)	Load integer constant 
465:     LD  4,-5(1)	Pop left into ac1 
466:    TNE  3,4,3	Op != 
467:     ST  3,-5(1)	Push left side 
468:     LD  3,-4(1)	Load variable rand
469:     ST  3,-6(1)	Push left side 
470:    LDC  3,90(6)	Load integer constant 
471:     LD  4,-6(1)	Pop left into ac1 
472:    TLT  3,4,3	Op < 
473:     LD  4,-5(1)	Pop left into ac1 
474:    AND  3,4,3	Op AND 
* THEN
* IF
476:    LDA  3,-2(0)	Load address of base of array board
477:     ST  3,-5(1)	Push left side 
478:     LD  3,-4(1)	Load variable rand
479:     ST  3,-6(1)	Push left side 
480:    LDC  3,11(6)	Load integer constant 
481:     LD  4,-6(1)	Pop left into ac1 
482:    ADD  3,4,3	Op + 
483:     LD  4,-5(1)	Pop left into ac1 
484:    SUB  3,4,3	compute location from index 
485:     LD  3,0(3)	Load array element 
486:     ST  3,-5(1)	Push left side 
487:    LDC  3,1(6)	Load integer constant 
488:    NEG  3,3,3	Op unary - 
489:     LD  4,-5(1)	Pop left into ac1 
490:    TNE  3,4,3	Op != 
* THEN
* EXPRESSION
492:     LD  3,-4(1)	Load variable rand
493:     ST  3,-5(1)	Push left side 
494:    LDC  3,11(6)	Load integer constant 
495:     LD  4,-5(1)	Pop left into ac1 
496:    ADD  3,4,3	Op + 
497:     ST  3,-5(1)	Push index 
498:    LDC  3,1(6)	Load integer constant 
499:     LD  4,-5(1)	Pop index 
500:    LDA  5,-2(0)	Load address of base of array board
501:    SUB  5,5,4	Compute offset of value 
502:     LD  4,0(5)	load lhs variable board
503:    ADD  3,4,3	op += 
504:     ST  3,0(5)	Store variable board
491:    JZR  3,13(7)	Jump around the THEN if false [backpatch] 
* END IF
475:    JZR  3,29(7)	Jump around the THEN if false [backpatch] 
* END IF
* BREAK
505:    JMP  7,-372(7)	break 
* END COMPOUND
152:    JZR  3,353(7)	Jump around the THEN if false [backpatch] 
* END IF
* END COMPOUND
506:    JMP  7,-375(7)	go to beginning of loop 
134:    JMP  7,372(7)	Jump past loop [backpatch] 
* END WHILE
* EXPRESSION
507:    LDC  3,1(6)	Load integer constant 
508:     LD  4,-2(1)	load lhs variable i
509:    ADD  3,4,3	op += 
510:     ST  3,-2(1)	Store variable i
* END COMPOUND
511:    JMP  7,-387(7)	go to beginning of loop 
131:    JMP  7,380(7)	Jump past loop [backpatch] 
* END WHILE
* END COMPOUND
* Add standard closing in case there is no return statement
512:    LDC  2,0(6)	Set return value to 0 
513:     LD  3,-1(1)	Load return address 
514:     LD  1,0(1)	Adjust fp 
515:    JMP  7,0(3)	Return 
* END FUNCTION CreateBoard
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION PrintBoard
516:     ST  3,-1(1)	Store return address 
* COMPOUND
* Compound Body
* EXPRESSION
517:    LDC  3,1(6)	Load integer constant 
518:     ST  3,-2(1)	Store variable i
* EXPRESSION
* CALL outnl
519:     ST  1,-3(1)	Store fp in ghost frame for outnl
* Param end outnl
520:    LDA  1,-3(1)	Load address of new frame 
521:    LDA  3,1(7)	Return address in ac 
522:    JMP  7,-489(7)	CALL outnl
523:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* WHILE
524:     LD  3,-2(1)	Load variable i
525:     ST  3,-3(1)	Push left side 
526:    LDC  3,101(6)	Load integer constant 
527:     LD  4,-3(1)	Pop left into ac1 
528:    TLT  3,4,3	Op < 
529:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* IF
531:    LDA  3,-103(0)	Load address of base of array guess
532:     ST  3,-3(1)	Push left side 
533:     LD  3,-2(1)	Load variable i
534:     ST  3,-4(1)	Push left side 
535:    LDC  3,1(6)	Load integer constant 
536:     LD  4,-4(1)	Pop left into ac1 
537:    SUB  3,4,3	Op - 
538:     LD  4,-3(1)	Pop left into ac1 
539:    SUB  3,4,3	compute location from index 
540:     LD  3,0(3)	Load array element 
* THEN
* COMPOUND
* Compound Body
* IF
542:    LDA  3,-2(0)	Load address of base of array board
543:     ST  3,-3(1)	Push left side 
544:     LD  3,-2(1)	Load variable i
545:     ST  3,-4(1)	Push left side 
546:    LDC  3,1(6)	Load integer constant 
547:     LD  4,-4(1)	Pop left into ac1 
548:    SUB  3,4,3	Op - 
549:     LD  4,-3(1)	Pop left into ac1 
550:    SUB  3,4,3	compute location from index 
551:     LD  3,0(3)	Load array element 
552:     ST  3,-3(1)	Push left side 
553:    LDC  3,1(6)	Load integer constant 
554:    NEG  3,3,3	Op unary - 
555:     LD  4,-3(1)	Pop left into ac1 
556:    TEQ  3,4,3	Op == 
* THEN
* EXPRESSION
* CALL outputb
558:     ST  1,-3(1)	Store fp in ghost frame for outputb
* Param 1
559:    LDC  3,1(6)	Load Boolean constant 
560:     ST  3,-5(1)	Push parameter 
* Param end outputb
561:    LDA  1,-3(1)	Load address of new frame 
562:    LDA  3,1(7)	Return address in ac 
563:    JMP  7,-542(7)	CALL outputb
564:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
557:    JZR  3,8(7)	Jump around the THEN if false [backpatch] 
* ELSE
* EXPRESSION
* CALL output
566:     ST  1,-3(1)	Store fp in ghost frame for output
* Param 1
567:    LDA  3,-2(0)	Load address of base of array board
568:     ST  3,-5(1)	Push left side 
569:     LD  3,-2(1)	Load variable i
570:     ST  3,-6(1)	Push left side 
571:    LDC  3,1(6)	Load integer constant 
572:     LD  4,-6(1)	Pop left into ac1 
573:    SUB  3,4,3	Op - 
574:     LD  4,-5(1)	Pop left into ac1 
575:    SUB  3,4,3	compute location from index 
576:     LD  3,0(3)	Load array element 
577:     ST  3,-5(1)	Push parameter 
* Param end output
578:    LDA  1,-3(1)	Load address of new frame 
579:    LDA  3,1(7)	Return address in ac 
580:    JMP  7,-565(7)	CALL output
581:    LDA  3,0(2)	Save the result in ac 
* Call end output
565:    JMP  7,16(7)	Jump around the ELSE [backpatch] 
* END IF
* END COMPOUND
541:    JZR  3,41(7)	Jump around the THEN if false [backpatch] 
* ELSE
* EXPRESSION
* CALL outputb
583:     ST  1,-3(1)	Store fp in ghost frame for outputb
* Param 1
584:    LDC  3,0(6)	Load Boolean constant 
585:     ST  3,-5(1)	Push parameter 
* Param end outputb
586:    LDA  1,-3(1)	Load address of new frame 
587:    LDA  3,1(7)	Return address in ac 
588:    JMP  7,-567(7)	CALL outputb
589:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
582:    JMP  7,7(7)	Jump around the ELSE [backpatch] 
* END IF
* IF
590:     LD  3,-2(1)	Load variable i
591:     ST  3,-3(1)	Push left side 
592:    LDC  3,10(6)	Load integer constant 
593:     LD  4,-3(1)	Pop left into ac1 
594:    MOD  3,4,3	Op % 
595:     ST  3,-3(1)	Push left side 
596:    LDC  3,0(6)	Load integer constant 
597:     LD  4,-3(1)	Pop left into ac1 
598:    TEQ  3,4,3	Op == 
* THEN
* EXPRESSION
* CALL outnl
600:     ST  1,-3(1)	Store fp in ghost frame for outnl
* Param end outnl
601:    LDA  1,-3(1)	Load address of new frame 
602:    LDA  3,1(7)	Return address in ac 
603:    JMP  7,-570(7)	CALL outnl
604:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
599:    JZR  3,5(7)	Jump around the THEN if false [backpatch] 
* END IF
* EXPRESSION
605:    LDC  3,1(6)	Load integer constant 
606:     LD  4,-2(1)	load lhs variable i
607:    ADD  3,4,3	op += 
608:     ST  3,-2(1)	Store variable i
* END COMPOUND
609:    JMP  7,-86(7)	go to beginning of loop 
530:    JMP  7,79(7)	Jump past loop [backpatch] 
* END WHILE
* EXPRESSION
* CALL outnl
610:     ST  1,-3(1)	Store fp in ghost frame for outnl
* Param end outnl
611:    LDA  1,-3(1)	Load address of new frame 
612:    LDA  3,1(7)	Return address in ac 
613:    JMP  7,-580(7)	CALL outnl
614:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* END COMPOUND
* Add standard closing in case there is no return statement
615:    LDC  2,0(6)	Set return value to 0 
616:     LD  3,-1(1)	Load return address 
617:     LD  1,0(1)	Adjust fp 
618:    JMP  7,0(3)	Return 
* END FUNCTION PrintBoard
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION Move
619:     ST  3,-1(1)	Store return address 
* COMPOUND
* Compound Body
* EXPRESSION
620:     LD  3,-2(1)	Load variable m
621:     ST  3,-3(1)	Push index 
622:    LDC  3,1(6)	Load Boolean constant 
623:     LD  4,-3(1)	Pop index 
624:    LDA  5,-103(0)	Load address of base of array guess
625:    SUB  5,5,4	Compute offset of value 
626:     ST  3,0(5)	Store variable guess
* IF
627:    LDA  3,-2(0)	Load address of base of array board
628:     ST  3,-3(1)	Push left side 
629:     LD  3,-2(1)	Load variable m
630:     LD  4,-3(1)	Pop left into ac1 
631:    SUB  3,4,3	compute location from index 
632:     LD  3,0(3)	Load array element 
633:     ST  3,-3(1)	Push left side 
634:    LDC  3,0(6)	Load integer constant 
635:     LD  4,-3(1)	Pop left into ac1 
636:    TEQ  3,4,3	Op == 
* THEN
* COMPOUND
* Compound Body
* IF
638:     LD  3,-2(1)	Load variable m
639:     ST  3,-3(1)	Push left side 
640:    LDC  3,9(6)	Load integer constant 
641:     LD  4,-3(1)	Pop left into ac1 
642:    TGT  3,4,3	Op > 
* THEN
* IF
644:    LDA  3,-2(0)	Load address of base of array board
645:     ST  3,-3(1)	Push left side 
646:     LD  3,-2(1)	Load variable m
647:     ST  3,-4(1)	Push left side 
648:    LDC  3,10(6)	Load integer constant 
649:     LD  4,-4(1)	Pop left into ac1 
650:    SUB  3,4,3	Op - 
651:     LD  4,-3(1)	Pop left into ac1 
652:    SUB  3,4,3	compute location from index 
653:     LD  3,0(3)	Load array element 
654:     ST  3,-3(1)	Push left side 
655:    LDC  3,0(6)	Load integer constant 
656:     LD  4,-3(1)	Pop left into ac1 
657:    TEQ  3,4,3	Op == 
658:     ST  3,-3(1)	Push left side 
659:    LDA  3,-103(0)	Load address of base of array guess
660:     ST  3,-4(1)	Push left side 
661:     LD  3,-2(1)	Load variable m
662:     ST  3,-5(1)	Push left side 
663:    LDC  3,10(6)	Load integer constant 
664:     LD  4,-5(1)	Pop left into ac1 
665:    SUB  3,4,3	Op - 
666:     LD  4,-4(1)	Pop left into ac1 
667:    SUB  3,4,3	compute location from index 
668:     LD  3,0(3)	Load array element 
669:    LDC  4,1(6)	Load 1 
670:    XOR  3,3,4	Op XOR to get logical not 
671:     LD  4,-3(1)	Pop left into ac1 
672:    AND  3,4,3	Op AND 
* THEN
* EXPRESSION
* CALL Move
674:     ST  1,-3(1)	Store fp in ghost frame for Move
* Param 1
675:     LD  3,-2(1)	Load variable m
676:     ST  3,-5(1)	Push left side 
677:    LDC  3,10(6)	Load integer constant 
678:     LD  4,-5(1)	Pop left into ac1 
679:    SUB  3,4,3	Op - 
680:     ST  3,-5(1)	Push parameter 
* Param end Move
681:    LDA  1,-3(1)	Load address of new frame 
682:    LDA  3,1(7)	Return address in ac 
683:    JMP  7,-65(7)	CALL Move
684:    LDA  3,0(2)	Save the result in ac 
* Call end Move
673:    JZR  3,11(7)	Jump around the THEN if false [backpatch] 
* END IF
643:    JZR  3,41(7)	Jump around the THEN if false [backpatch] 
* END IF
* IF
685:     LD  3,-2(1)	Load variable m
686:     ST  3,-3(1)	Push left side 
687:    LDC  3,10(6)	Load integer constant 
688:     LD  4,-3(1)	Pop left into ac1 
689:    MOD  3,4,3	Op % 
690:     ST  3,-3(1)	Push left side 
691:    LDC  3,0(6)	Load integer constant 
692:     LD  4,-3(1)	Pop left into ac1 
693:    TNE  3,4,3	Op != 
* THEN
* IF
695:    LDA  3,-2(0)	Load address of base of array board
696:     ST  3,-3(1)	Push left side 
697:     LD  3,-2(1)	Load variable m
698:     ST  3,-4(1)	Push left side 
699:    LDC  3,1(6)	Load integer constant 
700:     LD  4,-4(1)	Pop left into ac1 
701:    SUB  3,4,3	Op - 
702:     LD  4,-3(1)	Pop left into ac1 
703:    SUB  3,4,3	compute location from index 
704:     LD  3,0(3)	Load array element 
705:     ST  3,-3(1)	Push left side 
706:    LDC  3,0(6)	Load integer constant 
707:     LD  4,-3(1)	Pop left into ac1 
708:    TEQ  3,4,3	Op == 
709:     ST  3,-3(1)	Push left side 
710:    LDA  3,-103(0)	Load address of base of array guess
711:     ST  3,-4(1)	Push left side 
712:     LD  3,-2(1)	Load variable m
713:     ST  3,-5(1)	Push left side 
714:    LDC  3,1(6)	Load integer constant 
715:     LD  4,-5(1)	Pop left into ac1 
716:    SUB  3,4,3	Op - 
717:     LD  4,-4(1)	Pop left into ac1 
718:    SUB  3,4,3	compute location from index 
719:     LD  3,0(3)	Load array element 
720:    LDC  4,1(6)	Load 1 
721:    XOR  3,3,4	Op XOR to get logical not 
722:     LD  4,-3(1)	Pop left into ac1 
723:    AND  3,4,3	Op AND 
* THEN
* EXPRESSION
* CALL Move
725:     ST  1,-3(1)	Store fp in ghost frame for Move
* Param 1
726:     LD  3,-2(1)	Load variable m
727:     ST  3,-5(1)	Push left side 
728:    LDC  3,1(6)	Load integer constant 
729:     LD  4,-5(1)	Pop left into ac1 
730:    SUB  3,4,3	Op - 
731:     ST  3,-5(1)	Push parameter 
* Param end Move
732:    LDA  1,-3(1)	Load address of new frame 
733:    LDA  3,1(7)	Return address in ac 
734:    JMP  7,-116(7)	CALL Move
735:    LDA  3,0(2)	Save the result in ac 
* Call end Move
724:    JZR  3,11(7)	Jump around the THEN if false [backpatch] 
* END IF
694:    JZR  3,41(7)	Jump around the THEN if false [backpatch] 
* END IF
* IF
736:     LD  3,-2(1)	Load variable m
737:     ST  3,-3(1)	Push left side 
738:    LDC  3,9(6)	Load integer constant 
739:     LD  4,-3(1)	Pop left into ac1 
740:    MOD  3,4,3	Op % 
741:     ST  3,-3(1)	Push left side 
742:    LDC  3,0(6)	Load integer constant 
743:     LD  4,-3(1)	Pop left into ac1 
744:    TNE  3,4,3	Op != 
745:     ST  3,-3(1)	Push left side 
746:     LD  3,-2(1)	Load variable m
747:     ST  3,-4(1)	Push left side 
748:    LDC  3,0(6)	Load integer constant 
749:     LD  4,-4(1)	Pop left into ac1 
750:    TEQ  3,4,3	Op == 
751:     LD  4,-3(1)	Pop left into ac1 
752:     OR  3,4,3	Op OR 
* THEN
* IF
754:    LDA  3,-2(0)	Load address of base of array board
755:     ST  3,-3(1)	Push left side 
756:     LD  3,-2(1)	Load variable m
757:     ST  3,-4(1)	Push left side 
758:    LDC  3,1(6)	Load integer constant 
759:     LD  4,-4(1)	Pop left into ac1 
760:    ADD  3,4,3	Op + 
761:     LD  4,-3(1)	Pop left into ac1 
762:    SUB  3,4,3	compute location from index 
763:     LD  3,0(3)	Load array element 
764:     ST  3,-3(1)	Push left side 
765:    LDC  3,0(6)	Load integer constant 
766:     LD  4,-3(1)	Pop left into ac1 
767:    TEQ  3,4,3	Op == 
768:     ST  3,-3(1)	Push left side 
769:    LDA  3,-103(0)	Load address of base of array guess
770:     ST  3,-4(1)	Push left side 
771:     LD  3,-2(1)	Load variable m
772:     ST  3,-5(1)	Push left side 
773:    LDC  3,1(6)	Load integer constant 
774:     LD  4,-5(1)	Pop left into ac1 
775:    ADD  3,4,3	Op + 
776:     LD  4,-4(1)	Pop left into ac1 
777:    SUB  3,4,3	compute location from index 
778:     LD  3,0(3)	Load array element 
779:    LDC  4,1(6)	Load 1 
780:    XOR  3,3,4	Op XOR to get logical not 
781:     LD  4,-3(1)	Pop left into ac1 
782:    AND  3,4,3	Op AND 
* THEN
* EXPRESSION
* CALL Move
784:     ST  1,-3(1)	Store fp in ghost frame for Move
* Param 1
785:     LD  3,-2(1)	Load variable m
786:     ST  3,-5(1)	Push left side 
787:    LDC  3,1(6)	Load integer constant 
788:     LD  4,-5(1)	Pop left into ac1 
789:    ADD  3,4,3	Op + 
790:     ST  3,-5(1)	Push parameter 
* Param end Move
791:    LDA  1,-3(1)	Load address of new frame 
792:    LDA  3,1(7)	Return address in ac 
793:    JMP  7,-175(7)	CALL Move
794:    LDA  3,0(2)	Save the result in ac 
* Call end Move
783:    JZR  3,11(7)	Jump around the THEN if false [backpatch] 
* END IF
753:    JZR  3,41(7)	Jump around the THEN if false [backpatch] 
* END IF
* IF
795:     LD  3,-2(1)	Load variable m
796:     ST  3,-3(1)	Push left side 
797:    LDC  3,90(6)	Load integer constant 
798:     LD  4,-3(1)	Pop left into ac1 
799:    TLT  3,4,3	Op < 
* THEN
* IF
801:    LDA  3,-2(0)	Load address of base of array board
802:     ST  3,-3(1)	Push left side 
803:     LD  3,-2(1)	Load variable m
804:     ST  3,-4(1)	Push left side 
805:    LDC  3,10(6)	Load integer constant 
806:     LD  4,-4(1)	Pop left into ac1 
807:    ADD  3,4,3	Op + 
808:     LD  4,-3(1)	Pop left into ac1 
809:    SUB  3,4,3	compute location from index 
810:     LD  3,0(3)	Load array element 
811:     ST  3,-3(1)	Push left side 
812:    LDC  3,0(6)	Load integer constant 
813:     LD  4,-3(1)	Pop left into ac1 
814:    TEQ  3,4,3	Op == 
815:     ST  3,-3(1)	Push left side 
816:    LDA  3,-103(0)	Load address of base of array guess
817:     ST  3,-4(1)	Push left side 
818:     LD  3,-2(1)	Load variable m
819:     ST  3,-5(1)	Push left side 
820:    LDC  3,10(6)	Load integer constant 
821:     LD  4,-5(1)	Pop left into ac1 
822:    ADD  3,4,3	Op + 
823:     LD  4,-4(1)	Pop left into ac1 
824:    SUB  3,4,3	compute location from index 
825:     LD  3,0(3)	Load array element 
826:    LDC  4,1(6)	Load 1 
827:    XOR  3,3,4	Op XOR to get logical not 
828:     LD  4,-3(1)	Pop left into ac1 
829:    AND  3,4,3	Op AND 
* THEN
* EXPRESSION
* CALL Move
831:     ST  1,-3(1)	Store fp in ghost frame for Move
* Param 1
832:     LD  3,-2(1)	Load variable m
833:     ST  3,-5(1)	Push left side 
834:    LDC  3,10(6)	Load integer constant 
835:     LD  4,-5(1)	Pop left into ac1 
836:    ADD  3,4,3	Op + 
837:     ST  3,-5(1)	Push parameter 
* Param end Move
838:    LDA  1,-3(1)	Load address of new frame 
839:    LDA  3,1(7)	Return address in ac 
840:    JMP  7,-222(7)	CALL Move
841:    LDA  3,0(2)	Save the result in ac 
* Call end Move
830:    JZR  3,11(7)	Jump around the THEN if false [backpatch] 
* END IF
800:    JZR  3,41(7)	Jump around the THEN if false [backpatch] 
* END IF
* END COMPOUND
637:    JZR  3,204(7)	Jump around the THEN if false [backpatch] 
* END IF
* END COMPOUND
* Add standard closing in case there is no return statement
842:    LDC  2,0(6)	Set return value to 0 
843:     LD  3,-1(1)	Load return address 
844:     LD  1,0(1)	Adjust fp 
845:    JMP  7,0(3)	Return 
* END FUNCTION Move
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION main
846:     ST  3,-1(1)	Store return address 
* COMPOUND
* Compound Body
* EXPRESSION
* CALL input
847:     ST  1,-5(1)	Store fp in ghost frame for input
* Param end input
848:    LDA  1,-5(1)	Load address of new frame 
849:    LDA  3,1(7)	Return address in ac 
850:    JMP  7,-850(7)	CALL input
851:    LDA  3,0(2)	Save the result in ac 
* Call end input
852:     ST  3,0(0)	Store variable seed
* EXPRESSION
* CALL CreateBoard
853:     ST  1,-5(1)	Store fp in ghost frame for CreateBoard
* Param end CreateBoard
854:    LDA  1,-5(1)	Load address of new frame 
855:    LDA  3,1(7)	Return address in ac 
856:    JMP  7,-777(7)	CALL CreateBoard
857:    LDA  3,0(2)	Save the result in ac 
* Call end CreateBoard
* WHILE
858:    LDC  3,1(6)	Load Boolean constant 
859:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* EXPRESSION
* CALL PrintBoard
861:     ST  1,-5(1)	Store fp in ghost frame for PrintBoard
* Param end PrintBoard
862:    LDA  1,-5(1)	Load address of new frame 
863:    LDA  3,1(7)	Return address in ac 
864:    JMP  7,-349(7)	CALL PrintBoard
865:    LDA  3,0(2)	Save the result in ac 
* Call end PrintBoard
* EXPRESSION
* CALL input
866:     ST  1,-5(1)	Store fp in ghost frame for input
* Param end input
867:    LDA  1,-5(1)	Load address of new frame 
868:    LDA  3,1(7)	Return address in ac 
869:    JMP  7,-869(7)	CALL input
870:    LDA  3,0(2)	Save the result in ac 
* Call end input
871:     ST  3,-5(1)	Push left side 
872:    LDC  3,1(6)	Load integer constant 
873:     LD  4,-5(1)	Pop left into ac1 
874:    SUB  3,4,3	Op - 
875:     ST  3,-3(1)	Store variable x
* EXPRESSION
* CALL input
876:     ST  1,-5(1)	Store fp in ghost frame for input
* Param end input
877:    LDA  1,-5(1)	Load address of new frame 
878:    LDA  3,1(7)	Return address in ac 
879:    JMP  7,-879(7)	CALL input
880:    LDA  3,0(2)	Save the result in ac 
* Call end input
881:     ST  3,-5(1)	Push left side 
882:    LDC  3,1(6)	Load integer constant 
883:     LD  4,-5(1)	Pop left into ac1 
884:    SUB  3,4,3	Op - 
885:     ST  3,-4(1)	Store variable y
* IF
886:     LD  3,-3(1)	Load variable x
887:     ST  3,-5(1)	Push left side 
888:    LDC  3,9(6)	Load integer constant 
889:     LD  4,-5(1)	Pop left into ac1 
890:    TGT  3,4,3	Op > 
891:     ST  3,-5(1)	Push left side 
892:     LD  3,-4(1)	Load variable y
893:     ST  3,-6(1)	Push left side 
894:    LDC  3,9(6)	Load integer constant 
895:     LD  4,-6(1)	Pop left into ac1 
896:    TGT  3,4,3	Op > 
897:     LD  4,-5(1)	Pop left into ac1 
898:     OR  3,4,3	Op OR 
899:     ST  3,-5(1)	Push left side 
900:     LD  3,-3(1)	Load variable x
901:     ST  3,-6(1)	Push left side 
902:    LDC  3,0(6)	Load integer constant 
903:     LD  4,-6(1)	Pop left into ac1 
904:    TLT  3,4,3	Op < 
905:     LD  4,-5(1)	Pop left into ac1 
906:     OR  3,4,3	Op OR 
907:     ST  3,-5(1)	Push left side 
908:     LD  3,-4(1)	Load variable y
909:     ST  3,-6(1)	Push left side 
910:    LDC  3,0(6)	Load integer constant 
911:     LD  4,-6(1)	Pop left into ac1 
912:    TLT  3,4,3	Op < 
913:     LD  4,-5(1)	Pop left into ac1 
914:     OR  3,4,3	Op OR 
* THEN
* COMPOUND
* Compound Body
* EXPRESSION
* CALL outputc
916:     ST  1,-5(1)	Store fp in ghost frame for outputc
* Param 1
917:    LDC  3,66(6)	Load char constant 
918:     ST  3,-7(1)	Push parameter 
* Param end outputc
919:    LDA  1,-5(1)	Load address of new frame 
920:    LDA  3,1(7)	Return address in ac 
921:    JMP  7,-894(7)	CALL outputc
922:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* EXPRESSION
* CALL outputc
923:     ST  1,-5(1)	Store fp in ghost frame for outputc
* Param 1
924:    LDC  3,89(6)	Load char constant 
925:     ST  3,-7(1)	Push parameter 
* Param end outputc
926:    LDA  1,-5(1)	Load address of new frame 
927:    LDA  3,1(7)	Return address in ac 
928:    JMP  7,-901(7)	CALL outputc
929:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* EXPRESSION
* CALL outputc
930:     ST  1,-5(1)	Store fp in ghost frame for outputc
* Param 1
931:    LDC  3,69(6)	Load char constant 
932:     ST  3,-7(1)	Push parameter 
* Param end outputc
933:    LDA  1,-5(1)	Load address of new frame 
934:    LDA  3,1(7)	Return address in ac 
935:    JMP  7,-908(7)	CALL outputc
936:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* EXPRESSION
* CALL outnl
937:     ST  1,-5(1)	Store fp in ghost frame for outnl
* Param end outnl
938:    LDA  1,-5(1)	Load address of new frame 
939:    LDA  3,1(7)	Return address in ac 
940:    JMP  7,-907(7)	CALL outnl
941:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* BREAK
942:    JMP  7,-83(7)	break 
* END COMPOUND
915:    JZR  3,27(7)	Jump around the THEN if false [backpatch] 
* END IF
* IF
943:    LDA  3,-2(0)	Load address of base of array board
944:     ST  3,-5(1)	Push left side 
945:     LD  3,-3(1)	Load variable x
946:     ST  3,-6(1)	Push left side 
947:    LDC  3,10(6)	Load integer constant 
948:     LD  4,-6(1)	Pop left into ac1 
949:    MUL  3,4,3	Op * 
950:     ST  3,-6(1)	Push left side 
951:     LD  3,-4(1)	Load variable y
952:     LD  4,-6(1)	Pop left into ac1 
953:    ADD  3,4,3	Op + 
954:     LD  4,-5(1)	Pop left into ac1 
955:    SUB  3,4,3	compute location from index 
956:     LD  3,0(3)	Load array element 
957:     ST  3,-5(1)	Push left side 
958:    LDC  3,1(6)	Load integer constant 
959:    NEG  3,3,3	Op unary - 
960:     LD  4,-5(1)	Pop left into ac1 
961:    TEQ  3,4,3	Op == 
* THEN
* COMPOUND
* Compound Body
* EXPRESSION
963:    LDC  3,0(6)	Load integer constant 
964:     ST  3,-2(1)	Store variable i
* WHILE
965:     LD  3,-2(1)	Load variable i
966:     ST  3,-5(1)	Push left side 
967:    LDC  3,100(6)	Load integer constant 
968:     LD  4,-5(1)	Pop left into ac1 
969:    TLT  3,4,3	Op < 
970:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* EXPRESSION
972:     LD  3,-2(1)	Load variable i
973:     ST  3,-5(1)	Push index 
974:    LDC  3,1(6)	Load Boolean constant 
975:     LD  4,-5(1)	Pop index 
976:    LDA  5,-103(0)	Load address of base of array guess
977:    SUB  5,5,4	Compute offset of value 
978:     ST  3,0(5)	Store variable guess
* EXPRESSION
979:    LDC  3,1(6)	Load integer constant 
980:     LD  4,-2(1)	load lhs variable i
981:    ADD  3,4,3	op += 
982:     ST  3,-2(1)	Store variable i
* END COMPOUND
983:    JMP  7,-19(7)	go to beginning of loop 
971:    JMP  7,12(7)	Jump past loop [backpatch] 
* END WHILE
* EXPRESSION
* CALL PrintBoard
984:     ST  1,-5(1)	Store fp in ghost frame for PrintBoard
* Param end PrintBoard
985:    LDA  1,-5(1)	Load address of new frame 
986:    LDA  3,1(7)	Return address in ac 
987:    JMP  7,-472(7)	CALL PrintBoard
988:    LDA  3,0(2)	Save the result in ac 
* Call end PrintBoard
* EXPRESSION
* CALL outputc
989:     ST  1,-5(1)	Store fp in ghost frame for outputc
* Param 1
990:    LDC  3,66(6)	Load char constant 
991:     ST  3,-7(1)	Push parameter 
* Param end outputc
992:    LDA  1,-5(1)	Load address of new frame 
993:    LDA  3,1(7)	Return address in ac 
994:    JMP  7,-967(7)	CALL outputc
995:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* EXPRESSION
* CALL outputc
996:     ST  1,-5(1)	Store fp in ghost frame for outputc
* Param 1
997:    LDC  3,79(6)	Load char constant 
998:     ST  3,-7(1)	Push parameter 
* Param end outputc
999:    LDA  1,-5(1)	Load address of new frame 
1000:    LDA  3,1(7)	Return address in ac 
1001:    JMP  7,-974(7)	CALL outputc
1002:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* EXPRESSION
* CALL outputc
1003:     ST  1,-5(1)	Store fp in ghost frame for outputc
* Param 1
1004:    LDC  3,79(6)	Load char constant 
1005:     ST  3,-7(1)	Push parameter 
* Param end outputc
1006:    LDA  1,-5(1)	Load address of new frame 
1007:    LDA  3,1(7)	Return address in ac 
1008:    JMP  7,-981(7)	CALL outputc
1009:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* EXPRESSION
* CALL outputc
1010:     ST  1,-5(1)	Store fp in ghost frame for outputc
* Param 1
1011:    LDC  3,77(6)	Load char constant 
1012:     ST  3,-7(1)	Push parameter 
* Param end outputc
1013:    LDA  1,-5(1)	Load address of new frame 
1014:    LDA  3,1(7)	Return address in ac 
1015:    JMP  7,-988(7)	CALL outputc
1016:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* EXPRESSION
* CALL outputc
1017:     ST  1,-5(1)	Store fp in ghost frame for outputc
* Param 1
1018:    LDC  3,33(6)	Load char constant 
1019:     ST  3,-7(1)	Push parameter 
* Param end outputc
1020:    LDA  1,-5(1)	Load address of new frame 
1021:    LDA  3,1(7)	Return address in ac 
1022:    JMP  7,-995(7)	CALL outputc
1023:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* EXPRESSION
* CALL outnl
1024:     ST  1,-5(1)	Store fp in ghost frame for outnl
* Param end outnl
1025:    LDA  1,-5(1)	Load address of new frame 
1026:    LDA  3,1(7)	Return address in ac 
1027:    JMP  7,-994(7)	CALL outnl
1028:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* BREAK
1029:    JMP  7,-170(7)	break 
* END COMPOUND
962:    JZR  3,67(7)	Jump around the THEN if false [backpatch] 
* END IF
* EXPRESSION
1030:    LDC  3,0(6)	Load integer constant 
1031:     ST  3,-2(1)	Store variable i
* WHILE
1032:    LDA  3,-103(0)	Load address of base of array guess
1033:     ST  3,-5(1)	Push left side 
1034:     LD  3,-2(1)	Load variable i
1035:     LD  4,-5(1)	Pop left into ac1 
1036:    SUB  3,4,3	compute location from index 
1037:     LD  3,0(3)	Load array element 
1038:     ST  3,-5(1)	Push left side 
1039:    LDC  3,1(6)	Load Boolean constant 
1040:     LD  4,-5(1)	Pop left into ac1 
1041:    TEQ  3,4,3	Op == 
1042:     ST  3,-5(1)	Push left side 
1043:     LD  3,-2(1)	Load variable i
1044:     ST  3,-6(1)	Push left side 
1045:    LDC  3,100(6)	Load integer constant 
1046:     LD  4,-6(1)	Pop left into ac1 
1047:    TLT  3,4,3	Op < 
1048:     LD  4,-5(1)	Pop left into ac1 
1049:    AND  3,4,3	Op AND 
1050:    JNZ  3,1(7)	Jump to while part 
* DO
* EXPRESSION
1052:    LDC  3,1(6)	Load integer constant 
1053:     LD  4,-2(1)	load lhs variable i
1054:    ADD  3,4,3	op += 
1055:     ST  3,-2(1)	Store variable i
1056:    JMP  7,-25(7)	go to beginning of loop 
1051:    JMP  7,5(7)	Jump past loop [backpatch] 
* END WHILE
* IF
1057:     LD  3,-2(1)	Load variable i
1058:     ST  3,-5(1)	Push left side 
1059:    LDC  3,100(6)	Load integer constant 
1060:     LD  4,-5(1)	Pop left into ac1 
1061:    TEQ  3,4,3	Op == 
* THEN
* COMPOUND
* Compound Body
* EXPRESSION
* CALL PrintBoard
1063:     ST  1,-5(1)	Store fp in ghost frame for PrintBoard
* Param end PrintBoard
1064:    LDA  1,-5(1)	Load address of new frame 
1065:    LDA  3,1(7)	Return address in ac 
1066:    JMP  7,-551(7)	CALL PrintBoard
1067:    LDA  3,0(2)	Save the result in ac 
* Call end PrintBoard
* EXPRESSION
* CALL outputc
1068:     ST  1,-5(1)	Store fp in ghost frame for outputc
* Param 1
1069:    LDC  3,89(6)	Load char constant 
1070:     ST  3,-7(1)	Push parameter 
* Param end outputc
1071:    LDA  1,-5(1)	Load address of new frame 
1072:    LDA  3,1(7)	Return address in ac 
1073:    JMP  7,-1046(7)	CALL outputc
1074:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* EXPRESSION
* CALL outputc
1075:     ST  1,-5(1)	Store fp in ghost frame for outputc
* Param 1
1076:    LDC  3,65(6)	Load char constant 
1077:     ST  3,-7(1)	Push parameter 
* Param end outputc
1078:    LDA  1,-5(1)	Load address of new frame 
1079:    LDA  3,1(7)	Return address in ac 
1080:    JMP  7,-1053(7)	CALL outputc
1081:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* EXPRESSION
* CALL outputc
1082:     ST  1,-5(1)	Store fp in ghost frame for outputc
* Param 1
1083:    LDC  3,89(6)	Load char constant 
1084:     ST  3,-7(1)	Push parameter 
* Param end outputc
1085:    LDA  1,-5(1)	Load address of new frame 
1086:    LDA  3,1(7)	Return address in ac 
1087:    JMP  7,-1060(7)	CALL outputc
1088:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* EXPRESSION
* CALL outputc
1089:     ST  1,-5(1)	Store fp in ghost frame for outputc
* Param 1
1090:    LDC  3,33(6)	Load char constant 
1091:     ST  3,-7(1)	Push parameter 
* Param end outputc
1092:    LDA  1,-5(1)	Load address of new frame 
1093:    LDA  3,1(7)	Return address in ac 
1094:    JMP  7,-1067(7)	CALL outputc
1095:    LDA  3,0(2)	Save the result in ac 
* Call end outputc
* EXPRESSION
* CALL outnl
1096:     ST  1,-5(1)	Store fp in ghost frame for outnl
* Param end outnl
1097:    LDA  1,-5(1)	Load address of new frame 
1098:    LDA  3,1(7)	Return address in ac 
1099:    JMP  7,-1066(7)	CALL outnl
1100:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* BREAK
1101:    JMP  7,-242(7)	break 
* END COMPOUND
1062:    JZR  3,39(7)	Jump around the THEN if false [backpatch] 
* END IF
* EXPRESSION
* CALL Move
1102:     ST  1,-5(1)	Store fp in ghost frame for Move
* Param 1
1103:     LD  3,-3(1)	Load variable x
1104:     ST  3,-7(1)	Push left side 
1105:     LD  3,-4(1)	Load variable y
1106:     ST  3,-8(1)	Push left side 
1107:    LDC  3,10(6)	Load integer constant 
1108:     LD  4,-8(1)	Pop left into ac1 
1109:    MUL  3,4,3	Op * 
1110:     LD  4,-7(1)	Pop left into ac1 
1111:    ADD  3,4,3	Op + 
1112:     ST  3,-7(1)	Push parameter 
* Param end Move
1113:    LDA  1,-5(1)	Load address of new frame 
1114:    LDA  3,1(7)	Return address in ac 
1115:    JMP  7,-497(7)	CALL Move
1116:    LDA  3,0(2)	Save the result in ac 
* Call end Move
* END COMPOUND
1117:    JMP  7,-260(7)	go to beginning of loop 
860:    JMP  7,257(7)	Jump past loop [backpatch] 
* END WHILE
* END COMPOUND
* Add standard closing in case there is no return statement
1118:    LDC  2,0(6)	Set return value to 0 
1119:     LD  3,-1(1)	Load return address 
1120:     LD  1,0(1)	Adjust fp 
1121:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,1121(7)	Jump to init [backpatch] 
* INIT
1122:     LD  0,0(0)	Set the global pointer 
1123:    LDA  1,-203(0)	set first frame at end of globals 
1124:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
1125:    LDC  3,100(6)	load size of array board
1126:     ST  3,-1(0)	save size of array board
1127:    LDC  3,100(6)	load size of array guess
1128:     ST  3,-102(0)	save size of array guess
* END INIT GLOBALS AND STATICS
1129:    LDA  3,1(7)	Return address in ac 
1130:    JMP  7,-285(7)	Jump to main 
1131:   HALT  0,0,0	DONE! 
* END INIT
