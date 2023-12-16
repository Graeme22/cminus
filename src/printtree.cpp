#include "printtree.h"

// global counters for warnings and errors
int n_errors = 0;
int n_warnings = 0;
// whether or not to check initialization errors
bool checkInitialization = true;
// used for semantic error message for break
// statement, which can't be used outside a loop
int loopDepth = 0;
// points to the current function if inside one
FunDeclaration *currentFunction;
// whether or not the current function has a return
// statement. used for semantic error messages
bool hasReturn = false;
// memory offset variables.
// goffset is offset from global pointer,
// foffset is offset from local frame pointer,
// and toffset is offset from end of current
// frame (used for temporary vars and params)
int foffset = 0, goffset = 0, toffset = 0;
// location for break statements to jump to
int break_loc = 0;
std::vector<llvm::BasicBlock *> breakBlocks;
// LLVM globals
std::unique_ptr<llvm::LLVMContext> context;
std::unique_ptr<llvm::Module> llvmModule;
std::unique_ptr<llvm::IRBuilder<>> builder;
std::map<std::string, llvm::Value *> namedValues;

char *VERSION = (char *)"0.8";

int main(int argc, char *argv[]) {
	tree = new AST();
	tree->index = -1;

	// -d: turn on yydebug
	// -p: print AST
	// -l: generate LLVM code
	int dflag = 0, pflag = 0, hflag = 0, sflag = 0, mflag = 0, lflag = 0;
	int c;

	while((c = ourGetopt(argc, argv, (char *)"dphsml")) != -1) {
		switch(c) {
		case 'd':
			dflag = 1;
			break;
		case 'p':
			pflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case 'm':
			mflag = 1;
			pflag = 1;
			break;
		case 'l':
			lflag = 1;
			break;
		case '?':
		case 'h':
			usage();
			return -1;
		}
	}

	if(dflag)
		yydebug = 1;

	char *path = strdup(argv[optind]);
	// init LLVM things
	context = std::make_unique<llvm::LLVMContext>();
	llvmModule = std::make_unique<llvm::Module>(path, *context);
	builder = std::make_unique<llvm::IRBuilder<>>(*context);
	// create map
	initErrorProcessing();

	if(optind < argc) {
		yyin = fopen(path, "r");
		yyparse();
		fclose(yyin);
	} else
		yyparse();

	// create symbol table
	SymbolTable *table = new SymbolTable();
	table->debug(sflag);

	if(n_errors == 0) {
		tree->propagateInfo();

		// semantic analysis
		analyze(tree, table);

		if(pflag)
			tree->print(mflag == 1);
	}

	printf("Number of warnings: %d\n", n_warnings);
	printf("Number of errors: %d\n", n_errors);

	// do code generation
	if(n_errors == 0) {
		// replace trailing .c-
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

		if(lflag) {
			// do LLVM codegen
			generateLLVM(tree);
			// write LLVM output to .ll file
			path[n - 2] = 'l';
			path[n - 1] = 'l';
			std::string fileName = path;
			std::error_code errorCode;
			llvm::raw_fd_ostream outLL(fileName, errorCode);
			llvmModule->print(outLL, nullptr);
		} else {
			// do normal codegen
			code = fopen(path, "w+");
			generate(argv[optind], tree, table);
			fclose(code);
		}
	}

	return 0;
}

void usage() {
	printf("Usage: c- [options] [sourceFile]\n  -d  turn on Bison debugging\n  -h  this usage message\n  -p  print abstract syntax tree + types\n  -s  turn on syntax table debugging\n  -m  show memory usage\n  -l  generate LLVM code\n");
}

