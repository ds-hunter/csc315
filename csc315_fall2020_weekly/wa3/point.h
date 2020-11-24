#ifndef POINT_H
#define POINT_H

#include <sstream>

struct Point
{
    double xLoc, yLoc, zLoc;
    Point(double, double, double);
    double distance(const Point &) const;
};

std::ostream& operator<<(std::ostream& os, const Point &);

#endif
