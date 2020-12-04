#ifndef _FUN_H_
#define _FUN_H_

#include "ast.h"
#include "semantic.h"
#include "scanType.h"
#include "var.h"

class Par: public Var {

public:
	Par(TokenData *, bool);
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);

};

class FunDeclaration: public Var {

public:
	int loc;
	FunDeclaration(TokenData *, TokenData *, AST *, AST *);
	FunDeclaration(TokenData *, AST *, AST *);
	FunDeclaration(char *, TokenData *, AST *);
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);

};

class Call: public AST {

	char *name;

public:
	Call(TokenData *, AST *);
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);

};

class Return: public AST {

public:
	Return(int);
	Return(int, AST *);
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);

};

extern FunDeclaration *currentFunction;
extern bool hasReturn;

#endif