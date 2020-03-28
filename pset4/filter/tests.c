#include <stdio.h>
#include <math.h>
#include <string.h>

//structure
typedef struct {
    int rgbtRed;
    int rgbtGreen;
    int rgbtBlue;
}
RGBTRIPLE;

// declaring global variables
int height = 3;
int width = 3;

//declaring a new structure
RGBTRIPLE image[3][3];
RGBTRIPLE dummy[3][3];

// function prototypes
int whichPosition (int h, int w, int i, int j);
void copyArr (int h, int w, RGBTRIPLE origin[h][w], RGBTRIPLE destination[h][w]);

float gx(int i, int j, char channel[]);
float gy(int i, int j, char channel[]);
void calculateEdges();

// main application block
int main (void)
{
    // first row
    image[0][0].rgbtRed = 0;
    image[0][0].rgbtGreen = 10;
    image[0][0].rgbtBlue = 25;

    image[0][1].rgbtRed = 0;
    image[0][1].rgbtGreen = 10;
    image[0][1].rgbtBlue = 30;

    image[0][2].rgbtRed = 40;
    image[0][2].rgbtGreen = 60;
    image[0][2].rgbtBlue = 80;

    // second row
    image[1][0].rgbtRed = 20;
    image[1][0].rgbtGreen = 30;
    image[1][0].rgbtBlue = 90;

    image[1][1].rgbtRed = 30;
    image[1][1].rgbtGreen = 40;
    image[1][1].rgbtBlue = 100;

    image[1][2].rgbtRed = 80;
    image[1][2].rgbtGreen = 70;
    image[1][2].rgbtBlue = 90;

    // third row
    image[2][0].rgbtRed = 20;
    image[2][0].rgbtGreen = 20;
    image[2][0].rgbtBlue = 40;

    image[2][1].rgbtRed = 30;
    image[2][1].rgbtGreen = 10;
    image[2][1].rgbtBlue = 30;

    image[2][2].rgbtRed = 50;
    image[2][2].rgbtGreen = 40;
    image[2][2].rgbtBlue = 10;

    calculateEdges();

    copyArr(height, width, dummy, image);

    printf("case 1: %i %i %i -- Expected: 76 117 255\n", image[0][0].rgbtRed, image[0][0].rgbtGreen, image[0][0].rgbtBlue);
    printf("case 2: %i %i %i -- Expected: 213 228 255\n", image[0][1].rgbtRed, image[0][1].rgbtGreen, image[0][1].rgbtBlue);
    printf("case 3: %i %i %i -- Expected: 192 190 255\n", image[0][2].rgbtRed, image[0][2].rgbtGreen, image[0][2].rgbtBlue);
    printf("case 4: %i %i %i -- Expected: 114 102 255\n", image[1][0].rgbtRed, image[1][0].rgbtGreen, image[1][0].rgbtBlue);
    printf("case 9: %i %i %i -- Expected: 210 150 60\n", image[1][1].rgbtRed, image[1][1].rgbtGreen, image[1][1].rgbtBlue);
    printf("case 5: %i %i %i -- Expected: 103 108 255\n", image[1][2].rgbtRed, image[1][2].rgbtGreen, image[1][2].rgbtBlue);
    printf("case 6: %i %i %i -- Expected: 114 117 255\n", image[2][0].rgbtRed, image[2][0].rgbtGreen, image[2][0].rgbtBlue);
    printf("case 7: %i %i %i -- Expected: 200 197 255\n", image[2][1].rgbtRed, image[2][1].rgbtGreen, image[2][1].rgbtBlue);
    printf("case 8: %i %i %i -- Expected: 210 190 255\n", image[2][2].rgbtRed, image[2][2].rgbtGreen, image[2][2].rgbtBlue);

} //end of main-block

void calculateEdges()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            dummy[i][j].rgbtRed = fmin(255, round((float)sqrt(pow(gx(i,j,"rgbtRed"),2) + pow(gy(i,j,"rgbtRed"),2))));
            dummy[i][j].rgbtGreen = fmin(255, round((float)sqrt(pow(gx(i,j,"rgbtGreen"),2) + pow(gy(i,j,"rgbtGreen"),2))));
            dummy[i][j].rgbtBlue = fmin(255, round((float)sqrt(pow(gx(i,j,"rgbtBlue"),2) + pow(gy(i,j,"rgbtBlue"),2))));
        }
    }
}

