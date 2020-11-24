#include "labeledTile.h"
#include "graphics.h"
#include "callbacks.h"

LabeledTile::LabeledTile(int x, int y, int sizeX, int sizeY, string labelText,
        const float col[]) : 
    Tile(x, y, col), label(labelText), xSize(sizeX), ySize(sizeY)
{}

LabeledTile::~LabeledTile() {};
