/***************************************************************************//**
 * @file dfsPaths.cpp
 ******************************************************************************/
#include "dfsPaths.h"

/***************************************************************************//**
 * @brief Destructor for the DFSPaths class
 ******************************************************************************/
DFSPaths::~DFSPaths() {}

/***************************************************************************//**
 * @brief Constructor for the DFSPaths class
 *
 * @param[in] G - A pointer to the graph ADT to be used in the algorithm.
 * 
 * @param[in] v - The start vertex/node.
 ******************************************************************************/
DFSPaths::DFSPaths(Graph *G, int v)
{
    start = v;
    graph = G;
}

/***************************************************************************//**
 * @brief The recursive DFS algorithm function.
 *
 * @param[in] start - The start vertex/node.
 * 
 * @param[in] end - The end vertex/node.
 *
 * @param[in] stored - The stack that stores all traversed vertices.
 *
 * @param[in] path - The end path found by the algorithm from start vertex
 * to end vertex.
 ******************************************************************************/
void DFSPaths::DFS(int start, int end, stack<int> stored, list<int> &path)
{
    // Start at a starting node
    stored.push(start);
    visited[start] = true;

    // The stack has the path that was found or it will be empty
    if (start == end || stored.empty()) 
    {
        while (!stored.empty())
        {
            path.push_front(stored.top());
            stored.pop();
        }
        return;
    }

    // Visit adjacent nodes that have not yet been visited
    for (auto i : graph->adj(start))
    {
        if (visited[i] == false)
        {
            DFS(i, end, stored, path);
        } 
    }

    // Move to a previous node 
    stored.pop();
}


/***************************************************************************//**
 * @brief Constructor for the DFSPaths class
 *
 * @param[in] v - The vertex to find a path to.
 *
 * @returns true/false - If a path to the specified vertex was found.
 ******************************************************************************/
bool DFSPaths::hasPath(int v) 
{
    return !pathTo(v).empty();
}  

/***************************************************************************//**
 * @brief Constructor for the DFSPaths class
 *
 * @param[in] v - The vertex to find a path to using DFS.
 *
 * @returns list - The list of integers containing the vertex path from
 * the starting node to v, the ending node.
 ******************************************************************************/
std::list<int> DFSPaths::pathTo(int v)
{
    std::list<int> path;
    stack<int> stored;
    visited.clear();

    DFS(start, v, stored, path);

    return path;
}