float gx(int i, int j, char channel[])
{

    switch (whichPosition(height, width, i, j))
    {
        case 2:
        case 7:
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

        case 1:
            if (strcmp(channel, "rgbtRed") == 0)
                return (image[i][j].rgbtRed * 0) + (image[i][j + 1].rgbtRed * 2) + (image[i + 1][j].rgbtRed * 0) + (image[i + 1][j + 1].rgbtRed * 1);
            if (strcmp(channel, "rgbtGreen") == 0)
                return (image[i][j].rgbtGreen * 0) + (image[i][j + 1].rgbtGreen * 2) + (image[i + 1][j].rgbtGreen * 0) + (image[i + 1][j + 1].rgbtGreen * 1);
            if (strcmp(channel, "rgbtBlue") == 0)
                return (image[i][j].rgbtBlue * 0) + (image[i][j + 1].rgbtBlue * 2) + (image[i + 1][j].rgbtBlue * 0) + (image[i + 1][j + 1].rgbtBlue * 1);
            break;

        case 3:
            if (strcmp(channel, "rgbtRed") == 0)
                return (image[i][j - 1].rgbtRed * -2) + (image[i][j].rgbtRed * 0) + (image[i + 1][j - 1].rgbtRed * -1) + (image[i + 1][j].rgbtRed * 0);
            else if (strcmp(channel, "rgbtGreen") == 0)
                return (image[i][j - 1].rgbtGreen * -2) + (image[i][j].rgbtGreen * 0) + (image[i + 1][j - 1].rgbtGreen * -1) + (image[i + 1][j].rgbtGreen * 0);
            else if (strcmp(channel, "rgbtBlue") == 0)
                return (image[i][j - 1].rgbtBlue * -2) + (image[i][j].rgbtBlue * 0) + (image[i + 1][j - 1].rgbtBlue * -1) + (image[i + 1][j].rgbtBlue * 0);
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
                return (image[i - 1][j].rgbtRed * 0) + (image[i - 1][j + 1].rgbtRed * 1) + (image[i][j].rgbtRed * 0) + (image[i][j + 1].rgbtRed * 2);
            else if (strcmp(channel, "rgbtGreen") == 0)
                return (image[i - 1][j].rgbtGreen * 0) + (image[i - 1][j + 1].rgbtGreen * 1) + (image[i][j].rgbtGreen * 0) + (image[i][j + 1].rgbtGreen * 2);
            else if (strcmp(channel, "rgbtBlue") == 0)
                return (image[i - 1][j].rgbtBlue * 0) + (image[i - 1][j + 1].rgbtBlue * 1) + (image[i][j].rgbtBlue * 0) + (image[i][j + 1].rgbtBlue * 2);
            break;

        case 8:
            if (strcmp(channel, "rgbtRed") == 0)
                return (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * 0) + (image[i][j - 1].rgbtRed * -2) + (image[i][j].rgbtRed * 0);
            else if (strcmp(channel, "rgbtGreen") == 0)
                return (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * 0) + (image[i][j - 1].rgbtGreen * -2) + (image[i][j].rgbtGreen * 0);
            else if (strcmp(channel, "rgbtBlue") == 0)
                return (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * 0) + (image[i][j - 1].rgbtBlue * -2) + (image[i][j].rgbtBlue * 0);
            break;

        default:
            printf("Error calculating gx()!\n");
    }

    return 0;
}

