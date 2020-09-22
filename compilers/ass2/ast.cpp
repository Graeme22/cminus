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
	statement = s;
	type = (char *)"void";	
}

FunDeclaration::FunDeclaration(TokenData *t, TokenData *n, AST *p, AST *s): FunDeclaration(n, p, s) {
	type = strdup(t->tokenString);
}

void FunDeclaration::print() {
	printf("Func %s returns type %s [line: %d]\n", name, type, line);
	if(params != NULL)
		params->print();
	if(statement != NULL)
		statement->print();
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

// CompoundStatement

CompoundStatement::CompoundStatement(int l, AST *vars, AST *stmts) {
	line = l;
	localDeclarations = vars;
	statementList = stmts;
}

void CompoundStatement::print() {
	printf("Compound [line: %d]\n", line);
	// print children
	if(localDeclarations != NULL)
		localDeclarations->print();
	if(statementList != NULL)
		statementList->print();
}

// If

If::If(int l, AST *c, AST *i) {
	line = l;
	condition = c;
	ifStmt = i;
}

If::If(int l, AST *c, AST *i, AST *e): If(l, c, i) {
	elseStmt = e;
}

void If::print() {
	printf("If [line: %d]\n", line);
	condition->print();
	if(ifStmt != NULL)
		ifStmt->print();
	if(elseStmt != NULL)
		elseStmt->print();
}

// Relation

Relation::Relation(TokenData *data, AST *l, AST *r) {
	type = data->tokenClass;
	left = l;
	right = r;
	str = strdup(data->tokenString);
	line = data->line;
}

void Relation::print() {
	printf("Op: %s [line: %d]\n", str, line);
	left->print();
	right->print();
}

// Logic Expression

LogicExpression::LogicExpression(TokenData *data, AST *l, AST *r): LogicExpression(data, l) {
	right = r;
}

LogicExpression::LogicExpression(TokenData *data, AST *c) {
	left = c;
	type = data->tokenClass;
	str = strdup(data->tokenString);
	line = data->line;
}

void LogicExpression::print() {
	printf("Op: %s [line: %d]\n", str, line);
	left->print();
	if(right != NULL)
		right->print();
}

// Operation

Operation::Operation(TokenData *data, AST *c) {
	left = c;
	type = data->tokenClass;
	str = strdup(data->tokenString);
	line = data->line;
}

Operation::Operation(TokenData *data, AST *l, AST *r): Operation(data, l) {
	right = r;
}

void Operation::print() {
	printf("Op: %s [line %d]\n", str, line);
	left->print();
	if(right != NULL)
		right->print();
}

// VarAccess

VarAccess::VarAccess(TokenData *data) {
	name = strdup(data->tokenString);
	isArray = false;
	line = data->line;
}

VarAccess::VarAccess(AST *mut, AST *loc) {
	//name = strdup(data->tokenString);
	//line = data->line;
	location = loc;
	isArray = true;
}

void VarAccess::print() {
	printf("Id: %s [line: %d]\n", name, line);
	if(location != NULL)
		location->print();
}