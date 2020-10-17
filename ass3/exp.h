#ifndef _EXP_H_
#define _EXP_H_

#include "ast.h"
#include "scanType.h"
#include <iostream>
#include "parser.tab.h"

class Relation: public AST {

	int kind;
	char *str;

public:
	Relation(TokenData *, AST *, AST*);
	virtual void print();

};

class LogicExpression: public AST {

	int kind;
	char *str;

public:
	LogicExpression(TokenData *, AST *, AST *);
	LogicExpression(TokenData *, AST *);
	virtual void print();

};

class Operation: public AST {

	char *str;
	int id;

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