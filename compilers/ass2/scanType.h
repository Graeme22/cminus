#ifndef _SCANTYPE_H_
#define _SCANTYPE_H_

#define MAXCHILDREN 5

#include <string>
#include <stdbool.h>

struct TokenData {
	int tokenClass;
	char *tokenString;
	int line;
	// these may or may not be used depending on the class.
	int nValue;
	char cValue;
	std::string sValue;
};

typedef enum { STMT_K, EXP_K } NodeKind;
typedef enum { EXPRESSION_K, COMPOUND_K, SELECTION_K, ITERATION_K, RETURN_K, BREAK_K } StmtKind;
typedef enum { OP_K, CONST_K, ID_K } ExpKind;
// for type checking
typedef enum { INT_T, BOOL_T, CHAR_T } ExpType;

typedef struct treeNode {
	// connectivity
	struct treeNode *child[MAXCHILDREN];
	struct treeNode *sibling;

	int line;
	NodeKind node;
	union {
		DeclKind decl;
		StmtKind stmt;
		ExpKind exp;
	} kind;

	// extra properties, situational
	union {
		OpKind op;
		int nValue;
		char cValue;
		std::string sValue;
		char *name;
	} attr;

	ExpType type;
	bool isArray;
	bool isStatic;

	// TODO: more semantics
} TreeNode;

#endif
