// Implements a dictionary's functionality

#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // Primarily working with strings in this program.
#include <strings.h> // strcasecmp() to compare strings independant of case.
#include <stdio.h>
#include <ctype.h> // islower() function.


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next; // pointer to the next node.
}
node;

// Will hold total number of words once dictionary is loaded
int word_total = 0;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int key = hash(word);

    node *node_ptr = table[key];

    while (node_ptr != NULL)
    {
        if (strcasecmp(node_ptr -> word, word) == 0)
        {
            return true;
        }

        node_ptr = node_ptr -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int val = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        val += tolower(word[i]);
    }

    return val % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char temp_word[LENGTH + 1];

    while (fscanf(file, "%s\n", temp_word) != EOF)
    {
        node *temp_node = malloc(sizeof(node));

        strcpy(temp_node -> word, temp_word);

        int k = hash(temp_word);

        if (table[k] == NULL)
        {
            temp_node -> next = NULL;
            table[k] = temp_node;
        }
        else
        {
            temp_node -> next = table[k];
            table[k] = temp_node;
        }

        word_total++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_total;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *node_ptr = table[i];

        while (node_ptr != NULL)
        {
            node *del_node = node_ptr;
            node_ptr = node_ptr -> next;
            free(del_node);
        }

        table[i] = NULL;
    }
    return true;
}
