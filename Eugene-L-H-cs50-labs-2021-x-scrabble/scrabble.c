#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
string ALPHA = "abcdefghijklmnopqrstuvwxyz";

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 == score1)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }

}


int compute_score(string word)
{
    // TODO: Compute and return score for string
    char letter;
    bool upper = false;
    bool lower = false;
    int index;
    string first;
    int total = 0;
    int score;

    for (int i = 0, n = strlen(word); i <= n; i++)
    {
        // Iterate over each letter in the word
        letter = word[i];
        upper = isupper(letter);
        lower = islower(letter);

        // Check letter case
        if (upper == true)
        {
            // Changes uppercase char to lowercase
            letter = letter + 32;
        }

        if (upper == true || lower == true)
        {
            // Finding the index(int) of the letter within alphabet variable
            first = strchr(ALPHA, letter);
            index = first - ALPHA;

            // Extracting score from points using the index value from letter
            score = POINTS[index];

            // adding score to total for each letter in the word
            total += score;
        }

    }

    return total;
}