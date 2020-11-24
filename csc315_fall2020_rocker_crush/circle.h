#ifndef CIRCLE_H
#define CIRCLE_H

#include "gameTile.h"

class Circle : public GameTile 
{
    public:
        Circle(int, int, int, const float[]);
        ~Circle();
        void draw();
};

#endif
