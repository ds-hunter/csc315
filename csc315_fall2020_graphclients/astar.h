/***************************************************************************//**
 * @file astar.h
 ******************************************************************************/

#ifndef ASTAR_H
#define ASTAR_H
#include <map>
#include <stack>
#include <list>
#include <vector>
#include <cmath>
#include <limits>
#include <queue>
#include "weightedGraph.h"
#include "nodecompare.h"

using namespace std;

typedef pair<int, int> position;

/***************************************************************************//**
 * @class AStar
 *
 * @brief The AStar class implements the AStar algorithm for pathfinding between
 * nodes in a graph. Accurate for graphs that can be represented in grid form
 * where edges can only traverse in the 4 cardinal directions as the heuristic 
 * for this method involves using manhattan distance.
 *
 * \image html resources/imgs/WeightedGraph.png "Graph Used"
 *
 * Example: @include resources/examples/exampleAStar.cpp
 * Output: @include resources/examples/exampleAStar.output 
 ******************************************************************************/
class AStar
{
    private:
        WeightedGraph *graph; /**< The weighted graph ADT that is defined in
                                the constructor */
        map<int, position> grid; /**< A grid representation of all vertices in
                                   the graph, generated in the constructor. */
        map<int, bool> visited; /**< The map that contains all nodes that have
                                  been traversed. */
        map<int, int> prev; /**< The map that contains all previous nodes to 
                              a vertex key. */
        map<int, int> dist; /**< The map that contains all vertex distances from
                              the start node. */
        priority_queue<Node, vector<Node>, nodeCompare> heap /**< The heap ADT
                                that uses the manhattan distance between
                                the current node and the finish node to
                                sort in minheap format.*/;
        int start; /**< The vertex to start the algorithm at. */
        int finish; /**< The vertex in which the algorithm ends at. */
        double estimate(int, int);
        void relax(int, Edge e);
    public:
        AStar(WeightedGraph *, int, int);

        ~AStar();
        bool hasPath(int);
        list<int> pathTo(int);
        map<int, bool> Visited();
};
#endif
