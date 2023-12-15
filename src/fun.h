#ifndef _FUN_H_
#define _FUN_H_

#include <vector>
#include "ast.h"
#include "semantic.h"
#include "scanType.h"
#include "var.h"

class Par: public Var {

public:
	// create a parameter, flag is
	// whether or not it's an array
	Par(TokenData *, bool);
	// overridden
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);

};

class FunDeclaration: public Var {

public:
	// address in memory of function
	// so we can call it later
	int loc;
	// for LLVM pars
	std::vector<std::string> argNames;
	// create a function node with given return
	// type (overloaded)
	FunDeclaration(TokenData *, TokenData *, AST *, AST *);
	// create a function node of type void
	FunDeclaration(TokenData *, AST *, AST *);
	// create a "dummy" function node,
	// used for the I/O library
	// (there's probably a better way
	// of doing this)
	FunDeclaration(char *, TokenData *, AST *);
	// overridden
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);
	llvm::Function* codegen() override;

};

class Call: public AST {

	char *name;

public:
	// create a call node
	Call(TokenData *, AST *);
	// overridden
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);
	llvm::Value *codegen() override;

};

class Return: public AST {

public:
	// create a return node 
	// that returns nothing
	Return(int);
	// create a return node
	// that returns its child
	// (overloaded)
	Return(int, AST *);
	// overridden
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);
	llvm::Value *codegen() override;

};

extern FunDeclaration *currentFunction;
extern bool hasReturn;

#endif