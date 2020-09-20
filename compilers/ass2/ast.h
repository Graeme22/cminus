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
	AST *sibling;

public:
	AST();
	AST(AST *);
	virtual ~AST() {}
	virtual void print(int);
	virtual void append(AST *);
	void printPrefix();

};

class VarDeclaration: public AST {

	char *type;

public:
	VarDeclaration(TokenData *);

};

class VarDeclarationList: public AST {

	std::vector<char *> vars;

public:
	virtual void print(int);
	void append(TokenData *);

};

#endif
