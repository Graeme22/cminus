#include "ast.h"

// AST

AST::AST() {
	sibling = NULL;
	depth = -1;
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

void AST::addChild(AST *node) {
	children.push_back(node);
}

void AST::printPrefix() {
	if(isFirst)
		return;
	for(int i = 0; i < depth; i++)
		printf("!   ");
	if(isChild)
		printf("Child: %d  ", index);
	else
		printf("Sibling: %d  ", index);
}

void AST::print() {
	for(AST *child : children)
		child->print();
	if(sibling != NULL)
		sibling->print();
}

void AST::propagateInfo() {
	for(AST *child : children)
		child->depth = depth + 1;
	for(AST *itr = sibling; itr != NULL; itr = itr->sibling)
		itr->depth = depth;

	int i = 0;
	for(AST *child : children) {
		child->isChild = true;
		child->index = i++;
		child->propagateInfo();
	}
	i = 0;
	for(AST *itr = sibling; itr != NULL; itr = itr->sibling) {
		itr->propagateInfo();
		itr->index = i++;
	}
}

void AST::setFirst() {
	isFirst = true;
}

// List

void List::append(AST *item) {
	if(children.empty())
		addChild(item);
	else
		children[0]->append(item);
}