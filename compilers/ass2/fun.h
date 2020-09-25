#ifndef _FUN_H_
#define _FUN_H_

#include "ast.h"
#include "scanType.h"

class Par: public AST {

	bool isArray;
	int line;
	char *name;

public:
	Par(TokenData *, bool);
	virtual void print(char *);

};

class ParamList: public AST {

	Par *child;
	char *type;

public:
	ParamList(AST *);
	virtual void appendToChild(AST *);
	void setType(TokenData *);
	virtual void print();

};

class Params: public AST {

	ParamList *child;

public:
	Params(AST *);
	virtual void appendToChild(AST *);
	virtual void print();

};

class FunDeclaration: public AST {

	char *type;
	char *name;
	int line;
	Params *params;
	AST *statement;

public:
	FunDeclaration(TokenData *, TokenData *, AST *, AST *);
	FunDeclaration(TokenData *, AST *, AST *);
	virtual void print();

};

class Call: public AST {

	char *name;
	AST *args;
	int line;

public:
	Call(TokenData *, AST *);
	virtual void print();

};

#endif