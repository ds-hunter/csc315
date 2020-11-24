#include "point.h"
#include <iostream>
#include "math.h"

// Point constructor
Point::Point(double x, double y, double z) {
    xLoc = x;
    yLoc = y;
    zLoc = z;
}

// Distance method, return distance from current point to another
double Point::distance(const Point &p) const {
    double xDiff = pow(p.xLoc - xLoc, 2);
    double yDiff = pow(p.yLoc - yLoc, 2);
    double zDiff = pow(p.zLoc - zLoc, 2);

    return sqrt(xDiff + yDiff + zDiff);
}

// Overload operator for displaying the Point
std::ostream& operator<<(std::ostream& os, const Point &p) {
    os << '(' << p.xLoc << ", " << p.yLoc << ", " << p.zLoc << ')' << std::endl;

    return os;
}
