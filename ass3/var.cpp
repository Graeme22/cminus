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
			printf("Var %s: array of type %s [line: %d]\n", name, type, line);
		else
			printf("Var %s: type %s [line: %d]\n", name, type, line);
	} else
		printf("Var %s: undefined type [line: %d]\n", name, line);
	AST::print();
}

void Var::setTypeAndStatic(char *t, bool s) {
	type = strdup(t);
	isStatic = s;
	if(sibling != NULL)
		((Var *)sibling)->setTypeAndStatic(t, s);
}

char *Var::getType() {
	return type;
}

void Var::propagateScopes(SymbolTable *table) {
	bool success = table->insert(name, this);
	if(!success) {
		AST *existing = (AST *)table->lookup(name);
		printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n", line, name, existing->line);
		n_errors++;
	}
	AST::propagateScopes(table);
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

void VarAccess::propagateScopes(SymbolTable *table) {
	void *result = table->lookup(name);
	if(result == NULL) {
		printf("ERROR(%d): Symbol '%s' is not declared.\n", line, name);
		n_errors++;
	} else {
		AST *node = (AST *)result;
		if(node->isFunction) {
			printf("ERROR(%d): Cannot use function '%s' as a variable.\n", line, name);
			n_errors++;
		}
	}
	AST::propagateScopes(table);
}