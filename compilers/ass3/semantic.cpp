#include "semantic.h"

void analyze(AST *head) {
	// analysis here
}

void printNode(void *node) {
	// print here
}

/*
list of warnings

"ERROR(%d): '%s' is a simple variable and cannot be called.\n"
"ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n"
"ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n"
"ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n"
"ERROR(%d): Array '%s' should be indexed by type int but got %s.\n"
"ERROR(%d): Array index is the unindexed array '%s'.\n"
"ERROR(%d): Cannot index nonarray '%s'.\n"
"ERROR(%d): Cannot index nonarray.\n"
"ERROR(%d): Cannot return an array.\n"
"ERROR(%d): Cannot use function '%s' as a variable.\n"
"ERROR(%d): Symbol '%s' is already defined at line %d.\n"
"ERROR(%d): Symbol '%s' is not defined.\n"
"ERROR(%d): The operation '%s' does not work with arrays.\n"
"ERROR(%d): The operation '%s' only works with arrays.\n"
"ERROR(%d): Unary '%s' requires an operand of type %s but was given %s.\n"
"WARNING(%d): The variable %s seems not to be used.\n"
"WARNING(%d): Variable %s may be uninitialized when used here.\n"
*/