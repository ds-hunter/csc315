#ifndef GRAPH_H
#define GRAPH_H
#include <unordered_map>
#include <set>
#include <iostream>

using namespace std;

class Graph 
{
   unordered_map<int, set<int>> vertices;
   int numVertices;
   int numEdges;
public:
   Graph();
   Graph(istream &);
   Graph(const int *, int, int);

   int V();
   int E();
   set<int> Vertices();
   set<int> adj(int);
private:
   virtual void addEdge(int, int);
};

#endif
