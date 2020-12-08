* FUNCTION dog
42: ST 3,-1(1) Store return address.
* COMPOUND
* EXPRESSION
43: LD 3,-2(1) Load variable x
44: ST 3,-5(1) Save left side
45: LDC 3,111(6) Load constant
46: LD 4,-5(1) Load left into ac1
47: MUL 3,4,3 Op *
48: ST 3,-5(1) Save left side
49: LDC 3,222(6) Load constant
50: LD 4,-5(1) Load left into ac1
51: ADD 3,4,3 Op +
52: ST 3,-3(1) Store variable y
* EXPRESSION
53: LD 3,-3(1) Load variable y
54: ST 3,-4(1) Store variable z
* RETURN
55: LD 3,-4(1) Load variable z
56: LDA 2,0(3) Copy result to rt register
57: LD 3,-1(1) Load return address
58: LD 1,0(1) Adjust fp
59: LDA 7,0(3) Return
* END COMPOUND
* Add standard closing in case there is no return statement
60: LDC 2,0(6) Set return value to 0
61: LD 3,-1(1) Load return address
62: LD 1,0(1) Adjust fp
63: LDA 7,0(3) Return
* END FUNCTION dog
* FUNCTION main
64: ST 3,-1(1) Store return address.
* COMPOUND
* EXPRESSION
* Begin call to output
65: ST 1,-2(1) Store old fp in ghost frame
* Load param 1
* Begin call to dog
66: ST 1,-4(1) Store old fp in ghost frame
* Load param 1
67: LDC 3,666(6) Load constant
68: ST 3,-6(1) Store parameter
* Jump to dog
69: LDA 1,-4(1) Load address of new frame
70: LDA 3,1(7) Return address in ac
71: LDA 7,-30(7) CALL dog
72: LDA 3,0(2) Save the result in ac
* End call to dog
73: ST 3,-4(1) Store parameter
* Jump to output
74: LDA 1,-2(1) Load address of new frame
75: LDA 3,1(7) Return address in ac
76: LDA 7,-71(7) CALL output
77: LDA 3,0(2) Save the result in ac
* End call to output
* EXPRESSION
* Begin call to outnl
78: ST 1,-2(1) Store old fp in ghost frame
* Jump to outnl
79: LDA 1,-2(1) Load address of new frame
80: LDA 3,1(7) Return address in ac
81: LDA 7,-45(7) CALL outnl
82: LDA 3,0(2) Save the result in ac
* End call to outnl
* END COMPOUND
* Add standard closing in case there is no return statement
83: LDC 2,0(6) Set return value to 0
84: LD 3,-1(1) Load return address
85: LD 1,0(1) Adjust fp
86: LDA 7,0(3) Return
* END FUNCTION main
0: LDA 7,86(7) Jump to init [backpatch]
* INIT
87: LD 0,0(0) Set the global pointer
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
88: LDA 1,0(0) set first frame at end of globals
89: ST 1,0(1) store old fp (point to self)
90: LDA 3,1(7) Return address in ac
91: LDA 7,-28(7) Jump to main
92: HALT 0,0,0 DONE!
* END INIT