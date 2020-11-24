#ifndef SHAPE3D_H
#define SHAPE3D_H

#include "point.h"

class Shape3d
{
    protected:
        Point location;
        std::string typeName;
    public:
        Shape3d(Point &l, std::string s);
        virtual bool contains(const Point &) const = 0;
        virtual double volume() const = 0;
        std::string type();

        friend std::ostream& operator<<(std::ostream& os, const Shape3d *obj);
};

#endif
