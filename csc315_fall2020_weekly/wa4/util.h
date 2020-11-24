#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <GL/freeglut.h>

// Define window width & height
#define WINDOW_SIZE 400

void display();
void initOpenGL(int argc, char **argv);
float getRatioPosition(float val);

#endif
