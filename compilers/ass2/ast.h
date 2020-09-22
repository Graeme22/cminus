#ifndef _AST_H_
#define _AST_H_

#include <vector>
#include <string.h>
#include "scanType.h"

class AST {

protected:
	AST *sibling;

public:
	AST();
	virtual void print();
	virtual void append(AST *);

};

class Var: public AST {

	bool isArray;
	int arraySize;
	int line;
	char *name;

public:
	Var(TokenData *);
	Var(TokenData *, TokenData *);
	virtual void print(char *);

};

class Par: public AST {

	bool isArray;
	int line;
	char *name;

public:
	Par(TokenData *, bool);
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
	// points to the child, which may have any number of siblings.
	VarList *child;

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

class Statement: public AST {

};

class FunDeclaration: public AST {

	char *type;
	char *name;
	int line;
	Params *params;
	Statement *statement;

public:
	FunDeclaration(TokenData *, TokenData *, AST *, AST *);
	FunDeclaration(TokenData *, AST *, AST *);
	virtual void print();

};

#endif
