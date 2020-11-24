#include "graph.h"

//
//     1   --    2
//     |         |
//     3   --    4

Graph::Graph() {}

Graph::~Graph() {}

Graph::Graph(istream &inStream) : numVertices(0), numEdges(0)
{
   int v, w;

   while (!inStream.eof())
   {
      inStream >> v >> w;
      addEdge(v, w);
   }
   
   numVertices = vertices.size();
   for (int v : Vertices())
      numEdges += vertices[v].size();

   numEdges /= 2;
}

Graph::Graph(const int *grid, int width, int height) : numEdges(0)
{
   for (int x = 0 ; x < width ; x++)
   {
      for (int y = 0 ; y < height ; y++)
      {
         int index = y * width + x;
         if (!canEnter(x, y)) continue;
         if (canEnter(x, y+1)) addEdge(index, index+width);
         if (canEnter(x, y-1)) addEdge(index, index-width);
         if (canEnter(x+1, y)) addEdge(index+1, index);
         if (canEnter(x-1, y)) addEdge(index-1, index);
      }
   }
   
   numVertices = vertices.size();
   for (int v : Vertices())
      numEdges += adj(v).size();

   numEdges /= 2;
} 

void Graph::addEdge(int v, int w)
{
   vertices[v].insert(w);
   vertices[w].insert(v);
}

int Graph::V() { return numVertices ; }

int Graph::E() { return numEdges ; }

set<int> Graph::Vertices()
{
   set<int> retVal;
   for (auto &kv : vertices)
      retVal.insert(kv.first);

   return retVal;
}

set<int> Graph::adj(int v)
{
   return vertices[v];
}
