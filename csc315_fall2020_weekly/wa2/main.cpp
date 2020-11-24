#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>      /* printf, scanf, puts, NULL */
#include <cstdlib>     /* srand, rand */
#include <ctime> 
using namespace std;

// Size of N can be changed using the -D compiler option
// example: g++ -D N=1000
// sets N = 1000

#ifndef N
#define N 100
#endif

// Prototype for the bubble sort that I am using for this assignment
// (Definitely way slower than something like quicksort or stl sort)
void bubble_sort(vector<int> &arr, int n);

// Prototype for the find Kth largest function
// 
// array is a vector of numbers
// k tells the function to return the kth largest number from vector array
int findKthLargest(vector<int> &array, int k);

// Fill the vector with random numbers from 0 to ARRAY_SIZE - 1
void fillArray(vector<int> &a)
{
   srand(time(NULL));
   for (unsigned int i = 0 ; i < N ; i++)
      a.push_back(rand());
} 

int main(int argc, char *argv[])
{
   vector<int> numbers;
   fillArray(numbers);

   int k = N / 2;

   if (argc == 2)
      k = stoi(argv[1]);

   if (k >= N) k = N / 2;

   cout << "The " << k << "th largest number (out of " << N << ") is " 
        << findKthLargest(numbers, k) << endl;

   return 0;
}
