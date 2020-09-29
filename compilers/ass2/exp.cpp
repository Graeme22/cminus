#include "exp.h"

// Relation

Relation::Relation(TokenData *data, AST *left, AST *right) {
	type = data->tokenClass;
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
	type = data->tokenClass;
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
	type = data->tokenClass;
	str = strdup(data->tokenString);
	line = data->line;
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
		printf("Op: chsign [line: %d]\n", line);
	else
		printf("Op: %s [line: %d]\n", str, line);
	AST::print();
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
		std::cout << "Const: '" << data->sValue << "' [line: " << data->line << "]\n";
		break;
	default:
		printf("Const: %s [line: %d]\n", data->tokenString, data->line);
	}
	AST::print();
}