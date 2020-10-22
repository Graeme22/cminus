#ifndef _VAR_H_
#define _VAR_H_

#include "ast.h"
#include "scanType.h"

class Var: public AST {

public:
	char *name;
	int arraySize;
	bool isStatic, isFunction;
	bool used, notified;
	Var(TokenData *);
	Var(TokenData *, TokenData *);
	void setTypeAndStatic(char *, bool);
	virtual void print();
	virtual void propagateScopes(SymbolTable *);

};

class Id: public Var {

public:
	Id(TokenData *);
	virtual void print();
	virtual void propagateScopes(SymbolTable *);

};

#endif