#include <iostream>
#include <iomanip>
#include "dynamic.h"
#include "floydwarshall.h"
#include "amgraph.h"

using namespace std;

int main()
{
   vector<int> prices = {0,1,5,8,9,10,17,17,20};

   Amgraph *graph = new Amgraph(cin);
   Floydwarshall fw(graph);

   cout << "All Pairs distances:" << endl;
   for (int row = 1 ; row < 5 ; row++)
   {
      for (int col = 1 ; col < 5 ; col++)
         cout << setw(5) << fw.distance(row, col);

      cout << endl;
   }

   cout << "Fib(10) = " << fib(10) << endl;
   cout << "Rodcut(8) = " << rodcut(prices, 8) << endl;
}
