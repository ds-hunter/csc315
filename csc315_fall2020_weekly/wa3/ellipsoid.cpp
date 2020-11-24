#define _USE_MATH_DEFINES
#include "ellipsoid.h"
#include <math.h>

Ellipsoid::Ellipsoid(Point &p, double x, double y, double z) : 
    Shape3d(p, "Ellipsoid"), xRad(x), yRad(y), zRad(z) {}

bool Ellipsoid::contains(const Point &p) const {
    // Using the standard equation for an ellipsoid
    // (x-x1)^2/a + (y-y1)^2/b + (z-z1)^2/c <= 1
    // Our semifocal lengths (a,b,c) are the radi
    double xDiff = p.xLoc - location.xLoc;
    double yDiff = p.yLoc - location.yLoc;
    double zDiff = p.zLoc - location.zLoc;
    
    // Substitute for the equation
    return pow(xDiff, 2) / xRad + pow(yDiff, 2) / yRad + 
        pow(zDiff, 2) / zRad <= 1;
}

double Ellipsoid::volume() const {
    return (4.0 / 3.0) * M_PI * xRad * yRad * zRad;
}
