#include "stmt.h"

// CompoundStatement

CompoundStatement::CompoundStatement(int l, AST *vars, AST *stmt) {
	line = l;
	// append because list has a child and is hidden
	append(vars);
	append(stmt);
}

void CompoundStatement::print() {
	printPrefix();
	printf("Compound [line: %d]\n", line);
	AST::print();
}

// If

If::If(int l, AST *condition, AST *stmt) {
	line = l;
	addChild(condition);
	addChild(stmt);
}

If::If(int l, AST *condition, AST *stmt, AST *elseStmt): If(l, condition, stmt) {
	addChild(elseStmt);
}

void If::print() {
	printPrefix();
	printf("If [line: %d]\n", line);
	AST::print();
}

// While

While::While(int l, AST *cond, AST *stmt) {
	line = l;
	addChild(cond);
	addChild(stmt);
}

void While::print() {
	printPrefix();
	printf("While [line: %d]\n", line);
	AST::print();
}

// Break

Break::Break(int l) {
	line = l;
}

void Break::print() {
	printPrefix();
	printf("Break [line: %d]\n", line);
}

// Return

Return::Return(int l) {
	line = l;
}

Return::Return(int l, AST *stmt) {
	addChild(stmt);
	line = l;
}

void Return::print() {
	printPrefix();
	printf("Return [line: %d]\n", line);
	AST::print();
}

// For

For::For(int l, TokenData *itr, TokenData *arr, AST *stmt) {
	line = l;
	iterator = strdup(itr->tokenString);
	array = strdup(arr->tokenString);
	addChild(stmt);
}

void For::print() {
	printPrefix();
	printf("For [line: %d]\n", line);
	AST::print();
}