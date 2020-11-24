#include "cube.h"
#include <math.h>

Cube::Cube(Point &p, double l) : Shape3d(p, "Cube"), size(l) {}

bool Cube::contains(const Point &p) const {
    double xLowerBound = location.xLoc - size;
    double xUpperBound = location.xLoc + size;
    double yLowerBound = location.yLoc - size;
    double yUpperBound = location.yLoc + size;
    double zLowerBound = location.zLoc - size;
    double zUpperBound = location.zLoc + size;

    if (p.xLoc >= xLowerBound && p.xLoc <= xUpperBound)
        if (p.yLoc >= yLowerBound && p.yLoc <= yUpperBound)
            if (p.zLoc >= zLowerBound && p.zLoc <= zUpperBound)
                return true;
    
    return false;
}

double Cube::volume() const {
    return pow(size, 3);
}
