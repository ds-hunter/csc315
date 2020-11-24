#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "gameTile.h"

class Triangle : public GameTile 
{
    public:
        Triangle(int, int, int, const float[]);
        ~Triangle();
        void draw();
};

#endif
