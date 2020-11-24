/***************************************************************************//**
 * @file bfsPaths.cpp
 ******************************************************************************/
#include "bfsPaths.h"

/***************************************************************************//**
 * @brief Destructor for the BFSPaths class
 ******************************************************************************/
BFSPaths::~BFSPaths() {}

/***************************************************************************//**
 * @brief Constructor for the BFSPaths class. Calculates the path between v
 * and f upon an instantiation of a BFSPaths object.
 *
 * Complexity: O(|V| + |E|)
 *
 * @param[in] G - A pointer to the graph ADT to be used in the algorithm.
 * 
 * @param[in] v - The start/head vertex/node.
 *
 * @param[in] f - The final/tail vertex/node.
 ******************************************************************************/
BFSPaths::BFSPaths(Graph *G, int v, int f) : G(G), start(v), finish(f)
{
    int current;

    for (auto i : G->Vertices())
        data[i].first = numeric_limits<int>::infinity();

    // Begin at the start node
    queue<int> q;
    q.push(start);
    data[start].first = 0;

    // Traverse all vertices
    while (!q.empty())
    {
        current = q.front(); q.pop();        

        // Process adjacent nodes
        for (auto i : G->adj(current))
        {
            if (!visited[i])
            {
                visited[i] = true;
                q.push(i);
                data[i].first = data[current].first + 1;
                data[i].second = current;

                if (i == finish) return; // The final vertex has been found
            }
        }
    }
}

/***************************************************************************//**
 * @brief The hasPath function that returns whether or not a path exists from
 * head to tail node. (Or start to finish referenced by the BFSPaths class)
 *
 * @param[in] v - The node to find a path to from the starting node.
 *
 * @returns true/false - Whether or not a path exists from starting node to v.
 ******************************************************************************/
bool BFSPaths::hasPath(int v) 
{
    return data[v].first != numeric_limits<int>::infinity();
}

/***************************************************************************//**
 * @brief The distance function which returns the distance from the starting
 * node as calculated by the BFS algorithm.
 * 
 * @param[in] v - The start vertex/node.
 *
 * @returns int - The distance to the starting node from v or INT_MAX, no path
 * existed.
 ******************************************************************************/
int BFSPaths::distance(int v) {
    return data[v].first;
}

/***************************************************************************//**
 * @brief pathTo function for the BFSPaths class. Calculated a path to vertex
 * v using breadth-first search.
 * 
 * @param[in] v - The vertex/node to calculate a path to.
 *
 * @returns path - The list of integers containing the path to v from the start
 * node.
 ******************************************************************************/
std::list<int> BFSPaths::pathTo(int v)
{
    std::list<int> path;
    
    for (int i = v; i != start; i = data[i].second)
        path.push_front(i);
    
    path.push_front(start);
    return path;
}

/***************************************************************************//**
 * @brief The Visited function for the BFSPaths class. Returns the map
 * containing all nodes that have been traversed in the graph at the point of
 * function call. Presumably being used by the driver.
 *
 * @returns visited - The map containing all vertices that have been traversed.
 ******************************************************************************/
map<int, bool> BFSPaths::Visited()
{
    return visited;
}

