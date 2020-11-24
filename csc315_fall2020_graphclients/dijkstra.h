/***************************************************************************//**
 * @file dijkstra.h
 ******************************************************************************/
#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <list>
#include <limits>
#include <vector>
#include "weightedGraph.h"

typedef pair<double, int> dInfo;

/***************************************************************************//**
 * @class Dijkstra
 *
 * @brief The Dijkstra class implements Dijkstras algorithm for pathfinding
 * on nodes in a graph.
 *
 * \image html resources/imgs/WeightedGraph.png "Graph Used"
 *
 * Example: @include resources/examples/exampleDijkstras.cpp
 *
 * Output: @include resources/examples/exampleDijkstra.output
 ******************************************************************************/
class Dijkstra
{
    private:
        WeightedGraph *graph; /**< The weighted graph ADT that is defined in
                                the constructor */
        map<int, dInfo> data; /**< The map that holds the distance and previous
                                nodes for any node in the graph. */
        map<int, bool> visited; /**< The map that contains what nodes have been
                                  processed by the algorithm. */
        int start; /**< The vertex the algorithm will start at. */
        int finish; /**< The vertex the algorithm will end at. */

    public:
        Dijkstra(WeightedGraph *, int, int);

        ~Dijkstra();
        bool hasPath(int);
        list<int> pathTo(int);
        double distance(int);
        map<int, bool> Visited();
};
#endif
