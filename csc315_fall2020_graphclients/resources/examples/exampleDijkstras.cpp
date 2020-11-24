#include "../../weightedGraph.h"
#include "../../dijkstra.h"
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
    Dijkstra *dijkstra;
    std::ifstream fin;

    // Open a file containing information for the graph
    fin.open("../testWeighted.dat");
    wGraph = new WeightedGraph(fin);
    fin.close(); 

    // Grab some vertex data from the graph 
    startVertex = *wGraph->Vertices().begin();
    endVertex = *wGraph->Vertices().end();

    // Create an astar object 
    dijkstra = new Dijkstra(wGraph, startVertex, endVertex);

    // Get the path from startVertex to endVertex
    path = dijkstra->pathTo(endVertex);
    std::cout << "The path from vertex " << startVertex << " to " << endVertex
        << " is \n\t";
    for (int v : path)
        cout << v << " ";
    std::cout << std::endl;

    // Determine if there is a path between startVertex and endVertex
    if(dijkstra->hasPath(endVertex))
        std::cout << "A path exists to the end vertex!" << std::endl;
    else
        std::cout << "A path does not exist to the end vertex!" << std::endl;

    // Check if the end node was visited by the algorithm
    visitedVertices = dijkstra->Visited();
    std::cout << "End Vertex ";
    if (visitedVertices.find(endVertex) != visitedVertices.end())
       std::cout << (visitedVertices.at(endVertex) ? 
          "was visited" : "was not visited") << std::endl; 

    return 0;
}
