#ifndef _FUN_H_
#define _FUN_H_

#include "ast.h"
#include "semantic.h"
#include "scanType.h"
#include "var.h"

class Par: public Var {

public:
	Par(TokenData *, bool);
	virtual void print();

};

class FunDeclaration: public AST {

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