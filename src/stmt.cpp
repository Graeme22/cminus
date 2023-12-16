#include "stmt.h"

// CompoundStatement

CompoundStatement::CompoundStatement(int l, AST *vars, AST *stmt) {
	line = l;
	addChild(vars->sibling, 0);
	addChild(stmt->sibling, 1);
}

void CompoundStatement::print(bool showMemory) {
	printPrefix();
	printf("Compound [line: %d]\n", line);
	AST::print(showMemory);
}

void CompoundStatement::propagateScopes(SymbolTable *table) {
	if(!hasScopeException)
		table->enter("Compound");
	AST::propagateScopesChildren(table);
	if(!hasScopeException) {
		table->applyToAll(checkUsage);
		size = table->leave();
	}
	AST::propagateScopesSibling(table);
}

void CompoundStatement::generate(SymbolTable *globals, bool doSibling) {
	int toffset_old = toffset;
	if(!hasScopeException) {
		emitComment((char *)"COMPOUND");
		toffset = size;
	}
	AST::generateChildren(globals);
	if(!hasScopeException) {
		toffset = toffset_old;
		emitComment((char *)"END COMPOUND");
	}
	if(doSibling)
		AST::generateSibling(globals);
}

llvm::Value *CompoundStatement::codegen() {
	llvm::Value *toReturn = nullptr;
	if(children[0] != NULL)
		toReturn = children[0]->codegen();
	if(children[1] != NULL)
		toReturn = children[1]->codegen();
	if(sibling != NULL)
		toReturn = sibling->codegen();

	return toReturn;
}

// If

If::If(int l, AST *condition, AST *stmt) {
	line = l;
	addChild(condition, 0);
	addChild(stmt, 1);
	if(stmt != NULL)
		stmt->hasScopeException = true;
}

If::If(int l, AST *condition, AST *stmt, AST *elseStmt): If(l, condition, stmt) {
	addChild(elseStmt, 2);
}

void If::print(bool showMemory) {
	printPrefix();
	printf("If [line: %d]\n", line);
	AST::print(showMemory);
}

void If::propagateScopes(SymbolTable *table) {
	table->enter("If");
	children[0]->propagateScopes(table);
	if(strcmp(children[0]->type, (char *)"bool") != 0 && strcmp(children[0]->type, (char *)"undefined") != 0) {
		printf("ERROR(%d): Expecting Boolean test condition in if statement but got type %s.\n", line, children[0]->type);
		n_errors++;
	}
	if(children[0]->isArray) {
		printf("ERROR(%d): Cannot use array as test condition in if statement.\n", line);
		n_errors++;
	}
	if(children[1] != NULL)
		children[1]->propagateScopes(table);
	table->applyToAll(checkUsage);
	size = table->leave();
	if(children[2] != NULL)
		children[2]->propagateScopes(table);
	AST::propagateScopesSibling(table);
}

void If::generate(SymbolTable *globals, bool doSibling) {
	int toffset_old = toffset;
	toffset = size;
	emitComment((char *)"IF");
	children[0]->generate(globals);
	int if_loc = emitSkip(1), else_loc; // backpatch a jump to here
	if(children[1] != NULL)
		children[1]->generate(globals);
	if(children[2] != NULL)
		else_loc = emitSkip(1);
	backPatchAJumpToHere((char *)"JZR", 3, if_loc, (char *)"Jump if false [backpatch]");
	if(children[2] != NULL) {
		emitComment((char *)"ELSE");
		children[2]->generate(globals);
		backPatchAJumpToHere(else_loc, (char *)"Jump past if statement [backpatch]");
	}
	emitComment((char *)"END IF");
	toffset = toffset_old;
	if(doSibling)
		AST::generateSibling(globals);
}

llvm::Value *If::codegen() {
	llvm::Value *condition = children[0]->codegen();
	condition = builder->CreateICmpNE(condition, llvm::ConstantInt::get(*context, llvm::APInt(1, 0)));
	// if body
	llvm::Function *fn = builder->GetInsertBlock()->getParent();
	llvm::BasicBlock *thenBB = llvm::BasicBlock::Create(*context, "then", fn);
	llvm::BasicBlock *elseBB = llvm::BasicBlock::Create(*context, "else");
	llvm::BasicBlock *mergeBB = llvm::BasicBlock::Create(*context, "fi");
	builder->CreateCondBr(condition, thenBB, elseBB);

	// then body
	builder->SetInsertPoint(thenBB);
	llvm::Value *toReturn = children[1]->codegen();
	builder->CreateBr(mergeBB);
	thenBB = builder->GetInsertBlock();

	// else body
	fn->insert(fn->end(), elseBB);
	builder->SetInsertPoint(elseBB);
	if(children[2] != NULL)
		toReturn = children[2]->codegen();
	builder->CreateBr(mergeBB);
	elseBB = builder->GetInsertBlock();

	// merge body
	fn->insert(fn->end(), mergeBB);
	builder->SetInsertPoint(mergeBB);

	if(sibling != NULL)
		toReturn = sibling->codegen();
	return toReturn;
}

// While

While::While(int l, AST *cond, AST *stmt) {
	line = l;
	addChild(cond, 0);
	addChild(stmt, 1);
	if(stmt != NULL)
		stmt->hasScopeException = true;
}

