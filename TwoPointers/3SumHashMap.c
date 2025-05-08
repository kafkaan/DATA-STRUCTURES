#include <stdio.h>
#include <stdlib.h>


void swap(int *a, int *b);

// ----------------------------------- Sort --------------------------------------------------

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

// ------------------------------------------------------------------------------------------------------------

typedef struct HashSet
{
    int data;
    int count;
    struct HashSet *next;
} HashSet;

unsigned int generateHash(int data, unsigned int capacity)
{
    // Utilisation de l'algorithme de hachage fnv-1a pour un entier
    unsigned int hash = 2166136261u;  // Valeur d'amorçage FNV
    
    // Traite chaque octet de l'entier
    unsigned char *bytes = (unsigned char *)&data;
    for (size_t i = 0; i < sizeof(int); i++) {
        hash ^= bytes[i];
        hash *= 16777619u;  // Nombre premier FNV
    }
    
    return hash % capacity;
}

int checkAndAddInHashSet(HashSet **arr, int data, int capacity)
{
    unsigned int hash = generateHash(data, capacity);

    HashSet **top = &arr[hash];

    while (*top != NULL)
    {
        if ((*top)->data == data)
        {
            (*top)->count += 1;
            return 0;
        }

        top = &(*top)->next;
    }

    *top = malloc(sizeof(HashSet));
    (*top)->data = data;
    (*top)->count = 1;
    (*top)->next = NULL;

    return 0;
}

HashSet *getHashElement(int data, HashSet **arr, int capacity)
{
    unsigned int hash = generateHash(data, capacity);

    HashSet **top = &arr[hash];

    while (*top != NULL)
    {
        if ((*top)->data == data)
        {
            return *top;
        }

        top = &(*top)->next;
    }

    return NULL;
}

// -----------------------------------------------------------------

int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    quickSort(nums,0,numsSize-1);
    int index = 0;
    unsigned int capacity = numsSize;

    HashSet **array = malloc(sizeof(HashSet *) * capacity);

    for (int i = 0; i < capacity; i++)
    {
        array[i] = NULL;
    }

    for (int i = 0; i < numsSize; i++)
    {
        checkAndAddInHashSet(array, nums[i], capacity);
    }

    int **resArray = malloc(sizeof(int *) * numsSize * numsSize); // sécurité maximale

    int **pointer = resArray;

    for (int i = 0; i < numsSize; i++)
    {
        HashSet *set = getHashElement(nums[i], array, capacity);

        set->count -= 1;

        if (i && nums[i] == nums[i - 1])
        {
            continue;
        }

        for (int j = i + 1; j < numsSize; j++)
        {
            HashSet *set2 = getHashElement(nums[j], array, capacity);
            set2->count -= 1;

            if (j -1 > i && nums[j] == nums[j - 1])
            {
                continue;
            }

            int target = -(nums[i] + nums[j]);
            HashSet *targetSet = getHashElement(target, array, capacity);
            if (targetSet != NULL && (targetSet)->count > 0)
            {
                int *row = malloc(sizeof(int) * 3);

                row[0] = nums[i];
                row[1] = nums[j];
                row[2] = target;
                resArray[index] = row;

                index++;
            }
        }

        for (int j = i + 1; j < numsSize; j++)
        {
            HashSet *set3 = getHashElement(nums[j], array, capacity);
            set3->count += 1;
        }
    }
    *returnSize = index;

    *returnColumnSizes = malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; i++)
    {
        (*returnColumnSizes)[i] = 3;
    }
    return resArray;
}