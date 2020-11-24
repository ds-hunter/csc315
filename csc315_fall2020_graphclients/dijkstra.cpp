/********************************************************************//**
 * @file dijkstra.cpp
 ***********************************************************************/
#include "dijkstra.h"
#include <queue>


/***************************************************************************//**
 * @brief Destructor for the Dijkstra class.
 ******************************************************************************/
Dijkstra::~Dijkstra() {}

/***************************************************************************//**
 * @brief Constructor for the Dijkstra class. Calculates the path to the finish
 * node from the start node upon a new instantiation of a Dijkstra object.
 *
 * Complexity: O(|V| + E log|E|)
 *
 * @param[in] G - A pointer to the weighted graph ADT to be used in the algorithm.
 * 
 * @param[in] Start - The start/head vertex/node.
 *
 * @param[in] E - The final/tail vertex/node.
 ******************************************************************************/
Dijkstra::Dijkstra(WeightedGraph *G, int Start, int E) : graph(G), start(Start), finish(E)
{
    int w;
    bool finishFound = false;
    priority_queue<dInfo, vector<dInfo>, greater<dInfo>> pq;

    // initialize all distances to infinity
    for (auto i : G->Vertices())
        data[i].first = numeric_limits<double>::infinity();
    
    // Traverse the vertices
    pq.push(make_pair(0, start));
    data[start].first = 0;
    while (!pq.empty())
    {
        dInfo v = pq.top();
        pq.pop();
        
        // Check adjacent edge weights and nodes to be relaxed
        for (Edge e : graph->adj(v.second))
        {
            w = e.other(v.second);

            // This is just for visualizing what nodes have been traversed.
            // Stops marking nodes as visited when it finds the final path.
            if (w == finish) 
            {
                finishFound = true;
                visited[w] = true;
            }
            if (!finishFound && !visited[w]) visited[w] = true;

            // Check if a previously traversed path has more cost
            if (data[w].first > data[v.second].first + e.Weight())
            {
                data[w].first = data[v.second].first + e.Weight();
                data[w].second = v.second;
                pq.push(make_pair(data[w].first, w));
            }
        }       
    }
}

/***************************************************************************//**
 * @brief Visited function for the Dijkstra class. Simply returns the map of
 * processed nodes for visualization purposes.
 *
 * @returns map<int, bool> - The map that holds all processed nodes.
 ******************************************************************************/
map<int, bool> Dijkstra::Visited() 
{
    return visited; 
}

/***************************************************************************//**
 * @brief The hasPath function for the Dijkstra class. Determines whether or not
 * a path exists between the start node and vertex v.
 *
 * @param[in] v - The start/head vertex/node.
 *
 * @returns true/false - Whether or not a path exists between start to v.
 ******************************************************************************/
bool Dijkstra::hasPath(int v) 
{ 
    return data[v].first != numeric_limits<double>::infinity();
}

/***************************************************************************//**
 * @brief The pathTo function for the Dijkstra class. This will calculate a path
 * from the start vertex to vertex v using Dijkstras algorithm.
 *
 * @param[in] v - The vertex to path to.
 *
 * @returns path - The list of vertices between the start vertex and vertex v.
 ******************************************************************************/
std::list<int> Dijkstra::pathTo(int v)
{
    int curr = v;
    std::list<int> path;

    // Return an empty path if the distance is infinity
    if (!hasPath(v)) return path;
    
    while (curr != start)
    {
        path.push_front(curr);
        curr = data[curr].second;
    }

    path.push_front(start);

    return path;
}

/***************************************************************************//**
 * @brief Distance function for the Dijkstra class. Finds the distance between
 * the start node and vertex v.
 *
 * @param[in] v - The vertex to find the distance to.
 *
 * @returns double - The distance between the start node and vertex v.
 ******************************************************************************/
double Dijkstra::distance(int v) 
{ 
    return data[v].first;
}
