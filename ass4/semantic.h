#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_

#include "ast.h"
#include "var.h"
#include "exp.h"
#include "fun.h"
#include "scanType.h"
#include "symbolTable.h"

void analyze(AST *, SymbolTable *);
void checkUsage(std::string, void *);
TokenData *buildDummy(char *);

#endif