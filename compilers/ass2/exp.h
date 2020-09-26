#ifndef _EXP_H_
#define _EXP_H_

#include "ast.h"
#include "scanType.h"

class Relation: public AST {

	int type;
	char *str;
	int line;

public:
	Relation(TokenData *, AST *, AST*);
	virtual void print();

};

class LogicExpression: public AST {

	int type;
	char *str;
	int line;

public:
	LogicExpression(TokenData *, AST *, AST *);
	LogicExpression(TokenData *, AST *);
	virtual void print();

};

class Operation: public AST {

	int type;
	char *str;
	int line;

public:
	Operation(TokenData *, AST *, AST *);
	Operation(TokenData *, AST *);
	virtual void print();

};

class Constant: public AST {

	TokenData *data;

public:
	Constant(TokenData *);
	virtual void print();

};

#endif