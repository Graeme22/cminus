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

extern FILE *yyin;
AST *tree;
FILE *code;

void usage();
void loadIO(char *);

#endif