* C- compiler version C-F20
* Built: Nov 19, 2020
* Author: Robert B. Heckendorn
* File compiled:  fractal.c-
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
* FUNCTION Mandelbrot
 39:     ST  3,-1(1)	Store return address 
* COMPOUND
* Compound Body
* WHILE
 40:     LD  3,0(0)	Load variable TOP
 41:     ST  3,-3(1)	Push left side 
 42:     LD  3,-7(0)	Load variable YMax
 43:     LD  4,-3(1)	Pop left into ac1 
 44:    TLT  3,4,3	Op < 
 45:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* EXPRESSION
 47:    LDC  3,512(6)	Load integer constant 
 48:    NEG  3,3,3	Op unary - 
 49:     ST  3,-1(0)	Store variable LEFT
* WHILE
 50:     LD  3,-1(0)	Load variable LEFT
 51:     ST  3,-3(1)	Push left side 
 52:     LD  3,-6(0)	Load variable XMax
 53:     LD  4,-3(1)	Pop left into ac1 
 54:    TLT  3,4,3	Op < 
 55:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* EXPRESSION
 57:     LD  3,-1(0)	Load variable LEFT
 58:     ST  3,-5(1)	Store variable A
* EXPRESSION
 59:     LD  3,0(0)	Load variable TOP
 60:     ST  3,-4(1)	Store variable Bi
* EXPRESSION
 61:     LD  3,-5(1)	Load variable A
 62:     ST  3,-8(1)	Push left side 
 63:     LD  3,-5(1)	Load variable A
 64:     LD  4,-8(1)	Pop left into ac1 
 65:    MUL  3,4,3	Op * 
 66:     ST  3,-8(1)	Push left side 
 67:    LDC  3,256(6)	Load integer constant 
 68:     LD  4,-8(1)	Pop left into ac1 
 69:    DIV  3,4,3	Op / 
 70:     ST  3,-6(1)	Store variable NextA
* EXPRESSION
 71:     LD  3,-4(1)	Load variable Bi
 72:     ST  3,-8(1)	Push left side 
 73:     LD  3,-4(1)	Load variable Bi
 74:     LD  4,-8(1)	Pop left into ac1 
 75:    MUL  3,4,3	Op * 
 76:     ST  3,-8(1)	Push left side 
 77:    LDC  3,256(6)	Load integer constant 
 78:     LD  4,-8(1)	Pop left into ac1 
 79:    DIV  3,4,3	Op / 
 80:     ST  3,-7(1)	Store variable NextBi
* EXPRESSION
 81:     LD  3,-6(1)	Load variable NextA
 82:     ST  3,-8(1)	Push left side 
 83:     LD  3,-7(1)	Load variable NextBi
 84:     LD  4,-8(1)	Pop left into ac1 
 85:    ADD  3,4,3	Op + 
 86:     ST  3,-3(1)	Store variable Len
* EXPRESSION
 87:    LDC  3,0(6)	Load integer constant 
 88:     ST  3,-8(0)	Store variable iter
* WHILE
 89:     LD  3,-3(1)	Load variable Len
 90:     ST  3,-8(1)	Push left side 
 91:    LDC  3,1024(6)	Load integer constant 
 92:     LD  4,-8(1)	Pop left into ac1 
 93:    TLE  3,4,3	Op <= 
 94:     ST  3,-8(1)	Push left side 
 95:     LD  3,-8(0)	Load variable iter
 96:     ST  3,-9(1)	Push left side 
 97:    LDC  3,11(6)	Load integer constant 
 98:     LD  4,-9(1)	Pop left into ac1 
 99:    TLT  3,4,3	Op < 
