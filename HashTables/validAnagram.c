#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void swap(char *a, char *b);

// Partition function
int partition(char arr[], int low, int high)
{

    // Choose the pivot
    int pivot = arr[high];

    // Index of smaller element and indicates
    // the right position of pivot found so far
    int i = low - 1;

    // Traverse arr[low..high] and move all smaller
    // elements to the left side. Elements from low to
    // i are smaller after every iteration
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    // Move pivot after smaller elements and
    // return its position
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// The QuickSort function implementation
void quickSort(char arr[], int low, int high)
{
    if (low < high)
    {

        // pi is the partition return index of pivot
        int pi = partition(arr, low, high);

        // Recursion calls for smaller elements
        // and greater or equals elements
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void swap(char *a, char *b)
{
    char t = *a;
    *a = *b;
    *b = t;
}

bool isAnagram(char *s, char *t)
{
    if (strlen(s) != strlen(t))
        return false;

    quickSort(s, 0, strlen(s) - 1);
    quickSort(t, 0, strlen(t) - 1);

    while (*s && *t) {
        if (*s != *t)
            return false;
        s++;
        t++;
    }

    return true;  // Si on a parcouru tout sans problème
}
