#include "ast.h"
#include "ourgetopt.h"
#include <stdlib.h>
#include <stdio.h>
#include "scanType.h"
#include "semantic.h"
#include "symbolTable.h"
#include "parser.tab.h"

extern FILE *yyin;
AST *tree;