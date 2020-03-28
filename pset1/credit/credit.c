#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // input the credit card number
    long fullCardNumber = get_long("Number: ");
    long cardNumber = fullCardNumber;

    // declaring variables outside the loop
    int numberOfDigits = 0;
    int sumCheck = 0;

    // separating all numbers
    while (cardNumber > 0)
    {
        numberOfDigits++;
        int lastDigit = cardNumber % 10;
        cardNumber = (cardNumber - lastDigit) / 10;

        int product = 0;
        int unitDigit = 0;
        int decimalDigit = 0;

        // multiply every other digit by 2, starting with second-to-last digit
        if (numberOfDigits % 2 == 0)
        {
            product = lastDigit * 2;

            if (product >= 10)
            {
                unitDigit = product % 10;
                decimalDigit = (product - unitDigit) / 10;
                sumCheck += decimalDigit + unitDigit;
            }
            else
            {
                // add those products' digits together
                sumCheck += product;
            }
        }
        else
        {
            // add the sum to the sum of the digits that weren't multiplied by 2
            sumCheck += lastDigit;
        }
    }
    // initialising variable to keep the first digits
    int firstDigits = 0;

    // if the totals last digit is 0, number is valid!
    if (sumCheck % 10 == 0)
    {
        // American Express - 15 digits, starts with 34 or 37
        if (numberOfDigits == 15)
        {
            // checking first digits
            firstDigits = fullCardNumber / 10000000000000;
            if (firstDigits == 34 || firstDigits == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (numberOfDigits == 16)
        {
            //MasterCard - 16 digits, starts with 51, 52, 53, 54, 55
            firstDigits = fullCardNumber / 100000000000000;
            if (firstDigits == 51 ||
                firstDigits == 52 ||
                firstDigits == 53 ||
                firstDigits == 54 ||
                firstDigits == 55)
            {
                printf("MASTERCARD\n");
            }
            else if (firstDigits / 10 == 4)
            {
                //Visa - 16 digits, starts with 4
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (numberOfDigits == 13)
        {
            //Visa - 16 digits, starts with 4
            firstDigits = fullCardNumber / 100000000000;
            if (firstDigits == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
