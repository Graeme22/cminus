#include "fun.h"

// Par

Par::Par(TokenData *data, bool array): Var(data) {
	isArray = array;
	initialized = true;
}

void Par::print(bool showMemory) {
	printPrefix();
	char *mData;
	if(showMemory) {
		mData = (char *)malloc(50);
		sprintf(mData, " [mem: %s  size: %d  loc: %d]", mType, mSize, mOffset);
	}
	if(isArray)
		printf("Param %s: array of type %s%s [line: %d]\n", name, type, (showMemory ? mData : (char *)""), line);
	else
		printf("Param %s: type %s%s [line: %d]\n", name, type, (showMemory ? mData : (char *)""), line);
	AST::print(showMemory);
}

void Par::propagateScopes(SymbolTable *table) {
	AST::propagateScopesChildren(table);
	bool success = table->insert(name, this);
	if(children[0] != NULL && !children[0]->isConstant) {
		printf("ERROR(%d): Initializer for variable '%s' is not a constant expression.\n", line, name);
		n_errors++;
	}
	if(!success) {
		AST *existing = (AST *)table->lookup(name);
		printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n", line, name, existing->line);
		n_errors++;
	}
	if(children[0] != NULL && strcmp(children[0]->type, type) != 0 && strcmp(children[0]->type, (char *)"undefined")) {
		printf(	"ERROR(%d): Variable '%s' is of type %s but is being initialized with an expression of type %s.\n", line, name, type, children[0]->type);
		n_errors++;
	}
	
	mType = (char *)"Param";
	mOffset = foffset; // no need to store size for a passed array
	foffset -= mSize;
	AST::propagateScopesSibling(table);
}

void Par::generate(SymbolTable *globals) {}

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
	mOffset = -2;
	addChild(pars, 0);
}

void FunDeclaration::print(bool showMemory) {
	printPrefix();
	printf("Func %s: returns type %s [line: %d]\n", name, type, line);
	AST::print(showMemory);
}

void FunDeclaration::propagateScopes(SymbolTable *table) {
	bool success = table->insert(name, this);
	if(!success) {
		AST *existing = (AST *)table->lookup(name);
		printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n", line, name, existing->line);
		n_errors++;
	}
	currentFunction = this;
	hasReturn = false;
	table->enter("Function");
	// function takes up one word of memory
	foffset -= 2;
	mOffset = foffset;
	AST::propagateScopesChildren(table);
	if(!hasReturn && strcmp(type, (char *)"void") != 0) {
		printf("WARNING(%d): Expecting to return type %s but function '%s' has no return statement.\n", line, type, name);
		n_warnings++;
	}
	table->applyToAll(checkUsage);
	size = table->leave();
	AST::propagateScopesSibling(table);
}

void FunDeclaration::generate(SymbolTable *globals) {
	if(functionsGenerated)
		return;
	emitComment((char *)"FUNCTION", name);
	loc = emitSkip(0);
	toffset = size;
	emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
	AST::generateChildren(globals);
	emitRM((char *)"LDC", 2, 0, 6, (char *)"Set return value to 0");
	emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
	emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust frame pointer");
	emitRM((char *)"LDA", 7, 0, 3, (char *)"Return");
	emitComment((char *)"END FUNCTION", name);
	// we don't do this here because it will be done for us
	//AST::generateSibling(globals);
}

// Call

Call::Call(TokenData *data, AST *args) {
	name = strdup(data->tokenString);
	line = data->line;
	type = (char *)"undefined";
	addChild(args, 0);
}

void Call::print(bool showMemory) {
	printPrefix();
	if(strcmp(type, "undefined") == 0)
		printf("Call %s: undefined type [line: %d]\n", name, line);
	else
		printf("Call %s: type %s [line: %d]\n", name, type, line);
	AST::print(showMemory);
}

