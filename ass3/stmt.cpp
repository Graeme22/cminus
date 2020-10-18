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

void CompoundStatement::propagateScopes(SymbolTable *table) {
	if(!hasScopeException)
		table->enter("Compound");
	AST::propagateScopesChildren(table);
	if(!hasScopeException) {
		table->applyToAll(checkUsage);
		table->leave();
	}
	AST::propagateScopesSibling(table);
}

// If

If::If(int l, AST *condition, AST *stmt) {
	line = l;
	addChild(condition, 0);
	addChild(stmt, 1);
	if(stmt != NULL)
		stmt->hasScopeException = true;
}

If::If(int l, AST *condition, AST *stmt, AST *elseStmt): If(l, condition, stmt) {
	addChild(elseStmt, 2);
}

void If::print() {
	printPrefix();
	printf("If [line: %d]\n", line);
	AST::print();
}

void If::propagateScopes(SymbolTable *table) {
	table->enter("If");
	AST::propagateScopesChildren(table);
	table->applyToAll(checkUsage);
	table->leave();
	AST::propagateScopesSibling(table);
}

// While

While::While(int l, AST *cond, AST *stmt) {
	line = l;
	addChild(cond, 0);
	addChild(stmt, 1);
	if(stmt != NULL)
		stmt->hasScopeException = true;
}

void While::print() {
	printPrefix();
	printf("While [line: %d]\n", line);
	AST::print();
}

void While::propagateScopes(SymbolTable *table) {
	table->enter("While");
	AST::propagateScopesChildren(table);
	table->applyToAll(checkUsage);
	table->leave();
	AST::propagateScopesSibling(table);
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

void Return::propagateScopes(SymbolTable *table) {
	//if(children[0] != NULL)//handle array-ness later && children[0]->isArray)
	//	printf("ERROR(%d): Cannot return an array.\n", line);
	AST::propagateScopes(table);
}

// For

For::For(int l, TokenData *itr, TokenData *arr, AST *stmt) {
	line = l;
	Var *var = new Var(itr);
	var->initialized = true;
	addChild(var, 0);
	addChild(new VarAccess(arr), 1);
	addChild(stmt, 2);
	if(stmt != NULL)
		stmt->hasScopeException = true;
}

void For::print() {
	printPrefix();
	printf("For [line: %d]\n", line);
	AST::print();
}

void For::propagateScopes(SymbolTable *table) {
	table->enter("For");
	AST::propagateScopesChildren(table);
	table->applyToAll(checkUsage);
	table->leave();
	AST::propagateScopesSibling(table);
}