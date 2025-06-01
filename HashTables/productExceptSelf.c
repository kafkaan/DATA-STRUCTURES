#include <stdio.h>
#include <stdlib.h>

/*
Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation.
*/

int *productExceptSelf(int *nums, int numsSize, int *returnSize)
{
    // Définir la taille du tableau résultat
    *returnSize = numsSize;
    
    int *res = (int *)malloc(sizeof(int) * numsSize);
    if (!res)
        return NULL;
        
    int *pref = (int *)malloc(sizeof(int) * numsSize);
    int *suf = (int *)malloc(sizeof(int) * numsSize);
    
    if (!pref || !suf) {
        free(res);
        free(pref); // Libération sécurisée (fonctionne même si pref est NULL)
        free(suf);
        return NULL;
    }

    // Initialisation
    for (int i = 0; i < numsSize; i++)
    {
        res[i] = pref[i] = suf[i] = 1;
    }

    // Calculer les préfixes
    for (int i = 1; i < numsSize; i++)
    {
        pref[i] = nums[i-1] * pref[i-1];
    }

    // Calculer les suffixes (correction pour inclure i=0)
    for(int i = numsSize - 2; i >= 0; i--)
    {
        suf[i] = suf[i+1] * nums[i+1];
    }

    // Calculer le résultat
    for(int i = 0; i < numsSize; i++)
    {
        res[i] = suf[i] * pref[i];
    }

    // Libérer la mémoire des tableaux temporaires
    free(pref);
    free(suf);

    return res;
}