100:     LD  4,-8(1)	Pop left into ac1 
101:    AND  3,4,3	Op AND 
102:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* EXPRESSION
104:    LDC  3,2(6)	Load integer constant 
105:     ST  3,-8(1)	Push left side 
106:     LD  3,-5(1)	Load variable A
107:     ST  3,-9(1)	Push left side 
108:     LD  3,-4(1)	Load variable Bi
109:     LD  4,-9(1)	Pop left into ac1 
110:    MUL  3,4,3	Op * 
111:     LD  4,-8(1)	Pop left into ac1 
112:    MUL  3,4,3	Op * 
113:     ST  3,-8(1)	Push left side 
114:    LDC  3,256(6)	Load integer constant 
115:     LD  4,-8(1)	Pop left into ac1 
116:    DIV  3,4,3	Op / 
117:     ST  3,-8(1)	Push left side 
118:     LD  3,0(0)	Load variable TOP
119:     LD  4,-8(1)	Pop left into ac1 
120:    ADD  3,4,3	Op + 
121:     ST  3,-4(1)	Store variable Bi
* EXPRESSION
122:     LD  3,-6(1)	Load variable NextA
123:     ST  3,-8(1)	Push left side 
124:     LD  3,-7(1)	Load variable NextBi
125:     LD  4,-8(1)	Pop left into ac1 
126:    SUB  3,4,3	Op - 
127:     ST  3,-8(1)	Push left side 
128:     LD  3,-1(0)	Load variable LEFT
129:     LD  4,-8(1)	Pop left into ac1 
130:    ADD  3,4,3	Op + 
131:     ST  3,-5(1)	Store variable A
* EXPRESSION
132:     LD  3,-5(1)	Load variable A
133:     ST  3,-8(1)	Push left side 
134:     LD  3,-5(1)	Load variable A
135:     LD  4,-8(1)	Pop left into ac1 
136:    MUL  3,4,3	Op * 
137:     ST  3,-8(1)	Push left side 
138:    LDC  3,256(6)	Load integer constant 
139:     LD  4,-8(1)	Pop left into ac1 
140:    DIV  3,4,3	Op / 
141:     ST  3,-6(1)	Store variable NextA
* EXPRESSION
142:     LD  3,-4(1)	Load variable Bi
143:     ST  3,-8(1)	Push left side 
144:     LD  3,-4(1)	Load variable Bi
145:     LD  4,-8(1)	Pop left into ac1 
146:    MUL  3,4,3	Op * 
147:     ST  3,-8(1)	Push left side 
148:    LDC  3,256(6)	Load integer constant 
149:     LD  4,-8(1)	Pop left into ac1 
150:    DIV  3,4,3	Op / 
151:     ST  3,-7(1)	Store variable NextBi
* EXPRESSION
152:     LD  3,-6(1)	Load variable NextA
153:     ST  3,-8(1)	Push left side 
154:     LD  3,-7(1)	Load variable NextBi
155:     LD  4,-8(1)	Pop left into ac1 
156:    ADD  3,4,3	Op + 
157:     ST  3,-3(1)	Store variable Len
* EXPRESSION
158:     LD  3,-8(0)	load lhs variable iter
159:    LDA  3,1(3)	increment value of iter
160:     ST  3,-8(0)	Store variable iter
* END COMPOUND
161:    JMP  7,-73(7)	go to beginning of loop 
103:    JMP  7,58(7)	Jump past loop [backpatch] 
* END WHILE
* IF
162:     LD  3,-8(0)	Load variable iter
163:     ST  3,-8(1)	Push left side 
164:    LDC  3,10(6)	Load integer constant 
165:     LD  4,-8(1)	Pop left into ac1 
166:    TLT  3,4,3	Op < 
* THEN
* EXPRESSION
* CALL output
168:     ST  1,-8(1)	Store fp in ghost frame for output
* Param 1
169:     LD  3,-8(0)	Load variable iter
170:     ST  3,-10(1)	Push parameter 
* Param end output
171:    LDA  1,-8(1)	Load address of new frame 
172:    LDA  3,1(7)	Return address in ac 
173:    JMP  7,-158(7)	CALL output
174:    LDA  3,0(2)	Save the result in ac 
* Call end output
167:    JZR  3,8(7)	Jump around the THEN if false [backpatch] 
* ELSE
* EXPRESSION
* CALL outputb
176:     ST  1,-8(1)	Store fp in ghost frame for outputb
* Param 1
177:     LD  3,-8(0)	Load variable iter
178:     ST  3,-10(1)	Push left side 
179:    LDC  3,11(6)	Load integer constant 
180:     LD  4,-10(1)	Pop left into ac1 
181:    TEQ  3,4,3	Op == 
182:     ST  3,-10(1)	Push parameter 
* Param end outputb
183:    LDA  1,-8(1)	Load address of new frame 
184:    LDA  3,1(7)	Return address in ac 
185:    JMP  7,-164(7)	CALL outputb
186:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
175:    JMP  7,11(7)	Jump around the ELSE [backpatch] 
* END IF
* IF
187:     LD  3,-8(0)	Load variable iter
188:     ST  3,-8(1)	Push left side 
189:    LDC  3,11(6)	Load integer constant 
190:     LD  4,-8(1)	Pop left into ac1 
191:    TEQ  3,4,3	Op == 
* THEN
* COMPOUND
* Compound Body
* EXPRESSION
193:    LDC  3,0(6)	Load integer constant 
194:     ST  3,-8(1)	Push index 
195:     LD  3,-1(0)	Load variable LEFT
196:     LD  4,-8(1)	Pop index 
197:     LD  5,-2(1)	Load address of base of array JuliaVals
198:    SUB  5,5,4	Compute offset of value 
199:     ST  3,0(5)	Store variable JuliaVals
* EXPRESSION
200:    LDC  3,1(6)	Load integer constant 
201:     ST  3,-8(1)	Push index 
202:     LD  3,0(0)	Load variable TOP
203:     LD  4,-8(1)	Pop index 
204:     LD  5,-2(1)	Load address of base of array JuliaVals
205:    SUB  5,5,4	Compute offset of value 
206:     ST  3,0(5)	Store variable JuliaVals
* END COMPOUND
192:    JZR  3,14(7)	Jump around the THEN if false [backpatch] 
* END IF
* EXPRESSION
207:     LD  3,-4(0)	Load variable XStep
208:     LD  4,-1(0)	load lhs variable LEFT
209:    ADD  3,4,3	op += 
210:     ST  3,-1(0)	Store variable LEFT
* END COMPOUND
211:    JMP  7,-162(7)	go to beginning of loop 
 56:    JMP  7,155(7)	Jump past loop [backpatch] 
