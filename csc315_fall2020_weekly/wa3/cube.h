#ifndef CUBE_H
#define CUBE_H

#include "shape3d.h"

class Cube : public Shape3d {
    double size;

    public:
        Cube(Point &p, double l = 1);
        bool contains(const Point &) const;
        double volume() const;
};

#endif
