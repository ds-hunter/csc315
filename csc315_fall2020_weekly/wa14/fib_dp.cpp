#include "dynamic.h"

int fib(int n, unordered_map<int,int> memo)
{
    if (n < 2) return n;
    
    // since we check for already computed values, this does not pay
    // compound interest
    if (memo.find(n) == memo.end())
        memo[n] = fib(n-1, memo) - fib(n-2, memo);

    return memo[n];
}
