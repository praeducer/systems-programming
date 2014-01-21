/*
 * Title: HangmanBoard.h
 * Author: Paul Prae
 * Last Edited: September 13th, 2010
 * Project 2 for CSCI 1730 with Doc
 * 
 * Purpose of this file and associated program:
 *
 *     This is the header file for HangmanBoard.cpp which is part
 * of Project 2 titled "Hangman++." This header file will not
 * begin program execution. This file is the interface for the 
 * HangmanBoard.cpp which holds the class function definitions. 
 * The purpose of the HangmanBoard class is to implement the 
 * functionality of updating and operating the board.
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

using namespace std;

//HangmanBoard class definition
class HangmanBoard
{
public:

  //An array to hold all of the correct guesses and blanks to be displayed
  char guessDisplayArray[50];

  //Constructors
  HangmanBoard(); // Constructor that initializes the object
  HangmanBoard( int ); //Constructor that takes in an argument to represent amount of blanks

  //A function to update the data stored in the GameBoard object given a correct guess or missed guess
  //The first char parameter is the missed guess, the second char parameter is the correct guess
  //A zero value means that it was not a miss or not a correct guess. The last value is the blank to
  //replace.
  void updateGameboard( char, char, int);
  //A function to draw the current gameboard given an int that represents the stage
  void drawGameboard( );
  //A function to draw the current gallow given an int that represents which stage
  void drawGallows( );
  //A function to display the blanks and correct guesses, will use guessDisplayArray
  void displayCorrectGuesses();
  //A function to display guess misses, will use missedGuessList array
  void displayMissedGuesses();
  //A function to initialize the array that holds the number of blanks
  void initializeDisplayArray( int );
  //A function to display the last guess made
  void displayLastGuess();

  //A function to clear the gameboard
  void clearBoard();

  //A function to update the gallows given the stage to update to
  void updateGallows( int );

  //The following will add the appropriate new char to the designated array
  void updateMissedGuessList( char );
  void updateCorrectGuessList( char );
  void updateDisplayArray( char, int );//The int is where the char will be replaced
 
  //SETTERS
  void setLastGuess( char);
  void setNumberOfBlanks( int );
  void setNumberOfMisses( int );
  void setCurrentStage( int );

  //Getters
  char getLastGuess();
  int getNumberOfBlanks();
  int getNumberOfMisses();
  int getCurrentStage();

 private:
  
  //An integer to hold the number of blanks that represent the letters in the word to guess
  int numberOfBlanks;
  //An integer to hold the number of misses from the guesser
  int numberOfMisses;
  //An integer that represent which state or stage the board is in
  int currentStage;

  //A character variable to hold the last character guessed
  char lastGuess;

  //An array to hold the letters that were incorrect guesses
  char missedGuessList[50];
  //An array to hold the correct letters that were guessed
  char correctGuessList[50];

}; // end class HangmanBoard
