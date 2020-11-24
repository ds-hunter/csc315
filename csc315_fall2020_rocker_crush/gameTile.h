#ifndef GAMETILE_H
#define GAMETILE_H
#include "graphics.h"
#include "tile.h"
#include <string>

using namespace std;

class GameTile : public Tile 
{ 
    private:
        bool hovered = false;
    public :
        int size;
        string shape;
        GameTile(int, int, int, string shape, const float col[]);
        virtual ~GameTile();
        virtual void draw() = 0; 
        bool contains(int, int);
        void toggleHover(bool);
        void drawOutline();
        bool isHovered();
};

#endif
