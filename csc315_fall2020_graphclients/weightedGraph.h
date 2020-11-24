/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H
#include <iostream>
#include <map>
#include <set>
#include "defines.h"
#include "edge.h"

using namespace std;

typedef map<int, multiset<Edge>> map_t;
/********************************************************************//**
 * @class WeightedGraph
 **********************************************************************/
class WeightedGraph
{
   int numVertices;
   map_t edges;
   set<int> vertices;
public:
   WeightedGraph();
   WeightedGraph(istream &);
   WeightedGraph(const int *, int, int);

   void addEdge(Edge);
   multiset<Edge> adj(int);
   multiset<Edge> Edges();
   set<int> Vertices() const;
   int V() const;
   int E() const;
};
#endif
