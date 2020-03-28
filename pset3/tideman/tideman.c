#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];
int adj_matrix[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

// Counters
int pair_count;
int candidate_count;

// Personal Variables & Function Prototypes
bool visited[MAX];
bool hasCycle(int winner, int loser);
void print_tests(void);

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    // Starting the visited variable as unvisited (0)
    for (int i = 0; i < candidate_count; i++)
    {
        visited[i] = 0;
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    //print_tests(); // Print the Preferences Matrix, Pairs and Locked Pairs
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser  = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser  = i;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Temporary pairs container
    pair tmpPair[pair_count];

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser]
                < preferences[pairs[i].winner][pairs[i].loser])
            {
                tmpPair[i] = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = tmpPair[i];
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!hasCycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{

    // Variable to control the number of edges pointing to a candidate
    int edges[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        edges[i] = 0;
    }

    // Check the columns for edges and, if it exists, add to the edges array
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if(locked[j][i])
            {
                edges[i]++;
            }
        }
    }

    // Loop through the edges array and print the candidate with no edges, or the source of the graph
    for (int i = 0; i < candidate_count; i++)
    {
        if (edges[i] == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
}

// Check if there is a cycle in the graph
bool hasCycle(int winner, int loser)
{
    // Check for a antiparallel edges, what it's also a cycle
    if (locked[loser][winner])
    {
        return true;
    }

    // Mark the winner vertex as visited
    visited[winner] = 1;

    // Check if the loser has any connection of any other candidate and, if it's the case,
    // repeat (recursively) trying to find a pathway to the winner.
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] && visited[i] == 1)
        {
            hasCycle(i, winner);
            return true;
        }
    }

    return false;
}

// Printing the data necessary to test the program
void print_tests(void)
{
    // testing preferences function /////////////////////////
    printf("\n-----------------------------------------------\n");
    printf("--- PREFERENCES / ADJACENCY MATRIX ---\n");
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // testing pairs function ///////////////////////////////
    printf("--- PAIRS / NODES ---\n");
    for (int i = 0; i < pair_count; i++)
    {
        printf("%i - %i\n", pairs[i].winner, pairs[i].loser);
    }
    printf("\n");

    // testing lock_pairs function //////////////////////////
    printf("--- LOCK PAIRS / EDGE'S ---\n");
    for (int w = 0; w < candidate_count; w++)
    {
        for (int l = 0; l < candidate_count; l++)
        {
            printf("%s  ", locked[w][l] ? "true" : "false");
        }
        printf("\n");
    }
    printf("\n-----------------------------------------------\n");
    // end-test /////////////////////////////////////////////
}