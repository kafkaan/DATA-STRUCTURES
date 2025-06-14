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
    return data % capacity;
}

// ------- Function to check if data is alrady in the hahset -----------------------------

/// @brief Function to check if data is already in the hashset and add it if not.
/// @param arr array of pointers to HashSet
/// @param data data to check and add
/// @param capacity capacity of the hashset array
/// @details This function checks if the data is already present in the hashset. If it is, it returns -1.
/// @return -1 if the data is already present, 0 if the data was added successfully.
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

// ----------------- Main function to check duplicates ---------------------------------
bool containsDuplicate(int *nums, int numSize)
{
    unsigned int capacity = numSize;
    capacity = capacity * 2;

    // create array with correctly allocated memory
    HashSet **array = malloc(sizeof(HashSet *) * capacity);

    if (array == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return false; // or handle error as needed
    }
    // Initialize all elements to NULL
    for (int i = 0; i < capacity; i++)
    {
        array[i] = NULL;
    }

    for (int i = 0; i < numSize; i++)
    {
        if (checkAndAddInHashSet(array, nums[i], capacity) == -1)
        {
            return true;
        }
    }
    return false;
}

// -------------------------------------------- Main ----------------
void main(void)
{
    int nums1[] = {1, 2, 3, 4, 5};     // pas de doublons
    int nums2[] = {1, 2, 3, 2};        // doublon: 2
    int nums3[] = {7, 8, 9, 7, 10, 8}; // doublons: 7 et 8

    printf("Test 1 : %s\n", containsDuplicate(nums1, 5) ? "true" : "false");
    printf("Test 2 : %s\n", containsDuplicate(nums2, 4) ? "true" : "false");
    printf("Test 3 : %s\n", containsDuplicate(nums3, 6) ? "true" : "false");
}
