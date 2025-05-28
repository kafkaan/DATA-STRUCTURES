#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// ---------------- HashSet structure ---------------- >
typedef struct HashSet
{
    int data;
    int index;
    struct HashSet *next;
} HashSet;
// ---------------- HashSet structure ---------------- <


/// @brief Generate a hash value for the given data based on the capacity
/// @param data The integer data to hash
/// @param capacity The capacity of the hash table
/// @return The hash value as an unsigned integer
unsigned int generateHash(int data, unsigned int capacity)
{
    return data % capacity;
}

int checkAndAddInHashSet(HashSet **arr, int data, int index, int capacity)
{
    unsigned int hash = generateHash(data, capacity);
    HashSet **top = &arr[hash];

    while (*top != NULL)
    {
        if ((*top)->data == data)
        {
            return -1;
        }
        top = &(*top)->next;
    }
    *top = malloc(sizeof(HashSet));
    (*top)->data = data;
    (*top)->index = index;
    (*top)->next = NULL;
    return 0;
}


// --------------------- Main function --------------------- >
int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    unsigned int capacity = numsSize;

    capacity = capacity * 2;

    HashSet **array = malloc(sizeof(HashSet *) * capacity);

    for (int i = 0; i < capacity; i++)
    {
        array[i] = NULL;
    }

    for (int i = 0; i < numsSize; i++)
    {
        int t = target - nums[i];
        int hashToFind = generateHash(t, capacity);

        HashSet *cur = array[hashToFind];

        while (cur != NULL)
        {
            if (cur->data == t)
            {
                int *resArray = malloc(sizeof(int) * 2);
                resArray[0] = cur->index;
                resArray[1] = i;
                *returnSize = 2;

                // Ne pas oublier de free ici dans une vraie app
                return resArray;
            }
            cur = cur->next;
        }

        checkAndAddInHashSet(array, nums[i], i, capacity);
    }
    *returnSize = 0;
    return NULL;
}
