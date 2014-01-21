/*
 * Title: HangmanGame.h
 * Author: Paul Prae
 * Last Edited: September 14th, 2010
 * Project 2 for CSCI 1730 with Doc
 * 
 * Purpose of this file and associated program:
 *
 *     This is the header file for HangmanGame.cpp which is part
 * of Project 2 titled "Hangman++." This header file will not
 * begin program execution. This file is the interface for the 
 * HangmanGame.cpp which holds the class function definitions. 
 * The purpose of the HangmanGame class is to implement the 
 * functionality and logic of playing the game.
 *     The associated main program is to serve the following purpose:
 *     To play the traditional game of pen and paper hangman using
 * a purely command prompt and ASCII environment. There will be the
 * option of a computer or human guesser. A human will always operate
 * the board.
 *
 * Limitations of development resources:
 *     This code was written as directed by the instructions for Project
 * 2: Hangman++ program posted by Dr. Plaue on eLC at the University
 * of Georgia. It was written using concepts, ideas, and code presented
 * in class, on the eLC section for the class, in the textbook C++: How
 * To Program Seventh Edition by Deitel and Deitel, and from
 * http://www.cplusplus.com's Reference Libraries.
 * 
 * Statement of Academic Honesty:
 *     The following code represents my own work. I have neither
 * recieved nor given inappropriate assistance. I have not copied
 * or modified code from any source other than the course webpage,
 * eLC, or the course textbook. I recognize that any unauthorized
 * assistance or plagiarism will be handled in accordance with the
 * University of Georgia's Academic Honesty Policy and the policies 
 * of this course.
 *
 * This project was created on UNIX using Emacs
 */
#include "HangmanBoard.h"

#include <string>
using namespace std;

//HangmanGame class definition
class HangmanGame
{
public:

  //Public variables
  //A variable to hold the number of blanks
  int currentBlanks;
  //A variable to hold the number of guesses the computer has made
  int computerGuessAmount;

  //Variables to hold the current guesses
  string currentWordGuess;
  char currentCharGuess;

  //Constructors
  // Constructor that initializes the object
  HangmanGame();
  //Constructor that takes in two arguments to represent what type of guesser and number of blanks
  HangmanGame(string, int);
  
  //A function to play the Hangman Game with human guesser, returns a boolean to show that the game has ended
  //It will take a HangmanBoard object as a parameter
  bool playHumanGame( HangmanBoard );
  //A function to play the Hangman Game with computer guesser, returns a boolean to show that the game has ended
  //It will take a HangmanBoard object as a parameter
  bool playComputerGame( HangmanBoard );
  //The following function will act as the guessing agent for the computer player, returns char as guess
  char computerGuess( int );


  //The following functions will check the game status for a win or a loss
  bool checkForWin(HangmanBoard);
  bool checkForLoss(HangmanBoard);

  //Setters
  void setGuesserIsHuman( bool );
  void setGuesserHasWon( bool );
  void setContinueGame( bool );
  void setComputerGuessAmount( int );

  //Getters
  bool getGuesserIsHuman();
  bool getGuesserHasWon();
  bool getContinueGame();  
  int getComputerGuessAmount();

private:
  
  //A variable to hold whether the guesser is human
  bool guesserIsHuman;
  //A variable to hold whether the game has been won or not
  bool guesserHasWon;
  //A variable to hold whether to continue playing the game or not
  bool continueGame;



}; // end class HangmanGame
