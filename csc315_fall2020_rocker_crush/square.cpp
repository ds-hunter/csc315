#include "square.h"
#include "callbacks.h"

Square::Square(int xPos, int yPos, int size, const float col[]) : 
    GameTile(xPos, yPos, size, "Square", col) {}; 

Square::~Square() {};

void Square::draw()
{
    // Draw a square
    DrawFilledRectangle(x, actualY(y), (x + size), actualY(y + size), color);
}

