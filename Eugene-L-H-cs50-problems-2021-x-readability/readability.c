#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    // Prompt user to enter the text that they would like to analyse.
    string text = get_string("Please enter the text: ");

    // Loop that counts the number of letters, words and sentances in the text.
    char cur_char;
    float letters = 0;
    float words = 0;
    float sentances = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {

        cur_char = text[i];

        if (cur_char == ' ')
        {
            // A space denotes the end of a word so 1 is added.
            words += 1;
        }
        else if (cur_char == '.' || cur_char == '?' || cur_char == '!')
        {
            // Puntuation denotes the end of a sentance so 1 is added.
            sentances += 1;
        }

        // Check if cur_char is alphabetical. If it is, it is counted
        // as a letter. Punctuation and spaces are not counted as letters.
        if (isalpha(cur_char))
        {
            letters += 1;
        }

    }

    // Add one to words to account for lack of space on the last word.
    // Punctuation will be there instead.
    words += 1;

    // Calculate average number of letters per 100 words.
    float L = letters / words * 100;
    // Calculate the average number of sentances per 100 words.
    float S = sentances / words * 100;

    // Running results through Coleman-Liau algorithm to determine grade
    // level of the text.
    float grade = 0.0588 * L - 0.296 * S - 15.8;

    //Display to user what reading level their text is.
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(grade));
    }

}