#ifndef PRISM_H
#define PRISM_H

#include "shape3d.h"

class Prism : public Shape3d {
    double xDim, yDim, zDim;

    public: 
        Prism(Point &p, double x = 0, double y = 0, double z = 0);
        bool contains(const Point &) const;
        double volume() const;
};

#endif
