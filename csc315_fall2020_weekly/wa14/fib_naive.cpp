#include "dynamic.h"

// Naive approach, 
int fib(int n)
{
    if (n < 2)
        return n;
    
    // Recalculates values which have already been calculated
    return fib(n-1) + fib(n-2);
}

