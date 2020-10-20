#include "semantic.h"

/*
"ERROR(%d): '%s' requires both operands be arrays or not but lhs is%s an array and rhs is%s an array.\n" //assignment
"ERROR(%d): Array '%s' should be indexed by type int but got %s.\n"
"ERROR(%d): Array index is the unindexed array '%s'.\n"
"ERROR(%d): The operation '%s' does not work with arrays.\n"
"ERROR(%d): The operation '%s' only works with arrays.\n"
*/

void analyze(AST *tree, SymbolTable *table) {
	tree->propagateScopes(table);
	if(table->lookupGlobal("main") == NULL) {
		printf("ERROR(LINKER): Procedure main is not declared.\n");
		n_errors++;
	}
}

void checkUsage(std::string sym, void *node) {
	Var *treeNode = (Var *)node;
	if(!treeNode->used && !treeNode->isFunction) {
		Var *var = (Var *)treeNode;
		if(!var->notified) {
			printf("WARNING(%d): The variable %s seems not to be used.\n", var->line, var->name);
			n_warnings++;
			var->notified = true;
		}
	}
}