float gy(int i, int j, char channel[])
{
    switch (whichPosition(height, width, i, j))
    {
        case 2:
        case 7:
        case 9:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1) +
                    (image[i][j - 1].rgbtRed * 0) + (image[i][j].rgbtRed * 0) + (image[i][j + 1].rgbtRed * 0) +
                    (image[i + 1][j - 1].rgbtRed * 1) + (image[i + 1][j].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed * 1);
            }
            if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1) +
                    (image[i][j - 1].rgbtGreen * 0) + (image[i][j].rgbtGreen * 0) + (image[i][j + 1].rgbtGreen * 0) +
                    (image[i + 1][j - 1].rgbtGreen * 1) + (image[i + 1][j].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen * 1);
            }
            if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1) +
                    (image[i][j - 1].rgbtBlue * 0) + (image[i][j].rgbtBlue * 0) + (image[i][j + 1].rgbtBlue * 0) +
                    (image[i + 1][j - 1].rgbtBlue * 1) + (image[i + 1][j].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue * 1);
            }
            break;

        case 1:
            if (strcmp(channel, "rgbtRed") == 0)
                return (image[i][j].rgbtRed * 0) + (image[i][j + 1].rgbtRed * 0) + (image[i + 1][j].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed * 1);
            else if (strcmp(channel, "rgbtGreen") == 0)
                return (image[i][j].rgbtGreen * 0) + (image[i][j + 1].rgbtGreen * 0) + (image[i + 1][j].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen * 1);
            else if (strcmp(channel, "rgbtBlue") == 0)
                return (image[i][j].rgbtBlue * 0) + (image[i][j + 1].rgbtBlue * 0) + (image[i + 1][j].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue * 1);
            break;

        case 3:
            if (strcmp(channel, "rgbtRed") == 0)
                return (image[i][j - 1].rgbtRed * 0) + (image[i][j].rgbtRed * 0) + (image[i + 1][j - 1].rgbtRed * 1) + (image[i + 1][j].rgbtRed * 2);
            if (strcmp(channel, "rgbtGreen") == 0)
                return (image[i][j - 1].rgbtGreen * 0) + (image[i][j].rgbtGreen * 0) + (image[i + 1][j - 1].rgbtGreen * 1) + (image[i + 1][j].rgbtGreen * 2);
            if (strcmp(channel, "rgbtBlue") == 0)
                return (image[i][j - 1].rgbtBlue * 0) + (image[i][j].rgbtBlue * 0) + (image[i + 1][j - 1].rgbtBlue * 1) + (image[i + 1][j].rgbtBlue * 2);
            break;

        case 4:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1) + (image[i][j].rgbtRed * 0) +
                    (image[i][j + 1].rgbtRed * 0) + (image[i + 1][j].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed * 1);
            }
            if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1) + (image[i][j].rgbtGreen * 0) +
                    (image[i][j + 1].rgbtGreen * 0) + (image[i + 1][j].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen * 1);
            }
            if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1) + (image[i][j].rgbtBlue * 0) +
                    (image[i][j + 1].rgbtBlue * 0) + (image[i + 1][j].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue * 1);
            }
            break;

        case 5:
            if (strcmp(channel, "rgbtRed") == 0)
            {
                return (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * -2) + (image[i][j - 1].rgbtRed * 0) +
                    (image[i][j].rgbtRed * 0) + (image[i + 1][j - 1].rgbtRed * 1) + (image[i + 1][j].rgbtRed * 2);
            }
            if (strcmp(channel, "rgbtGreen") == 0)
            {
                return (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * -2) + (image[i][j - 1].rgbtGreen * 0) +
                (image[i][j].rgbtGreen * 0) + (image[i + 1][j - 1].rgbtGreen * 1) + (image[i + 1][j].rgbtGreen * 2);
            }
            if (strcmp(channel, "rgbtBlue") == 0)
            {
                return (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * -2) + (image[i][j - 1].rgbtBlue * 0) +
                    (image[i][j].rgbtBlue * 0) + (image[i + 1][j - 1].rgbtBlue * 1) + (image[i + 1][j].rgbtBlue * 2);
            }
            break;

        case 6:
            if (strcmp(channel, "rgbtRed") == 0)
                return (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1) + (image[i][j].rgbtRed * 0) + (image[i][j + 1].rgbtRed * 0);
            if (strcmp(channel, "rgbtGreen") == 0)
                return (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1) + (image[i][j].rgbtGreen * 0) + (image[i][j + 1].rgbtGreen * 0);
            if (strcmp(channel, "rgbtBlue") == 0)
                return (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1) + (image[i][j].rgbtBlue * 0) + (image[i][j + 1].rgbtBlue * 0);
            break;

        case 8:
            if (strcmp(channel, "rgbtRed") == 0)
                return (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * -2) + (image[i][j - 1].rgbtRed * 0) + (image[i][j].rgbtRed * 0);
            if (strcmp(channel, "rgbtGreen") == 0)
                return (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * -2) + (image[i][j - 1].rgbtGreen * 0) + (image[i][j].rgbtGreen * 0);
            if (strcmp(channel, "rgbtBlue") == 0)
                return (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * -2) + (image[i][j - 1].rgbtBlue * 0) + (image[i][j].rgbtBlue * 0);
            break;

        default:
            printf("Error calculating gy()!\n");
    }

    return 0;
}

