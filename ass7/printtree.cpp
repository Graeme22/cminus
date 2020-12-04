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

		// replace trailing .c-
		char *path = strdup(argv[optind]);
		int n = strlen(path);
		if(n > 3 && path[n - 1] == '-' && path[n - 2] == 'c' && path[n - 3] == '.') {
			path[n - 2] = 't';
			path[n - 1] = 'm';
		} else {
			printf("ERROR(I/O): Input filename must end in .c-\n");
			n_errors++;
			printf("Number of warnings: %d\n", n_warnings);
			printf("Number of errors: %d\n", n_errors);
			return -1;
		}
		
		code = fopen(path, "w+");
		// do code generation
		generate(argv[optind], tree, table);
		fclose(code);
	}

	printf("Number of warnings: %d\n", n_warnings);
	printf("Number of errors: %d\n", n_errors);

	return 0;
}

void usage() {
	printf("Usage: c- [options] [sourceFile]\n  -d  turn on Bison debugging\n  -h  this usage message\n  -P  print abstract syntax tree + types\n  -S  turn on syntax table debugging\n  -M  show memory usage\n");
}

// at this point the symbol table only contains the global scope, so functions and globals
void generate(char *filename, AST *tree, SymbolTable *globals) {
	// insert header comment
	emitComment((char *)"C- version:", VERSION);
	emitComment((char *)"by Graeme Holliday");
	emitComment((char *)"Input file:", filename);

	// backpatch a jump to init
	int entry = emitSkip(1);

	// input
	FunDeclaration *fun = (FunDeclaration *)globals->lookupGlobal((char *)"input");
	fun->loc = emitSkip(0);
	emitComment((char *)"FUNCTION input");
	emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
	emitRO((char *)"IN", 2, 2, 2, (char *)"Grab int input");
	emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
	emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust frame pointer");
	emitRM((char *)"LDA", 7, 0, 3, (char *)"Return");

	// output
	fun = (FunDeclaration *)globals->lookupGlobal((char *)"output");
	fun->loc = emitSkip(0);
	emitComment((char *)"FUNCTION output");
	emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
	emitRM((char *)"LD", 3, -2, 1, (char *)"Load parameter");
	emitRO((char *)"OUT", 3, 3, 3, (char *)"Output integer");
	emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
	emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust frame pointer");
	emitRM((char *)"LDA", 7, 0, 3, (char *)"Return");

	// inputb
	fun = (FunDeclaration *)globals->lookupGlobal((char *)"inputb");
	fun->loc = emitSkip(0);
	emitComment((char *)"FUNCTION inputb");
	emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
	emitRO((char *)"INB", 2, 2, 2, (char *)"Grab bool input");
	emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
	emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust frame pointer");
	emitRM((char *)"LDA", 7, 0, 3, (char *)"Return");

	// outputb
	fun = (FunDeclaration *)globals->lookupGlobal((char *)"outputb");
	fun->loc = emitSkip(0);
	emitComment((char *)"FUNCTION outputb");
	emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
	emitRM((char *)"LD", 3, -2, 1, (char *)"Load parameter");
	emitRO((char *)"OUTB", 3, 3, 3, (char *)"Output bool");
	emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
	emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust frame pointer");
	emitRM((char *)"LDA", 7, 0, 3, (char *)"Return");

	// inputc
	fun = (FunDeclaration *)globals->lookupGlobal((char *)"inputc");
	fun->loc = emitSkip(0);
	emitComment((char *)"FUNCTION inputc");
	emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
	emitRO((char *)"INC", 2, 2, 2, (char *)"Grab char input");
	emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
	emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust frame pointer");
	emitRM((char *)"LDA", 7, 0, 3, (char *)"Return");

	// outputc
	fun = (FunDeclaration *)globals->lookupGlobal((char *)"outputc");
	fun->loc = emitSkip(0);
	emitComment((char *)"FUNCTION outputc");
	emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
	emitRM((char *)"LD", 3, -2, 1, (char *)"Load parameter");
	emitRO((char *)"OUTC", 3, 3, 3, (char *)"Output char");
	emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
	emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust frame pointer");
	emitRM((char *)"LDA", 7, 0, 3, (char *)"Return");

	// outnl
	fun = (FunDeclaration *)globals->lookupGlobal((char *)"outnl");
	fun->loc = emitSkip(0);
	emitComment((char *)"FUNCTION outnl");
	emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
	emitRO((char *)"OUTNL", 3, 3, 3, (char *)"Output newline");
	emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
	emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust frame pointer");
	emitRM((char *)"LDA", 7, 0, 3, (char *)"Return");

	// main body of code
	emitComment((char *)"=================================================");
	tree->generate(globals);
	emitComment((char *)"=================================================");

	// init code
	emitComment((char *)"INIT");
	backPatchAJumpToHere(entry, (char *)"Jump to init [backpatch]");
	emitRM((char *)"LD", 0, 0, 0, (char *)"Set global pointer");
	// init globals, as statics have been omitted
	emitRM((char *)"LDA", 1, goffset, 0, (char *)"Set frame pointer");
	emitRM((char *)"ST", 1, 0, 1, (char *)"Store old frame pointer");
	emitRM((char *)"LDA", 3, 1, 7, (char *)"Return address");
	int loc = ((FunDeclaration *)globals->lookupGlobal((char *)"main"))->loc - emitSkip(0) - 1;
	emitRM((char *)"LDA", 7, loc, 7, (char *)"Jump to main");

}