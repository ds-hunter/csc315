#include "../../graph.h"
#include "../../bfsPaths.h"
#include <list>
#include <map>
#include <fstream>

int main()
{
    int startVertex;
    int endVertex;
    list<int> path;
    map<int, bool> visitedVertices;
    Graph *graph;
    BFSPaths *bfs;
    std::ifstream fin;

    // Open a file containing information for the graph
    fin.open("../testUnweighted.dat");
    graph = new Graph(fin);
    fin.close(); 

    // Grab some vertex data from the graph 
    startVertex = *graph->Vertices().begin();
    endVertex = *graph->Vertices().end();

    // Create an astar object 
    bfs = new BFSPaths(graph, startVertex, endVertex);

    // Get the path from startVertex to endVertex
    path = bfs->pathTo(endVertex);
    std::cout << "The path from vertex " << startVertex << " to " << endVertex
        << " is \n\t";
    for (int v : path)
        cout << v << " ";
    std::cout << std::endl;

    // Determine if there is a path between startVertex and endVertex
    if(bfs->hasPath(endVertex))
        std::cout << "A path exists to the end vertex!" << std::endl;
    else
        std::cout << "A path does not exist to the end vertex!" << std::endl;

    // Check if the end node was visited by the algorithm
    visitedVertices = bfs->Visited();
    std::cout << "End Vertex ";
    if (visitedVertices.find(endVertex) != visitedVertices.end())
       std::cout << (visitedVertices.at(endVertex) ? 
          "was visited" : "was not visited") << std::endl; 

    return 0;
}
