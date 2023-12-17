#include "exp.h"

// Operation

Operation::Operation(TokenData *data, AST *left) {
	addChild(left, 0);
	str = strdup(data->tokenString);
	line = data->line;
	id = data->tokenClass;
}

Operation::Operation(TokenData *data, AST *left, AST *right): Operation(data, left) {
	addChild(right, 1);
}

void Operation::print(bool showMemory) {
	printPrefix();
	if(strcmp(type, "undefined") == 0)
		printf("Op %s : undefined type [line: %d]\n", str, line);
	else
		printf("Op %s : type %s [line: %d]\n", str, type, line);
	AST::print(showMemory);
}

void Operation::propagateScopes(SymbolTable *table) {
	AST::propagateScopesChildren(table);
	
	char *_INT_ = (char *)"int";
	char *_BOOL_ = (char *)"bool";
	char *_UNDEFINED_ = (char *)"undefined";

	switch(id) {
	case ADD:
	case DIV:
	case MOD:
		type = (char *)"int";
		if(!validateL(_INT_)) {
			printf("ERROR(%d): '%s' requires operands of type %s but lhs is of type %s.\n", line, str, type, children[0]->type);
			n_errors++;
		}
		if(!validateR(_INT_)) {
			printf("ERROR(%d): '%s' requires operands of type %s but rhs is of type %s.\n", line, str, type, children[1]->type);
			n_errors++;
		}
		if(children[0]->isArray || children[1]->isArray) {
			printf("ERROR(%d): The operation '%s' does not work with arrays.\n", line, str);
			n_errors++;
		}
		break;
	case RAND:
		type = strdup(children[0]->type);
		if(!validateL(_INT_)) {
			printf("ERROR(%d): Unary '%s' requires an operand of type int but was given type %s.\n", line, str, children[0]->type);
			n_errors++;
		}
		if(children[0]->isArray) {
			printf("ERROR(%d): The operation '%s' does not work with arrays.\n", line, str);
			n_errors++;
		}
		isConstant = true;
		break;
	case AND:
	case OR:
		type = (char *)"bool";
		if(!validateL(_BOOL_)) {
			printf("ERROR(%d): '%s' requires operands of type %s but lhs is of type %s.\n", line, str, type, children[0]->type);
			n_errors++;
		}
		if(!validateR(_BOOL_)) {
			printf("ERROR(%d): '%s' requires operands of type %s but rhs is of type %s.\n", line, str, type, children[1]->type);
			n_errors++;
		}
		if(children[0]->isArray || children[1]->isArray) {
			printf("ERROR(%d): The operation '%s' does not work with arrays.\n", line, str);
			n_errors++;
		}
		break;
	case NOT:
		type = (char *)"bool";
		if(!validateL(_BOOL_)) {
			printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given type %s.\n", line, str, type, children[0]->type);
			n_errors++;
		}
		if(children[0]->isArray) {
			printf("ERROR(%d): The operation '%s' does not work with arrays.\n", line, str);
			n_errors++;
		}
		break;
	case EQ:
	case NEQ:
	case GEQ:
	case LEQ:
	case LT:
	case GT:
		type = (char *)"bool";
		if(strcmp(children[0]->type, children[1]->type) != 0 && strcmp(children[0]->type, _UNDEFINED_) != 0 && strcmp(children[1]->type, _UNDEFINED_) != 0) {
			printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", line, str, children[0]->type, children[1]->type);
			n_errors++;
		}
		if(children[0]->isArray && !children[1]->isArray || !children[0]->isArray && children[1]->isArray) {
			printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is%s an array and rhs is%s an array.\n", line, str, (children[0]->isArray ? "" : " not"), (children[1]->isArray ? "" : " not"));
			n_errors++;
		}
		break;
	case ASS:
		type = strdup(children[0]->type);
		if(strcmp(children[0]->type, children[1]->type) != 0 && strcmp(children[0]->type, _UNDEFINED_) != 0 && strcmp(children[1]->type, _UNDEFINED_) != 0) {
			printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", line, str, children[0]->type, children[1]->type);
			n_errors++;
		}
		if(children[0]->isArray && !children[1]->isArray || !children[0]->isArray && children[1]->isArray) {
			printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is%s an array and rhs is%s an array.\n", line, str, (children[0]->isArray ? "" : " not"), (children[1]->isArray ? "" : " not"));
			n_errors++;
		}
		break;
	case SUB:
		type = (char *)"int";
		if(children[1] == NULL) { // unary
			if(!validateL(_INT_)) {
				printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given type %s.\n", line, str, type, children[0]->type);
				n_errors++;
			}
			if(children[0]->isArray) {
				printf("ERROR(%d): The operation '%s' does not work with arrays.\n", line, str);
				n_errors++;
			}
			isConstant = true;
		} else { // binary
			if(!validateL(_INT_)) {
				printf("ERROR(%d): '%s' requires operands of type %s but lhs is of type %s.\n", line, str, type, children[0]->type);
				n_errors++;
			}
			if(!validateR(_INT_)) {
				printf("ERROR(%d): '%s' requires operands of type %s but rhs is of type %s.\n", line, str, type, children[1]->type);
				n_errors++;
			}
		}
		break;
	case MUL:
		type = (char *)"int";
		// unary
		if(children[1] == NULL) {
			if(!children[0]->isArray && strcmp(children[0]->type, (char *)"undefined") != 0) {
				printf("ERROR(%d): The operation '%s' only works with arrays.\n", line, str);
				n_errors++;
			}
		} else {
			if(!validateL(_INT_)) {
				printf("ERROR(%d): '%s' requires operands of type %s but lhs is of type %s.\n", line, str, type, children[0]->type);
				n_errors++;
			}
			if(!validateR(_INT_)) {
				printf("ERROR(%d): '%s' requires operands of type %s but rhs is of type %s.\n", line, str, type, children[1]->type);
				n_errors++;
			}
		}
		break;
	case ACCESS:
		type = strdup(children[0]->type);
		Var *child = (Var *)children[0];
		if(!children[0]->isArray) {
			printf("ERROR(%d): Cannot index nonarray '%s'.\n", line, child->name);
			n_errors++;
		}
		if(!validateR(_INT_)) {
			printf("ERROR(%d): Array '%s' should be indexed by type int but got type %s.\n", line, child->name, children[1]->type);
			n_errors++;
		}
		if(children[1]->isArray) {
			printf("ERROR(%d): Array index is the unindexed array '%s'.\n", line, ((Var *)children[1])->name);
			n_errors++;
		}
		break;
	}
	if(children[1] != NULL)
		if(children[0]->isConstant && children[1]->isConstant)
			isConstant = true;
	else if(children[0]->isConstant)
		isConstant = true;
	AST::propagateScopesSibling(table);
}

