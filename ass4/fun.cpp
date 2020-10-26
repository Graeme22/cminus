#include "fun.h"

// Par

Par::Par(TokenData *data, bool array): Var(data) {
	isArray = array;
	initialized = true;
}

void Par::print() {
	printPrefix();
	if(isArray)
		printf("Param %s: array of type %s [line: %d]\n", name, type, line);
	else
		printf("Param %s: type %s [line: %d]\n", name, type, line);
	AST::print();
}

// FunDeclaration

FunDeclaration::FunDeclaration(TokenData *n, AST *pars, AST *stmt): Var(n) {
	addChild(pars, 0);
	addChild(stmt, 1);
	if(stmt != NULL)
		stmt->hasScopeException = true;
	type = (char *)"void";
	isFunction = true;
}

FunDeclaration::FunDeclaration(TokenData *t, TokenData *n, AST *p, AST *s): FunDeclaration(n, p, s) {
	type = strdup(t->tokenString);
}

FunDeclaration::FunDeclaration(char *t, TokenData *n, AST *pars): Var(n) {
	if(t != NULL)
		type = strdup(t);
	else
		type = (char *)"void";
	isFunction = true;
	addChild(pars, 0);
}

void FunDeclaration::print() {
	printPrefix();
	printf("Func %s: returns type %s [line: %d]\n", name, type, line);
	AST::print();
}

void FunDeclaration::propagateScopes(SymbolTable *table) {
	bool success = table->insert(name, this);
	if(!success) {
		AST *existing = (AST *)table->lookup(name);
		printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n", line, name, existing->line);
		n_errors++;
	}
	table->enter("Function");
	AST::propagateScopesChildren(table);
	table->applyToAll(checkUsage);
	table->leave();
	AST::propagateScopesSibling(table);
}

// Call

Call::Call(TokenData *data, AST *args) {
	name = strdup(data->tokenString);
	line = data->line;
	type = (char *)"undefined";
	addChild(args, 0);
}

void Call::print() {
	printPrefix();
	if(strcmp(type, "undefined") == 0)
		printf("Call %s: undefined type [line: %d]\n", name, line);
	else
		printf("Call %s: type %s [line: %d]\n", name, type, line);
	AST::print();
}

void Call::propagateScopes(SymbolTable *table) {
	void *result = table->lookup(name);
	if(result == NULL) {
		printf("ERROR(%d): Symbol '%s' is not declared.\n", line, name);
		n_errors++;
	} else {
		Var *node = (Var *)result;
		if(!node->isFunction) {
			printf("ERROR(%d): '%s' is a simple variable and cannot be called.\n", line, name);
			n_errors++;
		}
		type = strdup(node->type);
		node->used = true;
	}
	AST::propagateScopes(table);
}