Hangman++
==========

In this project, each team will be required to design and implement a souped-up version of the classic game, Hangman (http://en.wikipedia.org/wiki/Hangman_(game)). 

You will implement the capabilities for both human and computer players. Each team must design and implement the following classes named as they are stated below. You may choose to add more classes:
1. HangmanBoard: a class that implements the functionality of updating and operating the board.
2. HangmanGame: a class that implements the functionality of playing a game of Hangman.
3. Hangman: a class that contains the main method to run HangmanGame.


Input and Output requirements
--------------------------------------------

The Hangman class must have a main method that can process input parameters:
+ The first argument (required) is for who is playing the initial role of a guesser: human or computer
+ The second argument is optional and it is an integer number indicating the number of blanks. If this is not indicated, you will need to prompt the human operator for the number of blanks.


In addition, you must support an optional –L flag that, when used, results in logging the games (i.e. who played what role and who won) to be placed into a file called Hangman.log. 


Sample Program Calls
-------------------------------

+ prompt% ./Hangman –L human
+ prompt% ./Hangman human –L
+ prompt% ./Hangman human 5


Project Requirements
---------------------

+ At the initial game, you must display “Hangman++” and an empty gallows on the console using output statements. DO NOT USE ANY GUI COMPONENTS TO DRAW THE BOARD. Drawing the gallows and hanging man will be an exercise in your ASCII art creativity; feel free to be as creative (or not) as you want, as long as the image displays properly in a terminal running at 150x40 columns (note that’s columns, not pixels)
+ Since the human is the hangman operator, the human player needs to think of a word and input the number of blanks needed (if the human is the hangman operator, assume that no special characters aside from A-­‐Z are used). Once the number of characters of the word the human has selected has been inputted, the gallows and blanks should be displayed as indicated above. In this mode, you will need to provide a prompt for the hangman operator to indicate whether a guess was correct (and if so, which blank(s)).
+ If a human is the guesser, the human needs to be prompted to guess a letter. If the letter is a “hit”, it is revealed in the blank where appropriate. If it’s a miss, the man is further hanged.
+ After a game is completed, you should prompt to see if another game is desired by. If so, you need to see if any roles are to be changed, and how many blanks are needed.


Note: When drawing your gallows, make sure that to the right (this makes it easier for you) of the hanged man, you indicate the missed letters. You may put the blanks anywhere you wish, as long as it looks “acceptable.”


Error Handling
----------------------

Your program should never crash or hang (pun, intended). You should handle file i/o problems by gently prompting if an error occurs. 
