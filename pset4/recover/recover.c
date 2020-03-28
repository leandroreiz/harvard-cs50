#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Used to work with files
#include <stdint.h> // Used to work with the type 'uint8_t' to define 'BYTE'

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Validate command's line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open file for reading
    FILE *file = fopen(argv[1], "r");

    // Validate if file exists
    if (file == NULL)
    {
        printf("File not found!\n");
        return 1;
    }

    // Allocate space in memory to read the file (each block is 512 bytes)
    unsigned char *buffer = malloc(sizeof(BYTE) * 512);

    // Read data from file and store inside the buffer array
    fread(buffer, sizeof(BYTE), 512, file);

    // Declaring variables
    int jpegFound = 0;
    int fileNumber = 0;
    FILE *img;

    // Read until the end of file (EOF)
    while (fread(buffer, sizeof(BYTE), 512, file) != 0)
    {
        // Check if the first BYTES are the JPEG pattern
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Check if the first jpeg was found
            if (!(jpegFound == 1))
            {
                // Change the boolean variable to true
                jpegFound = 1;

                // Create the name for the file and put into a string
                char filename[10];
                sprintf(filename, "%03i.jpg", fileNumber++);

                // Create a new JPEG file
                img = fopen(filename, "w");

                // Write the information into the newly created JPEG file
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
            else
            {
                // Close the previous file
                fclose(img);

                // Start writing to a new file
                char filename[10];
                sprintf(filename, "%03i.jpg", fileNumber++);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
        }
        else
        {
            // If a new jpeg wasn't found, continue writing to the opened file
            if (jpegFound)
            {
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
        }
    }

    // Close both, the card and image files
    fclose(file);
    fclose(img);

    // Free the allocated memory
    free(buffer);
}