void While::print(bool showMemory) {
	printPrefix();
	printf("While [line: %d]\n", line);
	AST::print(showMemory);
}

void While::propagateScopes(SymbolTable *table) {
	table->enter("While");
	loopDepth++;
	children[0]->propagateScopes(table);
	if(strcmp(children[0]->type, (char *)"bool") != 0 && strcmp(children[0]->type, (char *)"undefined") != 0) {
		printf("ERROR(%d): Expecting Boolean test condition in while statement but got type %s.\n", line, children[0]->type);
		n_errors++;
	}
	if(children[0]->isArray) {
		printf("ERROR(%d): Cannot use array as test condition in while statement.\n", line);
		n_errors++;
	}
	if(children[1] != NULL)
		children[1]->propagateScopes(table);
	table->applyToAll(checkUsage);
	size = table->leave();
	loopDepth--;
	AST::propagateScopesSibling(table);
}

void While::generate(SymbolTable *globals, bool doSibling) {
	int toffset_old = toffset;
	toffset = size;
	emitComment((char *)"WHILE");
	int entry = emitSkip(0);
	// evaluate expression
	children[0]->generate(globals);
	emitRM((char *)"JNZ", 3, 1, 7, (char *)"Jump into loop");
	int old_break_loc = break_loc;
	break_loc = emitSkip(1);
	if(children[1] != NULL)
		children[1]->generate(globals);
	emitGotoAbs(entry, (char *)"Go to beginning of loop");
	backPatchAJumpToHere(break_loc, (char *)"Jump past loop [backpatch]");
	break_loc = old_break_loc;
	emitComment((char *)"END WHILE");
	toffset = toffset_old;
	if(doSibling)
		AST::generateSibling(globals);
}

llvm::Value *While::codegen() {
	llvm::Function *fn = builder->GetInsertBlock()->getParent();
	llvm::BasicBlock *condBB = llvm::BasicBlock::Create(*context, "while", fn);
	llvm::BasicBlock *loopBB = llvm::BasicBlock::Create(*context, "loop");
	llvm::BasicBlock *endBB = llvm::BasicBlock::Create(*context, "end");
	builder->CreateBr(condBB);
	builder->SetInsertPoint(condBB);
	// loop condition
	llvm::Value *toReturn = children[0]->codegen();
	llvm::Value *condition = builder->CreateICmpNE(toReturn, llvm::ConstantInt::get(*context, llvm::APInt(1, 0)));
	builder->CreateCondBr(condition, loopBB, endBB);
	condBB = builder->GetInsertBlock();
	fn->insert(fn->end(), loopBB);
	// loop body
	breakBlocks.push_back(endBB); // doesn't work when there are nested breaks
	builder->SetInsertPoint(loopBB);
	toReturn = children[1]->codegen();
	builder->CreateBr(condBB);
	loopBB = builder->GetInsertBlock();
	breakBlocks.pop_back();
	// end
	fn->insert(fn->end(), endBB);
	builder->SetInsertPoint(endBB);

	if(sibling != NULL)
		toReturn = sibling->codegen();
	return toReturn;
}

// Break

Break::Break(int l) {
	line = l;
}

void Break::print(bool showMemory) {
	printPrefix();
	printf("Break [line: %d]\n", line);
	AST::print(showMemory);
}

void Break::propagateScopes(SymbolTable *table) {
	AST::propagateScopesChildren(table);
	if(loopDepth == 0) {
		printf("ERROR(%d): Cannot have a break statement outside of loop.\n", line);
		n_errors++;
	}
	AST::propagateScopesSibling(table);
}

void Break::generate(SymbolTable *globals, bool doSibling) {
	emitGotoAbs(break_loc, (char *)"Break");
	if(doSibling)
		AST::generateSibling(globals);
}

llvm::Value *Break::codegen() {
	llvm::Value *toReturn = builder->CreateBr(breakBlocks.back());
	if(sibling != NULL)
		toReturn = sibling->codegen();
	return toReturn;
}

// For

For::For(int l, TokenData *itr, TokenData *arr, AST *stmt) {
	line = l;
	Var *child = new Var(itr);
	child->initialized = true;
	child->isArray = false;
	addChild(child, 0);
	addChild(new Id(arr), 1);
	addChild(stmt, 2);
	if(stmt != NULL)
		stmt->hasScopeException = true;
}

void For::print(bool showMemory) {
	printPrefix();
	printf("For [line: %d]\n", line);
	AST::print(showMemory);
}

void For::propagateScopes(SymbolTable *table) {
	table->enter("For");
	loopDepth++;
	children[0]->propagateScopes(table);
	children[1]->propagateScopes(table);
	if(strcmp(children[1]->type, (char *)"undefined") != 0)
		children[0]->type = strdup(children[1]->type);
	if(!children[1]->isArray) {
		printf("ERROR(%d): For statement requires that symbol '%s' be an array to loop through.\n", children[1]->line, ((Id *)children[1])->name);
		n_errors++;
	}
	if(children[2] != NULL)
		children[2]->propagateScopes(table);
	table->applyToAll(checkUsage);
	size = table->leave();
	loopDepth--;
	AST::propagateScopesSibling(table);
}

void For::generate(SymbolTable *globals, bool doSibling) {
	// also do toffset
	emitComment((char *)"FOR");
	// not implemented due to lack of time
	AST::generate(globals);
}