#include <stdbool.h>

/*
 * Recherche si target est présent dans une matrice triée.
 * Étape 1 : Recherche de la ligne possible
 * Étape 2 : Recherche binaire dans cette ligne
 * Complexité : O(log m + log n)
 */

bool searchMatrix(int **matrix, int matrixSize, int *matrixColSize, int target) {
    
    // Verification of input parameters 
    if (matrixSize == 0 || *matrixColSize == 0) return false;

    // initialization of variables
    int top = 0;
    int bot = matrixSize - 1;
    int cols = *matrixColSize;

    // Étape 1 : Trouver la bonne ligne
    while (top <= bot) {
        int row = (top + bot) / 2;

        if (target > matrix[row][cols - 1]) {
            top = row + 1;
        } else if (target < matrix[row][0]) {
            bot = row - 1;
        } else {
            // target est potentiellement dans cette ligne
            break;
        }
    }

    // Si top dépasse bot, cela signifie que target n'est pas dans la matrice
    if (top > bot) return false;

    // La ligne est trouvée
    int row = (top + bot) / 2;

    // Étape 2 : Recherche binaire dans la ligne
    int left = 0;
    int right = cols - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (target == matrix[row][mid]) {
            return true;
        } else if (target < matrix[row][mid]) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return false;
}
