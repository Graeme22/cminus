#ifndef _AST_H_
#define _AST_H_

#include <vector>
#include <string.h>
#include <stdio.h>

class AST {

protected:
	std::vector<AST *> children;
	AST *sibling;
	int depth;
	bool isChild;

public:
	AST();
	virtual void print();
	void append(AST *);
	void addChild(AST *);
	void printPrefix();
	void propogateInfo();

};

#endif
