#include "helpers.h"
#include <math.h>
#include <string.h>

// Function prototypes
void detectEdges(int height, int width, RGBTRIPLE dummy[height][width], RGBTRIPLE image[height][width]);
float gx(int height, int width, int i, int j, char channel[], RGBTRIPLE image[height][width]);
float gy(int height, int width, int i, int j, char channel[], RGBTRIPLE image[height][width]);
void copyArr(int height, int width, RGBTRIPLE origin[height][width], RGBTRIPLE destination[height][width]);
int whichPosition(int height, int width, int i, int j);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate the average pixel value and round the result
            BYTE averageValue = round(((float) image[i][j].rgbtRed + (float) image[i][j].rgbtGreen + (float) image[i][j].rgbtBlue) / 3);

            // set each color values to the image 2D array
            image[i][j].rgbtRed = averageValue;
            image[i][j].rgbtGreen = averageValue;
            image[i][j].rgbtBlue = averageValue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // temporary variable
    RGBTRIPLE tmp;

    for (int i = 0; i < height; i++)
    {
        // invert only half of the screen width and, consequently, the other half will be inverted
        for (int j = 0; j < width / 2; j++)
        {
            tmp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE dummy[height][width];

    // calculates all the values for all possible pixel's positions
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            switch (whichPosition(height - 1, width - 1, i, j))
            {
                case 1:
                    dummy[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                                        image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4);
                    dummy[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                                          image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 4);
                    dummy[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                                         image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 4);
                    break;

                case 2:
                    dummy[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed +
                                                        image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6);

                    dummy[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                                                          image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6);

                    dummy[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                                                         image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6);
                    break;

                case 3:
                    dummy[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed +
                                                        image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 4);
                    dummy[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                                                          image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 4);
                    dummy[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                                                         image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 4);
                    break;

                case 4:
                    dummy[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed +
                                                        image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6);

                    dummy[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                                                          image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6);

                    dummy[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue +
                                                         image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6);
                    break;

                case 5:
                    dummy[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed +
                                                        image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6);

                    dummy[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                                                          image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6);

                    dummy[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue +
                                                         image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6);
                    break;

                case 6:
                    dummy[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i - 1][j].rgbtRed +
                                                        image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed) / 4);
                    dummy[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen +
                                                          image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 4);
                    dummy[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue +
                                                         image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 4);
                    break;

                case 7:
                    dummy[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed +
                                                        image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6);

                    dummy[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                                                          image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6);

                    dummy[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                                                         image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6);
                    break;

                case 8:
                    dummy[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i - 1][j].rgbtRed +
                                                        image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed) / 4);
                    dummy[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen +
                                                          image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen) / 4);
                    dummy[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue +
                                                         image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue) / 4);
                    break;

                case 9: // 178 193 201
                    dummy[i][j].rgbtRed = round((float)(image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                                        image[i - 1][j].rgbtRed + image[i][j].rgbtRed + image[i + 1][j].rgbtRed +
                                                        image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9);

                    dummy[i][j].rgbtGreen = round((float)(image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                                          image[i - 1][j].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                                                          image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9);

                    dummy[i][j].rgbtBlue = round((float)(image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                                         image[i - 1][j].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue +
                                                         image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9);
                    break;
            }
        }
    }

    // copy the 2D array
    copyArr(height, width, dummy, image);

}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a dummy array to receive the data for processing
    RGBTRIPLE dummy[height][width];

    // Call the function to detect the edges
    detectEdges(height, width, dummy, image);

    // Copy the dummy content into the image array (RGBTRIPLE)
    copyArr(height, width, dummy, image);
}

// Calculate and round the values for for all three color channels
void detectEdges(int height, int width, RGBTRIPLE dummy[height][width], RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            dummy[i][j].rgbtRed = fmin(255, round((float)sqrt(pow(gx(height, width, i, j, "rgbtRed", image), 2) +
                                                  pow(gy(height, width, i, j, "rgbtRed", image), 2))));
            dummy[i][j].rgbtGreen = fmin(255, round((float)sqrt(pow(gx(height, width, i, j, "rgbtGreen", image), 2) +
                                                    pow(gy(height, width, i, j, "rgbtGreen", image), 2))));
            dummy[i][j].rgbtBlue = fmin(255, round((float)sqrt(pow(gx(height, width, i, j, "rgbtBlue", image), 2) +
                                                   pow(gy(height, width, i, j, "rgbtBlue", image), 2))));
        }
    }
}

