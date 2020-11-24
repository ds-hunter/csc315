#include <iostream>
#include "util.h"

using namespace std;

int main(int argc, char **argv) 
{
    initOpenGL(argc, argv, 640, 520);

    glutMainLoop();

    return 0;
}
