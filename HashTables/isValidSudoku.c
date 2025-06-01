#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct HashSet
{
    char data;
    struct HashSet *next;
} HashSet;

int checkAndAddInHashSet(HashSet **arr, char data, int index)
{
    if (data == '.') return 0;

    unsigned int hash = index;
    HashSet **top = &arr[hash];

    while (*top != NULL)
    {
        if ((*top)->data == data)
        {
            return -1; // Duplicate found
        }
        top = &(*top)->next;
    }

    *top = malloc(sizeof(HashSet));
    (*top)->data = data;
    (*top)->next = NULL;

    return 0;
}

bool isValidSudoku(char **board, int boardSize, int *boardColSize)
{
    unsigned int capacity = 9;

    HashSet **rowsSet = malloc(sizeof(HashSet *) * capacity);
    HashSet **colsSet = malloc(sizeof(HashSet *) * capacity);
    HashSet **boxSet = malloc(sizeof(HashSet *) * capacity);

    for (int i = 0; i < capacity; i++)
    {
        rowsSet[i] = NULL;
        colsSet[i] = NULL;
        boxSet[i] = NULL;
    }

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardColSize[i]; j++)
        {
            char val = board[i][j];

            // Row check
            if (checkAndAddInHashSet(rowsSet, val, i) == -1)
                return false;

            // Column check
            if (checkAndAddInHashSet(colsSet, val, j) == -1)
                return false;

            // Box check: box index = (i / 3) * 3 + (j / 3)
            int boxIndex = (i / 3) * 3 + (j / 3);
            if (checkAndAddInHashSet(boxSet, val, boxIndex) == -1)
                return false;
        }
    }

    return true;
}