// execute the Gx Kernel
float gx(int height, int width, int i, int j, char channel[], RGBTRIPLE image[height][width])
{

    switch (whichPosition(height - 1, width - 1, i, j))
    {
        case 1:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i][j].rgbtRed * 0) + (image[i][j + 1].rgbtRed * 2) +
                       (image[i + 1][j].rgbtRed * 0) + (image[i + 1][j + 1].rgbtRed * 1);
            }
            else if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i][j].rgbtGreen * 0) + (image[i][j + 1].rgbtGreen * 2) +
                       (image[i + 1][j].rgbtGreen * 0) + (image[i + 1][j + 1].rgbtGreen * 1);
            }
            else if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i][j].rgbtBlue * 0) + (image[i][j + 1].rgbtBlue * 2) +
                       (image[i + 1][j].rgbtBlue * 0) + (image[i + 1][j + 1].rgbtBlue * 1);
            }
            break;

        case 2:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i][j - 1].rgbtRed * -2) + (image[i][j].rgbtRed * 0) + (image[i][j + 1].rgbtRed * 2) +
                       (image[i + 1][j - 1].rgbtRed * -1) + (image[i + 1][j].rgbtRed * 0) + (image[i + 1][j + 1].rgbtRed * 1);
            }
            else if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i][j - 1].rgbtGreen * -2) + (image[i][j].rgbtGreen * 0) + (image[i][j + 1].rgbtGreen * 2) +
                       (image[i + 1][j - 1].rgbtGreen * -1) + (image[i + 1][j].rgbtGreen * 0) + (image[i + 1][j + 1].rgbtGreen * 1);
            }
            else if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i][j - 1].rgbtBlue * -2) + (image[i][j].rgbtBlue * 0) + (image[i][j + 1].rgbtBlue * 2) +
                       (image[i + 1][j - 1].rgbtBlue * -1) + (image[i + 1][j].rgbtBlue * 0) + (image[i + 1][j + 1].rgbtBlue * 1);
            }
            break;

        case 3:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i][j - 1].rgbtRed * -2) + (image[i][j].rgbtRed * 0) +
                       (image[i + 1][j - 1].rgbtRed * -1) + (image[i + 1][j].rgbtRed * 0);
            }
            else if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i][j - 1].rgbtGreen * -2) + (image[i][j].rgbtGreen * 0) +
                       (image[i + 1][j - 1].rgbtGreen * -1) + (image[i + 1][j].rgbtGreen * 0);
            }
            else if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i][j - 1].rgbtBlue * -2) + (image[i][j].rgbtBlue * 0) +
                       (image[i + 1][j - 1].rgbtBlue * -1) + (image[i + 1][j].rgbtBlue * 0);
            }
            break;

        case 4:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i - 1][j].rgbtRed * 0) + (image[i - 1][j + 1].rgbtRed * 1) + (image[i][j].rgbtRed * 0) +
                       (image[i][j + 1].rgbtRed * 2) + (image[i + 1][j].rgbtRed * 0) + (image[i + 1][j + 1].rgbtRed * 1);
            }
            else if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i - 1][j].rgbtGreen * 0) + (image[i - 1][j + 1].rgbtGreen * 1) + (image[i][j].rgbtGreen * 0) +
                       (image[i][j + 1].rgbtGreen * 2) + (image[i + 1][j].rgbtGreen * 0) + (image[i + 1][j + 1].rgbtGreen * 1);
            }
            else if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i - 1][j].rgbtBlue * 0) + (image[i - 1][j + 1].rgbtBlue * 1) + (image[i][j].rgbtBlue * 0) +
                       (image[i][j + 1].rgbtBlue * 2) + (image[i + 1][j].rgbtBlue * 0) + (image[i + 1][j + 1].rgbtBlue * 1);
            }
            break;

        case 9:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * 0) + (image[i - 1][j + 1].rgbtRed * 1) +
                       (image[i][j - 1].rgbtRed * -2) + (image[i][j].rgbtRed * 0) + (image[i][j + 1].rgbtRed * 2) +
                       (image[i + 1][j - 1].rgbtRed * -1) + (image[i + 1][j].rgbtRed * 0) + (image[i + 1][j + 1].rgbtRed * 1);
            }
            else if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * 0) + (image[i - 1][j + 1].rgbtGreen * 1) +
                       (image[i][j - 1].rgbtGreen * -2) + (image[i][j].rgbtGreen * 0) + (image[i][j + 1].rgbtGreen * 2) +
                       (image[i + 1][j - 1].rgbtGreen * -1) + (image[i + 1][j].rgbtGreen * 0) + (image[i + 1][j + 1].rgbtGreen * 1);
            }
            else if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * 0) + (image[i - 1][j + 1].rgbtBlue * 1) +
                       (image[i][j - 1].rgbtBlue * -2) + (image[i][j].rgbtBlue * 0) + (image[i][j + 1].rgbtBlue * 2) +
                       (image[i + 1][j - 1].rgbtBlue * -1) + (image[i + 1][j].rgbtBlue * 0) + (image[i + 1][j + 1].rgbtBlue * 1);
            }
            break;

        case 5:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * 0) +
                       (image[i][j - 1].rgbtRed * -2) + (image[i][j].rgbtRed * 0) +
                       (image[i + 1][j - 1].rgbtRed * -1) + (image[i + 1][j].rgbtRed * 0);
            }
            else if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * 0) +
                       (image[i][j - 1].rgbtGreen * -2) + (image[i][j].rgbtGreen * 0) +
                       (image[i + 1][j - 1].rgbtGreen * -1) + (image[i + 1][j].rgbtGreen * 0);
            }
            else if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * 0) +
                       (image[i][j - 1].rgbtBlue * -2) + (image[i][j].rgbtBlue * 0) +
                       (image[i + 1][j - 1].rgbtBlue * -1) + (image[i + 1][j].rgbtBlue * 0);
            }
            break;

        case 6:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i - 1][j].rgbtRed * 0) + (image[i - 1][j + 1].rgbtRed * 1) +
                       (image[i][j].rgbtRed * 0) + (image[i][j + 1].rgbtRed * 2);
            }
            else if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i - 1][j].rgbtGreen * 0) + (image[i - 1][j + 1].rgbtGreen * 1) +
                       (image[i][j].rgbtGreen * 0) + (image[i][j + 1].rgbtGreen * 2);
            }
            else if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i - 1][j].rgbtBlue * 0) + (image[i - 1][j + 1].rgbtBlue * 1) +
                       (image[i][j].rgbtBlue * 0) + (image[i][j + 1].rgbtBlue * 2);
            }
            break;

        case 7:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * 0) + (image[i - 1][j + 1].rgbtRed * 1) +
                       (image[i][j - 1].rgbtRed * -2) + (image[i][j].rgbtRed * 0) + (image[i][j + 1].rgbtRed * 2);
            }
            else if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * 0) + (image[i - 1][j + 1].rgbtGreen * 1) +
                       (image[i][j - 1].rgbtGreen * -2) + (image[i][j].rgbtGreen * 0) + (image[i][j + 1].rgbtGreen * 2);
            }
            else if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * 0) + (image[i - 1][j + 1].rgbtBlue * 1) +
                       (image[i][j - 1].rgbtBlue * -2) + (image[i][j].rgbtBlue * 0) + (image[i][j + 1].rgbtBlue * 2);
            }
            break;

        case 8:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * 0) +
                       (image[i][j - 1].rgbtRed * -2) + (image[i][j].rgbtRed * 0);
            }
            else if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * 0) +
                       (image[i][j - 1].rgbtGreen * -2) + (image[i][j].rgbtGreen * 0);
            }
            else if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * 0) +
                       (image[i][j - 1].rgbtBlue * -2) + (image[i][j].rgbtBlue * 0);
            }
            break;
    }

    return 0;
}

