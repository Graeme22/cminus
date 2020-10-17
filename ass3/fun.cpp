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

void Par::propagateScopes(SymbolTable *table) {
	bool success = table->insert(name, this);
	if(!success) {
		AST *existing = (AST *)table->lookup(name);
		printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n", line, name, existing->line);
		n_errors++;
	}
	AST::propagateScopes(table);
}

// FunDeclaration

FunDeclaration::FunDeclaration(TokenData *n, AST *pars, AST *stmt) {
	name = strdup(n->tokenString);
	line = n->line;
	addChild(pars, 0);
	addChild(stmt, 1);
	if(stmt != NULL)
		stmt->hasScopeException = true;
	isFunction = true;
	type = (char *)"void";
}

FunDeclaration::FunDeclaration(TokenData *t, TokenData *n, AST *p, AST *s): FunDeclaration(n, p, s) {
	type = strdup(t->tokenString);
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
	table->leave();
	AST::propagateScopesSibling(table);
}

// Call

Call::Call(TokenData *data, AST *args) {
	name = strdup(data->tokenString);
	line = data->line;
	addChild(args, 0);
}

void Call::print() {
	printPrefix();
	printf("Call: %s [line: %d]\n", name, line);
	AST::print();
}

void Call::propagateScopes(SymbolTable *table) {
	void *result = table->lookupGlobal(name);
	if(result == NULL) {
		printf("ERROR(%d): Symbol '%s' is not declared.\n", line, name);
		n_errors++;
	} else {
		AST *node = (AST *)result;
		if(!node->isFunction) {
			printf("ERROR(%d): '%s' is a simple variable and cannot be called.\n", line, name);
			n_errors++;
		}
	}
	AST::propagateScopes(table);
}