#ifndef TREENODE_H
#define TREENODE_H

struct TreeNode {
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int, TreeNode* = nullptr, TreeNode* = nullptr);
    TreeNode *insert(TreeNode *root, int value);
    int SumOfLeaves(TreeNode *);
};

#endif
