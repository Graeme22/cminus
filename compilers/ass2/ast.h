#ifndef _AST_H_
#define _AST_H_

#include <vector>
#include <string.h>

class AST {

protected:
	std::vector<AST *> children;
	AST *sibling;

public:
	AST();
	virtual void print();
	virtual void append(AST *);

};

#endif
