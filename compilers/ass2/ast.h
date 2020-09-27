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
	int index;

public:
	AST();
	virtual void print();
	virtual void append(AST *);
	void addChild(AST *);
	void propagateInfo();
	void printPrefix();

};

class List: public AST {

public:
	virtual void append(AST *);

};

#endif
