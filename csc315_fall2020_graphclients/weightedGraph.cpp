/********************************************************************//**
 * @file
 ***********************************************************************/
#include "weightedGraph.h"

WeightedGraph::WeightedGraph() : numVertices(0) {}

/**************************************************************************//**
 * @brief Constructor
 *
 * The expectation is that the stream sent into this constructor consists of
 * pairs of integers which represent the edges in a graph followed by a
 * double precision value which represents the weight of the edge:
 *
 * 1 2 0.14
 * 1 3 0.54
 * 1 4 1.54
 * 2 5 2.22
 *
 * This input would create a graph with 5 vertices (1-5) and 4 edges described
 * by the pairs of integers and a double precision weight
 ******************************************************************************/

WeightedGraph::WeightedGraph(istream &fin)
{
    int v, w;
    double weight;

    while (!fin.eof())
    {
        fin >> v >> w >> weight;
        addEdge(Edge(v, w, weight));
    }

    numVertices = vertices.size();
}

WeightedGraph::WeightedGraph(const int *grid, int width, int height)
{
    for (int x = 0 ; x < width ; x++)
    {
        for (int y = 0 ; y < height ; y++)
        {
            int index = y * width + x;
            if (canEnter(x, y+1))
                addEdge(Edge(index,index+width, max(1,max(grid[index+width],grid[index]))));
            if (canEnter(x, y-1))
                addEdge(Edge(index,index-width, max(1,max(grid[index-width],grid[index]))));
            if (canEnter(x+1, y))
                addEdge(Edge(index, index+1, max(1,max(grid[index+1],grid[index]))));
            if (canEnter(x-1, y))
                addEdge(Edge(index, index-1, max(1,max(grid[index-1],grid[index]))));
        }
    }

    numVertices = vertices.size();
}

int WeightedGraph::V() const { return numVertices ; }

int WeightedGraph::E() const { return edges.size(); }

set<int> WeightedGraph::Vertices() const
{
    return vertices;
}

multiset<Edge> WeightedGraph::adj(int v)
{
    return edges[v];
}

multiset<Edge> WeightedGraph::Edges()
{
    multiset<Edge> retSet;
    for (auto &kv : edges)
        for (Edge e : edges[kv.first])
            retSet.insert(e);

    return retSet;
}

void WeightedGraph::addEdge(Edge e)
{
    int v = e.either();
    int w = e.other(v);
    edges[v].insert(e);
    edges[w].insert(e);
    vertices.insert(v);
    vertices.insert(w);
}
