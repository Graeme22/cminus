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
	loopDepth++;
	AST::propagateScopesChildren(table);
	table->applyToAll(checkUsage);
	table->leave();
	loopDepth--;
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

void Break::propagateScopes(SymbolTable *table) {
	AST::propagateScopesChildren(table);
	if(loopDepth == 0)
		printf("ERROR(%d): Cannot have a break statement outside of loop.\n", line);
	AST::propagateScopesSibling(table);
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
	AST::propagateScopesChildren(table);
	if(children[0] != NULL && children[0]->isArray) {
		printf("ERROR(%d): Cannot return an array.\n", line);
		n_errors++;
	}
	AST::propagateScopesSibling(table);
}

// For

For::For(int l, TokenData *itr, TokenData *arr, AST *stmt) {
	line = l;
	Var *child = new Var(itr);
	child->initialized = true;
	addChild(child, 0);
	addChild(new Id(arr), 1);
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
	loopDepth++;
	AST::propagateScopesChildren(table);
	if(!children[1]->isArray)
		printf("ERROR(%d): For statement requires that symbol '%s' be an array to loop through.\n", line, ((Id *)children[1])->name);
	table->applyToAll(checkUsage);
	table->leave();
	loopDepth--;
	AST::propagateScopesSibling(table);
}