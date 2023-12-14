#ifndef _EXP_H_
#define _EXP_H_

#include "ast.h"
#include "var.h"
#include "scanType.h"
#include <iostream>
#include "parser.tab.h"

extern bool checkInitialization;

class Operation: public AST {

public:
	// name of the operation, eg "<="
	char *str;
	// id of the operation, which is the
	// int defined by the parser.
	int id;
	// create an operation node with
	// left and right sides (binary)
	Operation(TokenData *, AST *, AST *);
	// create a unary operation node
	Operation(TokenData *, AST *);
	// type checking on left child
	bool validateL(char *);
	// type checking on right child
	bool validateR(char *);
	// overriden methods
	virtual void generate(SymbolTable *, bool);
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	llvm::Value *codegen() override;

};

class Assignment: public Operation {

public:
	// create an assignment node with
	// left and right children (binary)
	// so =, +=, -=, etc
	Assignment(TokenData *, AST *, AST *);
	// unary assignment (increment/decrement)
	Assignment(TokenData *, AST *);
	// overriden
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);

};

class ShortcutAssignment: public Assignment {

public:
	// just calls super constructor
	ShortcutAssignment(TokenData *, AST *);
	// overriden
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);

};

class Constant: public AST {

	TokenData *data;

public:
	// create constant node
	Constant(TokenData *);
	// overridden
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);
	llvm::Value *codegen() override;

};

#endif