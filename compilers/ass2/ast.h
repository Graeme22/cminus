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

class CompoundStatement: public AST {

	AST *localDeclarations;
	AST *statementList;
	int line;

public:
	CompoundStatement(int, AST *, AST *);
	virtual void print();

};

class If: public AST {

	AST *ifStmt;
	AST *elseStmt;
	AST *condition;
	int line;

public:
	// if-else
	If(int, AST *, AST *, AST *);
	// if
	If(int, AST *, AST *);
	virtual void print();

};

class Relation: public AST {

	AST *left;
	AST *right;
	int type;
	char *str;
	int line;

public:
	Relation(TokenData *, AST *, AST*);
	virtual void print();

};

class LogicExpression: public AST {

	AST *left;
	AST *right;
	int type;
	char *str;
	int line;

public:
	LogicExpression(TokenData *, AST *, AST *);
	LogicExpression(TokenData *, AST *);
	virtual void print();

};

class Operation: public AST {

	AST *left;
	AST *right;
	int type;
	char *str;
	int line;

public:
	Operation(TokenData *, AST *, AST *);
	Operation(TokenData *, AST *);
	virtual void print();

};

class VarAccess: public AST {

	char *name;
	bool isArray;
	int line;
	// this needs to be an int when we get to type checking
	AST *location;

public:
	VarAccess(TokenData *);
	VarAccess(AST *, AST *);
	virtual void print();

};

#endif
