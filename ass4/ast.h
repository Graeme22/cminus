#ifndef _AST_H_
#define _AST_H_

#define MAX_CHILDREN 3

#include <string.h>
#include <stdio.h>
#include "symbolTable.h"

extern int n_errors;
extern int n_warnings;

class AST {

public:
	AST *children[MAX_CHILDREN];
	AST *sibling;
	int index, depth;
	bool isChild, isFirst, isArray;
	char *type;
	int line;
	bool hasScopeException, initialized;

	AST();
	virtual void print();
	void append(AST *);
	void addChild(AST *, int);
	virtual void printPrefix();
	void propagateInfo();
	virtual void propagateScopes(SymbolTable *);
	void propagateScopesChildren(SymbolTable *);
	void propagateScopesSibling(SymbolTable *);
	virtual void initialize(SymbolTable *);

};

#endif
