#ifndef _VAR_H_
#define _VAR_H_

#include "ast.h"
#include "scanType.h"

class Var: public AST {

public:
	char *name;
	int arraySize;
	bool isStatic, isFunction, isArray;
	bool used, notified;
	Var(TokenData *);
	Var(TokenData *, TokenData *);
	void setTypeAndStatic(char *, bool);
	virtual void print();
	char *getType();
	virtual void propagateScopes(SymbolTable *);

};

class VarAccess: public AST {

public:
	char *name;
	bool isStatic;
	VarAccess(TokenData *);
	virtual void print();
	virtual void propagateScopes(SymbolTable *);

};

class ArrayAccess: public AST {

public:
	char *name;
	bool isStatic; // ?
	ArrayAccess(int, AST *, AST *);
	virtual void print();
	virtual void propagateScopes(SymbolTable *);

};

#endif