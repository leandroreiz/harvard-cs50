#include <stdio.h>

// opens a file and returns a file pointer to it
FILE* ptr = fopen(<filename>,<operation>);
// possible operations:
// r = read (just read a file content)
// w = write (overwrite the file if there something in it)
// a = append (insert at the end)

// closes the file pointed to by the given file pointer
fclose(<file pointer>);

// reads and returns the next character from the file pointed to
// IMPORTANT: the file pointer need to be open to reading
char ch = fgetc(<file pointer>);

// reads all charcters from a file and print them to the screen
char ch;
while ((ch = fgetc(ptr)) != EOF) // End Of File
    printf("%c", ch);

// inserts a character to the file
// the file must be open for writing or appending
fputc(<character>, <file pointer>);

// copying a file content
char ch;
while((ch = fgetc(ptr)) != EOF)
    fputc(ch, prt1);

// reads <qty> unit of size <size> from the file pointed to and stores them in memory in a buffer (usually an array) pointed to by <buffer>. Must be open for reading.
fread(<buffer>, <size>, <qty>, <file pointer>);
// 1. a pointer to the location where we're going to store that information
// 2. how large each unit of information will be
// 3. how many units of information we want to acquire
// 4. from which file we want to get them

int arr[10];
fread(arr, sizeof(int), 10, ptr); // reading 40 bytes of information and storing them in the variable array 'arr'

double *arr2 = malloc(sizeof(double) * 80);
fread(arr2, sizeof(double), 80, ptr);

char c;
fread(&c, sizeof(char), 1, ptr); // we need to pass the address as the first argument is a pointer

// exactly the same as 'fread' but for writing instead of reading
fwrite(<buffer>, <size>, <qty>, <file pointer>);

fwrite(arr, sizeof(int), 10, ptr); // from the buffer to the file


fgets(); // reads a full string from a file
fputs(); // writes a full string to a file
fprintf(); // writes a formatted string to a file
fseek(); // allows you rewind or fast-forward whitin a file
ftell(); // tells you at what (byte) position you are at whitin a file
feof(); // tells you whether you've read to the end of file
ferror(); // indicates whether an error has occurred in working with a file