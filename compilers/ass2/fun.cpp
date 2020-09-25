#include "fun.h"

// Par

Par::Par(TokenData *data, bool toggle) {
	name = strdup(data->tokenString);
	line = data->line;
	isArray = toggle;
}

void Par::print(char *type) {
	if(isArray)
		printf("Param %s is array of type %s [line: %d]\n", name, type, line);
	else
		printf("Param %s of type %s [line: %d]\n", name, type, line);
	if(sibling != NULL)
		((Par *)sibling)->print(type);
}

// FunDeclaration

FunDeclaration::FunDeclaration(TokenData *n, AST *p, AST *s) {
	name = strdup(n->tokenString);
	line = n->line;
	if(p != NULL)
		params = (Params *)p;
	else
		params = NULL;
	statement = s;
	type = (char *)"void";	
}

FunDeclaration::FunDeclaration(TokenData *t, TokenData *n, AST *p, AST *s): FunDeclaration(n, p, s) {
	type = strdup(t->tokenString);
}

void FunDeclaration::print() {
	printf("Func %s returns type %s [line: %d]\n", name, type, line);
	if(params != NULL)
		params->print();
	if(statement != NULL)
		statement->print();
}

// ParamList

ParamList::ParamList(AST *node) {
	child = (Par *)node;
}

void ParamList::appendToChild(AST *node) {
	child->append(node);
}

void ParamList::setType(TokenData *data) {
	type = strdup(data->tokenString);
}

void ParamList::print() {
	child->print(type);
	if(sibling != NULL)
		sibling->print();
}

// Params

Params::Params(AST *node) {
	child = (ParamList *)node;
}

void Params::appendToChild(AST *node) {
	child->append(node);
}

void Params::print() {
	child->print();
}

// Call

Call::Call(TokenData *data, AST *a) {
	name = strdup(data->tokenString);
	line = data->line;
	args = a;
}

void Call::print() {
	printf("Call: %s [line: %d]\n", name, line);
	if(args != NULL)
		args->print();
}