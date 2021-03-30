# cminus
This repository contains my custom compiler for the C- language.

Notably, some parts of the language were intentionally omitted from the initial language description in the final stage.
This includes `for` loops, `static` variables, and array initialization, as well as some array operations.
However everything else should be fully functional. If you run into any unexpected behavior, please open an issue.

C- is intended for educational purposes; however, with slight modifications it could easily be modified to run on x86_64 processors.
As is, it uses the Tiny virtual machine (binary included) which is essentially a very simple 32-bit processor.
The behavior of the Tiny Machine (TM) is described in the `docs` folder.

### Usage

Use the provided makefile to build the `c-` executable.
Then you may run it to produce output, for example:
```
./c- test.c-
```
This will produce a .tm output file with the Tiny assembly code, which can then be ran with:
```
echo "gq" | ./tm test.tm
```
Valid flags for c-:
-d    Turn on yydebug for parser debugging
-S    Turn on symbol table debugging
-P    Print the abstract syntax tree
-M    Print the abstract syntax tree with memory allocation information
-h    Help
