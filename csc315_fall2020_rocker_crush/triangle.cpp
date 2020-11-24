#include "triangle.h"
#include "callbacks.h"

Triangle::Triangle(int xPos, int yPos, int sideLength, const float col[]) : 
    GameTile(xPos, yPos, sideLength, "Triangle", col) {};

Triangle::~Triangle() {};

void Triangle::draw() 
{
    // Draw a triangle
    DrawFilledTriangle(x, (x + size), (x + (size / 2)), actualY(y), 
            actualY(y), actualY(y + size), color);
}
