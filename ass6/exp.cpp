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
	AST::propagateScopes(table);
}