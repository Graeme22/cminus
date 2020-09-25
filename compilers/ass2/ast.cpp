#include "ast.h"

// AST

AST::AST() {
	sibling = NULL;
}

void AST::append(AST *node) {
	if(sibling == NULL)
		sibling = node;
	else {
		AST *itr;
		for(itr = sibling; itr->sibling != NULL; itr = itr->sibling);
		itr->sibling = node;
	}
}

void AST::print() {
	for(AST *child : children)
		child->print();
	if(sibling != NULL)
		sibling->print();
}