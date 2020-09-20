#include "ast.h"

// AST

AST::AST() {
	depth = 0;
}

AST::AST(AST *parent) {
	depth = parent->depth + 1;
}

void AST::print(int index) {
	for(int i = 0; i < children.size(); i++)
		children[i]->print(i); // we need to know index so we know if we're a sibling
}

void AST::append(AST *child) {
	children.push_back(child);
}

void AST::printPrefix() {
	for(int i = 0; i < depth; i++)
		printf("!   ");
}

// Var Declaration

VarDeclaration::VarDeclaration(TokenData *data) {
	type = strdup(data->tokenString);
	line = data->line;
}

void VarDeclaration::print(int index) {
	for(int i = 0; i < vars.size(); i++) {
		printPrefix();
		if(i == 0)
			printf("Child: %d", index);
		else
			printf("Sibling: %d", i - 1);
		printf("  var %s of type %s [line: %d]\n", vars[i]->name, type, line);
	}
}

void VarDeclaration::append(VarDeclId *vdi) {
	vars.push_back(vdi);
}

// Var Decl Id

VarDeclId::VarDeclId(TokenData *data) {
	name = strdup(data->tokenString);
	isArray = false;
}

VarDeclId::VarDeclId(TokenData *data, int n): VarDeclId(data) {
	arraySize = n;
	isArray = true;
}