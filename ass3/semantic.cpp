#include "semantic.h"

/*
"ERROR(%d): '%s' requires both operands be arrays or not but lhs is%s an array and rhs is%s an array.\n"
"ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n"
"ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n"
"ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n"
"ERROR(%d): Array '%s' should be indexed by type int but got %s.\n"
"ERROR(%d): Array index is the unindexed array '%s'.\n"
"ERROR(%d): Cannot index nonarray '%s'.\n"
"ERROR(%d): Cannot index nonarray.\n"
"ERROR(%d): Cannot return an array.\n"
"ERROR(%d): The operation '%s' does not work with arrays.\n"
"ERROR(%d): The operation '%s' only works with arrays.\n"
"ERROR(%d): Unary '%s' requires an operand of %s but was given %s.\n"
*/

void analyze(AST *tree, SymbolTable *table) {
	tree->propagateScopes(table);
	if(table->lookupGlobal("main") == NULL) {
		printf("ERROR(LINKER): Procedure main is not declared.\n");
		n_errors++;
	}
}

void checkUsage(std::string sym, void *node) {
	AST *treeNode = (AST *)node;
	if(!treeNode->used && !treeNode->isFunction) {
		Var *var = (Var *)treeNode;
		if(!var->notified) {
			printf("WARNING(%d): The variable %s seems not to be used.\n", var->line, var->name);
			n_warnings++;
			var->notified = true;
		}
	}
}