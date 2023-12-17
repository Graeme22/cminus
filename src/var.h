#ifndef _VAR_H_
#define _VAR_H_

#include "ast.h"
#include "exp.h"
#include "scanType.h"

llvm::AllocaInst *createEntryBlockAlloca(llvm::Function *, const std::string &, llvm::Type *);

class Var: public AST {

public:
	char *name;
	int arraySize;
	// isFunction: functions are a subclass of
	// vars, as they need many of the same
	// properties
	bool isStatic, isFunction, isGlobal;
	// used: whether the var has ever been used.
	// notified: we don't send the var usage warning
	// message more than once, this is used to ensure
	// that
	bool used, notified;
	// creates a var node
	Var(TokenData *);
	// creates an array node with given size
	Var(TokenData *, TokenData *);
	// sets the type and static-ness of
	// the var, then propagates through
	// siblings (recursive)
	void setTypeAndStatic(char *, bool);
	// sets the var to initialized,
	// then propages through siblings
	// (recursive)
	void setInitialized();
	// overridden
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void initialize(SymbolTable *);
	virtual void generate(SymbolTable *, bool);
	llvm::Value *codegen() override;
	// LLVM type
	llvm::Type *getType();
	
};

class Id: public Var {

public:
	// creates an id (var reference) node
	Id(TokenData *);
	// overridden
	virtual void print(bool);
	virtual void propagateScopes(SymbolTable *);
	virtual void generate(SymbolTable *, bool);
	llvm::Value *codegen() override;

};

#endif