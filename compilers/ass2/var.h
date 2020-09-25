#ifndef _VAR_H_
#define _VAR_H_

#include "ast.h"
#include "scanType.h"

class Var: public AST {

	bool isArray;
	int arraySize;
	int line;
	char *name;
	AST *value;

public:
	Var(TokenData *);
	Var(TokenData *, TokenData *);
	void setValue(AST *);
	virtual void print(char *);

};

class VarList: public AST {

	Var *child;

public:
	VarList(AST *);
	virtual void print(char *);
	virtual void append(AST *);

};

class VarDeclaration: public AST {

	char *type;

public:
	VarDeclaration(TokenData *, AST *);
	virtual void print();

};

class ScopedVarDeclaration: public AST {

	bool isStatic;
	char *type;
	VarList *child;

public:
	ScopedVarDeclaration(TokenData *, AST *, bool);
	virtual void print();

};

class VarAccess: public AST {

	char *name;
	bool isArray;
	int line;
	// this needs to be an int when we get to type checking
	AST *var;
	AST *loc;

public:
	VarAccess(TokenData *);
	VarAccess(int, AST *, AST *);
	virtual void print();

};

#endif