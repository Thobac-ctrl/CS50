#include "helpers.h"

#include <stdio.h>
#include <stdint.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float red, blue, green;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = image[i][j].rgbtRed;
            green = image[i][j].rgbtGreen;
            blue = image[i][j].rgbtBlue;

            int average = round((red + green + blue) / 3);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;

            //printf("r:%f____g:%f____b:%f\n", red, green, blue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_buffer[height][width];
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            //Mirror horizontally
            //image_buffer[i][j].rgbtRed = image[height - 1 - i][j].rgbtRed;
            //image_buffer[i][j].rgbtGreen = image[height - 1 - i][j].rgbtGreen;
            //image_buffer[i][j].rgbtBlue = image[height - 1 - i][j].rgbtBlue;

            //Mirror perpendicular
            image_buffer[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image_buffer[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image_buffer[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
        }

    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image_buffer[i][j].rgbtRed;
            image[i][j].rgbtGreen = image_buffer[i][j].rgbtGreen;
            image[i][j].rgbtBlue = image_buffer[i][j].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Define temporary  buffer for calc
    float red, blue, green;
    RGBTRIPLE image_buffer[height][width];
    // Loop to copy image into buffer
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            //Array to compute each pixel in the image
            int row_calc[] = {row - 1, row, row + 1};
            int col_calc[] = {col - 1, col, col + 1};

            red = image[row][col].rgbtRed;
            green = image[row][col].rgbtGreen;
            blue = image[row][col].rgbtBlue;

            int count = 0;
            float av_red = 0;
            float av_green = 0;
            float av_blue = 0;
            //Loop for calculation for blur effect
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    int x_row = row_calc[i];
                    int y_col = col_calc[j];

                    if (x_row >= 0 && x_row < height && y_col >= 0 && y_col < width)
                    {
                        av_red += image[x_row][y_col].rgbtRed;
                        av_green += image[x_row][y_col].rgbtGreen;
                        av_blue += image[x_row][y_col].rgbtBlue;
                        count++;
                    }
                }
            }
            //Read manipulated image into buffer
            image_buffer[row][col].rgbtRed = round(av_red / count);
            image_buffer[row][col].rgbtGreen = round(av_green / count);
            image_buffer[row][col].rgbtBlue = round(av_blue / count);
        }
    }
    //Output manipulated image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image_buffer[i][j].rgbtRed;
            image[i][j].rgbtGreen = image_buffer[i][j].rgbtGreen;
            image[i][j].rgbtBlue = image_buffer[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Define temporary  buffer for calc
    RGBTRIPLE image_buffer[height][width];
    int gx_arr[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int gy_arr[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    // Loop to copy image into buffer
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            //Array to compute each pixel in the image
            int row_calc [] = {row - 1, row, row + 1};
            int col_calc [] = {col - 1, col, col + 1};
            
            float gx_red = 0;
            float gx_green = 0;
            float gx_blue = 0;

            float gy_red = 0;
            float gy_green = 0;
            float gy_blue = 0;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    int x_row = row_calc[i];
                    int y_col = col_calc[j];

                    if (x_row >= 0 && x_row < height && y_col >= 0 && y_col < width)
                    {
                        //Calculate each Pixel with  Sobel operator
                        gx_red += gx_arr[i][j] * image[x_row][y_col].rgbtRed;
                        gx_green += gx_arr[i][j] * image[x_row][y_col].rgbtGreen;
                        gx_blue += gx_arr[i][j] * image[x_row][y_col].rgbtBlue;

                        gy_red += gy_arr[i][j] * image[x_row][y_col].rgbtRed;
                        gy_green += gy_arr[i][j] * image[x_row][y_col].rgbtGreen;
                        gy_blue += gy_arr[i][j] * image[x_row][y_col].rgbtBlue;
                    }
                }
            }
            //Read manipulated image into buffer
            int result_red = round(sqrt(gx_red * gx_red + gy_red * gy_red));
            int result_green = round(sqrt(gx_green * gx_green + gy_green * gy_green));
            int result_blue = round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));

            image_buffer[row][col].rgbtRed = result_red > 255 ? 255 : result_red;
            image_buffer[row][col].rgbtGreen = result_green > 255 ? 255 : result_green;
            image_buffer[row][col].rgbtBlue = result_blue > 255 ? 255 : result_blue;
        }
    }
    //Output manipulated image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image_buffer[i][j].rgbtRed;
            image[i][j].rgbtGreen = image_buffer[i][j].rgbtGreen;
            image[i][j].rgbtBlue = image_buffer[i][j].rgbtBlue;
        }
    }
    return;
}
    
