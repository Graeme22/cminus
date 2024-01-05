# cminus
This repository contains my custom compiler for the C- language.

Notably, some parts of the language were intentionally omitted from the initial language description in the final stage. This includes `for` loops, `static` variables, and array initialization.

C- by default compiles for the Tiny virtual machine (binary can be created with `make tm`) which is essentially a very simple 32-bit processor. The behavior of the Tiny Machine (TM) is described in the `docs` folder.
However, you can also compile to LLVM using the `-l` flag (described below) to run on many different architectures.

### Usage

Use the provided makefile to build the `c-` executable.
Then you may run it to produce output, for example:
```
./c- test.c-
```
This will produce a .tm output file with the Tiny assembly code, which can then be run with:
```
echo "gq" | ./tm test.tm
```

To use the c- executable, run `./c- [flags] [source]`.
Valid flags for c-:
- d: Turn on yydebug for parser debugging
- s: Turn on symbol table debugging
- p: Print the abstract syntax tree with types
- m: Print the abstract syntax tree with memory allocation information
- l: Generate code for LLVM instead of for Tiny Machine
- h: Help
