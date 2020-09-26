#include "exp.h"

// Relation

Relation::Relation(TokenData *data, AST *left, AST *right) {
	type = data->tokenClass;
	addChild(left);
	addChild(right);
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
	addChild(right);
}

LogicExpression::LogicExpression(TokenData *data, AST *left) {
	addChild(left);
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
	addChild(left);
	type = data->tokenClass;
	str = strdup(data->tokenString);
	line = data->line;
}

Operation::Operation(TokenData *data, AST *left, AST *right): Operation(data, left) {
	addChild(right);
}

void Operation::print() {
	printPrefix();
	printf("Op: %s [line %d]\n", str, line);
	AST::print();
}

// Constant

Constant::Constant(TokenData *td) {
	data = td;
}

void Constant::print() {
	printPrefix();
	printf("Const: %s [line: %d]\n", data->tokenString, data->line);
}