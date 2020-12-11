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
	isGlobal = false;
	mSize = 1;
}

Var::Var(TokenData *left, TokenData *right): Var(left) {
	isArray = true;
	arraySize = right->nValue;
	mSize = arraySize + 1;
}

void Var::print(bool showMemory) {
	printPrefix();
	char *mData;
	if(showMemory) {
		mData = (char *)malloc(50);
		sprintf(mData, " [mem: %s  size: %d  loc: %d]", mType, mSize, mOffset);
	}
	if(isArray) {
		if(strcmp(type, "undefined") != 0) {
			if(isStatic)
				printf("Var %s: static array of type %s%s [line: %d]\n", name, type, (showMemory ? mData : (char *)""), line);
			else
				printf("Var %s: array of type %s%s [line: %d]\n", name, type, (showMemory ? mData : (char *)""), line);
		} else // if it's undefined we won't know whether it's static
			printf("Var %s: array of undefined type%s [line: %d]\n", name, (showMemory ? mData : (char *)""), line);
	} else {
		if(strcmp(type, "undefined") != 0) {
			if(isStatic)
				printf("Var %s: static type %s%s [line: %d]\n", name, type, (showMemory ? mData : (char *)""), line);
			else
				printf("Var %s: type %s%s [line: %d]\n", name, type, (showMemory ? mData : (char *)""), line);
		} else
			printf("Var %s: undefined type%s [line: %d]\n", name, (showMemory ? mData : (char *)""), line);
	}
	AST::print(showMemory);
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
	// memory management
	if(isStatic || table->depth() == 1) { // we're in global scope
		if(isStatic)
			mType = (char *)"Static";
		else
			mType = (char *)"Global";
		mOffset = goffset - (isArray ? 1 : 0); // the first index of an array is the size, we'll treat it as location -1
		goffset -= mSize;
		isGlobal = true;
	} else {
		mType = (char *)"Local";
		mOffset = foffset - (isArray ? 1 : 0);
		foffset -= mSize;
		isGlobal = false;
	}
	AST::propagateScopesSibling(table);
}

void Var::initialize(SymbolTable *table) {
	void *result = table->lookup(name);
	if(result != NULL) {
		Var *var = (Var *)result;
		var->initialized = true;
	}
}

void Var::generate(SymbolTable *table) {
	if(isArray) {
		emitRM((char *)"LDC", 3, arraySize, 6, (char *)"Load size of array", name);
		// size is stored at 0th element
		emitRM((char *)"ST", 3, mOffset + 1, (isGlobal ? 0 : 1), (char *)"Store size of array", name);
	}
	if(children[0] != NULL) {
		children[0]->generate(table);
		emitRM((char *)"ST", 3, mOffset, (isGlobal ? 0 : 1), (char *)"Initialize variable", name);
	}
}

// Id

Id::Id(TokenData *data): Var(data) {}

void Id::print(bool showMemory) {
	printPrefix();
	char *mData;
	if(showMemory) {
		mData = (char *)malloc(50);
		sprintf(mData, " [mem: %s  size: %d  loc: %d]", mType, mSize, mOffset);
	}
	if(isArray) {
		if(strcmp(type, "undefined") != 0) {
			if(isStatic)
				printf("Id %s: static array of type %s%s [line: %d]\n", name, type, (showMemory ? mData : (char *)""), line);
			else
				printf("Id %s: array of type %s%s [line: %d]\n", name, type, (showMemory ? mData : (char *)""), line);
		} else // if it's undefined we won't know whether it's static
			printf("Id %s: array of undefined type%s [line: %d]\n", name, (showMemory ? mData : (char *)""), line);
	} else {
		if(strcmp(type, "undefined") != 0) {
			if(isStatic)
				printf("Id %s: static type %s%s [line: %d]\n", name, type, (showMemory ? mData : (char *)""), line);
			else
				printf("Id %s: type %s%s [line: %d]\n", name, type, (showMemory ? mData : (char *)""), line);
		} else
			printf("Id %s: undefined type%s [line: %d]\n", name, (showMemory ? mData : (char *)""), line);
	}
	AST::print(showMemory);
}

void Id::propagateScopes(SymbolTable *table) {
	void *result = table->lookup(name);
	if(result == NULL) {
		printf("ERROR(%d): Variable '%s' is not declared.\n", line, name);
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
			isGlobal = var->isGlobal;
			mType = var->mType != NULL ? strdup(var->mType) : NULL;
			mSize = var->mSize;
			mOffset = var->mOffset;
			var->used = true;
			if(initialized)
				var->initialized = true;
			if(checkInitialization && !var->initialized && !var->notified) {
				printf("WARNING(%d): Variable %s may be uninitialized when used here.\n", line, name);
				n_warnings++;
				var->notified = true;
			}
		}	
	}
	AST::propagateScopes(table);
}

void Id::generate(SymbolTable *globals) {
	if(isArray)
		emitRM((char *)"LDA", 3, mOffset, (isGlobal ? 0 : 1), (char *)"Load address of array", name);
	else
		emitRM((char *)"LD", 3, mOffset, (isGlobal ? 0 : 1), (char *)"Load variable", name);
}