#ifndef _STMT_H_
#define _STMT_H_

#include "ast.h"
#include "scanType.h"
#include "var.h"
#include "semantic.h"

extern int loopDepth;
extern std::vector<llvm::BasicBlock *> breakBlocks;

class CompoundStatement: public AST {

public:
	// creates a compound node
	CompoundStatement(int, AST *, AST *);
	// overridden
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);
	llvm::Value *codegen() override;

};

class If: public AST {

public:
	// creates an if/else node
	If(int, AST *, AST *, AST *);
	// creates just an if node
	If(int, AST *, AST *);
	// overridden
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);
	llvm::Value *codegen() override;

};

class While: public AST {

public:
	// creates a while node
	While(int, AST *, AST *);
	// overridden
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);
	llvm::Value *codegen() override;

};

class For: public AST {

public:
	// creates a for node
	For(int, TokenData *, TokenData *, AST *);
	// overridden
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);

};

class Break: public AST {

public:
	// creates a break node
	Break(int);
	// overridden
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);
	llvm::Value *codegen() override;

};

#endif