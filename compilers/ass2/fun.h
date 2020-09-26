#ifndef _FUN_H_
#define _FUN_H_

#include "ast.h"
#include "scanType.h"

class Par: public AST {

	bool isArray;
	int line;
	char *name;
	char *type;

public:
	Par(TokenData *, bool);
	void setType(char *);
	virtual void print();

};

class FunDeclaration: public AST {

	char *type;
	char *name;
	int line;

public:
	FunDeclaration(TokenData *, TokenData *, AST *, AST *);
	FunDeclaration(TokenData *, AST *, AST *);
	virtual void print();

};

class Call: public AST {

	char *name;
	int line;

public:
	Call(TokenData *, AST *);
	virtual void print();

};

#endif