bool Operation::validateL(char *left) {
	return strcmp(children[0]->type, left) == 0 || strcmp(children[0]->type, (char *)"undefined") == 0;
}

bool Operation::validateR(char *right) {
	return strcmp(children[1]->type, right) == 0 || strcmp(children[1]->type, (char *)"undefined") == 0;
}

void Operation::generate(SymbolTable *globals, bool doSibling) {
	children[0]->generate(globals);
	if(children[1] != NULL) {
		emitRM((char *)"ST", 3, toffset--, 1, (char *)"Push left side");
		children[1]->generate(globals);
		emitRM((char *)"LD", 4, ++toffset, 1, (char *)"Pop left into ac1");
	}
	switch(id) {
	case ADD:
		emitRO((char *)"ADD", 3, 4, 3, (char *)"Op +");
		break;
	case SUB:
		if(children[1] == NULL) // unary
			emitRO((char *)"NEG", 3, 3, 3, (char *)"Op -");
		else
			emitRO((char *)"SUB", 3, 4, 3, (char *)"Op -");
		break;
	case MUL:
		if(children[1] == NULL) // unary
			emitRM((char *)"LD", 3, 1, 3, (char *)"Load array size"); // size is 1 above index
		else
			emitRO((char *)"MUL", 3, 4, 3, (char *)"Op *");
		break;
	case DIV:
		emitRO((char *)"DIV", 3, 4, 3, (char *)"Op /");
		break;
	case MOD:
		emitRO((char *)"MOD", 3, 4, 3, (char *)"Op %");
		break;
	case RAND:
		emitRO((char *)"RND", 3, 3, 3, (char *)"Op ?");
		break;
	case AND:
		emitRO((char *)"AND", 3, 4, 3, (char *)"Op &");
		break;
	case OR:
		emitRO((char *)"OR", 3, 4, 3, (char *)"Op |");
		break;
	case EQ:
		emitRO((char *)"TEQ", 3, 4, 3, (char *)"Op ==");
		break;
	case NEQ:
		emitRO((char *)"TNE", 3, 4, 3, (char *)"Op !=");
		break;
	case GEQ:
		emitRO((char *)"TGE", 3, 4, 3, (char *)"Op >=");
		break;
	case LEQ:
		emitRO((char *)"TLE", 3, 4, 3, (char *)"Op <=");
		break;
	case LT:
		emitRO((char *)"TLT", 3, 4, 3, (char *)"Op <");
		break;
	case GT:
		emitRO((char *)"TGT", 3, 4, 3, (char *)"Op >");
		break;
	case NOT:
		emitRM((char *)"LDC", 4, 1, 6, (char *)"Load 1");
		emitRO((char *)"XOR", 3, 3, 4, (char *)"Logical not");
		break;
	case ACCESS:
		emitRO((char *)"SUB", 3, 4, 3, (char *)"Compute element location");
		emitRM((char *)"LD", 3, 0, 3, (char *)"Store array element");
		break;
	}
	if(doSibling)
		AST::generateSibling(globals);
}

