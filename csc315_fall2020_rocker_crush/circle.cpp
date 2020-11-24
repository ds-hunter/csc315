#include "circle.h"
#include "callbacks.h"

Circle::Circle(int xPos, int yPos, int radius, const float col[]) : 
    GameTile(xPos, yPos, radius, "Circle", col) {}; 

Circle::~Circle() {};

void Circle::draw() 
{
    // Draw a circle
    DrawFilledEllipse((size / 2), (size / 2), (x + (size / 2)), 
            actualY(y + (size / 2)), color);
}

