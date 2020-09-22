#include "ast.h"

TreeNode::addSibling(TreeNode *node) {
	if(sibling == NULL)
		sibling = node;
	else {
		for(TreeNode *itr = sibling; itr->sibling != NULL; itr = itr->sibling);
		itr->sibling = node;
	}
}