void generateLLVM(AST *tree) {
	//int printf(const char *format, ...);
	auto charPtrTy = builder->getInt8PtrTy();
	llvmModule->getOrInsertFunction("printf", llvm::FunctionType::get(builder->getInt32Ty(), charPtrTy, true));
	//int scanf(const char *format, ...);
	llvmModule->getOrInsertFunction("scanf", llvm::FunctionType::get(builder->getInt32Ty(), charPtrTy, true));
	// outnl
	auto outnlType = llvm::FunctionType::get(builder->getVoidTy(), false);
	auto outnl = llvm::Function::Create(outnlType, llvm::Function::ExternalLinkage, "outnl", *llvmModule);
	llvm::BasicBlock *outnlBB = llvm::BasicBlock::Create(*context, "entry", outnl);
	builder->SetInsertPoint(outnlBB);
	llvm::Value *nl = builder->CreateGlobalStringPtr("\n");
	std::vector<llvm::Value*> outnlArgs{nl};
	auto fnPrintf = llvmModule->getFunction("printf");
	builder->CreateCall(fnPrintf, outnlArgs);
	builder->CreateRetVoid();
	llvm::verifyFunction(*outnl);
	// output
	std::vector<llvm::Type*> outputPars{llvm::Type::getInt32Ty(*context)};
	auto outputType = llvm::FunctionType::get(builder->getVoidTy(), outputPars, false);
	auto output = llvm::Function::Create(outputType, llvm::Function::ExternalLinkage, "output", *llvmModule);
	llvm::BasicBlock *outputBB = llvm::BasicBlock::Create(*context, "entry", output);
	builder->SetInsertPoint(outputBB);
	llvm::Value *d = builder->CreateGlobalStringPtr("%d");
	std::vector<llvm::Value*> outputArgs{d};
	for(auto &arg : output->args())
		outputArgs.push_back(&arg);
	builder->CreateCall(fnPrintf, outputArgs);
	builder->CreateRetVoid();
	llvm::verifyFunction(*output);
	// outputc
	std::vector<llvm::Type*> outputcPars{llvm::Type::getInt32Ty(*context)};
	auto outputcType = llvm::FunctionType::get(builder->getVoidTy(), outputPars, false);
	auto outputc = llvm::Function::Create(outputcType, llvm::Function::ExternalLinkage, "outputc", *llvmModule);
	llvm::BasicBlock *outputcBB = llvm::BasicBlock::Create(*context, "entry", outputc);
	builder->SetInsertPoint(outputcBB);
	llvm::Value *c = builder->CreateGlobalStringPtr("%c");
	std::vector<llvm::Value*> outputcArgs{c};
	for(auto &arg : outputc->args())
		outputcArgs.push_back(&arg);
	builder->CreateCall(fnPrintf, outputcArgs);
	builder->CreateRetVoid();
	llvm::verifyFunction(*outputc);
	// outputb
	std::vector<llvm::Type*> outputbPars{llvm::Type::getInt1Ty(*context)};
	auto outputbType = llvm::FunctionType::get(builder->getVoidTy(), outputbPars, false);
	auto outputb = llvm::Function::Create(outputbType, llvm::Function::ExternalLinkage, "outputb", *llvmModule);
	llvm::BasicBlock *outputbBB = llvm::BasicBlock::Create(*context, "entry", outputb);
	builder->SetInsertPoint(outputbBB);
	llvm::Value *b = builder->CreateGlobalStringPtr("%b");
	std::vector<llvm::Value*> outputbArgs{b};
	for(auto &arg : outputb->args())
		outputbArgs.push_back(&arg);
	builder->CreateCall(fnPrintf, outputbArgs);
	builder->CreateRetVoid();
	llvm::verifyFunction(*outputb);
	// input
	auto inputType = llvm::FunctionType::get(builder->getInt32Ty(), false);
	auto input = llvm::Function::Create(inputType, llvm::Function::ExternalLinkage, "input", *llvmModule);
	llvm::BasicBlock *inputBB = llvm::BasicBlock::Create(*context, "entry", input);
	builder->SetInsertPoint(inputBB);
	llvm::AllocaInst *inputVal = builder->CreateAlloca(llvm::Type::getInt32Ty(*context), nullptr, "tmp");
	std::vector<llvm::Value*> inputArgs{d, inputVal};
	auto fnScanf = llvmModule->getFunction("scanf");
	builder->CreateCall(fnScanf, inputArgs);
	auto res = builder->CreateLoad(llvm::Type::getInt32Ty(*context), inputVal);
	builder->CreateRet(res);
	llvm::verifyFunction(*input);
	// inputc
	auto inputcType = llvm::FunctionType::get(builder->getInt8Ty(), false);
	auto inputc = llvm::Function::Create(inputcType, llvm::Function::ExternalLinkage, "inputc", *llvmModule);
	llvm::BasicBlock *inputcBB = llvm::BasicBlock::Create(*context, "entry", inputc);
	builder->SetInsertPoint(inputcBB);
	llvm::AllocaInst *inputcVal = builder->CreateAlloca(llvm::Type::getInt8Ty(*context), nullptr, "tmpc");
	std::vector<llvm::Value*> inputcArgs{c, inputcVal};
	builder->CreateCall(fnScanf, inputcArgs);
	auto resc = builder->CreateLoad(llvm::Type::getInt8Ty(*context), inputcVal);
	builder->CreateRet(resc);
	llvm::verifyFunction(*input);
	// inputb (currently requires inputting 0 or 1)
	auto inputbType = llvm::FunctionType::get(builder->getInt1Ty(), false);
	auto inputb = llvm::Function::Create(inputbType, llvm::Function::ExternalLinkage, "inputb", *llvmModule);
	llvm::BasicBlock *inputbBB = llvm::BasicBlock::Create(*context, "entry", inputb);
	builder->SetInsertPoint(inputbBB);
	llvm::AllocaInst *inputbVal = builder->CreateAlloca(llvm::Type::getInt32Ty(*context), nullptr, "tmpb");
	std::vector<llvm::Value*> inputbArgs{b, inputbVal};
	builder->CreateCall(fnScanf, inputbArgs);
	auto resb = builder->CreateLoad(llvm::Type::getInt32Ty(*context), inputbVal);
	auto resbCast = builder->CreateIntCast(resb, llvm::Type::getInt1Ty(*context), false);
	builder->CreateRet(resbCast);
	llvm::verifyFunction(*inputb);

	tree->sibling->codegen();
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
	emitComment((char *)"END FUNCTION input");

	// inputb
	fun = (FunDeclaration *)globals->lookupGlobal((char *)"inputb");
	fun->loc = emitSkip(0);
	emitComment((char *)"FUNCTION inputb");
	emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
	emitRO((char *)"INB", 2, 2, 2, (char *)"Grab bool input");
	emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
	emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust frame pointer");
	emitRM((char *)"LDA", 7, 0, 3, (char *)"Return");
	emitComment((char *)"END FUNCTION inputb");

	// inputc
	fun = (FunDeclaration *)globals->lookupGlobal((char *)"inputc");
	fun->loc = emitSkip(0);
	emitComment((char *)"FUNCTION inputc");
	emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
	emitRO((char *)"INC", 2, 2, 2, (char *)"Grab char input");
	emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
	emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust frame pointer");
	emitRM((char *)"LDA", 7, 0, 3, (char *)"Return");
	emitComment((char *)"END FUNCTION inputc");

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
	emitComment((char *)"END FUNCTION output");

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
	emitComment((char *)"END FUNCTION outputb");

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
	emitComment((char *)"END FUNCTION outputc");

	// outnl
	fun = (FunDeclaration *)globals->lookupGlobal((char *)"outnl");
	fun->loc = emitSkip(0);
	emitComment((char *)"FUNCTION outnl");
	emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
	emitRO((char *)"OUTNL", 3, 3, 3, (char *)"Output newline");
	emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
	emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust frame pointer");
	emitRM((char *)"LDA", 7, 0, 3, (char *)"Return");
	emitComment((char *)"END FUNCTION outnl");

	// main body of code
	emitComment((char *)"=========================================");
	AST *itr;
	for(itr = tree->sibling; itr != NULL; itr = itr->sibling)
		if(((Var *)itr)->isFunction)
			itr->generate(globals, false);
	emitComment((char *)"=========================================");

	// init code
	emitComment((char *)"INIT");
	backPatchAJumpToHere(entry, (char *)"Jump to init [backpatch]");
	emitRM((char *)"LD", 0, 0, 0, (char *)"Set global pointer");
	emitRM((char *)"LDA", 1, goffset, 0, (char *)"Set frame pointer");
	emitRM((char *)"ST", 1, 0, 1, (char *)"Store old frame pointer");
	// init globals, as statics have been omitted
	toffset = -2;
	for(itr = tree->sibling; itr != NULL; itr = itr->sibling)
		if(!((Var *)itr)->isFunction)
			itr->generate(globals, false);

	// call main
	emitRM((char *)"LDA", 3, 1, 7, (char *)"Return address");
	int loc = ((FunDeclaration *)globals->lookupGlobal((char *)"main"))->loc - emitSkip(0) - 1;
	emitRM((char *)"JMP", 7, loc, 7, (char *)"Jump to main");
	emitComment((char *)"END INIT");

}