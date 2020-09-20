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
}

// Var Declaration List

/*
!   !   Child: 0  Var z of type int [line: 6]
!   !   Sibling: 0  Var zz of type int [line: 6]
!   !   Sibling: 1  Var c of type char [line: 7]
*/
void VarDeclarationList::print(int index) {
	// The tree itself will need to have a child/sibling structure.
	// we already have children but siblings don't point to each other.
	
}

void VarDeclarationList::append(TokenData *data) {
	vars.push_back(strdup(data->tokenString));
}