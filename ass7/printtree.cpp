#include "printtree.h"

int n_errors = 0;
int n_warnings = 0;
bool checkInitialization = true;
int loopDepth = 0;
FunDeclaration *currentFunction;
bool hasReturn = false;
int foffset = 0, goffset = 0;

char *VERSION = (char *)"0.7.1";

int main(int argc, char *argv[]) {
	tree = new AST();
	tree->index = -1;

	// -d: turn on yydebug
	// -p: print parse tree
	// -P: print AST & node types
	int dflag = 0, Pflag = 0, hflag = 0, Sflag = 0, Mflag = 0;
	int c;

	while((c = ourGetopt(argc, argv, (char *)"dPhSM")) != -1) {
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
		case 'M':
			Mflag = 1;
			Pflag = 1;
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

		// create symbol table
		SymbolTable *table = new SymbolTable();
		table->debug(Sflag);

		// semantic analysis
		analyze(tree, table);

		if(Pflag)
			tree->print(Mflag == 1);

		// create output file
		// TODO: make this match input file name up to the .c-
		code = fopen("a.tm", "w+");

		// roughly
		// tree->generate(table[globals], goffset)
		loadIO(argv[optind]);

		fclose(code);
	}

	printf("Number of warnings: %d\n", n_warnings);
	printf("Number of errors: %d\n", n_errors);

	return 0;
}

void usage() {
	printf("Usage: c- [options] [sourceFile]\n  -d  turn on Bison debugging\n  -h  this usage message\n  -P  print abstract syntax tree + types\n  -S  turn on syntax table debugging\n  -M  show memory usage\n");
}

void loadIO(char *inFile) {
	// insert header comment
	emitComment("C- version:", VERSION);
	emitComment("by Graeme Holliday\t12/2/20");
	emitComment("Input file:", inFile);

	// input
	emitComment("FUNCTION input");
	emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
	emitComment("END");

	/*
	* FUNCTION input
	1:     ST  3,-1(1)	Store return address 
	2:     IN  2,2,2	Grab int input 
	3:     LD  3,-1(1)	Load return address 
	4:     LD  1,0(1)	Adjust fp 
	5:    JMP  7,0(3)	Return 
	* END FUNCTION input
	*/
}