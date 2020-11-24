#include "treenode.h"

// Node Constructor
TreeNode::TreeNode(int v, TreeNode* l, TreeNode* r) : data(v), left(l), right(r) {}

// Insert value into the tree
TreeNode* TreeNode::insert(TreeNode *root, int value) {
    if (root == nullptr)
        return new TreeNode(value);

    if (root->data < value) 
        root->right = insert(root->right, value);
    else
        root->left = insert(root->left, value);

    return root;
}

int TreeNode::SumOfLeaves(TreeNode *node) {
    if (node == nullptr) return 0;

    // Node is a leaf
    if (node->left == nullptr && node->right == nullptr) return node->data;

    // Recursively get sum of all leaves
    return SumOfLeaves(node->left) + SumOfLeaves(node->right);
}
