#ifndef _STMT_H_
#define _STMT_H_

#include "ast.h"
#include "scanType.h"
#include "var.h"

class CompoundStatement: public AST {

	int line;

public:
	CompoundStatement(int, AST *, AST *);
	virtual void print();

};

class If: public AST {

	int line;

public:
	// if-else
	If(int, AST *, AST *, AST *);
	// if
	If(int, AST *, AST *);
	virtual void print();

};

class While: public AST {

	int line;

public:
	While(int, AST *, AST *);
	virtual void print();

};

class Return: public AST {

	int line;

public:
	Return(int);
	Return(int, AST *);
	virtual void print();

};

class For: public AST {

	int line;
	char *iterator;
	char *array;

public:
	For(int, TokenData *, TokenData *, AST *);
	virtual void print();

};

class Break: public AST {

	int line;

public:
	Break(int);
	virtual void print();

};

#endif