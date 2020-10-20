#ifndef _EXP_H_
#define _EXP_H_

#include "ast.h"
#include "scanType.h"
#include <iostream>
#include "parser.tab.h"

class Operation: public AST {

	char *str;
	int id;

public:
	Operation(TokenData *, AST *, AST *);
	Operation(TokenData *, AST *);
	virtual void print();
	virtual void propagateScopes(SymbolTable *);
	bool validateL(char *);
	bool validateR(char *);
	bool validate(char *, char *);

};

class Constant: public AST {

	TokenData *data;

public:
	Constant(TokenData *);
	virtual void print();

};

#endif