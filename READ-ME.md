# BINARY_SEARCH: *The Human Binary-Search Game*

#### Video Demo: <https://youtu.be/yA5kqE9NMBA>

#### Name: first: Eugene, last: Helland
	 Location: Calgary, Alberta, Canada


	Welcome to *BINARY_SEARCH: The Human Binary-Search Game*.

	BINARY_SEARCH is a command-line game written in Python.

	The objective is to guess a randomly generated number between 1 and 1000 within a set number of tries.
	Exceed that number and the game is lost. The most effective way to win is for the player to use
	binary search inside their own head when using their finite amount of guesses.

	After playing BINARY_SEARCH for some time the player will develop a solid understaning of how binary
	search works and why it is so powerful, because they will have been using it with their own brain!

	Aside from random luck with random guesses, it is impossible to win the game without using binary search!

	Imagine using linear-search to try and win:

	First guess: 1 "Higher"
	Second guess: 2 "Higher"
	Third guess: 3 "Higher"
	...
	Tenth guess: 10

	"Not quite! The number was 755"

	It would take forever that way. You would've needed 755 guesses to get that one!

	Now try it with binary-search...

 __To Run:__

	BINARY_SEARCH is a command-line program, so all that is required is to open it up on your command-line.
	On Windows, for example, the program can be right-clicked, the user selects "Open with > Python" and
	the program launches to the Command Prompt.

	The program is split up between two files: **binary_search.py** and **bs_mods.py**. **binary_search.py**
	contains the main program. **bs_mods.py** contains all of the modules that are imported into **binary_search.py**.

	**binary_search.py* is the file that must be exuted to play the game.

 __How to Play:__

	When BINARY_SEARCH is first loaded you will be presented with a welcome screen and be presented with a
	choice of difficulty.

	"normal" difficulty will allow the player 10 tries to guess the number.
	"hard" difficulty will allow the player just 6 tries to guess the number.

	From this point on the objective is to guess the number between 1 and 1000 that the computer is
	"thinking" of. Guesses must an integer between 1 and 1000.

	For your first guess it is recommended that you guess 500, right in the middle of 1000. Each guess should
	eliminate possible guesses by half.

	**If your guess of 500 gets the response of "Lower..." then that means that anything 500 and above is not
	going to be the number. Now the next binary search would be the mid point between 1 and 500 (250). With one
	guess you have eliminated your potential guesses by half! If after guessing 250 you get the response of "Higher",
	your next guess should be 375.**

	Contiune halving your guesses each time based on the feedback of "Higher" or "Lower" until you hone in on
	the answer. Once you get this process down you should be able to win the game most times on the "normal"
	difficulty.

	After each game ends, either through guessing the right number or though running out of guesses, the player
	will be presented with the option of starting a new game or not. If the player selects "no" the program will
	terminate and exit to the desktop.

	Good luck, and have fun training your brain to think a little bit more like a computer scientist!




