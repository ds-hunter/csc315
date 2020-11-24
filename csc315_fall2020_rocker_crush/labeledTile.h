#ifndef LABELEDTILE_H
#define LABELEDTILE_H

#include "tile.h"
#include <string>

using namespace std;

class LabeledTile : public Tile
{
    public:
        string label; 
        int xSize, ySize;
        LabeledTile(int, int, int, int, string, const float []);
        virtual ~LabeledTile();
        virtual void draw() = 0;
};

#endif
