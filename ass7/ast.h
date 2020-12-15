#ifndef _AST_H_
#define _AST_H_

// the max number of children a tree node can have.
// (in this version, 3 is the max, and is only found
// in the case of an if-else statement, but 2 is common.)
#define MAX_CHILDREN 3

#include <string.h>
#include <stdio.h>
#include "emitcode.h"
#include "symbolTable.h"

extern int n_errors;
extern int n_warnings;
extern int foffset;
extern int goffset;
extern int toffset;
extern int break_loc;

class AST {

public:
	// tree structure:
	// 		   Parent Node		-- 		Sibling
	//	      /     |     \
	//	Child 0  Child 1  Child 2
	//
	// each of these nodes can then have its own
	// children and a sibling, and so on.
	AST *children[MAX_CHILDREN];
	// so there can be up to MAX_CHILDREN
	// children but only 1 sibling for a
	// given node.
	AST *sibling;
	// depth is the height in the tree
	// used for printing the tree nicely
	// and also for being able to tell if
	// we're global (aka depth == 0)
	int index, depth;
	// flags to aid with semantic analysis.
	// isFirst: the very first node in the
	// tree is printed weirdly, that's all 
	// this is for.
	bool isChild, isFirst, isArray, isConstant, isGlobal;
	// for var nodes and expression nodes,
	// we need to know the type. it will be
	// either char, int, bool, or "undefined"
	char *type;
	// line: the line number we were declared
	// on. used for error messages
	// size: size of the frame in memory,
	// including all vars, params, etc.
	// used for anything with a scope
	// (functions, if, while, for, compound)
	int line, size;
	// hasScopeException: in the case of
	// a function (or if/while/for) that 
	// uses curly braces, we want it to
	// behave the same with or without.
	// for example:
	// while(true) i++;
	// shouldn't be different than
	// while(true) {
	// 		i++;
	// }
	// basically we just want to ignore the
	// first compound since the function/
	// if/while/for will already be handling
	// that functionality.
	// initialized: for variables, whether
	// or not the variable has been initialized
	// yet. used for semantic errors/warnings.
	bool hasScopeException, initialized;

	// type of memory used.
	// either global, static, param, or local.
	char *mType;
	// size in memory of the node
	int mSize;
	// location in memory of the beginning of the node
	int mOffset;

	AST();
	// prints the tree. flag is whether or
	// not to add memory allocation info.
	virtual void print(bool);
	// follow the sibling pointers until we
	// get to NULL, then set the given node
	// as the sibling of the last one:
	//
	// Parent  --  Sibling  --  Sibling of sibling  --  NULL
	//					becomes
	// Parent  --  Sibling  --  Sibling of Sibling  --  Sibling of sibling of sibling
	// 													  ^ given node is put here
	void append(AST *);
	// sets the given node as the child at the given
	// index in the children array.
	void addChild(AST *, int);
	// prints a number of indents relative
	// to the current node's depth in the tree
	virtual void printPrefix();
	// not very descriptive name, all this does
	// is set the depth and index properties of
	// all the nodes correctly (recursive)
	void propagateInfo();
	// I created this function as a way to recurse
	// the tree for semantic analysis. it's a bit
	// sloppy in places but it matched the errors
	// correctly. (recursive)
	// it also handles scopes with aid of the
	// symbol table.
	virtual void propagateScopes(SymbolTable *);
	// does the above function for the children
	// of the current node.
	void propagateScopesChildren(SymbolTable *);
	// calls the above function for the sibling.
	void propagateScopesSibling(SymbolTable *);
	virtual void initialize(SymbolTable *);
	// recursively generates the assembly code for 
	// the given node and its children (if applicable).
	// flag controls whether we call generate on the
	// sibling node.
	// this is necessary because sometimes we want
	// to do things in between generating this node
	// and its sibling, so this flag allows our
	// parent to do that if it needs to.
	virtual void generate(SymbolTable *, bool);
	// if no flag is passed, we assume true (overloaded)
	void generate(SymbolTable *);
	// generate the non-null children sequentially
	void generateChildren(SymbolTable *);
	// generate the sibling if it exists
	void generateSibling(SymbolTable *);
	
};

#endif
