#ifndef _VAR_H_
#define _VAR_H_

#include "ast.h"
#include "scanType.h"

class Var: public AST {

	bool isArray;
	int arraySize;
	int line;
	char *name;
	char *type;
	bool isStatic;

public:
	Var(TokenData *);
	Var(TokenData *, TokenData *);
	void setTypeAndStatic(char *, bool);
	virtual void print();
	char *getType();

};

class VarAccess: public AST {

	char *name;
	bool isArray;
	int line;

public:
	VarAccess(TokenData *);
	VarAccess(int, AST *, AST *);
	virtual void print();

};

#endif