#ifndef _FUN_H_
#define _FUN_H_

#include "ast.h"
#include "scanType.h"

class Par: public AST {

	bool isArray;
	char *name;
	char *type;

public:
	Par(TokenData *, bool);
	void setType(char *);
	virtual void print();
	virtual void propagateScopes(SymbolTable *);

};

class FunDeclaration: public AST {

	char *type;
	char *name;

public:
	FunDeclaration(TokenData *, TokenData *, AST *, AST *);
	FunDeclaration(TokenData *, AST *, AST *);
	virtual void print();
	virtual void propagateScopes(SymbolTable *);

};

class Call: public AST {

	char *name;

public:
	Call(TokenData *, AST *);
	virtual void print();
	virtual void propagateScopes(SymbolTable *);

};

#endif