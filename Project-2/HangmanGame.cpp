/*
 * Title: HangmanGame.cpp
 * Author: Paul Prae
 * Last Edited: September 14th, 2010
 * Project 2 for CSCI 1730 with Doc
 * 
 * Purpose of this file and associated program:
 *
 *     This is the file HangmanGame.cpp which is part
 * of Project 2 titled "Hangman++." This file will not
 * begin program execution. This is the file  
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

#include "HangmanGame.h"

#include <iostream>
#include <string>
using namespace std;

//Constructors
// Constructor that initializes the object
HangmanGame::HangmanGame(){

    HangmanBoard currentBoard(0);
    setGuesserIsHuman(true);
    setGuesserHasWon(false);
    setContinueGame(true);
    computerGuessAmount = 0;
    currentBlanks = 0;

}//end no arg constructor

//Constructor that takes in two arguments to represent what type of guesser and number of blanks
HangmanGame::HangmanGame(string guesser, int blanks){

    HangmanBoard currentBoard(blanks);

    currentBlanks = blanks;

    if(guesser == "human"){
      setGuesserIsHuman(true);
    }else{
      setGuesserIsHuman(false);
      computerGuessAmount = 0;
    }
    setGuesserHasWon(false);
    setContinueGame(true);

}//end two arg contructor
  
//A function to play the Hangman Game with human guesser, returns a boolean to show that the game has ended
//If the return value is false then the game discontinued properly
//It will take a HangmanBoard object as a parameter
bool HangmanGame::playHumanGame( HangmanBoard board){

    //Check for blanks stored
  while( (currentBlanks == 0)){

      cout << "I did not detect any blanks stored from the operator." << endl;
      cout << "How many blanks do you need operator? Only enter integers!" << endl;
      cin >> currentBlanks;

    }

    //While the game is supposed to continue, keep cycling through the game play
    while(getContinueGame()){
      
      board.drawGameboard();

      char currentAnswer = 'n';
      int currentIntAnswer = 0;

      cout << "Guesser, would you like to guess the word?(enter a lowercase y or n)" << endl;
      cin >> currentAnswer;
      while(currentAnswer == 'y'){

	cout << "Guesser, please enter your guess for the word in characters only now:" << endl;
	cin >> currentWordGuess;

	cout << "Guesser, you just entered: " << currentWordGuess << "." <<endl;
	cout << "Operator, is this correct?(enter a lowercase y or n)" <<endl;
	cin >> currentAnswer;

	if(currentAnswer == 'y'){

	  cout << "Guesser, GREAT JOB! Would you like to continue playing?" << endl;
	  cout << "(enter a lowercase y or n)" << endl;
	  cin >> currentAnswer;
	  if(currentAnswer == 'y'){

	    cout << "Sounds great!" << endl;
	    setContinueGame(true);
	    return getContinueGame();

	  }// end if
	  else{

	    cout << "Alright. See ya!" << endl;
	    setContinueGame(false);
	    return getContinueGame();

	  }//end else

	}//end if
	else{

	  cout << "Guesser, nice try. Would you like to try again? (enter a lowercase y or n)" << endl;
	  cin >> currentAnswer;

	}//end else

      }//end while

      cout << "Guesser, please make your first guess on a letter. Enter single characters only:" << endl;
      cin >> currentCharGuess;
      cout << "Operator, the guesser entered: " << currentCharGuess << "." << endl;
      cout << "Operator, is this correct? Please enter a single lowercase character y or n: " << endl;
      cin >> currentAnswer;

      if(currentAnswer == 'y'){
	
	cout << "Which blank should be replaced with " << currentCharGuess << "?" << endl;
	cout << "Please enter an integer value: " << endl;
	cin >> currentIntAnswer;
	
	//Update game board with new correct guess
	board.updateGameboard( '0', currentCharGuess, currentIntAnswer );

	if(checkForWin(board)){

	  cout << "The guesser just won! Congrats!" << endl;
	  board.drawGameboard();
	  setContinueGame(false);
	  setGuesserHasWon(true);
	  
	}

      }//end if
      else{

	cout << "Ok, " << currentCharGuess << " will be marked as a missed guess." << endl;
	cout << "The man hanging is another step closer to death." << endl;

	//The board will be updated with a missed guess
	board.updateGameboard( currentCharGuess, '0', '0');

	if(checkForLoss(board)){
	  
	  cout << "The guesser just lossed! Maybe next time..." << endl;
	  board.drawGameboard();
	  setContinueGame(false);
	  setGuesserHasWon(false);

	}

      }//end else

      //End game if the game is over or the user requested to leave
      if( (getContinueGame() == false) ){

	return getContinueGame();

      }//end if

      cout << "Shall we continue this round? Please enter a single lowercase character y or n: " << endl;
      cin >> currentAnswer;
      if(currentAnswer == 'n'){
	continueGame = false;
      }//end if

    }//end while
    
    cout << "The current round has ended." << endl;
    
    return getContinueGame();

}//end playHumanGame

//A function to play the Hangman Game with computer guesser, returns a boolean to show that the game has ended 
//It will take a HangmanBoard object as a parameter
bool HangmanGame::playComputerGame( HangmanBoard board ){

  //Check for blanks stored
  while( (currentBlanks == 0)){

    cout << "I did not detect any blanks stored from the operator." << endl;
    cout << "How many blanks do you need operator? Only enter integers!" << endl;
    cin >> currentBlanks;

  }

  //While the game is supposed to continue, keep cycling through the game play
  while(getContinueGame()){
      
    board.drawGameboard();

    char currentAnswer = 'n';
    int currentIntAnswer = 0;

    cout << "Guesser, would you like to guess the word?(enter a lowercase y or n)" << endl;
    cout << "n" << endl;
    while(currentAnswer == 'y'){

      cout << "Guesser, please enter your guess for the word in characters only now:" << endl;
      cin >> currentWordGuess;

      cout << "Guesser, you just entered: " << currentWordGuess << "." <<endl;
      cout << "Operator, is this correct?(enter a lowercase y or n)" <<endl;
      cin >> currentAnswer;

      if(currentAnswer == 'y'){

	cout << "Guesser, GREAT JOB! Would you like to continue playing?" << endl;
	cout << "(enter a lowercase y or n)" << endl;
	cin >> currentAnswer;
	if(currentAnswer == 'y'){

	  cout << "Sounds great!" << endl;
	  setContinueGame(true);
	  return getContinueGame();

	}// end if
	else{

	  cout << "Alright. See ya!" << endl;
	  setContinueGame(false);
	  return getContinueGame();

	}//end else

      }//end if
      else{

	cout << "Guesser, nice try. Would you like to try again? (enter a lowercase y or n)" << endl;
	cin >> currentAnswer;

      }//end else

    }//end while

    cout << "Guesser, please make your first guess on a letter. Enter single characters only:" << endl;
    currentCharGuess = computerGuess(computerGuessAmount);
    cout << currentCharGuess << endl;
    cout << "Operator, the guesser entered: " << currentCharGuess << "." << endl;
    cout << "Operator, is this correct? Please enter a single lowercase character y or n: " << endl;
    cin >> currentAnswer;

    if(currentAnswer == 'y'){
      
      cout << "Which blank should be replaced with " << currentCharGuess << "?" << endl;
      cout << "Please enter an integer value: " << endl;
      cin >> currentIntAnswer;
      
      //Update game board with new correct guess
      board.updateGameboard( '0', currentCharGuess, currentIntAnswer );

      if(checkForWin(board)){

	cout << "The guesser just won! Congrats!" << endl;
	board.drawGameboard();
	setContinueGame(false);
	setGuesserHasWon(true);
	  
      }

    }//end if
    else{

      cout << "Ok, " << currentCharGuess << " will be marked as a missed guess." << endl;
      cout << "The man hanging is another step closer to death." << endl;

      //The board will be updated with a missed guess
      board.updateGameboard( currentCharGuess, '0', '0');

      if(checkForLoss(board)){
	  
	cout << "The guesser just lossed! Maybe next time..." << endl;
	board.drawGameboard();
	setContinueGame(false);
	setGuesserHasWon(false);

      }

    }//end else

    //End game if the game is over or the user requested to leave
    if( (getContinueGame() == false) ){

      return getContinueGame();

    }//end if

    cout << "Shall we continue this round? Please enter a single lowercase character y or n: " << endl;
    cin >> currentAnswer;
    if(currentAnswer == 'n'){
      continueGame = false;
    }//end if

  }//end while
    
  cout << "The current round has ended." << endl;
  setComputerGuessAmount(0);  
  return getContinueGame();


}//end playComputerGame

//The following function will return a char as the current computer guess given which turn it is
char HangmanGame::computerGuess(int guessNumber){

  //This char array will hold the alphabet for the computer to use
  char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0'};

  if(guessNumber > 25){
    setComputerGuessAmount(0);
  }

  setComputerGuessAmount( (getComputerGuessAmount() + 1) );

  return alphabet[guessNumber];

}//end computerGuess

//The following functions will check the board for a win or a loss given a gameboard
bool HangmanGame::checkForWin(HangmanBoard checkBoard){

  //Iterate through the guessDisplayArray and count how many blanks remain
  //If there are no blanks in the array then the guesser has won
  int blanks = checkBoard.getNumberOfBlanks();
  int blankCount = 0;

  for(int i = 0; i < blanks; i++){

    if(checkBoard.guessDisplayArray[i] == '_'){

      blankCount++;

    }//end if

  }//end for loop

  if(blankCount == 0){
    return true;
  }else{
    return false;
  }

}//end checkForWin

bool HangmanGame::checkForLoss(HangmanBoard checkBoard){

  //Check the current stage, if stage 6 then the man is hung
  if( (checkBoard.getCurrentStage() == 6) ){
    return true;
  }else{
    return false;
  }

}//end checkForLoss

//Setters
void HangmanGame::setGuesserIsHuman( bool isHuman){

  guesserIsHuman = isHuman;

}//end setGuesserIsHuman

void HangmanGame::setGuesserHasWon( bool hasWon){

  guesserHasWon = hasWon;

}//end setGuesserHasWon

void HangmanGame::setContinueGame( bool shouldContinueGame){

  continueGame = shouldContinueGame;

}//end setContinueGame

void HangmanGame::setComputerGuessAmount(int amount){

  computerGuessAmount = amount;

}//end setComputerGuessAmount


  //Getters
bool HangmanGame::getGuesserIsHuman(){

  return guesserIsHuman;

}//end getGuesserIsHuman

bool HangmanGame::getGuesserHasWon(){

  return guesserHasWon;

}//end get guesserHasWon

bool HangmanGame::getContinueGame(){

  return continueGame;

}//end getContinueGame

int HangmanGame::getComputerGuessAmount(){

  return computerGuessAmount;

}//end getCOmputerGuessAmount

