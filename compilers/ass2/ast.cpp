#include "ast.h"

// AST

AST::AST() {
	sibling = NULL;
}

void AST::append(AST *node) {
	if(sibling == NULL)
		sibling = node;
	else {
		AST *itr;
		for(itr = sibling; itr->sibling != NULL; itr = itr->sibling);
		itr->sibling = node;
	}
}

void AST::print() {
	for(AST *itr = sibling; itr != NULL; itr = itr->sibling)
		itr->print();
}

// VarDeclaration

VarDeclaration::VarDeclaration(TokenData *data, AST *node) {
	type = strdup(data->tokenString);
	child = (VarList *)node;
}

void VarDeclaration::print() {
	child->print(type);
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
	if(sibling != NULL)
		((Var *)sibling)->print(type);
}

// Par

Par::Par(TokenData *data, bool toggle) {
	name = strdup(data->tokenString);
	line = data->line;
	isArray = toggle;
}

void Par::print(char *type) {
	if(isArray)
		printf("Param %s is array of type %s [line: %d]\n", name, type, line);
	else
		printf("Param %s of type %s [line: %d]\n", name, type, line);
	if(sibling != NULL)
		((Par *)sibling)->print(type);
}

// FunDeclaration

FunDeclaration::FunDeclaration(TokenData *n, AST *p, AST *s) {
	name = strdup(n->tokenString);
	line = n->line;
	if(p != NULL)
		params = (Params *)p;
	else
		params = NULL;
	statement = NULL; // statement = (Statement *)s;
	type = (char *)"void";	
}

FunDeclaration::FunDeclaration(TokenData *t, TokenData *n, AST *p, AST *s): FunDeclaration(n, p, s) {
	type = strdup(t->tokenString);
}

void FunDeclaration::print() {
	printf("Func %s returns type %s [line: %d]\n", name, type, line);
	if(params != NULL)
		params->print();
}

// ParamList

ParamList::ParamList(AST *node) {
	child = (Par *)node;
}

void ParamList::appendToChild(AST *node) {
	child->append(node);
}

void ParamList::setType(TokenData *data) {
	type = strdup(data->tokenString);
}

void ParamList::print() {
	child->print(type);
	if(sibling != NULL)
		sibling->print();
}

// Params

Params::Params(AST *node) {
	child = (ParamList *)node;
}

void Params::appendToChild(AST *node) {
	child->append(node);
}

void Params::print() {
	child->print();
}