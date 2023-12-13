#ifndef _PRINTTREE_H_
#define _PRINTTREE_H_

#include <stdlib.h>
#include <stdio.h>
#include "scanType.h"
#include "ast.h"
#include "ourgetopt.h"
#include "semantic.h"
#include "symbolTable.h"
#include "yyerror.h"
#include "parser.tab.h"
#include "emitcode.h"
#include "llvm.h"

extern FILE *yyin;
// the abstract syntax tree head!
AST *tree;
// the file to put the assembly code in
FILE *code;

// prints a usage message in console
void usage();
// creates the assembly code, by first
// loading in the I/O library, then by
// calling generate() on the head.
void generate(char *, AST *, SymbolTable *);
// LLVM generation
void generateLLVM(AST *);

#endif