/***************************************************************************//**
 * @file bfsPaths.h
 ******************************************************************************/
#ifndef __BFSPATHS_H
#define __BFSPATHS_H
#include <list>
#include <queue>
#include <map>
#include "graph.h"
#include <limits.h>

typedef pair<int, int> info;

/***************************************************************************//**
 * @class BFSPaths
 *
 * @brief BFSPaths class that contains all the necessary functions to calculate
 * a path from a starting node to an ending node using breadth-first search.
 *
 * \image html resources/imgs/UnweightedGraph.png "Graph Used"
 *
 * Example: @include resources/examples/exampleBFS.cpp
 *
 * Output: @include resources/examples/exampleBFS.output
 ******************************************************************************/
class BFSPaths
{
    private:
        Graph *G; /**< The graph ADT that is defined in the constructor. */
        int start; /**< The vertex that defines where the BFS algorithm will begin. */
        int finish; /**< The vertex that defines where the BFS algorithm will end. */
        map<int, info> data; /**< The map that contains the distance and previous node
                               data to be used within the algorithm. */
        map<int, bool> visited; /**< The map that contains the data for all vertices
                                  that have been traversed. */ 
    public:
        /// Given a graph and a start node, construct the client object
        BFSPaths(Graph *G, int s, int f);

        ~BFSPaths();
        /// Answers the question, is there a path from the start to vertex 'v'
        bool hasPath(int v);
        /// Returns the path (from start node to v) of the path if it exists
        std::list<int> pathTo(int v);
        /// Return the distance from the source to vertex 'v'
        int distance(int v);
        map<int, bool> Visited();
};

#endif
