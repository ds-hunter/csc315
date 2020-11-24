#include "prism.h"

Prism::Prism(Point &p, double x, double y, double z) : Shape3d(p, "Prism"), 
    xDim(x), yDim(y), zDim(z) {}

bool Prism::contains(const Point &p) const {
    // Assuming this is a rectangular prism, use the same
    // method as a cube but take into account the different
    // dimension sizes rather than a static size
    double xLowerBound = location.xLoc - xDim;
    double xUpperBound = location.xLoc + xDim;
    double yLowerBound = location.yLoc - yDim;
    double yUpperBound = location.yLoc + yDim;
    double zLowerBound = location.zLoc - zDim;
    double zUpperBound = location.zLoc + zDim;

    if (p.xLoc >= xLowerBound && p.xLoc <= xUpperBound)
        if (p.yLoc >= yLowerBound && p.yLoc <= yUpperBound)
            if (p.zLoc >= zLowerBound && p.zLoc <= zUpperBound)
                return true;
    
    return false;    
}

double Prism::volume() const {
    return xDim * yDim * zDim;
}
