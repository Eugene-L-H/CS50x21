#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        string candidate_name = candidates[i].name;

        // If a valid name was voted for, that candiate's vote tally goes
        // up by 1 and function returns true.
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;

            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Holds the highest value of vates a single candidate recieved.
    int highest = 0;

    // List of winners;
    int count = 0;
    string winners[MAX];
    int winners_index = 0;

    // Loop through canditdates vote totals to find the highest value.
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= highest)
        {
            highest = candidates[i].votes;
            count += 1;
        }
    }

    // Loop through candidates comparing their vote count to the highest value,
    // if they match the highest value their name is added to list of winners.
    for (int i = 0; i < candidate_count; i++)
    {

        if (candidates[i].votes == highest)
        {
            winners[winners_index] = candidates[i].name;

            winners_index += 1;
        }

    }

    winners[winners_index] = "/0";

    // Return name(s) of candidate(s) who won the election.
    int c = 0;

    for (int i = 0; i < winners_index; i++)
    {
        printf("%s\n", winners[i]);
    }

    return;
}

