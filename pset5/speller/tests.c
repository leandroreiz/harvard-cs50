#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdbool.h>

#define LENGTH 45

// Structures
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 5;

// Variables
int number_of_words = 0;
char buffer[LENGTH + 1];
node *table[N];
const char *dictionary_str = "./dictionaries/foo";

// Function prototypes
bool load();
unsigned int size();
unsigned int hash(const char *word);
bool check(const char *word);
void print();
void convert_to_lower(char *word);
bool unload(void);

// Main application
int main(int argc, char **argv)
{
    load(dictionary_str);
    print();
    printf("Number of words in the dictionary: %i\n", size());
    check("foo");
    unload();

    // Success
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
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

// Returns number of words in dictionary
unsigned int size()
{
    if (number_of_words > 0)
    {
        return number_of_words;
    }

    return 0;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char w[LENGTH + 1];
    strcpy(w, word);
    convert_to_lower(w);

    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int word_len = strlen(w);

    // do several rounds of multiplication
    for (; i < word_len; i++)
    {
        value = value * 37 + w[i];
    }

    // make sure value is 0 <= value < N
    value =  value % N;

    return value;
}

// Returns true if word is in dictionary, if it isn't return false
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

// Print the hash table
void print()
{
    for (int i = 0; i < N; i++)
    {
        // if data is NULL print the slot's number and an empty slot
        if (table[i] == NULL)
        {
            printf("\t%i\t---\n", i);
        }
        // if data were found print the slot's number and the data itself
        else
        {
            printf("\t%i\t ", i);
            node *n = table[i];
            while (n != NULL)
            {
                printf("%s - ", n->word);
                n = n->next;
            }
            printf("\n");
        }
    }
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
