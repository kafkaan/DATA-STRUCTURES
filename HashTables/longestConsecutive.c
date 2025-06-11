#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ------- struct type -------------------------------------------------------------------------
typedef struct HashSet
{
    int data;
    struct HashSet *next;
} HashSet;

// ------- generate hash for the index in the array ---------------------------------------
unsigned int generateHash(int data, unsigned int capacity)
{
    return (unsigned int)((data % (int)capacity + (int)capacity) % (int)capacity);
}

// ------- Function to check if data is alrady in the hahset -----------------------------
int checkAndAddInHashSet(HashSet **arr, int data, int capacity)
{
    // array contains pointers of hashsets
    unsigned int hash = generateHash(data, capacity);
    // get the pointer of the hashet with hash
    HashSet **top = &arr[hash];

    while (*top != NULL)
    {
        if ((*top)->data == data)
        {
            /// we find the elemet
            return -1;
        }
        top = &(*top)->next;
    }
    *top = malloc(sizeof(HashSet));
    (*top)->data = data;
    (*top)->next = NULL;
    return 0;
}

bool checkIfNumberInHashSet(HashSet **arr, int data, int capacity)
{
    // array contains pointers of hashsets
    unsigned int hash = generateHash(data, capacity);
    // get the pointer of the hashet with hash
    HashSet **top = &arr[hash];

    while (*top != NULL)
    {
        if ((*top)->data == data)
        {
            /// we find the elemet
            return true;
        }
        top = &(*top)->next;
    }

    return false;
}

int longestConsecutive(int *nums, int numsSize)
{
    int longest = 0;
    unsigned int capacity = numsSize;
    capacity = capacity * 3;

    // create array with correctly allocated memory ------
    HashSet **array = malloc(sizeof(HashSet *) * capacity);

    for (int i = 0; i < capacity; i++)
    {
        array[i] = NULL;
    }

    for (int i = 0; i < numsSize; i++)
    {
        checkAndAddInHashSet(array, nums[i], capacity);
    }

    // 🔄 Étape 1 : aplatir tous les éléments dans un tableau de HashSet *
    HashSet **flatList = malloc(sizeof(HashSet *) * numsSize);
    int flatCount = 0;

    for (int i = 0; i < capacity; i++)
    {
        HashSet *node = array[i];
        while (node)
        {
            flatList[flatCount++] = node;
            node = node->next;
        }
    }
    HashSet **pointer = flatList;

    for (int i = 0; i < flatCount; i++)
    {
        if (!checkIfNumberInHashSet(array, (flatList[i]->data) - 1, capacity))
        {
            int length = 1;
            while (checkIfNumberInHashSet(array, (flatList[i]->data) + length, capacity))
            {
                length += 1;
            }
            longest = longest > length ? longest : length;
        }
    }

    return longest;
}