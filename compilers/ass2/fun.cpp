#include "fun.h"

// Par

Par::Par(TokenData *data, bool toggle) {
	name = strdup(data->tokenString);
	line = data->line;
	isArray = toggle;
}

void Par::setType(char *t) {
	type = strdup(t);
	if(sibling != NULL)
		((Par *)sibling)->setType(t);
}

void Par::print() {
	printPrefix();
	if(isArray)
		printf("Param %s is array of type %s [line: %d]\n", name, type, line);
	else
		printf("Param %s of type %s [line: %d]\n", name, type, line);
	AST::print();
}

// FunDeclaration

FunDeclaration::FunDeclaration(TokenData *n, AST *p, AST *s) {
	name = strdup(n->tokenString);
	line = n->line;
	addChild(p);
	addChild(s);
	type = (char *)"void";
}

FunDeclaration::FunDeclaration(TokenData *t, TokenData *n, AST *p, AST *s): FunDeclaration(n, p, s) {
	type = strdup(t->tokenString);
}

void FunDeclaration::print() {
	printPrefix();
	printf("Func %s returns type %s [line: %d]\n", name, type, line);
	AST::print();
}

// Call

Call::Call(TokenData *data, AST *args) {
	name = strdup(data->tokenString);
	line = data->line;
	addChild(args);
}

void Call::print() {
	printPrefix();
	printf("Call: %s [line: %d]\n", name, line);
	AST::print();
}