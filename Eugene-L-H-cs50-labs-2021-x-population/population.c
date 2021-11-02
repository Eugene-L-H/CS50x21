#include <cs50.h>
#include <stdio.h>

// Call function that asks user for starting population.
int llamas(void);

int main(void)
{
    // TODO: Prompt for start size
    printf("\nWhat is the starting population?\n");
    int pop = llamas();
    while (pop < 9)
    {
        printf("\nIf we start with fewer than 9 llamas, the population of llamas will quickly become stagnant!\n");
        pop = llamas();
    }
    

    // TODO: Prompt for end size
    printf("\nWhat is the final population?\n");
    int final = llamas();
    while (final < pop)
    {
        printf("\nThe population will increase, not decrease. Enter a final\
 populaiton size that is more than the starting.\n");
        final = llamas();
    }

    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    while (pop < final)
    {
        // Calculate number of llama births/deaths in the year
        int births = pop / 3;
        int deaths = pop / 4;
        
        // Calculate the year-end population
        pop = (pop + births) - deaths;
        
        // Adds one year to the year count if population is still less than final
        years++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", years);
}

// Function that prompts user to enter an integer representing a group of llamas
int llamas(void)
{
    int n = get_int("\nHow many llamas?: ");
    return n;
}