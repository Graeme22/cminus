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
	char *str;
	int id;
	Operation(TokenData *, AST *, AST *);
	Operation(TokenData *, AST *);
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	bool validateL(char *);
	bool validateR(char *);
	virtual void generate(SymbolTable *, bool);

};

class Assignment: public Operation {

public:
	Assignment(TokenData *, AST *, AST *);
	Assignment(TokenData *, AST *);
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);

};

class ShortcutAssignment: public Assignment {

public:
	ShortcutAssignment(TokenData *, AST *);
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);

};

class Constant: public AST {

	TokenData *data;

public:
	Constant(TokenData *);
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);

};

#endif