#ifndef TILE_H
#define TILE_H


class Tile
{
    public:
        int x, y;
        const float *color;
        Tile();
        virtual ~Tile();
        Tile(int, int, const float []);
        virtual void draw() = 0;
};

#endif
