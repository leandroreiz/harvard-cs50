// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 65000;

// Hash table
node *table[N];

// Variable to keep track of the number of words in the dictionary
int number_of_words = 0;

// Function prototype
void convert_to_lower(char *word);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // hash word to obtain a hash value
    int hash_value = hash(word);

    // access linked list at that index in the hash table
    node *n = table[hash_value];

    // traverse linked list, looking for the word (strcasecmp)
    while (n != NULL)
    {
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }

        n = n->next;
    }

    return false;
}

// Hashes word to a number
// The Hash Function bellow was obtained in this video on YouTube: https://www.youtube.com/watch?v=wg8hZxMRwcw
unsigned int hash(const char *word)
{

    char hash_word[LENGTH + 1];
    strcpy(hash_word, word);
    convert_to_lower(hash_word);

    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int word_len = strlen(hash_word);

    // do several rounds of multiplication
    for (; i < word_len; i++)
    {
        value = value * 37 + hash_word[i];
    }

    // make sure value is 0 <= value < N
    value =  value % N;

    return value;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // declare a variable to keep the words loaded
    char buffer[LENGTH + 1];

    // open dictionary file
    FILE *file_ptr;
    file_ptr = fopen(dictionary, "r");

    // check if the file exists
    if (file_ptr == NULL)
    {
        printf("Error opening file\n");
        return false;
    }

    // read through the file from the beginning to the end
    while (fscanf(file_ptr, "%s", buffer) != EOF)
    {
        // count the number of words in a global variable
        number_of_words++;

        // create a new node for each word
        node *n = malloc(sizeof(node));

        // check if there is enough space in memory
        if (n == NULL)
        {
            return false;
        }

        // copy the string into the node
        strcpy(n->word, buffer);

        // hash word to obtain a hash value
        int hash_value = hash(n->word);

        // insert node into hash table at that location
        n->next = table[hash_value];
        table[hash_value] = n;
    }

    fclose(file_ptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (number_of_words > 0)
    {
        return number_of_words;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        // access linked list at the first item
        node *n = table[i];

        // create another variable to keep track of the freed memory
        node *tmp;

        // traverse linked list freeing the memory allocated in the nodes
        while (n != NULL)
        {
            tmp = n;
            n = n->next;
            free(tmp);
        }
    }

    return true;
}

void convert_to_lower(char *word)
{
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] >= 'A' && word[i] <= 'Z')
        {
            word[i] = word[i] + 32;
        }
    }
}
