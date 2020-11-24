#include "gameTile.h"
#include "callbacks.h"
#include "graphics.h"
#include <iostream>

using namespace std;

GameTile::GameTile(int xPos, int yPos, int s, string type, const float col[]) : 
    Tile(xPos, yPos, col), size(s), shape(type) {};

GameTile::~GameTile() {};

bool GameTile::contains(int xLoc, int yLoc) 
{
    return (xLoc >= x && xLoc <= x + size) && (actualY(yLoc) >= y && 
            actualY(yLoc) <= y + size);
}

void GameTile::toggleHover(bool cond) 
{
    if (hovered != cond)
        glutPostRedisplay();
    hovered = cond;
}

void GameTile::drawOutline()
{
    // Normal case
    if (x != 140 + 8 * 55 && y != 8 * 55 - 20)
        DrawRectangle(x - 3, actualY(y - 3), x + 120, actualY(y + 118), Yellow);
    // Right side, not bottom right corner
    else if (x == 140 + 8 * 55 && y != 8 * 55 - 20)
        DrawRectangle(x - 63, actualY(y - 3), x + 63, actualY(y + 118), Yellow);
    // Bottom edge, not bottom right corner
    else if (x != 140 && x != 140 + 8 * 55 && y == 8 * 55 - 20)
        DrawRectangle(x - 3, actualY(y + 60), x + 120, actualY(y - 60), Yellow);
    else // Bottom right corner
        DrawRectangle(x - 60, actualY(y + 60), x + 60, actualY(y - 60), Yellow);
}

bool GameTile::isHovered() 
{
    return hovered;
}
