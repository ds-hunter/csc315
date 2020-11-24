#include "graph.h"

Graph::Graph() {}

Graph::Graph(std::istream &fin)
{
    int v, w;

    while (!fin.eof()) {
        fin >> v >> w;
        addEdge(v, w);
    }
}

Graph::Graph(const int *grid, int width, int height)
{
    int row, col;

    for (int i = 0; i < width*height; i++) {
        row = i / width;
        col = i % width;
        
        if (grid[i] == 0)
        {
            // Check right/left edges
            if (col-1 >= 0)
                if (grid[i-1] == 0)
                    addEdge(i, i-1);
            if (col+1 < width)
                if (grid[i+1] == 0)
                    addEdge(i, i+1);
            
            // Check top/bottom edges
            if (i-width >= 0)
                if (grid[i-width] == 0)
                    addEdge(i, i-width);
            if (i+width < width*height)
                if (grid[i+width] == 0)
                    addEdge(i, i+width);
        }
    }

}

void Graph::addEdge(int v, int w)
{
    //vertexList[v].insert(w);
    vertices[v].insert(w);
}

int Graph::V()
{
    return vertices.size();
}

int Graph::E()
{
    int edges = 0;

    for (auto obj : vertices)
        edges += obj.second.size();

    return edges;
}

std::set<int> Graph::Vertices()
{
    std::set<int> temp;

    for (auto obj : vertices)
        temp.insert(obj.first);

    return temp;
}

std::set<int> Graph::adj(int v)
{
    std::set<int> temp;

    for (int edge : vertices[v])
        temp.insert(edge);

    return temp;
}

