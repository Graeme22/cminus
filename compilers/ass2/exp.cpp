#include "exp.h"

// Relation

Relation::Relation(TokenData *data, AST *l, AST *r) {
	type = data->tokenClass;
	left = l;
	right = r;
	str = strdup(data->tokenString);
	line = data->line;
}

void Relation::print() {
	printf("Op: %s [line: %d]\n", str, line);
	left->print();
	right->print();
}

// Logic Expression

LogicExpression::LogicExpression(TokenData *data, AST *l, AST *r): LogicExpression(data, l) {
	right = r;
}

LogicExpression::LogicExpression(TokenData *data, AST *c) {
	left = c;
	type = data->tokenClass;
	str = strdup(data->tokenString);
	line = data->line;
}

void LogicExpression::print() {
	printf("Op: %s [line: %d]\n", str, line);
	left->print();
	if(right != NULL)
		right->print();
}

// Operation

Operation::Operation(TokenData *data, AST *c) {
	left = c;
	type = data->tokenClass;
	str = strdup(data->tokenString);
	line = data->line;
}

Operation::Operation(TokenData *data, AST *l, AST *r): Operation(data, l) {
	right = r;
}

void Operation::print() {
	printf("Op: %s [line %d]\n", str, line);
	left->print();
	if(right != NULL)
		right->print();
}

// Constant

Constant::Constant(TokenData *td) {
	data = td;
}

void Constant::print() {
	printf("Const: %s [line: %d]\n", data->tokenString, data->line);
}