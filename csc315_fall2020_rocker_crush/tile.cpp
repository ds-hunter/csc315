#include "tile.h"

Tile::Tile()
{}

Tile::~Tile() 
{}

Tile::Tile(int xLoc, int yLoc, const float col[]) : x(xLoc), y(yLoc), color(col)
{}
