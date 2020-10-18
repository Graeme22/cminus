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
	printPrefix();
	if(strcmp(type, "undefined") != 0){
		if(isArray) {
			if(isStatic)
				printf("Var %s: static array of type %s [line: %d]\n", name, type, line);
			else
				printf("Var %s: array of type %s [line: %d]\n", name, type, line);
		} else {
			if(isStatic)
				printf("Var %s: static type %s [line: %d]\n", name, type, line);
			else
				printf("Var %s: type %s [line: %d]\n", name, type, line);
		}
	} else {
		if(isArray)
			printf("Var %s: array of undefined type [line: %d]\n", name, line);
		else
			printf("Var %s: undefined type [line: %d]\n", name, line);
	}
	AST::print();
}

void Var::setTypeAndStatic(char *t, bool s) {
	type = strdup(t);
	isStatic = s;
	if(isStatic)
		initialized = true;
	if(sibling != NULL)
		((Var *)sibling)->setTypeAndStatic(t, s);
}

void Var::propagateScopes(SymbolTable *table) {
	if(children[0] != NULL)
		initialized = true;
	bool success = table->insert(name, this);
	if(!success) {
		AST *existing = (AST *)table->lookup(name);
		printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n", line, name, existing->line);
		n_errors++;
	}
	AST::propagateScopes(table);
}

// VarAccess

VarAccess::VarAccess(TokenData *data): Var(data) {}

void VarAccess::print() {
	printPrefix();
	if(strcmp(type, "undefined") != 0){
		if(isArray) {
			if(isStatic)
				printf("Id %s: static array of type %s [line: %d]\n", name, type, line);
			else
				printf("Id %s: array of type %s [line: %d]\n", name, type, line);
		} else {
			if(isStatic)
				printf("Id %s: static type %s [line: %d]\n", name, type, line);
			else
				printf("Id %s: type %s [line: %d]\n", name, type, line);
		}
	} else
		printf("Id %s: undefined type [line: %d]\n", name, line);
	AST::print();
}

void VarAccess::propagateScopes(SymbolTable *table) {
	void *result = table->lookup(name);
	if(result == NULL) {
		printf("ERROR(%d): Symbol '%s' is not declared.\n", line, name);
		n_errors++;
	} else {
		Var *node = (Var *)result;
		if(node->isFunction) {
			printf("ERROR(%d): Cannot use function '%s' as a variable.\n", line, name);
			n_errors++;
		} else {
			type = strdup(node->type);
			isArray = node->isArray;
			isStatic = node->isStatic;
			isFunction = node->isFunction;
			node->used = true;
			if(initialized)
				node->initialized = true;
			if(!node->initialized && !node->notified) {
				printf("WARNING(%d): Variable %s may be uninitialized when used here.\n", line, name);
				n_warnings++;
				node->notified = true;
			}
		}
		
	}
	AST::propagateScopes(table);
}

// ArrayAccess

ArrayAccess::ArrayAccess(int l, AST *id, AST *loc) {
	line = l;
	addChild(id, 0);
	addChild(loc, 1);
	type = (char *)"undefined";
}

void ArrayAccess::print() {
	printPrefix();
	if(strcmp(type, "undefined") == 0)
		printf("Op [ : undefined type [line: %d]\n", line);
	else
		printf("Op [ : type %s [line: %d]\n", type, line);
	AST::print();
}

void ArrayAccess::propagateScopes(SymbolTable *table) {
	AST::propagateScopesChildren(table);
	type = strdup(children[0]->type);
	AST::propagateScopesSibling(table);
}