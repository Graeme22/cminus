#include "var.h"

// Var

Var::Var(TokenData *data) {
	name = strdup(data->tokenString);
	line = data->line;
	arraySize = 0;
	isStatic = false;
	isFunction = false;
	used = false;
	notified = false;
	initialized = false;
}

Var::Var(TokenData *left, TokenData *right): Var(left) {
	isArray = true;
	arraySize = right->nValue;
}

void Var::print() {
	printPrefix();
	if(isArray) {
		if(strcmp(type, "undefined") != 0) {
			if(isStatic)
				printf("Var %s: static array of type %s [line: %d]\n", name, type, line);
			else
				printf("Var %s: array of type %s [line: %d]\n", name, type, line);
		} else // if it's undefined we won't know whether it's static
			printf("Var %s: array of undefined type [line: %d]\n", name, line);
	} else {
		if(strcmp(type, "undefined") != 0) {
			if(isStatic)
				printf("Var %s: static type %s [line: %d]\n", name, type, line);
			else
				printf("Var %s: type %s [line: %d]\n", name, type, line);
		} else
			printf("Var %s: undefined type [line: %d]\n", name, line);
	}
	AST::print();
}

void Var::setTypeAndStatic(char *t, bool s) {
	type = strdup(t);
	isStatic = s;
	if(sibling != NULL) // we're part of a list, e.g. par list or var list
		((Var *)sibling)->setTypeAndStatic(t, s);
}

void Var::setInitialized() {
	initialized = true;
	if(sibling != NULL)
		((Var *)sibling)->setInitialized();
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

// Id

Id::Id(TokenData *data): Var(data) {}

void Id::print() {
	printPrefix();
	if(isArray) {
		if(strcmp(type, "undefined") != 0) {
			if(isStatic)
				printf("Id %s: static array of type %s [line: %d]\n", name, type, line);
			else
				printf("Id %s: array of type %s [line: %d]\n", name, type, line);
		} else // if it's undefined we won't know whether it's static
			printf("Id %s: array of undefined type [line: %d]\n", name, line);
	} else {
		if(strcmp(type, "undefined") != 0) {
			if(isStatic)
				printf("Id %s: static type %s [line: %d]\n", name, type, line);
			else
				printf("Id %s: type %s [line: %d]\n", name, type, line);
		} else
			printf("Id %s: undefined type [line: %d]\n", name, line);
	}
	AST::print();
}

void Id::propagateScopes(SymbolTable *table) {
	void *result = table->lookup(name);
	if(result == NULL) {
		printf("ERROR(%d): Symbol '%s' is not declared.\n", line, name);
		n_errors++;
	} else {
		Var *var = (Var *)result;
		if(var->isFunction) {
			printf("ERROR(%d): Cannot use function '%s' as a variable.\n", line, name);
			n_errors++;
		} else {
			type = strdup(var->type);
			isArray = var->isArray;
			isStatic = var->isStatic;
			isFunction = var->isFunction;
			var->used = true;
			if(initialized)
				var->initialized = true;
			if(!var->initialized && !var->notified) {
				printf("WARNING(%d): Variable %s may be uninitialized when used here.\n", line, name);
				n_warnings++;
				var->notified = true;
			}
		}
		
	}
	AST::propagateScopes(table);
}