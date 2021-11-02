"""This module contains the functions for binary_search.py"""

art = """ 
 ________                                   _  _   
 /  _____/ __ __   ____   ______ ______   __| || |__
/   \  ___|  |  \_/ __ \ /  ___//  ___/   \   __   /
\    \_\  \  |  /\  ___/ \___ \ \___ \     |  ||  | 
 \______  /____/  \___  >____  >____  >   /_  ~~  _\\
        \/            \/     \/     \/      |_||_|
        """


def select_difficulty():
    """Returns player-selected difficulty, either 'normal' or 'hard'"""
    while True:
        difficulty = input(
            '\nPlease select a difficulty; "normal" or "hard": ').lower()
        if difficulty == "n":
            difficulty = "normal"
        elif difficulty == "h":
            difficulty = "hard"

        if difficulty != "normal" and difficulty != "hard":
            print('\nPlease enter either "normal" or "hard"')
            continue

        return difficulty


def first_guess():
    """Asks unique first question and returns the player's
    first guess at the number"""
    while True:
        try:
            guess = int(input("\nI'm thinking of a number between 1 and 1000, \
can you guess what it is?: "))
            if guess > 1000 or guess < 0:
                print("\n*Please enter an integer between 1 and 1000*")
                continue
        except ValueError:
            print("\n*Please enter an integer*")
            continue

        return guess


def generic_guess():
    """Asks generic question and returns the player's subsequent
    guesses at the number"""
    while True:
        try:
            guess = int(input("\nGuess again: "))
            if guess > 1000 or guess < 0:
                print("\n*Please enter an integer between 1 and 1000*")
                continue
        except ValueError:
            print("\n*Please enter an integer*")
            continue

        return guess


def play_again():
    """Prompt asking the player if they would like to play again.
    Contains a loop to ensure proper input"""
    while True:
        play = input("\nWould you like to play again? 'yes' or 'no': ").lower()
        # Converts a "y" or "n" answer into full "yes" or "no".
        if play == "y":
            play = "yes"
        elif play == "n":
            play = "no"

        # Only allowes "yes" or "no" to be passed to the return function
        if play != "yes" and play != "no":
            print("\nPlease enter either 'yes' or 'no'")
            continue

        return play
