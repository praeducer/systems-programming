---------------------------------------------------------------------------
All files created by Paul Prae

Files:
	readme			This file
	Hangman.cpp		A C++ program that will become the executable file 
once the Makefile is run. It will run the game Hangman++.
	HangmanGame.cpp		The class that contains all of the logic for the
Hangman++ game. It contains the required functions to play the game.
	HangmanGame.h		The header file for HangmanGame.cpp
	HangmanBoard.cpp	This file contains all of the functions required
to display the information of the game status.
	HangmanBoard.h		This file is the header file for HangmanBoard.cpp

---------------------------------------------------------------------------

PERFORM THE FOLLOWING COMMANDS WHILE IN THE DIRECTORY THAT CONTAINS THE FILES
To compile program Hangman.cpp and associated files execute:
-------------------------------------------------------------

> make

To run the program execute:

> make run

To clean up after the program and remove the install execute:

> make clean


How to operate the program:
-----------------------------
Follow on screen instructions. There are only a few actions you can take.
Make sure to follow instructions precisely.
The logic is similar to the traditional game of Hangman. You can issue 
command line arguments for the type of guesser, the blanks required for
the word to be guessed, and a flag of -L if you want to log the file.