llvm::Value *Operation::codegen() {
	llvm::Value *lhs = children[0]->codegen();
	llvm::Value *rhs;
	if(children[1] != NULL)
		rhs = children[1]->codegen();
	switch(id) {
	case ADD:
		return builder->CreateAdd(lhs, rhs);
	case SUB:
		if(children[1] == NULL) // unary negation
			return builder->CreateNeg(lhs);
		else // subtraction
			return builder->CreateSub(lhs, rhs);
	case MUL:
		if(children[1] == NULL) // unary array size
			break; // size is 1 above index
		else // multiplication
			return builder->CreateMul(lhs, rhs);
	case DIV:
		return builder->CreateSDiv(lhs, rhs);
	case MOD:
		return builder->CreateURem(lhs, rhs);
	case RAND:
		//handle arrays and non-arrays
		break;
	case AND:
		return builder->CreateAnd(lhs, rhs);
	case OR:
		return builder->CreateOr(lhs, rhs);
	case EQ:
		return builder->CreateICmpEQ(lhs, rhs);
	case NEQ:
		return builder->CreateICmpNE(lhs, rhs);
	case GEQ:
		return builder->CreateICmpSGE(lhs, rhs);
	case LEQ:
		return builder->CreateICmpSLE(lhs, rhs);
	case LT:
		return builder->CreateICmpSLT(lhs, rhs);
	case GT:
		return builder->CreateICmpSGT(lhs, rhs);
	case NOT:
		return builder->CreateNot(lhs);
	case ACCESS:
		break;
	}
	return lhs;
}

// Assignment

Assignment::Assignment(TokenData *data, AST *left, AST *right): Operation(data, left, right) {}

Assignment::Assignment(TokenData *data, AST *left): Operation(data, left) {}

void Assignment::print(bool showMemory) {
	printPrefix();
	if(strcmp(type, "undefined") == 0)
		printf("Assign %s : undefined type [line: %d]\n", str, line);
	else {
		if(children[0]->isArray)
			printf("Assign %s : array of type %s [line: %d]\n", str, type, line);
		else
			printf("Assign %s : type %s [line: %d]\n", str, type, line);
	}
	AST::print(showMemory);
}

void Assignment::propagateScopes(SymbolTable *table) {
	checkInitialization = false;
	children[0]->propagateScopes(table);
	checkInitialization = true;
	children[1]->propagateScopes(table);

	if(id == ASS) {
		type = strdup(children[0]->type);
		if(strcmp(children[0]->type, children[1]->type) != 0 && strcmp(children[0]->type, (char *)"undefined") != 0 && strcmp(children[1]->type, (char *)"undefined") != 0) {
			printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", line, str, children[0]->type, children[1]->type);
			n_errors++;
		}
		if(children[0]->isArray && !children[1]->isArray || !children[0]->isArray && children[1]->isArray) {
			printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is%s an array and rhs is%s an array.\n", line, str, (children[0]->isArray ? "" : " not"), (children[1]->isArray ? "" : " not"));
			n_errors++;
		}
	} else {
		type = (char *)"int";
		if(!validateL(type)) {
			printf("ERROR(%d): '%s' requires operands of type %s but lhs is of type %s.\n", line, str, type, children[0]->type);
			n_errors++;
		}
		if(!validateR(type)) {
			printf("ERROR(%d): '%s' requires operands of type %s but rhs is of type %s.\n", line, str, type, children[1]->type);
			n_errors++;
		}
		if(children[0]->isArray || children[1]->isArray) {
			printf("ERROR(%d): The operation '%s' does not work with arrays.\n", line, str);
			n_errors++;
		}
	}

	children[0]->initialize(table);
	AST::propagateScopesSibling(table);
}

