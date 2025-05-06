#include <stdlib.h>



int* twoSum(int* numbers, int numbersSize, int target, int* returnSize)
{
    int i = 0;
    int j = numbersSize - 1;

    while (i < j)
    {
        int sum = numbers[i] + numbers[j];

        if (sum == target)
        {
            int* array = malloc(sizeof(int) * 2);
            array[0] = i + 1;
            array[1] = j + 1;
            *returnSize = 2;
            return array;
        }
        else if (sum < target)
        {
            i++;
        }
        else
        {
            j--;
        }
    }

    *returnSize = 0;
    return NULL;
}