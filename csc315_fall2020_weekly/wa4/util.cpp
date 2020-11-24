#include "graphics.h"
#include "util.h"
#include "callbacks.h"
#include <iostream>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    // TreeNode *left = new TreeNode(14, new TreeNode(12), new TreeNode(16));
    // TreeNode *right = new TreeNode(30, new TreeNode(28), new TreeNode(32));
    // TreeNode *root = new TreeNode(25, left, right);

    // -24 + 16 ( DIFF FOR TEXT X POSITION ) 
    // +- 20 ( DIFF FOR LINE Y POSITION )
    // DrawLine(-16, 180, 20, 160, White);
    // DrawTextString("Test", 200, 200, White);

    // DrawTree(root, -16, 180, 1);

    // DrawTextString("12", -24, 180, White); 

    glutSwapBuffers();
}

void initOpenGL(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    
    glutInitWindowSize(400, 400);
    
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    // glutMouseFunc(mouse);
    // glutPassiveMotionFunc(MouseMove);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
}

float getRatioPosition(float val) {
    return val / (WINDOW_SIZE / 2);
}