void Assignment::generate(SymbolTable *globals, bool doSibling) {
	// if the child has a child, left-hand side is an array access operation
	if(children[0]->children[0] == NULL) {
		children[1]->generate(globals);
		Id *lhs = (Id *)children[0];
		if(id != ASS)
			emitRM((char *)"LD", 4, lhs->mOffset, (lhs->isGlobal ? 0 : 1), (char *)"Load variable", lhs->name);
		switch (id) {
		case ADDASS:
			emitRO((char *)"ADD", 3, 4, 3, (char *)"Op", str);
			break;
		case SUBASS:
			emitRO((char *)"SUB", 3, 4, 3, (char *)"Op", str);
			break;
		case MULASS:
			emitRO((char *)"MUL", 3, 4, 3, (char *)"Op", str);
			break;
		case DIVASS:
			emitRO((char *)"DIV", 3, 4, 3, (char *)"Op", str);
			break;
		}
		emitRM((char *)"ST", 3, lhs->mOffset, (lhs->isGlobal ? 0 : 1), (char *)"Store variable", lhs->name);
	} else {
		// left-hand side of access operation is the variable
		Id *lhs = (Id *)children[0]->children[0];
		// and the right hand side is the index, which is an expression
		children[0]->children[1]->generate(globals);
		emitRM((char *)"ST", 3, toffset--, 1, (char *)"Push left side");
		children[1]->generate(globals);
		emitRM((char *)"LD", 4, ++toffset, 1, (char *)"Pop left into ac1");
		if(strcmp(lhs->mType, "Param") == 0)
			emitRM((char *)"LD", 5, lhs->mOffset, 1, (char *)"Load address of array", lhs->name);
		else
			emitRM((char *)"LDA", 5, lhs->mOffset, (lhs->isGlobal ? 0 : 1), (char *)"Load address of array", lhs->name);
		emitRO((char *)"SUB", 5, 5, 4, (char *)"Compute element location");
		if(id != ASS)
			emitRM((char *)"LD", 4, 0, 5, (char *)"Load copy of element");
		switch (id) {
		case ADDASS:
			emitRO((char *)"ADD", 3, 4, 3, (char *)"Op", str);
			break;
		case SUBASS:
			emitRO((char *)"SUB", 3, 4, 3, (char *)"Op", str);
			break;
		case MULASS:
			emitRO((char *)"MUL", 3, 4, 3, (char *)"Op", str);
			break;
		case DIVASS:
			emitRO((char *)"DIV", 3, 4, 3, (char *)"Op", str);
			break;
		}
		emitRM((char *)"ST", 3, 0, 5, (char *)"Store array element");
	}
	if(doSibling)
		AST::generateSibling(globals);
}

llvm::Value *Assignment::codegen() {
	llvm::Value *toReturn;
	if(id == ASS) {
		Id *lhs = (Id *)children[0];
		llvm::Value *rhs = children[1]->codegen();
		std::string nm = lhs->name;
		builder->CreateStore(rhs, namedValues[nm]);
		toReturn = rhs;
	}
	if(sibling != NULL)
		toReturn = sibling->codegen();
	return toReturn;
}

// ShortcutAssignment

ShortcutAssignment::ShortcutAssignment(TokenData *data, AST *left): Assignment(data, left) {}

void ShortcutAssignment::print(bool showMemory) {
	printPrefix();
	if(strcmp(type, "undefined") == 0)
		printf("Assign %s : undefined type [line: %d]\n", str, line);
	else
		printf("Assign %s : type %s [line: %d]\n", str, type, line);
	AST::print(showMemory);
}

void ShortcutAssignment::propagateScopes(SymbolTable *table) {
	AST::propagateScopesChildren(table);
	type = (char *)"int";
	if(!validateL(type)) {
		printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given type %s.\n", line, str, type, children[0]->type);
		n_errors++;
	}
	if(children[0]->isArray) {
		printf("ERROR(%d): The operation '%s' does not work with arrays.\n", line, str);
		n_errors++;
	}
	AST::propagateScopesSibling(table);
}

