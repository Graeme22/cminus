#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_

#include "ast.h"
#include "symbolTable.h"

void analyze(AST *, SymbolTable *);
void printNode(void *);

#endif