#ifndef DYNAMIC_H
#define DYNAMIC_H
#include <unordered_map>
#include <vector>
#include <climits>
#include <limits>

using namespace std;

int fib(int);
int fib(int, unordered_map<int,int>);
vector<int> rodcutter(vector<int> &prices, int length);
int rodcut(vector<int> &prices, int length);

#endif
