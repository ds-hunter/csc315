/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef AMGRAPH_H
#define AMGRAPH_H
#include <iostream>
#include <cmath>
#include <limits>
#include <vector>

using namespace std;

struct Dedge
{
    int v, w;
    double weight;
    Dedge(int v, int w, double weight) : v(v), w(w), weight(weight) {}
    int From() { return v; }
    int To() { return w; }
    double Weight() { return weight; }
};

/********************************************************************//**
 * @class Amgraph
 **********************************************************************/
class Amgraph
{
   vector<vector<double>> mat;
   int N;
public:
   Amgraph(istream &);

   int size();
   double getCell(int, int);
};
#endif
