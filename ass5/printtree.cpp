#include "printtree.h"

int n_errors = 0;
int n_warnings = 0;
bool checkInitialization = true;
int loopDepth = 0;
FunDeclaration *currentFunction;
bool hasReturn = false;

int main(int argc, char *argv[]) {
	tree = new AST();
	tree->index = -1;

	// -d: turn on yydebug
	// -p: print parse tree
	// -P: print AST & node types
	int dflag = 0, Pflag = 0, hflag = 0, Sflag = 0;
	int c;

	while((c = ourGetopt(argc, argv, (char *)"dPhS")) != -1) {
		switch(c) {
		case 'd':
			dflag = 1;
			break;
		case 'P':
			Pflag = 1;
			break;
		case 'h':
			hflag = 1;
			break;
		case 'S':
			Sflag = 1;
			break;
		case '?':
			usage();
			return -1;
		}
	}

	if(dflag)
		yydebug = 1;

	if(hflag)
		usage();

	// create map
	initErrorProcessing();

	if(optind < argc) {
		yyin = fopen(argv[optind], "r");
		yyparse();
		fclose(yyin);
	} else
		yyparse();

	if(n_errors == 0) {
		tree->propagateInfo();

		// semantic analysis
		SymbolTable *table = new SymbolTable();
		table->debug(Sflag);

		analyze(tree, table);
	}

	printf("Number of warnings: %d\n", n_warnings);
	printf("Number of errors: %d\n", n_errors);

	if(n_errors == 0) {
		if(Pflag)
			tree->print();

		// code generation
		// TODO
	}

	return 0;
}

void usage() {
	printf("Usage: c- [options] [sourceFile]\n  -d  turn on Bison debugging\n  -h  this usage message\n  -P  print abstract syntax tree + types\n  -S  turn on syntax table debugging\n");
}