#include "ast.h"

// AST

AST::AST() {
	sibling = NULL;
	depth = 0;
	index = 1;
	isChild = false;
	isFirst = false;
}

void AST::append(AST *node) {
	if(node == NULL)
		return;
	if(sibling == NULL)
		sibling = node;
	else {
		AST *itr;
		for(itr = sibling; itr->sibling != NULL; itr = itr->sibling);
		itr->sibling = node;
	}
}

void AST::addChild(AST *child, int n) {
	if(child == NULL)
		return;
	children[n] = child;
	child->index = n;
	child->isChild = true;
}

void AST::printPrefix() {
	if(isFirst)
		return;
	for(int i = 0; i < depth; i++)
		printf(".   ");
	if(isChild)
		printf("Child: %d  ", index);
	else
		printf("Sibling: %d  ", index);
}

void AST::print() {
	for(int i = 0; i < MAX_CHILDREN; i++)
		if(children[i] != NULL)
			children[i]->print();
	if(sibling != NULL)
		sibling->print();
}

void AST::setFirst() {
	isFirst = true;
}

void AST::propagateInfo() {
	for(int i = 0; i < MAX_CHILDREN; i++) {
		if(children[i] != NULL) {
			children[i]->depth = depth + 1;
			children[i]->propagateInfo();
		}
	}
	if(sibling != NULL) {
		sibling->depth = depth;
		if(!isChild)
			sibling->index = index + 1;
		sibling->propagateInfo();
	}
}