//--------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------- BLUR -----------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------
void blur (void) {
    // calculates all the values for all possible pixel's positions
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            switch (whichPosition(height, width, i, j))
            {
                case 1:
                    dummy[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed)/4);
                    dummy[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen)/4);
                    dummy[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue)/4);
                    break;

                case 2:
                    dummy[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed +
                        image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed)/6);

                    dummy[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                        image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen)/6);

                    dummy[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                        image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue)/6);
                    break;

                case 3:
                    dummy[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed)/4);
                    dummy[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen)/4);
                    dummy[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue)/4);
                    break;

                case 4:
                    dummy[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed +
                        image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed)/6);

                    dummy[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                        image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen)/6);

                    dummy[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue +
                        image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue)/6);
                    break;

                case 5:
                    dummy[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed +
                        image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed)/6);

                    dummy[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                        image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen)/6);

                    dummy[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue +
                        image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue)/6);
                    break;

                case 6:
                    dummy[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed)/4);
                    dummy[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen)/4);
                    dummy[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue)/4);
                    break;

                case 7:
                    dummy[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed +
                        image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed)/6);

                    dummy[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                        image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen)/6);

                    dummy[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                        image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue)/6);
                    break;

                case 8:
                    dummy[i][j].rgbtRed = round((float)(image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed)/4);
                    dummy[i][j].rgbtGreen = round((float)(image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen)/4);
                    dummy[i][j].rgbtBlue = round((float)(image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue)/4);
                    break;

                case 9: // 178 193 201
                    dummy[i][j].rgbtRed = round((float)(image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                        image[i - 1][j].rgbtRed + image[i][j].rgbtRed + image[i + 1][j].rgbtRed +
                        image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed)/9);

                    dummy[i][j].rgbtGreen = round((float)(image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                        image[i - 1][j].rgbtGreen + image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                        image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen)/9);

                    dummy[i][j].rgbtBlue = round((float)(image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                        image[i - 1][j].rgbtBlue + image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue +
                        image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue)/9);
                    break;
            }
        }
    }

    // copy the 2D array
    copyArr(height, width, dummy, image);

    // testing the output
    printf("case 1: %i, %i, %i\n", image[0][0].rgbtRed, image[0][0].rgbtGreen, image[0][0].rgbtBlue);
    printf("case 2: %i, %i, %i\n", image[0][1].rgbtRed, image[0][1].rgbtGreen, image[0][1].rgbtBlue);
    printf("case 3: %i, %i, %i\n", image[0][2].rgbtRed, image[0][2].rgbtGreen, image[0][2].rgbtBlue);
    printf("case 4: %i, %i, %i\n", image[1][0].rgbtRed, image[1][0].rgbtGreen, image[1][0].rgbtBlue);
    printf("case 9: %i, %i, %i\n", image[1][1].rgbtRed, image[1][1].rgbtGreen, image[1][1].rgbtBlue);
    printf("case 5: %i, %i, %i\n", image[1][2].rgbtRed, image[1][2].rgbtGreen, image[1][2].rgbtBlue);
    printf("case 6: %i, %i, %i\n", image[2][0].rgbtRed, image[2][0].rgbtGreen, image[2][0].rgbtBlue);
    printf("case 7: %i, %i, %i\n", image[2][1].rgbtRed, image[2][1].rgbtGreen, image[2][1].rgbtBlue);
    printf("case 8: %i, %i, %i\n", image[2][2].rgbtRed, image[2][2].rgbtGreen, image[2][2].rgbtBlue);
}

void copyArr (int h, int w, RGBTRIPLE origin[h][w], RGBTRIPLE destination[h][w])
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            destination[i][j] = origin[i][j];
        }
    }
}

int whichPosition (int h, int w, int i, int j)
{
    int maxWidth = w - 1;
    int maxHeight = h - 1;

    if (i == 0 && j == 0)
        return 1;
    else if (i == 0 && j > 0 && j < maxWidth)
        return 2;
    else if (i == 0 && j == maxWidth)
        return 3;
    else if (i > 0 && i < maxHeight && j == 0)
        return 4;
    else if (i > 0 && i < maxHeight && j == maxWidth)
        return 5;
    else if (i == maxHeight && j == 0)
        return 6;
    else if (i == maxHeight && j > 0 && j < maxWidth)
        return 7;
    else if (i == maxHeight && j == maxWidth)
        return 8;
    else
        return 9;
}

    /* TESTS FOR GREYSCALE
    *************************
    int height = 1;
    int width = 1;

    image[0][0].rgbtRed = 27;
    image[0][0].rgbtGreen = 28;
    image[0][0].rgbtBlue = 28;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate the average pixel value
            float averageValue = round(((float) image[i][j].rgbtRed + (float) image[i][j].rgbtGreen + (float) image[i][j].rgbtBlue) / 3);

            // set each color values to the image 2D array
            image[i][j].rgbtRed = ceil(averageValue);
            image[i][j].rgbtGreen = round(averageValue);
            image[i][j].rgbtBlue = averageValue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%i, %i, %i\n", image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
        }
    }

    int width = 6;
    int height = 6;

    int arr[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            arr[i][j] = 0;
        }
    }

     for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%i ", arr[i][j]);
        }
        printf("\n\n");
    }

    arr[0][0] = 1;
    arr[0][1] = 2;
    arr[0][2] = 3;
    arr[0][3] = 4;
    arr[0][4] = 5;
    arr[0][5] = 6;
    arr[1][0] = 7;
    arr[1][1] = 8;
    arr[1][2] = 9;
    arr[1][3] = 10;
    arr[1][4] = 11;
    arr[1][5] = 12;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%i ", arr[i][j]);
        }
        printf("\n");
    }

    // temporary variable
    int tmp = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
            tmp = arr[i][j];
            arr[i][j] = arr[i][width - (j + 1)];
            arr[i][width - (j + 1)] = tmp;
        }
    }

    printf("\n-----------------------\n");

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%i ", arr[i][j]);
        }
        printf("\n");
    }
    */