#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "shape3d.h"

class Ellipsoid : public Shape3d {
    double xRad, yRad, zRad;

    public:
        Ellipsoid(Point &p, double x = 0, double y = 0, double z = 0);
        bool contains(const Point &) const;
        double volume() const;
};

#endif
