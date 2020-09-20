#ifndef _AST_H_
#define _AST_H_

#include <vector>
#include <iostream>
#include <string>
#include <string.h>
#include "scanType.h"

class AST {

protected:
	std::vector<AST *> children;
	int depth = 0;

public:
	AST();
	AST(AST *);
	virtual ~AST() {}
	virtual void print(int);
	virtual void append(AST *);
	void printPrefix();

};

class VarDeclId: public AST {

	bool isArray;
	int arraySize;

public:
	char *name;
	VarDeclId(TokenData *);
	VarDeclId(TokenData *, int);

};

class VarDeclaration: public AST {

	char *type;
	std::vector<VarDeclId *> vars;
	int line;

public:
	VarDeclaration(TokenData *);
	virtual void print(int);
	void append(VarDeclId *);

};

#endif
