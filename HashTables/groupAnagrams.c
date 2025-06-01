#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// ----------------------------------- hashsets ------------------------------------ >
typedef struct WordNode
{
    char *word;
    struct WordNode *next;
} WordNode;


typedef struct AnagramGroup
{
    char *signature;           // Signature triée qui identifie ce groupe
    WordNode *words;           // Liste des mots dans ce groupe
    int size;                  // Nombre de mots dans ce groupe
    struct AnagramGroup *next; // Prochain groupe dans le même bucket
} AnagramGroup;


// ----------------------------------- hashsets end ------------------------------------ >


// Génère une signature (mot trié) pour un mot
char *getSignature(char *word)
{
    char *signature = strdup(word);
    if (!signature)
        return NULL;

    quickSort(signature, 0, strlen(signature) - 1);
    return signature;
}

// ---------------------------------------------- ADD WORD ---------------------- >
void addWord(AnagramGroup **table, char *word, int capacity, int *groupCount)
{
    // if word is NULL or empty, ignore it
    if (!word)
        return;

    // create a signature for the word
    char *signature = getSignature(word);
    // if signature is NULL (memory allocation failed), ignore it
    if (!signature)
        return;

    // ------------------------------------ Hash ------------------------------- >
    unsigned long hash = 5381;
    for (char *p = signature; *p; p++)
    {
        hash = ((hash << 5) + hash) + *p; // hash * 33 + c
    }
    hash %= capacity;
    // ------------------------------------ Hash End  ------------------------------- >
   
    // Cherche si un groupe avec cette signature existe déjà
    AnagramGroup *curr = table[hash];
    AnagramGroup *prev = NULL;

    while (curr)
    {
        if (strcmp(signature, curr->signature) == 0)
        {
            // Groupe trouvé, ajouter le mot
            WordNode *newWord = malloc(sizeof(WordNode));
            if (!newWord)
            {
                free(signature);
                return;
            }

            newWord->word = strdup(word);
            if (!newWord->word)
            {
                free(newWord);
                free(signature);
                return;
            }

            newWord->next = curr->words;
            curr->words = newWord;
            curr->size++;
            free(signature); // Libère la signature temporaire
            return;
        }

        prev = curr;
        curr = curr->next;
    }

    // Aucun groupe trouvé, créer un nouveau
    AnagramGroup *newGroup = malloc(sizeof(AnagramGroup));
    if (!newGroup)
    {
        free(signature);
        return;
    }

    newGroup->signature = signature; // Utilise la signature générée
    newGroup->size = 1;
    newGroup->next = NULL;

    // Ajoute le premier mot
    WordNode *newWord = malloc(sizeof(WordNode));
    if (!newWord)
    {
        free(signature);
        free(newGroup);
        return;
    }

    newWord->word = strdup(word);
    if (!newWord->word)
    {
        free(newWord);
        free(signature);
        free(newGroup);
        return;
    }

    newWord->next = NULL;
    newGroup->words = newWord;

    // Ajoute le groupe au tableau
    if (prev)
    {
        prev->next = newGroup;
    }
    else
    {
        table[hash] = newGroup;
    }

    (*groupCount)++;
}


// ------------------------------ Trie ----------------------------------------------------------- >
// Partition function pour quickSort
int partition(char arr[], int low, int high)
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
// QuickSort implementation
void quickSort(char arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
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
// ------------------------------ Trie End ----------------------------------------------------------- >

// --------------------------- Main ------------------------------------------------------------------
char ***groupAnagrams(char **strs, int strsSize, int *returnSize, int **returnColumnSizes)
{
    // Utilise un nombre premier pour la taille de la table de hashage
    unsigned int capacity = strsSize;
    *returnSize = 0;

    // Initialise la table de hashage
    AnagramGroup **table = calloc(capacity, sizeof(AnagramGroup *));
    if (!table)
        return NULL;

    // Ajoute chaque mot à son groupe d'anagrammes
    for (int i = 0; i < strsSize; i++)
    {
        addWord(table, strs[i], capacity, returnSize);
    }

    // Alloue les tableaux de résultats
    char ***result = malloc(sizeof(char **) * (*returnSize));
    if (!result)
    {
        // Gestion d'erreur - libérer la mémoire
        // (code de nettoyage omis pour la concision)
        return NULL;
    }

    *returnColumnSizes = malloc(sizeof(int) * (*returnSize));
    if (!*returnColumnSizes)
    {
        free(result);
        // (code de nettoyage omis)
        return NULL;
    }

    // Collecte les groupes
    int groupIndex = 0;

    for (int i = 0; i < capacity; i++)
    {
        AnagramGroup *group = table[i];

        while (group)
        {
            // Alloue le tableau pour ce groupe
            char **words = malloc(sizeof(char *) * group->size);
            if (!words)
                continue;

            // Copie les mots de la liste chaînée vers le tableau
            int wordIndex = 0;
            WordNode *wordNode = group->words;

            while (wordNode)
            {
                words[wordIndex++] = strdup(wordNode->word);
                WordNode *temp = wordNode;
                wordNode = wordNode->next;
                free(temp->word);
                free(temp);
            }

            // Stocke le groupe dans le résultat
            result[groupIndex] = words;
            (*returnColumnSizes)[groupIndex] = group->size;

            // Passe au groupe suivant
            AnagramGroup *temp = group;
            group = group->next;
            free(temp->signature);
            free(temp);

            groupIndex++;
        }
    }

    free(table);
    return result;
}


// --------------------------------------- Main End -------------------------------------------- >
int main()
{
    char *strs[] = {"eat", "tea", "tan", "ate", "nat", "bat"};
    int strsSize = sizeof(strs) / sizeof(strs[0]);
    int returnSize;
    int *returnColumnSizes;

    char ***result = groupAnagrams(strs, strsSize, &returnSize, &returnColumnSizes);

    // Affichage des résultats
    printf("Nombre de groupes : %d\n", returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        printf("Groupe %d : ", i + 1);
        for (int j = 0; j < returnColumnSizes[i]; j++)
        {
            printf("%s ", result[i][j]);
        }
        printf("\n");
    }

    // Libération de la mémoire
    for (int i = 0; i < returnSize; i++)
    {
        for (int j = 0; j < returnColumnSizes[i]; j++)
        {
            free(result[i][j]);
        }
        free(result[i]);
    }
    free(result);
    free(returnColumnSizes);

    return 0;
}