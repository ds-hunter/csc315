#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <iostream>
#include <map>
#include "bfsPaths.h"
#include "dfsPaths.h"
#include "dijkstra.h"
#include "astar.h"

#define BLOCKED olc::GREY
#define START olc::GREEN
#define END   olc::RED
#define HEAVY olc::VERY_DARK_YELLOW
#define MEDIUM olc::DARK_YELLOW
#define LIGHT olc::YELLOW
#define NORMAL olc::BLUE

const std::map<olc::Pixel, int> pixelToInt = {
   {olc::BLUE, 1}, {olc::YELLOW, 2}, {olc::DARK_YELLOW, 3}, 
   {olc::VERY_DARK_YELLOW, 4}, {olc::RED, 6}, {olc::GREEN, 7}, {olc::GREY, -1}
};

const std::map<int, olc::Pixel> intToPixel = {
   {1, olc::BLUE}, {2, olc::YELLOW}, {3, olc::DARK_YELLOW},
   {4, olc::VERY_DARK_YELLOW}, {6, olc::RED}, {7, olc::GREEN}, {-1, olc::GREY}
};

using namespace std;

enum Paths {NOPATH, BFS, DFS, ASTAR, DIJKSTRA};
enum GraphType {UNWEIGHTED, WEIGHTED};

class Terrain : public olc::PixelGameEngine
{
   Paths thePath;
   GraphType theGraph;
   Graph *graph;
   WeightedGraph *wGraph;
   BFSPaths *bfsPaths;
   DFSPaths *dfsPaths;
   Dijkstra *dijkstra;
   AStar *astar;
   int nMapWidth;
   int nMapHeight;
   int nCellSize;
   int nBorderWidth;
   int nStart, nEnd;
   olc::Pixel *cWeightMap;
   int *grid;
   const char *inputFile;
   list<int> path;
   bool singleStep;

public:
   Terrain(int argc, char **argv) : thePath(NOPATH), theGraph(UNWEIGHTED), graph(nullptr), wGraph(nullptr), bfsPaths(nullptr), dfsPaths(nullptr), dijkstra(nullptr), astar(nullptr), inputFile(nullptr), singleStep(true)
   {
      nBorderWidth = 2;
      nCellSize = 8;
      sAppName = "SD Mines Terrain";

      if (argc == 2) inputFile = argv[1];
   }

public:
   // Called once at the start, so create things here
   bool OnUserCreate()
   {
      printUsage();
      if (inputFile != nullptr)
         ReadGrid(inputFile);
      else
      {
         nMapWidth = ScreenWidth() / nCellSize;
         nMapHeight = ScreenHeight() / nCellSize;
         nStart = 0;
         nEnd = nMapWidth * nMapHeight - 1;

         cWeightMap = new olc::Pixel[nMapWidth * nMapHeight];
         grid = new int[nMapWidth * nMapHeight];

         for (int p = 0 ; p < nMapWidth * nMapHeight ; p++)
         {
            grid[p] = 1;
            cWeightMap[p] = NORMAL;
         }

         cWeightMap[nStart] = START;
         cWeightMap[nEnd] = END;
         grid[nStart] = pixelToInt.at(olc::GREEN);
         grid[nEnd] = pixelToInt.at(olc::RED);
      }

      graph = new Graph(grid, nMapWidth, nMapHeight);
      wGraph = new WeightedGraph(grid, nMapWidth, nMapHeight);
      return true;
   }

   void ReadGrid(const char *filename)
   {
      bool foundBadPixel = false;
      auto p = [&](int x, int y) { return y * nMapWidth + x ; };
      ifstream fin;
      fin.open(filename, ios::binary);
      fin >> nMapHeight >> nMapWidth;
  
      nCellSize = ScreenHeight() / nMapHeight; 
      nStart = 0 ; nEnd = nMapHeight * nMapWidth - 1; 
      cWeightMap = new olc::Pixel[nMapWidth * nMapHeight];
      grid = new int[nMapWidth * nMapHeight];

      for (int y = 0 ; y < nMapHeight ; y++)
      {
         for (int x = 0 ; x < nMapWidth ; x++)
         {
            int tmp;
            fin >> tmp;
            if (intToPixel.find(tmp) == intToPixel.end())
            {
               tmp = pixelToInt.at(NORMAL);
               foundBadPixel = true;
            }
            grid[p(x,y)] = tmp;
            cWeightMap[p(x,y)] = intToPixel.at(tmp);
            if (intToPixel.at(tmp) == START) nStart = p(x,y);
            if (intToPixel.at(tmp) == END) nEnd = p(x,y);
         }
      }
      if (foundBadPixel)
         cout << "Some pixels in input file were invalid and changed to open cell\n";
      fin.close();
   }

