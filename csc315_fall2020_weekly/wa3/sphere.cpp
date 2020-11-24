#define _USE_MATH_DEFINES
#include "sphere.h"
#include <cmath>

Sphere::Sphere(Point &p, double r) : Shape3d(p, "Sphere"), radius(r) {}

bool Sphere::contains(const Point &p) const {
    return p.distance(location) <= radius;
}

double Sphere::volume() const {
    return (4.0 / 3.0) * M_PI * pow(radius, 3);
}