* END WHILE
* EXPRESSION
* CALL outnl
212:     ST  1,-3(1)	Store fp in ghost frame for outnl
* Param end outnl
213:    LDA  1,-3(1)	Load address of new frame 
214:    LDA  3,1(7)	Return address in ac 
215:    JMP  7,-182(7)	CALL outnl
216:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* EXPRESSION
217:     LD  3,-5(0)	Load variable YStep
218:     LD  4,0(0)	load lhs variable TOP
219:    ADD  3,4,3	op += 
220:     ST  3,0(0)	Store variable TOP
* END COMPOUND
221:    JMP  7,-182(7)	go to beginning of loop 
 46:    JMP  7,175(7)	Jump past loop [backpatch] 
* END WHILE
* END COMPOUND
* Add standard closing in case there is no return statement
222:    LDC  2,0(6)	Set return value to 0 
223:     LD  3,-1(1)	Load return address 
224:     LD  1,0(1)	Adjust fp 
225:    JMP  7,0(3)	Return 
* END FUNCTION Mandelbrot
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION Julia
226:     ST  3,-1(1)	Store return address 
* COMPOUND
* Compound Body
* WHILE
227:     LD  3,0(0)	Load variable TOP
228:     ST  3,-4(1)	Push left side 
229:     LD  3,-7(0)	Load variable YMax
230:     LD  4,-4(1)	Pop left into ac1 
231:    TLT  3,4,3	Op < 
232:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* EXPRESSION
234:    LDC  3,512(6)	Load integer constant 
235:    NEG  3,3,3	Op unary - 
236:     ST  3,-1(0)	Store variable LEFT
* WHILE
237:     LD  3,-1(0)	Load variable LEFT
238:     ST  3,-4(1)	Push left side 
239:     LD  3,-6(0)	Load variable XMax
240:     LD  4,-4(1)	Pop left into ac1 
241:    TLT  3,4,3	Op < 
242:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* EXPRESSION
244:     LD  3,-1(0)	Load variable LEFT
245:     ST  3,-6(1)	Store variable A
* EXPRESSION
246:     LD  3,0(0)	Load variable TOP
247:     ST  3,-5(1)	Store variable Bi
* EXPRESSION
248:     LD  3,-6(1)	Load variable A
249:     ST  3,-9(1)	Push left side 
250:     LD  3,-6(1)	Load variable A
251:     LD  4,-9(1)	Pop left into ac1 
252:    MUL  3,4,3	Op * 
253:     ST  3,-9(1)	Push left side 
254:    LDC  3,256(6)	Load integer constant 
255:     LD  4,-9(1)	Pop left into ac1 
256:    DIV  3,4,3	Op / 
257:     ST  3,-7(1)	Store variable NextA
* EXPRESSION
258:     LD  3,-5(1)	Load variable Bi
259:     ST  3,-9(1)	Push left side 
260:     LD  3,-5(1)	Load variable Bi
261:     LD  4,-9(1)	Pop left into ac1 
262:    MUL  3,4,3	Op * 
263:     ST  3,-9(1)	Push left side 
264:    LDC  3,256(6)	Load integer constant 
265:     LD  4,-9(1)	Pop left into ac1 
266:    DIV  3,4,3	Op / 
267:     ST  3,-8(1)	Store variable NextBi
* EXPRESSION
268:     LD  3,-7(1)	Load variable NextA
269:     ST  3,-9(1)	Push left side 
270:     LD  3,-8(1)	Load variable NextBi
271:     LD  4,-9(1)	Pop left into ac1 
272:    ADD  3,4,3	Op + 
273:     ST  3,-4(1)	Store variable Len
* EXPRESSION
274:    LDC  3,0(6)	Load integer constant 
275:     ST  3,-8(0)	Store variable iter
* WHILE
276:     LD  3,-4(1)	Load variable Len
277:     ST  3,-9(1)	Push left side 
278:    LDC  3,1024(6)	Load integer constant 
279:     LD  4,-9(1)	Pop left into ac1 
280:    TLE  3,4,3	Op <= 
281:     ST  3,-9(1)	Push left side 
282:     LD  3,-8(0)	Load variable iter
283:     ST  3,-10(1)	Push left side 
284:    LDC  3,11(6)	Load integer constant 
285:     LD  4,-10(1)	Pop left into ac1 
286:    TLT  3,4,3	Op < 
287:     LD  4,-9(1)	Pop left into ac1 
288:    AND  3,4,3	Op AND 
289:    JNZ  3,1(7)	Jump to while part 
* DO
* COMPOUND
* Compound Body
* EXPRESSION
291:    LDC  3,2(6)	Load integer constant 
292:     ST  3,-9(1)	Push left side 
293:     LD  3,-6(1)	Load variable A
294:     ST  3,-10(1)	Push left side 
295:     LD  3,-5(1)	Load variable Bi
296:     LD  4,-10(1)	Pop left into ac1 
297:    MUL  3,4,3	Op * 
298:     LD  4,-9(1)	Pop left into ac1 
299:    MUL  3,4,3	Op * 
300:     ST  3,-9(1)	Push left side 
301:    LDC  3,256(6)	Load integer constant 
302:     LD  4,-9(1)	Pop left into ac1 
303:    DIV  3,4,3	Op / 
304:     ST  3,-9(1)	Push left side 
305:     LD  3,-3(1)	Load variable CBi
306:     LD  4,-9(1)	Pop left into ac1 
307:    ADD  3,4,3	Op + 
308:     ST  3,-5(1)	Store variable Bi
* EXPRESSION
309:     LD  3,-7(1)	Load variable NextA
310:     ST  3,-9(1)	Push left side 
311:     LD  3,-8(1)	Load variable NextBi
312:     LD  4,-9(1)	Pop left into ac1 
313:    SUB  3,4,3	Op - 
314:     ST  3,-9(1)	Push left side 
315:     LD  3,-2(1)	Load variable CA
316:     LD  4,-9(1)	Pop left into ac1 
317:    ADD  3,4,3	Op + 
318:     ST  3,-6(1)	Store variable A
* EXPRESSION
319:     LD  3,-6(1)	Load variable A
320:     ST  3,-9(1)	Push left side 
321:     LD  3,-6(1)	Load variable A
322:     LD  4,-9(1)	Pop left into ac1 
323:    MUL  3,4,3	Op * 
324:     ST  3,-9(1)	Push left side 
325:    LDC  3,256(6)	Load integer constant 
326:     LD  4,-9(1)	Pop left into ac1 
327:    DIV  3,4,3	Op / 
328:     ST  3,-7(1)	Store variable NextA
* EXPRESSION
329:     LD  3,-5(1)	Load variable Bi
330:     ST  3,-9(1)	Push left side 
331:     LD  3,-5(1)	Load variable Bi
332:     LD  4,-9(1)	Pop left into ac1 
333:    MUL  3,4,3	Op * 
334:     ST  3,-9(1)	Push left side 
335:    LDC  3,256(6)	Load integer constant 
336:     LD  4,-9(1)	Pop left into ac1 
337:    DIV  3,4,3	Op / 
338:     ST  3,-8(1)	Store variable NextBi
* EXPRESSION
339:     LD  3,-7(1)	Load variable NextA
340:     ST  3,-9(1)	Push left side 
341:     LD  3,-8(1)	Load variable NextBi
342:     LD  4,-9(1)	Pop left into ac1 
343:    ADD  3,4,3	Op + 
344:     ST  3,-4(1)	Store variable Len
* EXPRESSION
345:     LD  3,-8(0)	load lhs variable iter
346:    LDA  3,1(3)	increment value of iter
347:     ST  3,-8(0)	Store variable iter
* END COMPOUND
348:    JMP  7,-73(7)	go to beginning of loop 
290:    JMP  7,58(7)	Jump past loop [backpatch] 
* END WHILE
* IF
349:     LD  3,-8(0)	Load variable iter
350:     ST  3,-9(1)	Push left side 
351:    LDC  3,10(6)	Load integer constant 
352:     LD  4,-9(1)	Pop left into ac1 
353:    TLT  3,4,3	Op < 
* THEN
* EXPRESSION
* CALL output
355:     ST  1,-9(1)	Store fp in ghost frame for output
* Param 1
356:     LD  3,-8(0)	Load variable iter
357:     ST  3,-11(1)	Push parameter 
* Param end output
358:    LDA  1,-9(1)	Load address of new frame 
359:    LDA  3,1(7)	Return address in ac 
360:    JMP  7,-345(7)	CALL output
361:    LDA  3,0(2)	Save the result in ac 
* Call end output
354:    JZR  3,8(7)	Jump around the THEN if false [backpatch] 
* ELSE
* EXPRESSION
* CALL outputb
363:     ST  1,-9(1)	Store fp in ghost frame for outputb
* Param 1
364:     LD  3,-8(0)	Load variable iter
365:     ST  3,-11(1)	Push left side 
366:    LDC  3,11(6)	Load integer constant 
367:     LD  4,-11(1)	Pop left into ac1 
368:    TEQ  3,4,3	Op == 
369:     ST  3,-11(1)	Push parameter 
* Param end outputb
370:    LDA  1,-9(1)	Load address of new frame 
371:    LDA  3,1(7)	Return address in ac 
372:    JMP  7,-351(7)	CALL outputb
373:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
362:    JMP  7,11(7)	Jump around the ELSE [backpatch] 
* END IF
* EXPRESSION
374:     LD  3,-4(0)	Load variable XStep
375:     LD  4,-1(0)	load lhs variable LEFT
376:    ADD  3,4,3	op += 
377:     ST  3,-1(0)	Store variable LEFT
* END COMPOUND
378:    JMP  7,-142(7)	go to beginning of loop 
243:    JMP  7,135(7)	Jump past loop [backpatch] 
* END WHILE
* EXPRESSION
* CALL outnl
379:     ST  1,-4(1)	Store fp in ghost frame for outnl
* Param end outnl
380:    LDA  1,-4(1)	Load address of new frame 
381:    LDA  3,1(7)	Return address in ac 
382:    JMP  7,-349(7)	CALL outnl
383:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* EXPRESSION
384:     LD  3,-5(0)	Load variable YStep
385:     LD  4,0(0)	load lhs variable TOP
386:    ADD  3,4,3	op += 
387:     ST  3,0(0)	Store variable TOP
* END COMPOUND
388:    JMP  7,-162(7)	go to beginning of loop 
233:    JMP  7,155(7)	Jump past loop [backpatch] 
* END WHILE
* END COMPOUND
* Add standard closing in case there is no return statement
389:    LDC  2,0(6)	Set return value to 0 
390:     LD  3,-1(1)	Load return address 
391:     LD  1,0(1)	Adjust fp 
392:    JMP  7,0(3)	Return 
* END FUNCTION Julia
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION main
393:     ST  3,-1(1)	Store return address 
* COMPOUND
394:    LDC  3,2(6)	load size of array JuliaVals
395:     ST  3,-2(1)	save size of array JuliaVals
* Compound Body
* EXPRESSION
396:    LDC  3,320(6)	Load integer constant 
397:    NEG  3,3,3	Op unary - 
398:     ST  3,0(0)	Store variable TOP
* EXPRESSION
399:    LDC  3,512(6)	Load integer constant 
400:    NEG  3,3,3	Op unary - 
401:     ST  3,-1(0)	Store variable LEFT
* EXPRESSION
402:    LDC  3,640(6)	Load integer constant 
403:     ST  3,-2(0)	Store variable HEIGHT
* EXPRESSION
404:    LDC  3,716(6)	Load integer constant 
405:     ST  3,-3(0)	Store variable WIDTH
* EXPRESSION
406:     LD  3,-3(0)	Load variable WIDTH
407:     ST  3,-5(1)	Push left side 
408:    LDC  3,40(6)	Load integer constant 
409:     LD  4,-5(1)	Pop left into ac1 
410:    DIV  3,4,3	Op / 
411:     ST  3,-4(0)	Store variable XStep
* EXPRESSION
412:     LD  3,-2(0)	Load variable HEIGHT
413:     ST  3,-5(1)	Push left side 
414:    LDC  3,36(6)	Load integer constant 
415:     LD  4,-5(1)	Pop left into ac1 
416:    DIV  3,4,3	Op / 
417:     ST  3,-5(0)	Store variable YStep
* EXPRESSION
418:     LD  3,-1(0)	Load variable LEFT
419:     ST  3,-5(1)	Push left side 
420:     LD  3,-3(0)	Load variable WIDTH
421:     LD  4,-5(1)	Pop left into ac1 
422:    ADD  3,4,3	Op + 
423:     ST  3,-6(0)	Store variable XMax
* EXPRESSION
424:     LD  3,0(0)	Load variable TOP
425:     ST  3,-5(1)	Push left side 
426:     LD  3,-2(0)	Load variable HEIGHT
427:     LD  4,-5(1)	Pop left into ac1 
428:    ADD  3,4,3	Op + 
429:     ST  3,-7(0)	Store variable YMax
* EXPRESSION
* CALL Mandelbrot
430:     ST  1,-5(1)	Store fp in ghost frame for Mandelbrot
* Param 1
431:    LDA  3,-3(1)	Load address of base of array JuliaVals
432:     ST  3,-7(1)	Push parameter 
* Param end Mandelbrot
433:    LDA  1,-5(1)	Load address of new frame 
434:    LDA  3,1(7)	Return address in ac 
435:    JMP  7,-397(7)	CALL Mandelbrot
436:    LDA  3,0(2)	Save the result in ac 
* Call end Mandelbrot
* EXPRESSION
* CALL outnl
437:     ST  1,-5(1)	Store fp in ghost frame for outnl
* Param end outnl
438:    LDA  1,-5(1)	Load address of new frame 
439:    LDA  3,1(7)	Return address in ac 
440:    JMP  7,-407(7)	CALL outnl
441:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* EXPRESSION
442:    LDC  3,320(6)	Load integer constant 
443:    NEG  3,3,3	Op unary - 
444:     ST  3,0(0)	Store variable TOP
* EXPRESSION
445:    LDC  3,512(6)	Load integer constant 
446:    NEG  3,3,3	Op unary - 
447:     ST  3,-1(0)	Store variable LEFT
* EXPRESSION
448:    LDC  3,640(6)	Load integer constant 
449:     ST  3,-2(0)	Store variable HEIGHT
* EXPRESSION
450:    LDC  3,716(6)	Load integer constant 
451:     ST  3,-3(0)	Store variable WIDTH
* EXPRESSION
452:     LD  3,-3(0)	Load variable WIDTH
453:     ST  3,-5(1)	Push left side 
454:    LDC  3,40(6)	Load integer constant 
455:     LD  4,-5(1)	Pop left into ac1 
456:    DIV  3,4,3	Op / 
457:     ST  3,-4(0)	Store variable XStep
* EXPRESSION
458:     LD  3,-2(0)	Load variable HEIGHT
459:     ST  3,-5(1)	Push left side 
460:    LDC  3,36(6)	Load integer constant 
461:     LD  4,-5(1)	Pop left into ac1 
462:    DIV  3,4,3	Op / 
463:     ST  3,-5(0)	Store variable YStep
* EXPRESSION
464:     LD  3,-1(0)	Load variable LEFT
465:     ST  3,-5(1)	Push left side 
466:     LD  3,-3(0)	Load variable WIDTH
467:     LD  4,-5(1)	Pop left into ac1 
468:    ADD  3,4,3	Op + 
469:     ST  3,-6(0)	Store variable XMax
* EXPRESSION
470:     LD  3,0(0)	Load variable TOP
471:     ST  3,-5(1)	Push left side 
472:     LD  3,-2(0)	Load variable HEIGHT
473:     LD  4,-5(1)	Pop left into ac1 
474:    ADD  3,4,3	Op + 
475:     ST  3,-7(0)	Store variable YMax
* EXPRESSION
* CALL Julia
476:     ST  1,-5(1)	Store fp in ghost frame for Julia
* Param 1
477:    LDA  3,-3(1)	Load address of base of array JuliaVals
478:     ST  3,-7(1)	Push left side 
479:    LDC  3,0(6)	Load integer constant 
480:     LD  4,-7(1)	Pop left into ac1 
481:    SUB  3,4,3	compute location from index 
482:     LD  3,0(3)	Load array element 
483:     ST  3,-7(1)	Push parameter 
* Param 2
484:    LDA  3,-3(1)	Load address of base of array JuliaVals
485:     ST  3,-8(1)	Push left side 
486:    LDC  3,1(6)	Load integer constant 
487:     LD  4,-8(1)	Pop left into ac1 
488:    SUB  3,4,3	compute location from index 
489:     LD  3,0(3)	Load array element 
490:     ST  3,-8(1)	Push parameter 
* Param end Julia
491:    LDA  1,-5(1)	Load address of new frame 
492:    LDA  3,1(7)	Return address in ac 
493:    JMP  7,-268(7)	CALL Julia
494:    LDA  3,0(2)	Save the result in ac 
* Call end Julia
* END COMPOUND
* Add standard closing in case there is no return statement
495:    LDC  2,0(6)	Set return value to 0 
496:     LD  3,-1(1)	Load return address 
497:     LD  1,0(1)	Adjust fp 
498:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,498(7)	Jump to init [backpatch] 
* INIT
499:     LD  0,0(0)	Set the global pointer 
500:    LDA  1,-9(0)	set first frame at end of globals 
501:     ST  1,0(1)	store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
502:    LDA  3,1(7)	Return address in ac 
503:    JMP  7,-111(7)	Jump to main 
504:   HALT  0,0,0	DONE! 
* END INIT
