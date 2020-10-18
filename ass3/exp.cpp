#include "exp.h"

// Operation

Operation::Operation(TokenData *data, AST *left) {
	addChild(left, 0);
	str = strdup(data->tokenString);
	line = data->line;
	id = data->tokenClass;
	
	switch(id) {
	case ADDASS:
	case SUBASS:
	case DIVASS:
	case MULASS:
	case ADD:
	case SUB:
	case MUL:
	case DIV:
	case INC:
	case DEC:
	case MOD:
	case RAND:
	case (int)'[':
		type = (char *)"int";
		break;
	case AND:
	case OR:
	case NOT:
	case EQ:
	case NEQ:
	case GEQ:
	case LEQ:
	case LT:
	case GT:
		type = (char *)"bool";
		break;
	default:
		type = (char *)"undefined";
	}
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
	if(id == ASS)
		type = strdup(children[0]->type);
	AST::propagateScopesSibling(table);
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