#ifndef _AST_H_
#define _AST_H_

#include <vector>
#include <string.h>
#include <stdio.h>

class AST {

protected:
	int depth;
	bool isChild;
	bool isFirst;

public:
	std::vector<AST *> children;
	AST *sibling;
	int index;
	AST();
	virtual void print();
	virtual void append(AST *);
	void addChild(AST *);
	void setFirst();
	virtual void propagateInfo();
	virtual void printPrefix();

};

class List: public AST {

public:
	virtual void append(AST *);

};

#endif
