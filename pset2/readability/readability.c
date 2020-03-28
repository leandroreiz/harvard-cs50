#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//declaring functions
int count_letters(string s);
int count_words(string s);
int count_sentences(string s);
float coleman_index(string s);

//main application
int main(void)
{
    //getting information with the user
    string text = get_string("Text: ");

    //call function to calculate the grade
    int grade = round(coleman_index(text));

    //printing the results
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

//count letters
int count_letters(string s)
{
    int count = 0;

    for (int i = 0; i < strlen(s); i++)
    {
        if (isalpha(s[i]))
        {
            count++;
        }
    }

    return count;
}

//count words
int count_words(string s)
{
    int count = 0;

    for (int i = 0; i < strlen(s); i++)
    {
        //if the char is different from a space, count it as a word
        if (!isspace(s[i]))
        {
            count++;
            //after finding a word, start counting again after finding something different from a character or punctuation
            while (isalpha(s[i]) || ispunct(s[i]))
            {
                i++;
            }
        }
        //if it's a space, increment the controller variable
        else
        {
            i++;
        }
    }

    return count;
}

//count sentences
int count_sentences(string s)
{
    int count = 0;

    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            count++;
        }
    }

    return count;
}

//Coleman-Liua's index
float coleman_index(string s)
{
    //calculate using Coleman-Liau's index
    float average_letters = (float) count_letters(s) / (float) count_words(s) * 100;
    float average_sentences = (float) count_sentences(s) / (float) count_words(s) * 100;

    return 0.0588 * average_letters - 0.296 * average_sentences - 15.8;
}