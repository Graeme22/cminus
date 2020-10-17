#include "exp.h"

// Relation

Relation::Relation(TokenData *data, AST *left, AST *right) {
	kind = data->tokenClass;
	addChild(left, 0);
	addChild(right, 1);
	str = strdup(data->tokenString);
	line = data->line;
}

void Relation::print() {
	printPrefix();
	printf("Op: %s [line: %d]\n", str, line);
	AST::print();
}

// Logic Expression

LogicExpression::LogicExpression(TokenData *data, AST *left, AST *right): LogicExpression(data, left) {
	addChild(right, 1);
}

LogicExpression::LogicExpression(TokenData *data, AST *left) {
	addChild(left, 0);
	kind = data->tokenClass;
	str = strdup(data->tokenString);
	line = data->line;
}

void LogicExpression::print() {
	printPrefix();
	printf("Op: %s [line: %d]\n", str, line);
	AST::print();
}

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
	case (int)'*':
	case (int)'?':
	case (int)'-':
	case (int)'+':
	case (int)'/':
	case (int)'%':
		type = (char *)"int";
		break;
	case (int)'&':
	case (int)'|':
	case (int)'!':
	case EQ:
	case NEQ:
	case GEQ:
	case LEQ:
	case (int)'<':
	case (int)'>':
		type = (char *)"bool";
		break;
	default:
		type = (char *)"undefined";
	// case [], =: varies
	}
}

Operation::Operation(TokenData *data, AST *left, AST *right): Operation(data, left) {
	addChild(right, 1);
}

void Operation::print() {
	printPrefix();
	if(strcmp(str, "=") == 0 || strcmp(str, "++") == 0 || strcmp(str, "--") == 0 || strcmp(str, "+=") == 0 || strcmp(str, "-=") == 0
|| strcmp(str, "*=") == 0 || strcmp(str, "/=") == 0)
		printf("Assign: %s [line: %d]\n", str, line);
	else if(strcmp(str, "-") == 0 && children[1] == NULL) // if there is no right child then it's unary minus
		printf("Op chsign : type %s [line: %d]\n", type, line);
	else
		printf("Op %s : type %s [line: %d]\n", str, type, line);
	AST::print();
}

void Operation::propagateScopes(SymbolTable *table) {
	if(id == ASS)
		children[0]->initialized = true;
	AST::propagateScopes(table);
}

// Constant

Constant::Constant(TokenData *td) {
	data = td;
}

void Constant::print() {
	printPrefix();
	switch(data->tokenClass) {
	case CHARCONST:
		printf("Const: '%c' [line: %d]\n", data->cValue, data->line);
		break;
	case STRINGCONST:
		std::cout << "Const: \"" << data->sValue << "\" [line: " << data->line << "]\n";
		break;
	default:
		printf("Const: %s [line: %d]\n", data->tokenString, data->line);
	}
	AST::print();
}