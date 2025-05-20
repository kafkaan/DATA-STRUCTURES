#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>  // Pour utiliser INT_MAX

#define MAX_SIZE 100

typedef struct
{
    int arr[MAX_SIZE];
    int arrMin[MAX_SIZE];

    int min;
    
    int top;
    int minTop;

} MinStack;

MinStack *minStackCreate()
{
    MinStack *stack = malloc(sizeof(MinStack));
    if (stack == NULL)
    {
        return NULL; // Gestion d'erreur d'allocation
    }
    stack->top = -1;
    stack->minTop = -1;
    stack->min = INT_MAX;  // Correctement initialisé avec INT_MAX
    return stack;
}

bool isStackFull(MinStack *stack)
{
    return stack->top == MAX_SIZE - 1;
}

bool isEmpty(MinStack *stack)
{
    return stack->top == -1;
}

void minStackPush(MinStack *obj, int val)
{
    if (isStackFull(obj))
    {
        exit(-1);
    }

    if (obj->min >= val)
    {
        obj->arrMin[++obj->minTop] = val;
        obj->min = val;
    }

    obj->arr[++obj->top] = val;  // Correction: = au lieu de ==
}

void minStackPop(MinStack *obj)
{
    if (isEmpty(obj))
    {
        exit(-1);
    }

    int popped = obj->arr[obj->top];
    if (popped == obj->min)
    {
        obj->minTop--;
        if (obj->minTop >= 0)
            obj->min = obj->arrMin[obj->minTop];
        else
            obj->min = INT_MAX;  // Cas où la pile des minimums est vide
    }
    obj->top--;
}

int minStackTop(MinStack *obj)
{
    if (isEmpty(obj))
    {
        // Gestion d'erreur si nécessaire
        return -1;
    }
    return obj->arr[obj->top];
}

int minStackGetMin(MinStack *obj)
{
    if (obj->minTop < 0)
    {
        // Gestion d'erreur si nécessaire
        return INT_MAX;
    }
    return obj->min;
}

void minStackFree(MinStack *obj)
{
    free(obj);
}