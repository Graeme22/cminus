#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_

#include "ast.h"
#include "var.h"
#include "exp.h"
#include "fun.h"
#include "scanType.h"
#include "symbolTable.h"

// perform semantic analysis on the AST.
// first loads I/O symbols into the table,
// then calls propagateScopes() on the head.
void analyze(AST *, SymbolTable *);
// designed to be called by SyntaxTable::applyToAll()
// checks to see if created vars were ever used
// if not, a warning is issued
void checkUsage(std::string, void *);
// builds a "dummy" symbol, used to
// construct the I/O symbols
TokenData *buildDummy(char *);

#endif