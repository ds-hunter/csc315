/********************************************************************//**
 * @file astar.cpp
 ***********************************************************************/
#include "astar.h"

/***************************************************************************//**
 * @brief Destructor for the AStar class.
 ******************************************************************************/
AStar::~AStar() {}

/***************************************************************************//**
 * @brief Constructor for the AStar class. Calculates the shortest path to the
 * finish node from the start node using a heuristic function as a means of
 * finding a more optimal path than the Dijkstra method.
 *
 * Complexity: O(V + E log(V)) (Best-case)
 *             O(|V|+Elog|E|) (Worst-Case)
 *
 * 
 * @param[in] G - A pointer to the weighted graph ADT to be used in the algorithm.
 * 
 * @param[in] s - The start/head vertex/node.
 *
 * @param[in] f - The final/tail vertex/node.
 *
 * \bug Visited nodes are not displayed properly. Not sure how to fix this.
 *
 ******************************************************************************/
AStar::AStar(WeightedGraph *G, int s, int f) : graph(G), start(s), finish(f)
{
    set<int> vertexList = G->Vertices();
    int x = 0, y = 0;

    // Assign x, y position for all vertices.. traversable or not.
    for (auto v : vertexList)
    {
        grid[v].first = x;
        grid[v].second = y;
        x++;
        if (x == sqrt(vertexList.size()))
        {
            y++;
            x = 0;
        }
        dist[v] = numeric_limits<int>::max();
    }

    dist[start] = 0;
    heap.push(Node(start, estimate(start, finish)));
    while (!heap.empty())
    {
        Node node = heap.top(); heap.pop();
        if (node.vertex == finish) return;
        for (Edge e : G->adj(node.vertex))
        {
            relax(node.vertex, e); 
        }
    }
}

/***************************************************************************//**
 * @brief estimate function for the AStar class. Calculates the estimated
 * manhattan distance between vertices v and f by multiplying an average weight
 * cost of adjacent edges to v by the change in x position plus the change in y
 * position.
 *
 * @returns double - The estimated manhattan distance between v and f.
 ******************************************************************************/
double AStar::estimate(int v, int f)
{
    // Estimate the distance between two nodes using manhattan dist since
    // we can't move diagonally for this grid
    list<double> weights;
    double dx = abs(grid[f].first - grid[v].first);
    double dy = abs(grid[f].second - grid[v].second);

    // Store adjacent weight costs to v to get the lowest weight cost for
    // an estimate 
    for (auto e : graph->adj(v))
    {
        weights.push_back(e.Weight());
    }
    weights.sort();

    // Calculate a tie breaker for a more accurate heuristic using properties
    // of cross product
    double dx1 = grid[v].first - grid[f].first;
    double dy1 = grid[v].second - grid[f].second;
    double dx2 = grid[start].first - grid[f].first;
    double dy2 = grid[start].second - grid[f].second;
    double cross = abs(dx1*dy2 - dx2*dy1);

    return (cross * .001) + weights.front() * (dx + dy);
}

/***************************************************************************//**
 * @brief Relax function for the AStar class. Relaxes adjacent edges to vertex
 * v and adds the adjacent vertices to the heap to be calculated. 
 ******************************************************************************/
void AStar::relax(int v, Edge e)
{
    int w = e.other(v);
    if (dist[w] > dist[v] + e.Weight())
    {
        visited[w] = true;
        dist[w] = dist[v] + e.Weight();
        prev[w] = v;
        heap.push(Node(w, estimate(w, finish)));
    }
}

/***************************************************************************//**
 * @brief Visited function for the AStar class. Simply returns the map of
 * processed nodes for visualization purposes.
 *
 * @returns map<int, bool> - The map that holds all processed nodes.
 ******************************************************************************/
map<int, bool> AStar::Visited() 
{ 
    return visited; 
}


/***************************************************************************//**
 * @brief The pathTo function for the AStar class. This will calculate a path
 * from the start vertex to vertex v using an edit of the Dijkstra algorithm
 * where a heuristic function is included in determining the best path.
 *
 * @param[in] v - The vertex to path to.
 *
 * @returns path - The list of vertices between the start vertex and vertex v.
 ******************************************************************************/
list<int> AStar::pathTo(int v) 
{ 
    list<int> path;
    int curr;

    if (!hasPath(v)) return path;

    for (curr = v; curr != start; curr = prev[curr])
        path.push_front(curr);

    path.push_front(start);

    return path; 
}


/***************************************************************************//**
 * @brief The hasPath function for the AStar class. Determines whether a path
 * exists between vertex v and the end vertex.
 *
 * @returns true/false - Whether or not a path exists between vertex v and the
 * finish node.
 ******************************************************************************/
bool AStar::hasPath(int v) 
{ 
    return dist[v] != numeric_limits<double>::infinity();
}
