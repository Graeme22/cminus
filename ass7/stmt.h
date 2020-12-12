#ifndef _STMT_H_
#define _STMT_H_

#include "ast.h"
#include "scanType.h"
#include "var.h"
#include "semantic.h"

extern int loopDepth;

class CompoundStatement: public AST {

public:
	CompoundStatement(int, AST *, AST *);
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);

};

class If: public AST {

public:
	// if-else
	If(int, AST *, AST *, AST *);
	// if
	If(int, AST *, AST *);
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);

};

class While: public AST {

public:
	While(int, AST *, AST *);
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);

};

class For: public AST {

public:
	For(int, TokenData *, TokenData *, AST *);
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);

};

class Break: public AST {

public:
	Break(int);
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);

};

#endif