   void WriteGrid()
   {
      auto p = [&](int x, int y) { return y * nMapWidth + x ; };
      ofstream fout;
      fout.open("Output", ios::binary);

      fout << nMapHeight << " " << nMapWidth << endl;
      for (int y = 0 ; y < nMapHeight ; y++)
      {
         for (int x = 0 ; x < nMapWidth ; x++)
            fout << pixelToInt.at(cWeightMap[p(x,y)]) << " ";
   
         fout << endl;
      }
      fout.close();
   }

   void redraw()
   {
      auto p = [&](int x, int y) { return y * nMapWidth + x ; };
      for (int x = 0 ; x < nMapWidth ; x++)
      {
         for (int y = 0 ; y < nMapHeight ; y++)
         {
            FillRect(x * nCellSize, y * nCellSize, nCellSize - nBorderWidth, nCellSize - nBorderWidth, cWeightMap[p(x,y)]);
         }
      }
   }

   void resetMap()
   {
      for (int v = 0 ; v < nMapWidth * nMapHeight ; v++)
      {
         cWeightMap[v] = intToPixel.at(grid[v]);

         if (intToPixel.at(grid[v]) == START) nStart = v;
         if (intToPixel.at(grid[v]) == END) nEnd = v;
      }
   }

   void cleanPath()
   {
      for (int v = 0 ; v < nMapWidth * nMapHeight ; v++)
         if (cWeightMap[v] == olc::DARK_BLUE)
            cWeightMap[v] = NORMAL;

      if (bfsPaths != nullptr)
      {
         for (int w : bfsPaths->pathTo(nEnd))
            if (w != nStart && w != nEnd)
               cWeightMap[w] = NORMAL;

         delete bfsPaths;
         bfsPaths = nullptr;
      }
      if (dfsPaths != nullptr)
      {
         for (int w : dfsPaths->pathTo(nEnd))
            if (w != nStart && w != nEnd)
               cWeightMap[w] = NORMAL;

         delete dfsPaths;
         dfsPaths = nullptr;
      }
      if (dijkstra != nullptr)
      {
         for (int w : dijkstra->pathTo(nEnd))
            if (w != nStart && w != nEnd)
               cWeightMap[w] = NORMAL;
       
         dijkstra = nullptr;
      }
      if (astar != nullptr)
      {
         for (int w : astar->pathTo(nEnd))
            if (w != nStart && w != nEnd)
               cWeightMap[w] = NORMAL;

         astar = nullptr;
      }
   }

   void onLeftMouseUp()
   {
      auto p = [&](int x, int y) { return y * nMapWidth + x ; };
      int nSelectedCellX = GetMouseX() / nCellSize;
      int nSelectedCellY = GetMouseY() / nCellSize;

      cleanPath();
      if (cWeightMap[p(nSelectedCellX, nSelectedCellY)] == BLOCKED)
      {
	 grid[p(nSelectedCellX, nSelectedCellY)] = pixelToInt.at(NORMAL);
         cWeightMap[p(nSelectedCellX, nSelectedCellY)] = NORMAL;
      }
      else
      {
         grid[p(nSelectedCellX, nSelectedCellY)] = pixelToInt.at(BLOCKED);
         cWeightMap[p(nSelectedCellX, nSelectedCellY)] = BLOCKED;
      }

      delete graph;
      delete wGraph;
      graph = new Graph(grid, nMapWidth, nMapHeight);
      wGraph = new WeightedGraph(grid, nMapWidth, nMapHeight);
   }

   void onRightMouseUp()
   {
      auto p = [&](int x, int y) { return y * nMapWidth + x ; };
      int nSelectedCellX = GetMouseX() / nCellSize;
      int nSelectedCellY = GetMouseY() / nCellSize;
      int point = p(nSelectedCellX, nSelectedCellY);
      if (GetKey(olc::Key::SHIFT).bHeld)
      {
         cleanPath();
         cWeightMap[nEnd] = NORMAL;
         nEnd = point;
         cWeightMap[nEnd] = END;
      }
      else
      {
         cleanPath();
         cWeightMap[nStart] = NORMAL;
         nStart = point;
         cWeightMap[nStart] = START;
      }
   }

   list<int> performDFS()
   {
      cleanPath();
      list<int> path;
      thePath = DFS;
      dfsPaths = new DFSPaths(graph, nStart);
      path = dfsPaths->pathTo(nEnd);
      return path;
   }

