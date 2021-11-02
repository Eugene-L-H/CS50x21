#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string ALPHA = "abcdefghijklmnopqrstuvwxyz";

int duplicate(string user_key);
int invalid_characters(string user_key);

int main(int argc, string argv[])
{
    // Program will fail to execute if none or more than one argument is made
    // or if their key length < 26.
    if (argc != 2)
    {
        printf("Please enter a 26-letter key.\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must be 26 letters long.\n");
        return 1;
    }


    // Program will fail to execute if key contains duplicate chars.
    string key = argv[1];
    int duplicate_char = duplicate(key);
    if (duplicate_char == 1)
    {
        printf("Key must not contain duplicate characters.");
        return 1;
    }

    // Program will fail to execute if key contains numbers or
    // special characters.
    int special_characters = invalid_characters(key);
    if (special_characters == 1)
    {
        printf("Key can only contain alphabetical characters.");
        return 1;
    }


    // Prompt user for text that they would like to encode.
    string text = get_string("plaintext: ");

    // Empty array to store coded letters.
    char cipher[strlen(text) + 1];
    char letter;
    string first;
    int index;
    bool uppercase = false;

    // Encode text to output cipher.
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Will encode alphabetical chars only.
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                uppercase = true;
            }

            // Finding the index(int) of the letter within global ALPHA variable.
            first = strchr(ALPHA, tolower(text[i]));
            index = first - ALPHA;

            letter = key[index];

            // Convert to upper or lowercase.
            if (uppercase)
            {
                letter = toupper(letter);
            }
            else
            {
                letter = tolower(letter);
            }

        }

        // Non-alphabetic chars will be passed un-coded.
        else
        {
            letter = text[i];
        }

        cipher[i] = letter;
        uppercase = false;
    }

    cipher[strlen(text)] = '\0';

    printf("ciphertext: %s\n", cipher);
}


int duplicate(string user_key)
// Detects duplicate characters present in user submitted key.
{
    char ALPHA_char;
    char KEY_char;
    int count;

    for (int i = 0; i < 26; i++)
    {
        // If count triggers to 2 that means there is a duplicate char
        // in key.
        count = 0;

        ALPHA_char = tolower(ALPHA[i]);

        // Loop through chars of key comparing them against ALPHA chars,
        // if 2 matches are made, program will exit.
        for (int j = 0, n = 26; j < n; j++)
        {
            KEY_char = tolower(user_key[j]);

            if (ALPHA_char == KEY_char)
            {
                count += 1;
            }
            // Program exits if count == 2, meaning a duplicate char was found.
            if (count == 2)
            {
                return 1;
            }

        }

    }
    return 0;
}


int invalid_characters(string user_key)
// Detects non-alphabetic characters present in user submitted key.
{
    // Loop through user submitted key's characters checking for alpha.
    for (int i = 0; i < 26; i++)
    {

        if (isalpha(user_key[i]) == false)
        {
            return 1;
        }
    }

    return 0;
}