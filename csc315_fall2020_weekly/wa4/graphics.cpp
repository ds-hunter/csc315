#include "graphics.h"
#include <iostream>
#include <sstream>
#include <string>

void DrawLine(float x1, float y1, float x2, float y2, const float color[]) {
    glLineWidth(1);
    glColor3fv(color);
    glBegin(GL_LINES);
        glVertex2f(getRatioPosition(x1), getRatioPosition(y1));
        glVertex2f(getRatioPosition(x2), getRatioPosition(y2));
    glEnd();
}

void DrawTextString(std::string str, float x, float y, const float color[]) {
    glColor3fv(color);
    glRasterPos2f(getRatioPosition(x), getRatioPosition(y));
    for (auto x : str)
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, x);
}

void DrawTree(TreeNode *node, int x, int y, int depth) {
    std::stringstream num;
    if (depth > 2) depth = 2;
    if (node != nullptr) {
        num << node->data;
        DrawTextString(num.str(), x, y, White);
        if (node->right != nullptr) {
            DrawLine(x + 10, y - 2, x + 30, y - 13, White);
            DrawTree(node->right, (x + 44) - depth*8, y - 20, depth + 1);
        }
        if (node->left != nullptr) {
            DrawLine(x + 7, y - 2, x - 30, y - 13, White);
            DrawTree(node->left, (x - 48)  + depth*8, y - 20, depth + 1);
        }
    } else {
        std::cout << "No tree available" << std::endl;
    }
}
