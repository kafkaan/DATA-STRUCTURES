
#include <stdio.h>
#include <stdlib.h>

int maxProfitTwoPointers(int *prices, int pricesSize)
{
    int l = 0;

    int r = 1;

    int maxP = 0;

    while (r < pricesSize)
    {
        if (prices[l] < prices[r])
        {
            int profit = prices[r] - prices[l];
            maxP = maxP > profit ? maxP : profit;
        }
        else
        {
            l = r;
        }

        r += 1;
    }
}