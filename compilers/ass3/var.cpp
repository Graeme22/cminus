#include "var.h"

// Var

Var::Var(TokenData *data) {
	name = strdup(data->tokenString);
	line = data->line;
	isArray = false;
	isStatic = false;
	type = (char *)"undefined";
}

Var::Var(TokenData *data, TokenData *size): Var(data) {
	arraySize = size->nValue;
	isArray = true;
}

void Var::print() {
	// add static in here
	printPrefix();
	if(strcmp(type, "undefined") != 0){
		if(isArray)
			printf("Var %s is array of type %s [line: %d]\n", name, type, line);
		else
			printf("Var %s of type %s [line: %d]\n", name, type, line);
	} else
		printf("Var %s of undefined type [line: %d]\n", name, line);
	AST::print();
}

void Var::setTypeAndStatic(char *t, bool s) {
	type = strdup(t);
	isStatic = s;
	if(sibling != NULL)
		((Var *)sibling)->setTypeAndStatic(t, s);
}

// VarAccess

VarAccess::VarAccess(TokenData *data) {
	name = strdup(data->tokenString);
	isArray = false;
	line = data->line;
}

VarAccess::VarAccess(int l, AST *var, AST *loc) {
	line = l;
	addChild(var, 0);
	addChild(loc, 1);
	isArray = true;
}

void VarAccess::print() {
	printPrefix();
	if(children[1] == NULL)
		printf("Id: %s [line: %d]\n", name, line);
	else
		printf("Op: [ [line: %d]\n", line);
	AST::print();
}