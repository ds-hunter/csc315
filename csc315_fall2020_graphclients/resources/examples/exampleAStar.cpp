#include "../../weightedGraph.h"
#include "../../astar.h"
#include <list>
#include <map>
#include <fstream>

int main()
{
    int startVertex;
    int endVertex;
    list<int> path;
    map<int, bool> visitedVertices;
    WeightedGraph *wGraph;
    AStar *astar;
    std::ifstream fin;

    // Open a file containing information for the graph
    fin.open("../testWeighted.dat");
    wGraph = new WeightedGraph(fin);
    fin.close(); 

    // Grab some vertex data from the graph 
    startVertex = *wGraph->Vertices().begin();
    endVertex = *wGraph->Vertices().end();

    // Create an astar object 
    astar = new AStar(wGraph, startVertex, endVertex);

    // Get the path from startVertex to endVertex
    path = astar->pathTo(endVertex);
    std::cout << "The path from vertex " << startVertex << " to " << endVertex
        << " is \n\t";
    for (int v : path)
        cout << v << " ";
    std::cout << std::endl;

    // Determine if there is a path between startVertex and endVertex
    if(astar->hasPath(endVertex))
        std::cout << "A path exists to the end vertex!" << std::endl;
    else
        std::cout << "A path does not exist to the end vertex!" << std::endl;

    // Check if the end node was visited
    visitedVertices = astar->Visited();
    std::cout << "End Vertex ";
    if (visitedVertices.find(endVertex) != visitedVertices.end())
       std::cout << (visitedVertices.at(endVertex) ? 
          "was visited" : "was not visited") << std::endl; 

    return 0;
}
