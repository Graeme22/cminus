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
		else if(isStatic)
			printf("Var %s: static type %s [line: %d]\n", name, type, line);
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
	if(children[0] != NULL)
		initialized = true;
	AST::propagateScopes(table);
}

// VarAccess

VarAccess::VarAccess(TokenData *data) {
	name = strdup(data->tokenString);
	isStatic = false;
	line = data->line;
}

void VarAccess::print() {
	printPrefix();
	if(strcmp(type, "undefined") == 0)
		printf("Id %s: undefined type [line: %d]\n", name, line);
	else if(isStatic)
		printf("Id %s: static type %s [line: %d]\n", name, type, line);
	else
		printf("Id %s: type %s [line: %d]\n", name, type, line);
	AST::print();
}

void VarAccess::propagateScopes(SymbolTable *table) {
	AST::propagateScopesChildren(table);
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
			isStatic = node->isStatic;
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
	AST::propagateScopesSibling(table);
}

// ArrayAccess

ArrayAccess::ArrayAccess(int l, AST *id, AST *loc) {
	line = l;
	addChild(id, 0);
	addChild(loc, 1);
}

void ArrayAccess::print() {
	printf("Op [ : type int [line: %d]\n", line);
	AST::print();
}

void ArrayAccess::propagateScopes(SymbolTable *table) {

}