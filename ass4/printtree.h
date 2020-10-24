#ifndef _PRINTTREE_H_
#define _PRINTTREE_H_

#include <stdlib.h>
#include <stdio.h>
#include "scanType.h"
#include "ast.h"
#include "ourgetopt.h"
#include "semantic.h"
#include "symbolTable.h"
#include "parser.tab.h"

extern FILE *yyin;
AST *tree;

void usage();

#endif