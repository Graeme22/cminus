#include "stmt.h"

// CompoundStatement

CompoundStatement::CompoundStatement(int l, AST *vars, AST *stmt) {
	line = l;
	addChild(vars->sibling, 0);
	addChild(stmt->sibling, 1);
}

void CompoundStatement::print() {
	printPrefix();
	printf("Compound [line: %d]\n", line);
	AST::print();
}

// If

If::If(int l, AST *condition, AST *stmt) {
	line = l;
	addChild(condition, 0);
	addChild(stmt, 1);
}

If::If(int l, AST *condition, AST *stmt, AST *elseStmt): If(l, condition, stmt) {
	addChild(elseStmt, 2);
}

void If::print() {
	printPrefix();
	printf("If [line: %d]\n", line);
	AST::print();
}

// While

While::While(int l, AST *cond, AST *stmt) {
	line = l;
	addChild(cond, 0);
	addChild(stmt, 1);
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
	AST::print();
}

// Return

Return::Return(int l) {
	line = l;
}

Return::Return(int l, AST *stmt) {
	addChild(stmt, 0);
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
	addChild(new Var(itr), 0);
	addChild(new VarAccess(arr), 1);
	addChild(stmt, 2);
}

void For::print() {
	printPrefix();
	printf("For [line: %d]\n", line);
	AST::print();
}