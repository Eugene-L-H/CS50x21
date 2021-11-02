#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    bool name_present = false;
    int vote;

    // Loop through candidate names seaching for a match.
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            name_present = true;
            vote = i;
        }
    }

    if (!name_present)
    {
        // If parameter name is not matched in candidate list function returns
        // false.
        return false;
    }
    // Update 2-dimentional array "preferences" with the voter their vote rank.
    preferences[voter][rank] = vote;

    return true;
}


// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int v = 0; v < voter_count; v++)
    {
        for (int r = 0; r < candidate_count; r++)
        {
            int c = preferences[v][r];
            if (candidates[c].eliminated == false)
            {
                candidates[c].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int highest = 0;
    int votes;
    int win;
    float majority = ceil((float)voter_count / 2);

    // Determine which candidate(s) has the highest amount of votes.
    for (int i = 0; i < candidate_count; i++)
    {
        votes = candidates[i].votes;

        // Looks for current highest vote count per candidate.
        if (votes > highest)
        {
            // Update current highest vote count.
            highest = votes;
        }
    }

    // Select candidate(s) with vote count that matches the highest vote count.
    for (int i = 0; i < candidate_count; i++)
    {
        // Tally of current candidate's vote score, check to see if they win.
        win = candidates[i].votes;

        if (win == highest)
        {
            // If candidate's vote score is the highest and also carries more
            // than half of the total votes they are declared the winner.
            if (win > majority)
            {
                // Display the name of the winning candidate.
                printf("%s\n", candidates[i].name);

                return true;
            }
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int highest;
    int votes;

    // Determine which candidate(s) has the highest amount of votes.
    for (int i = 0; i < candidate_count; i++)
    {

        if (!candidates[i].eliminated)
        {
            votes = candidates[i].votes;

            // Looks for current highest vote count per candidate.
            if (votes > highest)
            {

                // Update current highest vote count.
                highest = votes;

            }

        }

    }

    int lowest = highest;

    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            votes = candidates[i].votes;

            if (votes < lowest)
            {

                lowest = votes;

            }

        }

    }

    return lowest;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{

    // Check each candidate's total vote count against the minimum.
    for (int i = 0; i < candidate_count; i++)
    {
        // If a single candidate's total vote count does not equal the minimum
        // there is not a tie.
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }

    }
    return;
}
