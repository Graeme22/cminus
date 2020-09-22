#ifndef _AST_H_
#define _AST_H_

#define MAXCHILDREN 3

#include <string>

class TreeNode {

public:
	TreeNode *children[MAXCHILDREN];
	TreeNode *sibling;

	int line;
	NodeKind nodeKind;
	union {
		DeclKind decl;
		StmtKind stmt;
		ExpKind exp;
	} kind;

	// extra info
	union {
		OpKind op;
		int nValue;
		char cValue;
		std::string sValue;
		char *name;
	} attr;
	ExpType expType;
	bool isArray;
	bool isStatic;

	void addSibling(TreeNode *);

};

#endif
