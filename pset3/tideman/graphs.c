
// Adjacency Matrix
#include <stdio.h>
#include <cs50.h>

#define matrix_size 5

int graph[matrix_size][matrix_size] =
{
    { 0,0,1,0,0 },
    { 0,0,1,0,0 },
    { 1,1,0,1,1 },
    { 0,0,1,0,1 },
    { 0,0,1,1,0 }
};

bool isLinked(int v1, int v2);

int main(void)
{
    printf("%s\n", (isLinked(0, 2)) ? "There is a link!" : "Nope! There isn't a link.");
}

bool isLinked(int v1, int v2)
{
    if(graph[v1][v2])
        return true;
    return false;
}