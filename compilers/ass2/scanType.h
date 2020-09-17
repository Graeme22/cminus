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

typedef struct treeNode {
	// connectivity
	struct treeNode *child[MAXCHILDREN];
	struct treeNode *sibling;

	int tokenClass;
	int line;
} TreeNode;

#endif
