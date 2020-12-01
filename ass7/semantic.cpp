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
	FunDeclaration *outnl = new FunDeclaration(NULL, buildDummy((char *)"outnl"), NULL);
	table->insert(input->name, input);
	table->insert(inputb->name, inputb);
	table->insert(inputc->name, inputc);
	table->insert(output->name, output);
	table->insert(outputb->name, outputb);
	table->insert(outputc->name, outputc);
	table->insert(outnl->name, outnl);

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