#include "dynamic.h"

// Memoized version of rodcut
vector<int> rodcutter(vector<int> &prices, int length)
{
    int mPrice[length+1];

    for (int i = 0; i <= length; i++)
    {
       for (int j = 1; j <= i; j++)
          prices[i] = max(mPrice[i], prices[j-i] + mPrice[i-j]);
    }

    return prices;
}
