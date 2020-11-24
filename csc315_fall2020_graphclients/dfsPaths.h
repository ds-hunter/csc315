/***************************************************************************//**
 * @file dfsPaths.h
 ******************************************************************************/

#ifndef DFSPATHS_H
#define DFSPATHS_H
#include <list>
#include "graph.h"
#include <stack>
#include <limits>

/***************************************************************************//**
 * @class DFSPaths
 *
 * @brief A class that implements pathfinding using a depth-first search
 * algorithm.
 *
 * Complexity: O(|V| + |E|)
 *
 * \image html resources/imgs/UnweightedGraph.png "Graph Used"
 *
 * Example: @include resources/examples/exampleDFS.cpp
 *
 * Output: @include resources/examples/exampleDFS.output
 ******************************************************************************/
class DFSPaths
{
    private:
        Graph *graph; /**< The graph ADT that is defined in the constructor */
        int start; /**< The value of the first vertex to be traversed */
        map<int, bool> visited; /**< A map of all traversed nodes */
        void DFS(int start, int end, stack<int>, list<int> &);
    public:
        DFSPaths(Graph *G, int s);

        ~DFSPaths();
        bool hasPath(int v);
        std::list<int> pathTo(int v);
};
#endif
