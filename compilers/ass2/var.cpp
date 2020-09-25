#include "var.h"

// VarDeclaration

VarDeclaration::VarDeclaration(TokenData *data, AST *node) {
	type = strdup(data->tokenString);
	children.push_back(node);
}

void VarDeclaration::print() {
	((VarList *)children[0])->print(type);
	if(sibling != NULL)
		sibling->print();
}

// ScopedVarDeclaration

ScopedVarDeclaration::ScopedVarDeclaration(TokenData *data, AST *node, bool toggle) {
	type = strdup(data->tokenString);
	child = (VarList *)node;
	isStatic = toggle;
}

void ScopedVarDeclaration::print() {
	child->print(type);
}

// VarList

VarList::VarList(AST *node) {
	child = (Var *)node;
}

void VarList::print(char *type) {
	child->print(type);
}

void VarList::append(AST *node) {
	child->append(node);
}

// Var

Var::Var(TokenData *data) {
	name = strdup(data->tokenString);
	line = data->line;
	isArray = false;
}

Var::Var(TokenData *data, TokenData *size): Var(data) {
	arraySize = size->nValue;
	isArray = true;
}

void Var::print(char *type) {
	if(isArray)
		printf("Var %s is array of type %s [line: %d]\n", name, type, line);
	else
		printf("Var %s of type %s [line: %d]\n", name, type, line);
	if(value != NULL)
		value->print();
	if(sibling != NULL)
		((Var *)sibling)->print(type);
}

void Var::setValue(AST *v) {
	value = v;
}

// VarAccess

VarAccess::VarAccess(TokenData *data) {
	name = strdup(data->tokenString);
	isArray = false;
	line = data->line;
}

VarAccess::VarAccess(int l, AST *v, AST *l2) {
	line = l;
	var = v;
	loc = l2;
	isArray = true;
}

void VarAccess::print() {
	if(var == NULL)
		printf("Id: %s [line: %d]\n", name, line);
	else {
		printf("Op: [ [line: %d]\n", line);
		var->print();
		loc->print();
	}
}