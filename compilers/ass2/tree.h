#ifndef _TREE_H_
#define _TREE_H_

#define MAX_CHILDREN 5

class Node {

	int line;
	int depth;
	TokenData *data;

	TreeNode *sibling;
	TreeNode *children[MAX_CHILDREN];

public:
	void addSibling(TreeNode *);
	void print();

}

class programNode: public Node {

public:
	programNode(Node *);

}

class declarationListNode: public Node {}
class declarationNode: public Node {}
class varDeclarationNode: public Node {}
class scopedVarDeclarationNode: public Node {}
class varDeclList: public Node {}


#endif
