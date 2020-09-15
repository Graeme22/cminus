#ifndef _SCANTYPE_H_
#define _SCANTYPE_H_

#include <string>
<<<<<<< HEAD
#include <stdbool.h>
=======
>>>>>>> 58ccb7e945a25bf7d050b8aa0d87b1b7f00fc668

struct TokenData {
	int tokenClass;
	char *tokenString;
	int line;
	// these may or may not be used depending on the class.
	int nValue;
	char cValue;
	std::string sValue;
};

/*typedef struct treeNode {
	// connectivity
	struct treeNode *child[MAXCHILDREN];
	struct treeNode *sibling;

	// node kind
	int line;
	NodeKind node;
	union {
		DeclKind decl;
		StmtKind stmt;
		ExpKind exp;
	} kind;

	// extra node properties, varies by node
	union {
		OpKind op;
		int nValue; // for both ints and bools
		char cValue;
		std::string sValue;
		char *name; // ?
	} attr;

	ExpType type; // for type checking
	bool isArray;
	bool isStatic;

	// more semantics here later.
} TreeNode;*/

#endif
