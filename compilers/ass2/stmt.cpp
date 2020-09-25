#include "stmt.h"

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

// While

While::While(int l, AST *cond, AST *stmt) {
	line = l;
	condition = cond;
	statement = stmt;
}

void While::print() {
	printf("While [line: %d]\n", line);
	condition->print();
	if(statement != NULL)
		statement->print();
}

// Break

Break::Break(int l) {
	line = l;
}

void Break::print() {
	printf("Break [line: %d]\n", line);
}

// Return

Return::Return(int l) {
	line = l;
}

Return::Return(int l, AST *s) {
	stmt = s;
	line = l;
}

void Return::print() {
	printf("Return [line: %d]\n", line);
	if(stmt != NULL)
		stmt->print();
}

// For

For::For(int l, TokenData *data1, TokenData *data2, AST *s) {
	line = l;
	child1 = new Var(data1);
	child2 = new Var(data2);
	stmt = s;
}

void For::print() {
	printf("For [line: %d]\n", line);
	child1->print();
	child2->print();
	if(stmt != NULL)
		stmt->print();
}