#ifndef _VAR_H_
#define _VAR_H_

#include "ast.h"
#include "exp.h"
#include "scanType.h"

class Var: public AST {

public:
	char *name;
	int arraySize;
	bool isStatic, isFunction, isGlobal;
	bool used, notified;
	Var(TokenData *);
	Var(TokenData *, TokenData *);
	void setTypeAndStatic(char *, bool);
	void setInitialized();
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void initialize(SymbolTable *);
	virtual void generate(SymbolTable *, bool);
	
};

class Id: public Var {

public:
	Id(TokenData *);
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);

};

#endif