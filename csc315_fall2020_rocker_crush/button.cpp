#include "button.h"
#include "graphics.h"
#include "callbacks.h"
#include <iostream>

Button::Button(int x, int y, int size, string label, const float col[]) : 
    LabeledTile(x, y, size, size, label, col)
{}

Button::~Button() {};

void Button::draw() 
{
    DrawFilledRectangle(x, actualY(y), x + xSize, actualY(y + ySize), color);
    DrawTextString(label, x, actualY(y + ySize/2), White);
}

bool Button::contains(int xLoc, int yLoc) 
{
    // check that the x-Location + y-Location point to one of the buttons
    bool contained =  (xLoc >= x && xLoc <= x + xSize) 
        && (actualY(yLoc) >= y && actualY(yLoc) <= y + ySize);

    return contained;
}
