#include "ast.h"

// AST

AST::AST() {
	sibling = NULL;
	depth = 0;
	isChild = false;
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

void AST::addChild(AST *node) {
	children.push_back(node);
}

void AST::printPrefix() {
	for(int i = 0; i < depth; i++)
		printf("!   ");
	//if(isChild)
	//	printf("Child: %d  ", 0);
	//else
	//	printf("Sibling: %d  ", 0);
}

void AST::print() {
	for(AST *child : children)
		child->print();
	if(sibling != NULL)
		sibling->print();
}

void AST::propogateInfo() {
	for(AST *child : children)
		child->depth = depth + 1;
	for(AST *itr = sibling; itr != NULL; itr = itr->sibling)
		itr->depth = depth;

	for(AST *child : children) {
		child->isChild = true;
		child->propogateInfo();
	}
	for(AST *itr = sibling; itr != NULL; itr = itr->sibling)
		itr->propogateInfo();
}