void ShortcutAssignment::generate(SymbolTable *globals, bool doSibling) {
	int value = (strcmp(str, "++") == 0) ? 1 : -1;
	// if the child has a child, left-hand side is an array access operation
	if(children[0]->children[0] == NULL) {
		AST::generateChildren(globals);
		emitRM((char *)"LDA", 3, value, 3, (char *)"Op", str);
		Id *id = (Id *)children[0];
		emitRM((char *)"ST", 3, id->mOffset, (id->isGlobal ? 0 : 1), (char *)"Store variable", id->name);
	} else {
		// left-hand side of access operation is the variable
		Id *lhs = (Id *)children[0]->children[0];
		// and the right hand side is the index, which is an expression
		children[0]->children[1]->generate(globals);
		if(strcmp(lhs->mType, "Param") == 0)
			emitRM((char *)"LD", 5, lhs->mOffset, 1, (char *)"Load address of array", lhs->name);
		else
			emitRM((char *)"LDA", 5, lhs->mOffset, (lhs->isGlobal ? 0 : 1), (char *)"Load address of array", lhs->name);
		emitRO((char *)"SUB", 5, 5, 3, (char *)"Compute element location");
		emitRM((char *)"LD", 3, 0, 5, (char *)"Load copy of element");
		emitRO((char *)"LDA", 3, value, 3, (char *)"Op", str);
		emitRM((char *)"ST", 3, 0, 5, (char *)"Store array element");
	}
	if(doSibling)
		AST::generateSibling(globals);
}

// Constant

Constant::Constant(TokenData *td) {
	data = td;
	isConstant = true;
	switch(data->tokenClass) {
	case CHARCONST:
		type = (char *)"char";
		break;
	case STRINGCONST:
		type = (char *)"char";
		isArray = true;
		mSize = (td->sValue).length() + 1; // add 1 for array
		mType = (char *)"Global";
		break;
	case NUMCONST:
		type = (char *)"int";
		break;
	case BOOLCONST:
		type = (char *)"bool";
		break;
	}
}

void Constant::print(bool showMemory) {
	printPrefix();
	switch(data->tokenClass) {
	case CHARCONST:
		printf("Const: '%c' : type char [line: %d]\n", data->cValue, data->line);
		break;
	case STRINGCONST:
		if(showMemory)
			std::cout << "Const \"" << data->sValue << "\" : array of type char [mem: " << mType << "  size: " << mSize << "  loc: " << mOffset << "] [line: " << data->line << "]\n";
		else
			std::cout << "Const \"" << data->sValue << "\" : array of type char [line: " << data->line << "]\n";
		break;
	case NUMCONST:
		printf("Const %s : type int [line: %d]\n", data->tokenString, data->line);
		break;
	case BOOLCONST:
		printf("Const %s : type bool [line: %d]\n", data->tokenString, data->line);
		break;
	}
	AST::print(showMemory);
}

void Constant::propagateScopes(SymbolTable *table) {
	// only do anything if we're a STRINGCONST
	if(isArray) {
		mOffset = goffset - 1;
		goffset -= mSize;
	}
	AST::propagateScopesSibling(table);
}

void Constant::generate(SymbolTable *globals, bool doSibling) {
	switch(data->tokenClass) {
	case CHARCONST:
		emitRM((char *)"LDC", 3, (int)data->cValue, 6, (char *)"Load constant");
		break;
	case STRINGCONST:
		// omitted for sake of time
		break;
	case NUMCONST:
	case BOOLCONST:
		emitRM((char *)"LDC", 3, data->nValue, 6, (char *)"Load constant");
		break;
	}
	if(doSibling)
		AST::generateSibling(globals);
}

llvm::Value *Constant::codegen() {
	switch(data->tokenClass) {
	case CHARCONST:
		return llvm::ConstantInt::get(*context, llvm::APInt(8, uint8_t(data->cValue), false));
	case STRINGCONST:
		return llvm::ConstantDataArray::getString(*context, data->sValue, true);
	case NUMCONST:
		return llvm::ConstantInt::get(*context, llvm::APInt(32, data->nValue, true));
	case BOOLCONST:
		return llvm::ConstantInt::get(*context, llvm::APInt(1, data->nValue));
	}
	// unreachable
	return nullptr;
}