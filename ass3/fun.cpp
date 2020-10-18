#include "fun.h"

// Par

Par::Par(TokenData *data, bool array): Var(data) {
	name = strdup(data->tokenString);
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

FunDeclaration::FunDeclaration(TokenData *n, AST *pars, AST *stmt) {
	name = strdup(n->tokenString);
	line = n->line;
	addChild(pars, 0);
	addChild(stmt, 1);
	if(stmt != NULL)
		stmt->hasScopeException = true;
	type = (char *)"void";
	var = new Var(n);
	var->isFunction = true;
	var->type = strdup(type);
}

FunDeclaration::FunDeclaration(TokenData *t, TokenData *n, AST *p, AST *s): FunDeclaration(n, p, s) {
	type = strdup(t->tokenString);
	var->type = strdup(type);
}

void FunDeclaration::print() {
	printPrefix();
	printf("Func %s: returns type %s [line: %d]\n", name, type, line);
	AST::print();
}

void FunDeclaration::propagateScopes(SymbolTable *table) {
	bool success = table->insert(name, var);
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
	void *result = table->lookupGlobal(name);
	if(result == NULL) {
		printf("ERROR(%d): Symbol '%s' is not declared.\n", line, name);
		n_errors++;
	} else {
		Var *node = (Var *)result;
		if(!node->isFunction) {
			printf("ERROR(%d): '%s' is a simple variable and cannot be called.\n", line, name);
			n_errors++;
		} else
			type = strdup(node->type);
	}
	AST::propagateScopes(table);
}