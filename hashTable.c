#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Helper function for memory allocation with error checking
void *emalloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    return ptr;
}

char *strsave(const char *str)
{
    return strcpy(emalloc(strlen(str) + 1), str);
}

// ------- defines -----
#define HASHSIZE 101  // Better to use a prime number for hash table size

// ----- hash table struct ---
typedef struct nlist
{
    char *name;
    struct nlist *next;
} nlist;

// ---- global table ---------
static nlist *hashtab[HASHSIZE];

// ---- hash function --------
unsigned int hash(char *s)
{
    unsigned int hashval;

    for (hashval = 0; *s != '\0';)
        hashval = hashval * 31 + *s++;  // Better hash function
    return hashval % HASHSIZE;  // Use modulo for correct hash value
}

// ------ lookup ------------
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    {
        if (strcmp(s, np->name) == 0)
        {
            return np; // found
        }
    }

    return NULL;
}

// ----- main add function -----
struct nlist *install(char *name)
{
    struct nlist *np;
    unsigned int hashval;

    if ((np = lookup(name)) == NULL)
    {
        np = (struct nlist *)emalloc(sizeof(*np));
        if (np == NULL)
        {
            return NULL;
        }

        if ((np->name = strsave(name)) == NULL)
        {
            free(np);  // Prevent memory leak
            return NULL;
        }

        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    
    return np;  // Always return the node
}