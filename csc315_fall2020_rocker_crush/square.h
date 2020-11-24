#ifndef SQUARE_H
#define SQUARE_H

#include "gameTile.h"

class Square : public GameTile 
{
    public:
        Square(int, int, int, const float[]);
        ~Square();
        void draw();
};

#endif
