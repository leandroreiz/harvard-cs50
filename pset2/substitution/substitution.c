#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

bool validate_arg(string s);
void ciphertext(string text, string key);

//main function
int main(int argc, string argv[])
{
    //run if the user entered only ONE argument
    if (argc == 2)
    {
        if (validate_arg(argv[1]))
        {
            //getting the string with the user
            string plaintext = get_string("plaintext:  ");

            //calling the function to cipher and print the results
            printf("ciphertext: ");
            ciphertext(plaintext, argv[1]);
            printf("\n");

            //finishing the program
            return 0;
        }
        else
        {
            printf("Key must contain 26 unique alphabetic characters.\n");
            return 1;
        }
    }
    else
    {
        //do not run the program
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

//validating the key
bool validate_arg(string s)
{
    //is 26?
    if (strlen(s) == 26)
    {
        //loop through the key
        for (int i = 0; i < strlen(s); i++)
        {
            //is an alphabetic character?
            if (isalpha(s[i]))
            {
                //is unique?
                for (int j = i + 1; j < strlen(s); j++)
                {
                    if (s[i] == s[j])
                    {
                        return false;
                    }
                }
            }
            else
            {
                return false;
            }
        }

        //it passed all the tests
        return true;
    }
    else
    {
        return false;
    }
}

//encrypiting the text
void ciphertext(string text, string key)
{
    //default american alphabet
    const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //looping through the plaintext
    for (int i = 0; i < strlen(text); i++)
    {
        //is alphabetic?
        if (isalpha(text[i]))
        {
            //is uppercase?
            if (isupper(text[i]))
            {
                //looping through the alphabet (upper)
                for (int j = 0; j < strlen(alphabet); j++)
                {
                    if (text[i] == alphabet[j])
                    {
                        printf("%c", toupper(key[j]));
                    }
                }
            }
            //then it's lowercase
            else
            {
                //looping through the alphabet (lower)
                for (int j = 0; j < strlen(alphabet); j++)
                {
                    if (text[i] == tolower(alphabet[j]))
                    {
                        printf("%c", tolower(key[j]));
                    }
                }
            }
        }
        else
        {
            //if it's not alphabetic, then just print it
            printf("%c", text[i]);
        }
    }
}