#ifndef _TREE_H_
#define _TREE_H_

#define MAX_CHILDREN 5

class TreeNode {

	int line;
	TokenData *data;

	TreeNode *sibling;
	TreeNode *children[MAX_CHILDREN];

public:

	void addSibling(TreeNode *);

}

#endif
