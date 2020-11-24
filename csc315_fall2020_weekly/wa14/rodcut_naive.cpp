#include "dynamic.h"

int rodcut(vector<int> &prices, int length)
{
    if (length == 0)
        return 0;

    int maxValue = INT_MIN; 

    for (int i = 1; i <= length; i++)
    {
        int cost = prices[i-1] + rodcut(prices, length - i);

        if (cost > maxValue)
            maxValue = cost;
    }

    return maxValue;
}
