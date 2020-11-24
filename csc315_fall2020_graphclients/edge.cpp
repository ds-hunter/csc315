/********************************************************************//**
 * @file
 ***********************************************************************/
#include "edge.h"

Edge::Edge(int v, int w, double wgt) : v(v), w(w), weight(wgt) {}

int Edge::either() const 
{ 
   return v ; 
}

int Edge::other(int vertex) const
{
   if (vertex == v) 
      return w;

   return v;
}

double Edge::Weight() const
{
   return weight;
}

bool Edge::operator<(const Edge &rhs) const
{
   if (weight > rhs.weight) 
      return true;

   return false;
}

std::ostream &operator <<(std::ostream &os, const Edge &e)
{
   int v = e.either();
   int w = e.other(v);
   os << v << "-" << w << " " << e.weight;
   return os;
}
