#ifndef _VAR_H_
#define _VAR_H_

#include "ast.h"
#include "scanType.h"

class Var: public AST {

	int arraySize;
	bool isStatic;

public:
	char *name;
	Var(TokenData *);
	Var(TokenData *, TokenData *);
	void setTypeAndStatic(char *, bool);
	virtual void print();
	char *getType();
	virtual void propagateScopes(SymbolTable *);

};

class VarAccess: public AST {

	char *name;

public:
	VarAccess(TokenData *);
	VarAccess(int, AST *, AST *);
	virtual void print();
	virtual void propagateScopes(SymbolTable *);

};

#endif