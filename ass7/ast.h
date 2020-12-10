#ifndef _AST_H_
#define _AST_H_

#define MAX_CHILDREN 3

#include <string.h>
#include <stdio.h>
#include "emitcode.h"
#include "symbolTable.h"

extern int n_errors;
extern int n_warnings;
extern int foffset;
extern int goffset;
extern int toffset;

class AST {

public:
	AST *children[MAX_CHILDREN];
	AST *sibling;
	int index, depth;
	bool isChild, isFirst, isArray, isConstant, isSolo, isGlobal;
	char *type;
	int line, size;
	bool hasScopeException, initialized;

	char *mType;
	int mSize;
	int mOffset;

	AST();
	virtual void print(bool);
	void append(AST *);
	void addChild(AST *, int);
	virtual void printPrefix();
	void propagateInfo();
	virtual void propagateScopes(SymbolTable *);
	void propagateScopesChildren(SymbolTable *);
	void propagateScopesSibling(SymbolTable *);
	virtual void initialize(SymbolTable *);
	virtual void generate(SymbolTable *);
	void generateChildren(SymbolTable *);
	void generateSibling(SymbolTable *);
	
};

#endif
