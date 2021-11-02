from random import randint
import bs_mods

print(bs_mods.art)

# Displays greeting to player
print("Welcome to BINARY_SEARCH: The Human Binary Search Game!")

# Variable that when set to "False" will terminate the session.
run = True

# Loop that will contain the game.
while run:

    # Computer selects a random number between 1 - 1000
    number = randint(1, 1001)

    # Counter that tallies the players guesses
    count = 0

    # Player selects a difficulty
    difficulty = bs_mods.select_difficulty()

    # Difficulty is set based on player's choice. "hard" difficulty adds 4
    # to the "count" variable reducing the player's guesses from 10 to 6.
    if difficulty == "hard":
        count += 4

    print(f"\n  *You have {10 - count} tries to guess the number*")

    first_question = True

    # Loop that contains the guessing cycle
    while True:

        # Generic message is displayed after first_guess set to false
        if not first_question:
            guess = bs_mods.generic_guess()

        # player makes their first guess
        if first_question:
            guess = bs_mods.first_guess()
            first_question = False

        count += 1

        # The player's guess is compared against the number and they are
        #  informed whether they need to guess higher or lower on ther next guess
        if guess == number:
            print("\nThat's it! You got it, well done :)")
            break
        elif count == 10:
            print(f"\nNot quite! The number was {number}.")
            break
        elif guess < number:
            print("\n Higher...")
        elif guess > number:
            print("\nLower...")

        # Displays a message infoming the use how many guesses they have left.
        if count < 9:
            print(f"You have {10 - count} guesses left.")
        elif count == 9:
            print("You have 1 guess left!")

    # Asks if player would like to play another game
    play_again = bs_mods.play_again()
    if play_again == "yes":
        continue
    elif play_again == "no":
        print("\n   Thanks for playing!\n")
        run = False
