#include <stdio.h>

void swap(int *a, int *b);

int main(void)
{
    char s[10];

    printf("What's your name? ");
    scanf("%s", s);
    printf("Hello %s!\n", s);

    int a = 1, b = 2;
    printf("%i, %i\n", a, b);
    swap(&a, &b);
    printf("%i, %i\n", a, b);
}

void swap(int *a, int *b)
{
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}