// execute the Gy Kernel
float gy(int height, int width, int i, int j, char channel[], RGBTRIPLE image[height][width])
{
    switch (whichPosition(height - 1, width - 1, i, j))
    {
        case 1:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i][j].rgbtRed * 0) + (image[i][j + 1].rgbtRed * 0) +
                       (image[i + 1][j].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed * 1);
            }
            else if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i][j].rgbtGreen * 0) + (image[i][j + 1].rgbtGreen * 0) +
                       (image[i + 1][j].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen * 1);
            }
            else if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i][j].rgbtBlue * 0) + (image[i][j + 1].rgbtBlue * 0) +
                       (image[i + 1][j].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue * 1);
            }
            break;

        case 2:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i][j - 1].rgbtRed * 0) + (image[i][j].rgbtRed * 0) + (image[i][j + 1].rgbtRed * 0) +
                       (image[i + 1][j - 1].rgbtRed * 1) + (image[i + 1][j].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed * 1);
            }
            else if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i][j - 1].rgbtGreen * 0) + (image[i][j].rgbtGreen * 0) + (image[i][j + 1].rgbtGreen * 0) +
                       (image[i + 1][j - 1].rgbtGreen * 1) + (image[i + 1][j].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen * 1);
            }
            else if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i][j - 1].rgbtBlue * 0) + (image[i][j].rgbtBlue * 0) + (image[i][j + 1].rgbtBlue * 0) +
                       (image[i + 1][j - 1].rgbtBlue * 1) + (image[i + 1][j].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue * 1);
            }
            break;

        case 3:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i][j - 1].rgbtRed * 0) + (image[i][j].rgbtRed * 0) +
                       (image[i + 1][j - 1].rgbtRed * 1) + (image[i + 1][j].rgbtRed * 2);
            }
            else if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i][j - 1].rgbtGreen * 0) + (image[i][j].rgbtGreen * 0) +
                       (image[i + 1][j - 1].rgbtGreen * 1) + (image[i + 1][j].rgbtGreen * 2);
            }
            else if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i][j - 1].rgbtBlue * 0) + (image[i][j].rgbtBlue * 0) +
                       (image[i + 1][j - 1].rgbtBlue * 1) + (image[i + 1][j].rgbtBlue * 2);
            }
            break;

        case 4:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1) + (image[i][j].rgbtRed * 0) +
                       (image[i][j + 1].rgbtRed * 0) + (image[i + 1][j].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed * 1);
            }
            else if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1) + (image[i][j].rgbtGreen * 0) +
                       (image[i][j + 1].rgbtGreen * 0) + (image[i + 1][j].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen * 1);
            }
            else if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1) + (image[i][j].rgbtBlue * 0) +
                       (image[i][j + 1].rgbtBlue * 0) + (image[i + 1][j].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue * 1);
            }
            break;

        case 9:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1) +
                       (image[i][j - 1].rgbtRed * 0) + (image[i][j].rgbtRed * 0) + (image[i][j + 1].rgbtRed * 0) +
                       (image[i + 1][j - 1].rgbtRed * 1) + (image[i + 1][j].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed * 1);
            }
            else if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1) +
                       (image[i][j - 1].rgbtGreen * 0) + (image[i][j].rgbtGreen * 0) + (image[i][j + 1].rgbtGreen * 0) +
                       (image[i + 1][j - 1].rgbtGreen * 1) + (image[i + 1][j].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen * 1);
            }
            else if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1) +
                       (image[i][j - 1].rgbtBlue * 0) + (image[i][j].rgbtBlue * 0) + (image[i][j + 1].rgbtBlue * 0) +
                       (image[i + 1][j - 1].rgbtBlue * 1) + (image[i + 1][j].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue * 1);
            }
            break;

        case 5:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * -2) + (image[i][j - 1].rgbtRed * 0) +
                       (image[i][j].rgbtRed * 0) + (image[i + 1][j - 1].rgbtRed * 1) + (image[i + 1][j].rgbtRed * 2);
            }
            else if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * -2) + (image[i][j - 1].rgbtGreen * 0) +
                       (image[i][j].rgbtGreen * 0) + (image[i + 1][j - 1].rgbtGreen * 1) + (image[i + 1][j].rgbtGreen * 2);
            }
            else if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * -2) + (image[i][j - 1].rgbtBlue * 0) +
                       (image[i][j].rgbtBlue * 0) + (image[i + 1][j - 1].rgbtBlue * 1) + (image[i + 1][j].rgbtBlue * 2);
            }
            break;

        case 6:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1) +
                       (image[i][j].rgbtRed * 0) + (image[i][j + 1].rgbtRed * 0);
            }
            else if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1) +
                       (image[i][j].rgbtGreen * 0) + (image[i][j + 1].rgbtGreen * 0);
            }
            else if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1) +
                       (image[i][j].rgbtBlue * 0) + (image[i][j + 1].rgbtBlue * 0);
            }
            break;

        case 7:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1) +
                       (image[i][j - 1].rgbtRed * 0) + (image[i][j].rgbtRed * 0) + (image[i][j + 1].rgbtRed * 0);
            }
            else if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1) +
                       (image[i][j - 1].rgbtGreen * 0) + (image[i][j].rgbtGreen * 0) + (image[i][j + 1].rgbtGreen * 0);
            }
            else if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1) +
                       (image[i][j - 1].rgbtBlue * 0) + (image[i][j].rgbtBlue * 0) + (image[i][j + 1].rgbtBlue * 0);
            }
            break;

        case 8:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * -2) +
                       (image[i][j - 1].rgbtRed * 0) + (image[i][j].rgbtRed * 0);
            }
            else if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * -2) +
                       (image[i][j - 1].rgbtGreen * 0) + (image[i][j].rgbtGreen * 0);
            }
            else if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * -2) +
                       (image[i][j - 1].rgbtBlue * 0) + (image[i][j].rgbtBlue * 0);
            }
            break;
    }

    return 0;
}

// Copy one RGBTRIPLE into another
void copyArr(int height, int width, RGBTRIPLE origin[height][width], RGBTRIPLE destination[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            destination[i][j] = origin[i][j];
        }
    }
}

// Find in which position the indexes 'i' and 'j' so we can calculate the values according to it
int whichPosition(int height, int width, int i, int j)
{
    if (i == 0 && j == 0)
    {
        return 1;
    }
    else if (i == 0 && j > 0 && j < width)
    {
        return 2;
    }
    else if (i == 0 && j == width)
    {
        return 3;
    }
    else if (i > 0 && i < height && j == 0)
    {
        return 4;
    }
    else if (i > 0 && i < height && j == width)
    {
        return 5;
    }
    else if (i == height && j == 0)
    {
        return 6;
    }
    else if (i == height && j > 0 && j < width)
    {
        return 7;
    }
    else if (i == height && j == width)
    {
        return 8;
    }
    else
    {
        return 9;
    }
}
