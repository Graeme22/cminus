# cminus
This repository contains my custom compiler for the C- language (grammar above).
The project is split into the different stages in the progress of the compiler, so each assignment builds on the previous one.

Documentation is pretty lacking except on ass7, which contains decent documentation on just about everything.
Since each assignment builds on the previous one, I'd recommend looking at ass7's documentation even while working on earlier assignments, as it should still be relevant and helpful.

Notably, some parts of the language were intentionally omitted from the initial language description *for the last assignment (ass7) ONLY*.
This includes `for` loops, `static` variables, and array initialization, as well as some array operations.
However everything else should be fully functional. If you run into any unexpected behavior, please open an issue.

C- is intended for educational purposes; however, with slight modifications it could easily be modified to fun on x86_64 processors.
As is, it uses the Tiny virtual machine (binary included) which is essentially a very simple 32-bit processor.
The behavior of the Tiny Machine (TM) is provided in the attached tmDescription pdf.

### Usage

For any given assignment, simply use the provided makefile to build the `c-` executable.
Then you may run it to produce output, for example:
```
./c- test.c-
```
In the final stage (ass7), this will produce a .tm output file with the Tiny assembly code, which can then be ran with:
```
echo "gq" | ./tm test.tm
```
Valid flags for C-:
- -d	Turn on yydebug for parser debugging
- -S	Turn on symbol table debugging
- -P	Print the abstract syntax tree
- -M	Print the abstract syntax tree with memory allocation information
- -h	Help