   list <int> performBFS()
   {
      cleanPath();
      bfsPaths = new BFSPaths(graph, nStart, nEnd);
      path = bfsPaths->pathTo(nEnd);
      thePath = BFS;
      for (int v : graph->Vertices())
         if (bfsPaths->Visited()[v] && v != nStart && v != nEnd) 
            cWeightMap[v] = olc::DARK_BLUE;
      return path;
   } 

   list<int> performDijkstra()
   {
      cleanPath();
      thePath = DIJKSTRA;
      dijkstra = new Dijkstra(wGraph, nStart, nEnd);
      path = dijkstra->pathTo(nEnd);
      for (int v : wGraph->Vertices())
         if (dijkstra->Visited()[v] && v != nStart && v != nEnd)
            cWeightMap[v] = olc::DARK_BLUE;

      return path;
   }

   list<int> performAStar()
   {
      cleanPath();
      thePath = ASTAR;
      astar = new AStar(wGraph, nStart, nEnd);
      path = astar->pathTo(nEnd);
      for (int v : wGraph->Vertices())
         if (astar->Visited()[v] && v != nStart && v != nEnd) 
            cWeightMap[v] = olc::DARK_BLUE;

      return path;
   }

   bool OnUserUpdate(float fElapsedTime)
   {
      auto p = [&](int x, int y) { return y * nMapWidth + x ; };
      Clear(olc::BLACK);

      redraw();

      int nSelectedCellX = GetMouseX() / nCellSize;
      int nSelectedCellY = GetMouseY() / nCellSize;

      if (GetMouse(0).bReleased)
      {
	     onLeftMouseUp();
	     switch (thePath)
	     {
		     case BFS:
			     path = performBFS();
			     break;
		     case DFS:
			     path = performDFS();
			     break;
		     case ASTAR:
			     path = performAStar();
			     break;
		     case DIJKSTRA:
			     path = performDijkstra();
			     break;
		     default:
			     break;
	     }
      }

      if (GetMouse(1).bReleased) onRightMouseUp();

      if (GetKey(olc::Key::K1).bPressed)
         cWeightMap[p(nSelectedCellX, nSelectedCellY)] = NORMAL;
   
      if (GetKey(olc::Key::K2).bPressed)
         cWeightMap[p(nSelectedCellX, nSelectedCellY)] = LIGHT;

      if (GetKey(olc::Key::K3).bPressed)
         cWeightMap[p(nSelectedCellX, nSelectedCellY)] = MEDIUM;
   
      if (GetKey(olc::Key::K4).bPressed)
         cWeightMap[p(nSelectedCellX, nSelectedCellY)] = HEAVY;
 
      if (GetKey(olc::Key::C).bPressed) resetMap();

      if (GetKey(olc::Key::S).bPressed) singleStep = !singleStep;
 
      if (GetKey(olc::Key::B).bPressed) path = performBFS();
      else if (GetKey(olc::Key::D).bPressed) path = performDFS();
      else if (GetKey(olc::Key::K).bPressed) path = performDijkstra();
      else if (GetKey(olc::Key::A).bPressed) path = performAStar();
  
      if (GetKey(olc::Key::W).bPressed) WriteGrid();

      list<int>::iterator w = path.begin();
      while (w != path.end())
      {
         if (*w != nStart && *w != nEnd) cWeightMap[*w] = olc::CYAN;

         path.erase(w);
         if (singleStep) break;
         w = path.begin();
      }
      return !(GetKey(olc::Key::Q).bPressed || GetKey(olc::Key::ESCAPE).bPressed);
   }

   void printUsage()
   {
      cout << "Key:			Function\n";
      cout << "----			--------\n";
      cout << " A			Run the AStar algorithm\n";
      cout << " B			Run the BFS algorithm\n";
      cout << " C			Clear grid to original state\n";
      cout << " D			Run the DFS algorithm\n";
      cout << " K			Run the Dijkstra's algorithm\n";
      cout << " S			Toggle single stepping for algorithm\n";
      cout << " W			Write out current grid to file 'Output'\n";
      cout << " (ESCAPE Key|Q)		Exit the program\n";
      cout << "Left Mouse		Place barrier\n";
      cout << "Right Mouse		Move start point\n";
      cout << "Shift Right Mouse	Move end point\n";
   }
};

int main(int argc, char **argv)
{
   Terrain demo(argc, argv);
   if (demo.Construct(480, 480, 2, 2))
      demo.Start();

   return 0;
}