void Call::propagateScopes(SymbolTable *table) {
	void *result = table->lookup(name);
	if(result == NULL) {
		printf("ERROR(%d): Function '%s' is not declared.\n", line, name);
		n_errors++;
		AST::propagateScopesChildren(table);
	} else {
		Var *node = (Var *)result;
		if(!node->isFunction) {
			printf("ERROR(%d): '%s' is a simple variable and cannot be called.\n", line, name);
			n_errors++;
		} else {
			type = strdup(node->type);
			node->used = true;
			FunDeclaration *fun = (FunDeclaration *)result;
			AST *passed = children[0];
			AST *expected = fun->children[0];
			int i = 0;
			do {
				if(i++ != 0) {
					passed = passed->sibling;
					expected = expected->sibling;
				}
				if(passed == NULL && expected != NULL) {
					printf("ERROR(%d): Too few parameters passed for function '%s' declared on line %d.\n", line, name, fun->line);
					n_errors++;
				} else if(passed != NULL && expected == NULL) {
					printf("ERROR(%d): Too many parameters passed for function '%s' declared on line %d.\n", line, name, fun->line);
					n_errors++;
				}
				if(passed != NULL) {
					passed->isSolo = true;
					passed->propagateScopes(table);
				}
				if(passed != NULL && expected != NULL) {
					// type checking
					if(strcmp(passed->type, (char *)"undefined") != 0 && strcmp(passed->type, expected->type) != 0) {
						printf("ERROR(%d): Expecting type %s in parameter %d of call to '%s' declared on line %d but got type %s.\n", line, expected->type, i, name, fun->line, passed->type);
						n_errors++;
					}
					// arrayness checking
					if(passed->isArray && !expected->isArray) {
						printf("ERROR(%d): Not expecting array in parameter %d of call to '%s' declared on line %d.\n", line, i, name, fun->line);
						n_errors++;
					} else if(!passed->isArray && expected->isArray) {
						printf("ERROR(%d): Expecting array in parameter %d of call to '%s' declared on line %d.\n", line, i, name, fun->line);
						n_errors++;
					}
				}
			} while(passed != NULL && expected != NULL);
			// if we called with too many parameters, then we haven't finished propagation
			if(passed != NULL && passed->sibling != NULL)
				passed->sibling->propagateScopes(table);
		}
	}
	AST::propagateScopesSibling(table);
}

void Call::generate(SymbolTable *globals) {
	FunDeclaration *fun = (FunDeclaration *)globals->lookupGlobal(name);
	emitComment((char *)"CALL", name);
	emitRM((char *)"ST", 1, toffset, 1, (char *)"save old frame pointer");
	int toffset_old = toffset;
	toffset -= 2;
	for(AST *itr = children[0]; itr != NULL; itr = itr->sibling) {
		itr->generate(globals);
		emitRM((char *)"ST", 3, toffset--, 1, (char *)"Store parameter");
	}
	toffset = toffset_old;
	emitRM((char *)"LDA", 1, toffset, 1, (char *)"move frame pointer to new frame");
	emitRM((char *)"LDA", 3, 1, 7, (char *)"compute return address");
	int loc = fun->loc - emitSkip(0) - 1;
	emitRM((char *)"LDA", 7, loc, 7, (char *)"call", fun->name);
	emitRM((char *)"LDA", 3, 0, 2, (char *)"save the result");
	emitComment((char *)"END CALL", name);
	AST::generateSibling(globals);
}

// Return

Return::Return(int l) {
	line = l;
}

Return::Return(int l, AST *stmt) {
	addChild(stmt, 0);
	line = l;
}

void Return::print(bool showMemory) {
	printPrefix();
	printf("Return [line: %d]\n", line);
	AST::print(showMemory);
}

void Return::propagateScopes(SymbolTable *table) {
	AST::propagateScopesChildren(table);
	if(children[0] == NULL && strcmp(currentFunction->type, (char *)"void") != 0) {
		printf("ERROR(%d): Function '%s' at line %d is expecting to return type %s but return has no return value.\n", line, currentFunction->name, currentFunction->line, currentFunction->type);
		n_errors++;
	}
	if(children[0] != NULL && strcmp(currentFunction->type, (char *)"void") == 0) {
		printf("ERROR(%d): Function '%s' at line %d is expecting no return value, but return has return value.\n", line, currentFunction->name, currentFunction->line);
		n_errors++;
	}
	if(children[0] != NULL && strcmp(currentFunction->type, children[0]->type) != 0 && strcmp(children[0]->type, (char *)"undefined") != 0 && strcmp(currentFunction->type, (char *)"void") != 0) {
		printf("ERROR(%d): Function '%s' at line %d is expecting to return type %s but got type %s.\n", line, currentFunction->name, currentFunction->line, currentFunction->type, children[0]->type);
		n_errors++;
	}
	if(children[0] != NULL && children[0]->isArray) {
		printf("ERROR(%d): Cannot return an array.\n", line);
		n_errors++;
	}
	hasReturn = true;
	AST::propagateScopesSibling(table);
}

void Return::generate(SymbolTable *globals) {
	emitComment((char *)"RETURN");
	AST::generateChildren(globals); // this should end up in register 3
	emitRM((char *)"LDA", 2, 0, 3, (char *)"put answer in return register");
	emitRM((char *)"LD", 3, -1, 1, (char *)"recover old PC");
	emitRM((char *)"LD", 1, 0, 1, (char *)"pop the frame");
	emitRM((char *)"LDA", 7, 0, 3, (char *)"jump to old PC");
	emitComment((char *)"END RETURN");
	AST::generateSibling(globals);
}
