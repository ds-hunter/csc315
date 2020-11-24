#include <iostream>
#include <vector>
#include "point.h"
#include "shape3d.h"
#include "sphere.h"
#include "cube.h"
#include "prism.h"
#include "ellipsoid.h"

using namespace std;

int main()
{
   Point p(1, 1, 1);          /// Create a Point at coordinate [1,1,1]

   std::vector<Shape3d *> shapes;
   
   shapes.push_back(new Sphere(p));
   shapes.push_back(new Cube(p));
   shapes.push_back(new Prism(p, 1.0, 2.0, 1.0));
   shapes.push_back(new Ellipsoid(p, 1.0, 1.0, 2.0));

   Point q(1.1, 1.1, 1.1);    /// Create a Point at coordinate [1.1,1.1,1.1]

   for (Shape3d *shape : shapes)
      if (shape->contains(q))
         cout << shape->type() << " at " << shape << " contains point at " << q << "\n";

   for (Shape3d *shape : shapes)
      cout << "Volume of " << shape->type() << " = " << shape->volume() << endl;
   
   return 0;
}
