#ifndef _VAR_H_
#define _VAR_H_

#include "ast.h"
#include "scanType.h"

class Var: public AST {

public:
	char *name;
	bool isStatic, isArray, isFunction;
	bool used, notified, initialized;
	Var(TokenData *);
	void setTypeAndStatic(char *, bool);
	virtual void print();
	virtual void propagateScopes(SymbolTable *);

};

class Array: public Var {

public:
	int size;
	Array(TokenData *);
	Array(TokenData *, TokenData *);
	virtual void print();

};

class VarAccess: public Var {

public:
	VarAccess(TokenData *);
	virtual void print();
	virtual void propagateScopes(SymbolTable *);

};

class ArrayAccess: public Array {

public:
	ArrayAccess(TokenData *, AST *);
	virtual void print();
	virtual void propagateScopes(SymbolTable *);

};

#endif