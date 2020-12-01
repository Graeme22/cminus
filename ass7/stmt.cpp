#include "stmt.h"

// CompoundStatement

CompoundStatement::CompoundStatement(int l, AST *vars, AST *stmt) {
	line = l;
	addChild(vars->sibling, 0);
	addChild(stmt->sibling, 1);
}

void CompoundStatement::print(bool showMemory) {
	printPrefix();
	printf("Compound [line: %d]\n", line);
	AST::print(showMemory);
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

void If::print(bool showMemory) {
	printPrefix();
	printf("If [line: %d]\n", line);
	AST::print(showMemory);
}

void If::propagateScopes(SymbolTable *table) {
	table->enter("If");
	children[0]->propagateScopes(table);
	if(strcmp(children[0]->type, (char *)"bool") != 0 && strcmp(children[0]->type, (char *)"undefined") != 0) {
		printf("ERROR(%d): Expecting Boolean test condition in if statement but got type %s.\n", line, children[0]->type);
		n_errors++;
	}
	if(children[0]->isArray) {
		printf("ERROR(%d): Cannot use array as test condition in if statement.\n", line);
		n_errors++;
	}
	if(children[1] != NULL)
		children[1]->propagateScopes(table);
	table->applyToAll(checkUsage);
	table->leave();
	if(children[2] != NULL)
		children[2]->propagateScopes(table);
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

void While::print(bool showMemory) {
	printPrefix();
	printf("While [line: %d]\n", line);
	AST::print(showMemory);
}

void While::propagateScopes(SymbolTable *table) {
	table->enter("While");
	loopDepth++;
	children[0]->propagateScopes(table);
	if(strcmp(children[0]->type, (char *)"bool") != 0 && strcmp(children[0]->type, (char *)"undefined") != 0) {
		printf("ERROR(%d): Expecting Boolean test condition in while statement but got type %s.\n", line, children[0]->type);
		n_errors++;
	}
	if(children[0]->isArray) {
		printf("ERROR(%d): Cannot use array as test condition in while statement.\n", line);
		n_errors++;
	}
	if(children[1] != NULL)
		children[1]->propagateScopes(table);
	table->applyToAll(checkUsage);
	table->leave();
	loopDepth--;
	AST::propagateScopesSibling(table);
}

// Break

Break::Break(int l) {
	line = l;
}

void Break::print(bool showMemory) {
	printPrefix();
	printf("Break [line: %d]\n", line);
	AST::print(showMemory);
}

void Break::propagateScopes(SymbolTable *table) {
	AST::propagateScopesChildren(table);
	if(loopDepth == 0) {
		printf("ERROR(%d): Cannot have a break statement outside of loop.\n", line);
		n_errors++;
	}
	AST::propagateScopesSibling(table);
}

// For

For::For(int l, TokenData *itr, TokenData *arr, AST *stmt) {
	line = l;
	Var *child = new Var(itr);
	child->initialized = true;
	child->isArray = false;
	addChild(child, 0);
	addChild(new Id(arr), 1);
	addChild(stmt, 2);
	if(stmt != NULL)
		stmt->hasScopeException = true;
}

void For::print(bool showMemory) {
	printPrefix();
	printf("For [line: %d]\n", line);
	AST::print(showMemory);
}

void For::propagateScopes(SymbolTable *table) {
	table->enter("For");
	loopDepth++;
	children[0]->propagateScopes(table);
	children[1]->propagateScopes(table);
	if(strcmp(children[1]->type, (char *)"undefined") != 0)
		children[0]->type = strdup(children[1]->type);
	if(!children[1]->isArray) {
		printf("ERROR(%d): For statement requires that symbol '%s' be an array to loop through.\n", children[1]->line, ((Id *)children[1])->name);
		n_errors++;
	}
	if(children[2] != NULL)
		children[2]->propagateScopes(table);
	table->applyToAll(checkUsage);
	table->leave();
	loopDepth--;
	AST::propagateScopesSibling(table);
}