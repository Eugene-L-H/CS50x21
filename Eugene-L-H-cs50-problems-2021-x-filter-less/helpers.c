#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through image's pixels and set each color-value to the average of
    // of each original RGB value together.
    for (int i = 0; i < height; i++) // Iterate through rows.
    {
        // Iterate through each pixel in the row.
        for (int j = 0; j < width; j++)
        {
            float average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.00;
            int round_avg = round(average);

            image[i][j].rgbtRed = round_avg;
            image[i][j].rgbtGreen = round_avg;
            image[i][j].rgbtBlue = round_avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) // Iterate through rows.
    {
        // Iterate through each pixel in the row.
        for (int j = 0; j < width; j++)
        {
            int s_red = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int s_green = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int s_blue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if (s_red > 255)
            {
                s_red = 255;
            }
            if (s_green > 255)
            {
                s_green = 255;
            }
            if (s_blue > 255)
            {
                s_blue = 255;
            }

            image[i][j].rgbtRed = s_red;
            image[i][j].rgbtGreen = s_green;
            image[i][j].rgbtBlue = s_blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE mirror[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            mirror[i][j] = image[i][(width - j) - 1];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = mirror[i][j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // Iterate through rows.
    for (int i = 0; i < height; i++)
    {
        // Iterate through pixels.
        for (int j = 0; j < width; j++)
        {
            int red = 0;
            int green = 0;
            int blue = 0;
            float count = 0.00;

            // Iterate one pixel row above, equal, and below.
            for (int h = -1; h < 2; h++)
            {
                // Iterate one pixel to the left, same, and to the right on each row.
                for (int w = -1; w < 2; w++)
                {
                    // Skip current iteration if it goes out of array.
                    if (i + h < 0 || i + h > height - 1 || j + w < 0 || j + w > width - 1)
                    {
                        continue;
                    }

                    red += image[i + h][j + w].rgbtRed;
                    green += image[i + h][j + w].rgbtGreen;
                    blue += image[i + h][j + w].rgbtBlue;

                    count++;
                }

            }

            copy[i][j].rgbtRed = round(red / count);
            copy[i][j].rgbtGreen = round(green / count);
            copy[i][j].rgbtBlue = round(blue / count);

        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
        }
    }
    return;
}
