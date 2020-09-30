#include "printtree.h"

int main(int argc, char *argv[]) {
	tree = new AST();
	tree->index = -1;

	// -d: turn on yydebug
	// -p: print parse tree
	// -P: print AST & node types
	int dflag = 0, pflag = 0, Pflag = 0;
	int c;
	int n_errors = 0, n_warnings = 0;

	while((c = ourGetopt(argc, argv, (char *)"dp")) != -1) {
		switch(c) {
		case 'd':
			dflag = 1;
			break;
		case 'p':
			pflag = 1;
			break;
		case '?':
			fprintf(stderr, "usage: c- [-d] [-p] file\n");
			return -1;
		}
	}

	if(dflag)
		yydebug = 1;

	if(optind < argc) {
		yyin = fopen(argv[optind], "r");
		yyparse();
		fclose(yyin);
	} else
		yyparse();

	if(n_errors == 0) {
		tree->propagateInfo();

		if(pflag)
			tree->print();

		// semantic analysis
		SymbolTable *table = new SymbolTable();
		analyze(tree);

		if(Pflag)
			table->print(printNode);
	}

	printf("Number of errors: %d\n", n_errors);
	printf("Number of warnings: %d\n", n_warnings);

	return 0;
}