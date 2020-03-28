#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int m; // creates a variable 'm' in the stack
    int *a; // creates a variable 'a' (pointers to integers) also in the stack
    int *b = malloc(sizeof(int)); // creates a container 'b' in the stack that points to a allocated space in the memory at the heap.
    a = &m; // 'a' gets 'm' address or we could say 'a' points to 'm'
    a = b; // 'a' now points to the same place that 'b' points
    m = 10; // simply assign the value 10 to the 'm' variable
    *b = m + 2; // 12 // dereference 'b' and put some value in that memory location

    free(b); // we don't need this memory anymore, so we need to free it

    //*a = 11; // this will cause a 'segmentation fault', crashing your application because we're trying to access memory that was already freed (remember that a = b)
}
