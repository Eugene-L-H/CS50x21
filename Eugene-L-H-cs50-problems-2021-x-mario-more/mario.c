#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Asks user to input how many blocks high they want their pyramid
    int height = get_int("Height: ");
    while (height < 1 || height > 8)
    {
        height = get_int("Please enter an integer between 1 and 8: ");
    }

    // Builds ascii pyramid that is as many blocks high and wide as the user
    // input.
    int rows;
    int bricks;
    int spaces;
    for (rows = 1; rows < height + 1; rows++)
    {
        for (spaces = 0; spaces < height - rows; spaces++)
        {
            printf(" ");
        }
        // Print row of bricks.
        for (bricks = 0; bricks < rows; bricks++)
        {
            printf("#");
        }
        // Print space that goes inbetween the two pyrimids on same row.
        printf("  ");
        // Print 2nd row of bricks.
        for (bricks = 0; bricks < rows; bricks++)
        {
            printf("#");
        }
        // Creates new line after each row.
        printf("\n");
    }

}