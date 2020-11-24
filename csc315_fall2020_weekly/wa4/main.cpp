#include <iostream>
#include "treenode.h"
#include "util.h"
#include "graphics.h"

int SumOfBinaryTreeLeaves(TreeNode *root);

using namespace std;

int main(int argc, char **argv) {
    initOpenGL(argc, argv);
    glutMainLoop();

    return 0;
}

int SumOfBinaryTreeLeaves(TreeNode* root) {
    // Base Cases
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr)
        return root->data;
     
    return SumOfBinaryTreeLeaves(root->left) + SumOfBinaryTreeLeaves(root->right);
}
