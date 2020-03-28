#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // initialize the variable
    int height = 0;

    // ask for the height until the number entered is between 1-8
    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0 || height > 8);

    // repeats the code for each line
    for (int i = 1; i <= height; i++)
    {
        // declaring variables
        int whiteSpaces = height - i; // number of empty spaces
        int numberOfHashes = height - whiteSpaces; // number of hashes per line

        // print the empty spaces needed for the first column
        for (int j = 0; j < whiteSpaces; j++)
        {
            printf(" ");
        }

        // print the hashes for the right side
        for (int k = 0; k < numberOfHashes; k++)
        {
            printf("#");
        }

        // gap between the pyramids
        printf("  ");

        // print the hashes for the left side, no spaces needed
        for (int l = 0; l < numberOfHashes; l++)
        {
            printf("#");
        }

        // skip the line
        printf("\n");
    }
}
