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

void Operation::print() {
	printPrefix();
	if(id == ASS || id == INC || id == DEC || id == ADDASS || id == SUBASS || id == MULASS || id == DIVASS) {
		if(strcmp(type, "undefined") == 0)
			printf("Assign %s : undefined type [line: %d]\n", str, line);
		else {
			if(children[0]->isArray)
				printf("Assign %s : array of type %s [line: %d]\n", str, type, line);
			else
				printf("Assign %s : type %s [line: %d]\n", str, type, line);
		}
	} else {
		if(strcmp(type, "undefined") == 0)
			printf("Op %s : undefined type [line: %d]\n", str, line);
		else
			printf("Op %s : type %s [line: %d]\n", str, type, line);
	}
	AST::print();
}

void Operation::propagateScopes(SymbolTable *table) {
	AST::propagateScopesChildren(table);
	
	char *_INT_ = (char *)"int";
	char *_BOOL_ = (char *)"bool";
	char *_UNDEFINED_ = (char *)"undefined";

	switch(id) {
	case ADDASS:
	case SUBASS:
	case DIVASS:
	case MULASS:
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
	case INC:
	case DEC:
	case RAND:
		type = (char *)"int";
		if(!validateL(_INT_)) {
			printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given type %s.\n", line, str, type, children[0]->type);
			n_errors++;
		}
		if(children[0]->isArray) {
			printf("ERROR(%d): The operation '%s' does not work with arrays.\n", line, str);
			n_errors++;
		}
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
		if(children[0]->isArray && !children[1]->isArray || children[0]->isArray && !children[1]->isArray) {
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
		if(children[0]->isArray && !children[1]->isArray || children[0]->isArray && !children[1]->isArray) {
			printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is%s an array and rhs is%s an array.\n", line, str, (children[0]->isArray ? "" : " not"), (children[1]->isArray ? "" : " not"));
			n_errors++;
		}
		// do the same thing with array-ness
		break;
	// these options can be either unary or binary
	case SUB:
		type = (char *)"int";
		// unary
		if(children[1] == NULL) {
			if(!validateL(_INT_)) {
				printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given type %s.\n", line, str, type, children[0]->type);
				n_errors++;
			}
			if(children[0]->isArray) {
				printf("ERROR(%d): The operation '%s' does not work with arrays.\n", line, str);
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
	case MUL:
		type = (char *)"int";
		// unary
		if(children[1] == NULL) {
			if(!validateL(_INT_)) {
				printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given type %s.\n", line, str, type, children[0]->type);
				n_errors++;
			}
			if(!children[0]->isArray) {
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
		child->initialized = true;
		break;
	}
	AST::propagateScopesSibling(table);
}

bool Operation::validateL(char *left) {
	return strcmp(children[0]->type, left) == 0 || strcmp(children[0]->type, (char *)"undefined") == 0;
}

bool Operation::validateR(char *right) {
	return strcmp(children[1]->type, right) == 0 || strcmp(children[1]->type, (char *)"undefined") == 0;
}

// Constant

Constant::Constant(TokenData *td) {
	data = td;
	switch(data->tokenClass) {
	case CHARCONST:
		type = (char *)"char";
		break;
	case STRINGCONST:
		type = (char *)"char";
		isArray = true;
		break;
	case NUMCONST:
		type = (char *)"int";
		break;
	case BOOLCONST:
		type = (char *)"bool";
		break;
	}
}

void Constant::print() {
	printPrefix();
	switch(data->tokenClass) {
	case CHARCONST:
		printf("Const: '%c' : type char [line: %d]\n", data->cValue, data->line);
		break;
	case STRINGCONST:
		std::cout << "Const \"" << data->sValue << "\": array of type char [line: " << data->line << "]\n";
		break;
	case NUMCONST:
		printf("Const %s : type int [line: %d]\n", data->tokenString, data->line);
		break;
	case BOOLCONST:
		printf("Const %s : type bool [line: %d]\n", data->tokenString, data->line);
		break;
	}
	AST::print();
}