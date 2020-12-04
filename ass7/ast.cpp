#include "ast.h"

// AST

AST::AST() {
	sibling = NULL;
	depth = 0;
	index = 1;
	isChild = false;
	isFirst = false;
	isArray = false;
	isSolo = false;
	isConstant = false;
	initialized = false;
	line = -1;
	type = (char *)"undefined";
	hasScopeException = false;
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
	children[n] = child;
	if(child == NULL)
		return;
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

void AST::print(bool showMemory) {
	for(int i = 0; i < MAX_CHILDREN; i++)
		if(children[i] != NULL)
			children[i]->print(showMemory);
	if(sibling != NULL)
		sibling->print(showMemory);
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

void AST::propagateScopes(SymbolTable *table) {
	propagateScopesChildren(table);
	propagateScopesSibling(table);
}

void AST::propagateScopesChildren(SymbolTable *table) {
	for(int i = 0; i < MAX_CHILDREN; i++)
		if(children[i] != NULL)
			children[i]->propagateScopes(table);
}

void AST::propagateScopesSibling(SymbolTable *table) {
	if(sibling != NULL && !isSolo)
		sibling->propagateScopes(table);
}

void AST::initialize(SymbolTable *table) {
	for(int i = 0; i < MAX_CHILDREN; i++)
		if(children[i] != NULL)
			children[i]->initialize(table);
	if(sibling != NULL)
		sibling->initialize(table);
}

void AST::generate(SymbolTable *globals) {
	for(int i = 0; i < MAX_CHILDREN; i++)
		if(children[i] != NULL)
			children[i]->initialize(globals);
	if(sibling != NULL)
		sibling->initialize(globals);
}