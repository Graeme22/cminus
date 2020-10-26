#include "semantic.h"

void analyze(AST *tree, SymbolTable *table) {
	// add I/O symbols to table
	FunDeclaration *input = new FunDeclaration((char *)"int", buildDummy((char *)"input"), NULL);
	FunDeclaration *inputb = new FunDeclaration((char *)"bool", buildDummy((char *)"inputb"), NULL);
	FunDeclaration *inputc = new FunDeclaration((char *)"char", buildDummy((char *)"inputc"), NULL);
	Par *p_i = new Par(buildDummy((char *)"*dummy"), false);
	p_i->type = (char *)"int";
	Par *p_b = new Par(buildDummy((char *)"*dummy"), false);
	p_b->type = (char *)"bool";
	Par *p_c = new Par(buildDummy((char *)"*dummy"), false);
	p_c->type = (char *)"char";
	FunDeclaration *output = new FunDeclaration(NULL, buildDummy((char *)"output"), p_i);
	FunDeclaration *outputb = new FunDeclaration(NULL, buildDummy((char *)"outputb"), p_b);
	FunDeclaration *outputc = new FunDeclaration(NULL, buildDummy((char *)"outputc"), p_c);
	table->insert(input->name, input);
	table->insert(inputb->name, inputb);
	table->insert(inputc->name, inputc);
	table->insert(output->name, output);
	table->insert(outputb->name, outputb);
	table->insert(outputc->name, outputc);

	// do semantic analysis
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

TokenData *buildDummy(char *name) {
	TokenData *td = new TokenData;
	td->line = -1;
	td->tokenString = strdup(name);
	return td;
}

/*
"ERROR(%d): Cannot have a break statement outside of loop.\n"
"ERROR(%d): Cannot use array as test condition in %s statement.\n"
"ERROR(%d): Cannot use function '%s' as a variable.\n"
"ERROR(%d): Expecting %s in parameter %i of call to '%s' declared on line %d but got %s.\n"
"ERROR(%d): Expecting Boolean test condition in %s statement but got %s.\n"
"ERROR(%d): Expecting array in parameter %i of call to '%s' declared on line %d.\n"
"ERROR(%d): For statement requires that symbol '%s' be an array to loop through.\n"
"ERROR(%d): Function '%s' at line %d is expecting no return value, but return has return value.\n"
"ERROR(%d): Function '%s' at line %d is expecting to return %s but got %s.\n"
"ERROR(%d): Function '%s' at line %d is expecting to return %s but return has no return value.\n"
"ERROR(%d): Function '%s' is not declared.\n"
"ERROR(%d): Initializer for variable '%s' is not a constant expression.\n"
"ERROR(%d): Not expecting array in parameter %i of call to '%s' declared on line %d.\n"
"ERROR(%d): The operation '%s' does not work with arrays.\n"
"ERROR(%d): The operation '%s' only works with an array or int.\n"
"ERROR(%d): The operation '%s' only works with arrays.\n"
"ERROR(%d): Too few parameters passed for function '%s' declared on line %d.\n"
"ERROR(%d): Too many parameters passed for function '%s' declared on line %d.\n"
"ERROR(%d): Variable '%s' is not declared.\n"
"ERROR(%d): Variable '%s' is of %s but is being initialized with an expression of %s.\n"
"WARNING(%d): Expecting to return %s but function '%s' has no return statement.\n"
*/