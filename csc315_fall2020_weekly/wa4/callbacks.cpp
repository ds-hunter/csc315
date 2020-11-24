#include "callbacks.h"
#include "graphics.h"
#include "treenode.h"
#include "util.h"
#include "sstream"
#include "string"
#include <iostream>

void keyboard(unsigned char key, int x, int y) {
    int value;
    static TreeNode *root = nullptr;
    static std::stringstream num; 
    static std::stringstream title;

    // glutSetWindowTitle("Inserting : " << num.str().c_str());
    if (key == 13) {
        num >> value;
        num.clear();
        num.str("");
        title.str("");
        std::cout << value << " inserted. Clearing stream." << std::endl;
        std::cout << std::string('-', 15) << std::endl << std::endl;

        // Insert value into the tree & update the title
        if (!root) root = root->insert(root, value);
        else root->insert(root, value);
        title << "Inserting: <none> | " << "Leaf Sum: " << root->SumOfLeaves(root)
            << std::endl;
        

        // Display tree and update screen
        glClear(GL_COLOR_BUFFER_BIT);
        DrawTree(root, -16, 180, 1);
        glutSwapBuffers();
    } else if (key >= 48 && key <= 57) {
        num << key;
        title.str("");
        title << "Inserting: <" << num.str() << "> | " << "Leaf Sum: " << root->SumOfLeaves(root)
            << std::endl;
        std::cout << "[" << num.str() << "]" << std::endl;
    }

    glutSetWindowTitle(title.str().c_str());
}
