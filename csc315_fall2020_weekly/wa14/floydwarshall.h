/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef FLOYDWARSHALL_H
#define FLOYDWARSHALL_H
#include <list>
#include <vector>
#include "amgraph.h"

using namespace std;

/********************************************************************//**
 * @class Floydwarshall
 **********************************************************************/
class Floydwarshall
{
   vector<vector<double>> memo;
   vector<vector<int>> next;
public:
   Floydwarshall(Amgraph *);

   bool hasPath(int, int);
   list<int> pathTo(int, int);
   double distance(int, int);

private:
   void initialize(Amgraph *);
   void executeFW();
   void checkForNegCycles();
};
#endif
