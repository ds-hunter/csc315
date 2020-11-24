#include "shape3d.h"

Shape3d::Shape3d(Point &l, std::string s) : location(l), typeName(s) {}

std::string Shape3d::type() {
    return typeName;
}

std::ostream& operator<<(std::ostream& os, const Shape3d *obj) {
    os << obj->location;
    return os;
}
