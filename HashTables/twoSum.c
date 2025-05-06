#include <stdlib.h>
#include <stdio.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    for(int i = 0; i < numsSize; i++)
    {
        for(int j = 0 ; j < numsSize; j++)
        {
            if(i != j)
            {
                if(nums[i] + nums[j] == target)
                {
                    int *array = malloc(sizeof(int) * 2);
                    array[0] = i;
                    array[1] = j;
                    *returnSize = 2; // <- bonne pratique pour informer le caller
                    return array;
                }
            }
        }
    }

    *returnSize = 0;
    return NULL; // <- Ajout ici : s'il n'y a pas de solution, retourne NULL
}
