#ifndef _AST_H_
#define _AST_H_

#define MAX_CHILDREN 3

#include <string.h>
#include <stdio.h>

class AST {

public:
	AST *children[MAX_CHILDREN];
	AST *sibling;
	int index, depth;
	bool isChild, isFirst;

	AST();
	virtual void print();
	void append(AST *);
	void addChild(AST *, int);
	void setFirst();
	virtual void printPrefix();
	void propagateInfo();

};

#endif
