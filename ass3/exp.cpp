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
	if(strcmp(str, "=") == 0 || strcmp(str, "++") == 0 || strcmp(str, "--") == 0 || strcmp(str, "+=") == 0 || strcmp(str, "-=") == 0 || strcmp(str, "*=") == 0 || strcmp(str, "/=") == 0) {
		if(strcmp(type, "undefined") == 0)
			printf("Assign %s : undefined type [line: %d]\n", str, line);
		else
			printf("Assign %s : type %s [line: %d]\n", str, type, line);
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
	bool success;
	switch(id) {
	case ADDASS:
	case SUBASS:
	case DIVASS:
	case MULASS:
	case ADD:
	case SUB:
	case MUL:
	case DIV:
	case MOD:
		type = (char *)"int";
		if(!validateL((char *)"int")) {
			printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n", line, str, type, children[0]->type);
			n_errors++;
		}
		if(!validateR((char *)"int")) {
			printf("ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n", line, str, type, children[1]->type);
			n_errors++;
		}
		break;
	case INC:
	case DEC:
	case RAND:
		type = (char *)"int";
		if(!validateL((char *)"int")) {
			printf("ERROR(%d): Unary '%s' requires an operand of %s but was given %s.\n", line, str, type, children[0]->type);
			n_errors++;
		}
		break;
	case AND:
	case OR:
		type = (char *)"bool";
		if(!validateL((char *)"bool")) {
			printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n", line, str, type, children[0]->type);
			n_errors++;
		}
		if(!validateR((char *)"bool")) {
			printf("ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n", line, str, type, children[1]->type);
			n_errors++;
		}
		break;
	case NOT:
		type = (char *)"bool";
		if(!validateL((char *)"bool")) {
			printf("ERROR(%d): Unary '%s' requires an operand of %s but was given %s.\n", line, str, type, children[0]->type);
			n_errors++;
		}
		break;
	case EQ:
	case NEQ:
		type = (char *)"bool";
		success = validate((char *)"int", (char *)"int") || validate((char *)"bool", (char *)"bool") || validate((char *)"char", (char *)"char");
		if(!success) {
			printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", line, str, children[0]->type, children[1]->type);
			n_errors++;
		}
		break;
	case GEQ:
	case LEQ:
	case LT:
	case GT:
		type = (char *)"bool";
		if(!validateL((char *)"int")) {
			printf("ERROR(%d): '%s' requires operands of %s but lhs is of %s.\n", line, str, type, children[0]->type);
			n_errors++;
		}
		if(!validateR((char *)"int")) {
			printf("ERROR(%d): '%s' requires operands of %s but rhs is of %s.\n", line, str, type, children[1]->type);
			n_errors++;
		}
		break;
	case ASS:
		type = strdup(children[0]->type);
		success = validate((char *)"int", (char *)"int") || validate((char *)"bool", (char *)"bool") || validate((char *)"char", (char *)"char");
		if(!success) {
			printf("ERROR(%d): '%s' requires operands of the same type but lhs is %s and rhs is %s.\n", line, str, children[0]->type, children[1]->type);
			n_errors++;
		}
		break;
	}
	AST::propagateScopesSibling(table);
}

bool Operation::validateL(char *left) {
	return strcmp(children[0]->type, left) == 0;
}

bool Operation::validateR(char *right) {
	return strcmp(children[1]->type, right) == 0;
}

bool Operation::validate(char *left, char *right) {
	return validateL(left) && validateR(right);
}

// Constant

Constant::Constant(TokenData *td) {
	data = td;
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