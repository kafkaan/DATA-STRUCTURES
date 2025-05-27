#include <stdlib.h>
#include <stdio.h>

/*

Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.
Example 1:

Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Example 2:

Input: nums = [1], k = 1
Output: [1]
*/


/// @brief struct Hashset contains data the frequence of the elemnt and next element pointer -------------------- >
typedef struct HashSet
{
    int data;
    int frequence;
    struct HashSet *next;
} HashSet;


// ----------------------------------------------------- Sort ------------------------------------------------------ >
void swap(HashSet **a, HashSet **b)
{
    HashSet *temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function
int partition(HashSet **arr, int low, int high)
{
    HashSet *pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j]->frequence < pivot->frequence)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(HashSet **arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ----------------------------------------------------- Sort End ------------------------------------------------------ >


// ----------------------------- Hash ------------------------
unsigned int generateHash(int data, unsigned int capacity)
{
    const unsigned int knuth = 2654435761u;
    return (data * knuth) % capacity;
}

int checkAndAddInHashSet(HashSet **arr, int data, int capacity)
{
    unsigned int hash = generateHash(data, capacity);

    HashSet **top = &arr[hash];

    while (*top != NULL)
    {
        if ((*top)->data == data)
        {
            (*top)->frequence += 1;
            return -1;
        }
        top = &(*top)->next;
    }

    *top = malloc(sizeof(HashSet));
    (*top)->data = data;
    (*top)->frequence = 1;
    (*top)->next = NULL;
   
    return 0;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *topKFrequent(int *nums, int numsSize, int k, int *returnSize)
{
    unsigned int capacity = numsSize * 2;

    HashSet **table = malloc(sizeof(HashSet *) * capacity);
    for (int i = 0; i < capacity; i++)
        table[i] = NULL;

    // Remplir la table de hachage
    for (int i = 0; i < numsSize; i++) {
        checkAndAddInHashSet(table, nums[i], capacity);
    }

    // 🔄 Étape 1 : aplatir tous les éléments dans un tableau de HashSet *
    HashSet **flatList = malloc(sizeof(HashSet *) * numsSize);
    int flatCount = 0;

    for (int i = 0; i < capacity; i++) {
        HashSet *node = table[i];
        while (node) {
            flatList[flatCount++] = node;
            node = node->next;
        }
    }

    // 🧮 Tri décroissant des fréquences
    quickSort(flatList, 0, flatCount - 1);

    // Récupérer les k premiers éléments
    int *res = malloc(sizeof(int) * k);
    for (int i = 0; i < k; i++) {
        res[i] = flatList[flatCount - 1 - i]->data;  // décroissant
    }

    *returnSize = k;

    free(flatList);
    free(table);
    return res;
}




