/*
 * Title: HangmanBoard.cpp
 * Author: Paul Prae
 * Last Edited: September 13th, 2010
 * Project 2 for CSCI 1730 with Doc
 * 
 * Purpose of this file and associated program:
 *
 *     This is HangmanBoard.cpp which is part of Project 2 titled 
 * "Hangman++." This file holds the class function definitions. 
 * The purpose of the HangmanBoard class is to implement the 
 * functionality of updating and operating the board. It is not 
 * responsible for program execution.
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

#include <iostream>
using namespace std;

#include "HangmanBoard.h"



//Constructor that initializes the object and all of the appropriate variables
HangmanBoard::HangmanBoard(){

  //Initialize all values to zero because game has not started
  numberOfBlanks = 0;
  numberOfMisses = 0;
  currentStage = 0;
  lastGuess = '~';
  missedGuessList[0] = '\0';
  correctGuessList[0] = '\0';
  guessDisplayArray[0] = '\0';

}//end zero argument constructor

//Constructor with one argument that creates the appropriate amount of blanks for guessing
HangmanBoard::HangmanBoard( int blanks ){

  //Initialize blanks and misses given the number of blanks to guess
  numberOfBlanks = blanks;
  numberOfMisses = 0;
  currentStage = 0;
  lastGuess = '~';
  missedGuessList[0] = '\0';
  correctGuessList[0] = '\0';
  guessDisplayArray[0] = '\0';
  initializeDisplayArray(blanks);

}//end single argument constructor

/*A function to update the update the data of the GameBoard given a new miss or correct guess
 *A zero value will represent that a guess was not missed or not correct
 *The last value represents if it was a correct guess which blank should it replace
 */
void HangmanBoard::updateGameboard( char miss, char correct, int replace){

  //If the miss variable is set to zero then it was a correct guess
  //We will then update the board as expected
  if( (miss == '0') ){

    updateCorrectGuessList(correct);
    updateDisplayArray(correct, replace);
    setLastGuess(correct);

  }

  //If the correct guess value was set to zero then it was a miss
  //We will then update the board as expected
  else {
    if( (correct == '0') ){

      setLastGuess(miss);
      setNumberOfMisses( ((getNumberOfMisses()) + 1) );
      currentStage = (getNumberOfMisses());
      updateMissedGuessList(miss);

    }
    else{
      cout << "Gameboard did not update." << endl;
    }
  }

}//end updateGameboard

//A function to draw the current gameboard
void HangmanBoard::drawGameboard(){

  //The following lines will draw all the pieces of the gameboard in order
  drawGallows();
  displayCorrectGuesses();
  cout << endl;
  displayMissedGuesses();
  cout << endl;
  displayLastGuess();
  cout << endl;

}//End drawGameboard

//A function to draw the current gallow
void HangmanBoard::drawGallows(){

  /* First we will check which stage that needs to be displayed via a switch statement
   * We will then use the correct array that needs to be displayed
   * The main while loop in each case will iterate through this ascii char array and display the
   * art one line at a time. Lines are specified by 'N'
   */

  //This will hold our counter for the iteration
  int i = 0;

  switch( currentStage ){

  case 0:{
    char asciiGallowStage0[] = {' ', ' ', ' ', '_', '_', '_', 'N', ' ', ' ', '|', ' ', ' ', ' ', '|', 'N', ' ', ' ', '|', 'N', ' ', ' ', '|', 'N', ' ', ' ', '|', 'N', '_', '_', '|', '_', '_', '_', '_', '_', 'N', '\0'};

    while( (asciiGallowStage0[i] != '\0') ){

      if( (asciiGallowStage0[i] == 'N') ){
	cout << endl;
      }
      else{
	cout << asciiGallowStage0[i];
      }
      i++;

    }//end while for stage 0
    break;}

  case 1:{
    char asciiGallowStage1[] = {' ', ' ', ' ', '_', '_', '_', 'N', ' ', ' ', '|', ' ', ' ', ' ', '|', 'N', ' ', ' ', '|', ' ', ' ', ' ', 'o', 'N', ' ', ' ', '|', 'N', ' ', ' ', '|', 'N', '_', '_', '|', '_', '_', '_', '_', '_', 'N', '\0'};
    
    while( (asciiGallowStage1[i] != '\0') ){

      if( (asciiGallowStage1[i] == 'N') ){
        cout << endl;
      }
      else{
        cout << asciiGallowStage1[i];
      }
      i++;

    }//end while for stage 1
    break;}

  case 2:{
    char asciiGallowStage2[] = {' ', ' ', ' ', '_', '_', '_', 'N', ' ', ' ', '|', ' ', ' ', ' ', '|', 'N', ' ', ' ', '|', ' ', ' ', ' ', 'o', 'N', ' ', ' ', '|', ' ', ' ', '\\', 'N', ' ', ' ', '|', 'N', '_', '_', '|', '_', '_', '_', '_', '_', 'N', '\0' };

    while( (asciiGallowStage2[i] != '\0') ){

      if( (asciiGallowStage2[i] == 'N') ){
        cout << endl;
      }
      else{
        cout << asciiGallowStage2[i];
      }
      i++;

    }//end while for stage 2
    break;}

  case 3:{
    char asciiGallowStage3[] = {' ', ' ', ' ', '_', '_', '_', 'N', ' ', ' ', '|', ' ', ' ', ' ', '|', 'N', ' ', ' ', '|', ' ', ' ', ' ', 'o', 'N', ' ', ' ', '|', ' ', ' ', '\\', '0', 'N', ' ', ' ', '|', 'N', '_', '_', '|', '_', '_', '_', '_', '_', 'N', '\0'};

    while( (asciiGallowStage3[i] != '\0') ){

      if( (asciiGallowStage3[i] == 'N') ){
        cout << endl;
      }
      else{
        cout << asciiGallowStage3[i];
      }
      i++;

    }//end while for stage 3
    break;}

  case 4:{
    char asciiGallowStage4[] = {' ', ' ', ' ', '_', '_', '_', 'N', ' ', ' ', '|', ' ', ' ', ' ', '|', 'N', ' ', ' ', '|', ' ', ' ', ' ', 'o', 'N', ' ', ' ', '|', ' ', ' ', '\\', '0', '/', 'N', ' ', ' ', '|', 'N', '_', '_', '|', '_', '_', '_', '_', '_', 'N', '\0'};

    while( (asciiGallowStage4[i] != '\0') ){

      if( (asciiGallowStage4[i] == 'N') ){
        cout << endl;
      }
      else{
        cout << asciiGallowStage4[i];
      }
      i++;

    }//end while for stage 4
    break;}

  case 5:{
    char asciiGallowStage5[] = {' ', ' ', ' ', '_', '_', '_', 'N', ' ', ' ', '|', ' ', ' ', ' ', '|', 'N', ' ', ' ', '|', ' ', ' ', ' ', 'o', 'N', ' ', ' ', '|', ' ', ' ', '\\', '0', '/', 'N', ' ', ' ', '|', ' ', ' ', '/', 'N', '_', '_', '|', '_', '_', '_', '_', '_', 'N', '\0'};

    while( (asciiGallowStage5[i] != '\0') ){

      if( (asciiGallowStage5[i] == 'N') ){
        cout << endl;
      }
      else{
        cout << asciiGallowStage5[i];
      }
      i++;

    }//end while for stage 5
    break;}

  case 6:{
    char asciiGallowStage6[] = {' ', ' ', ' ', '_', '_', '_', 'N', ' ', ' ', '|', ' ', ' ', ' ', '|', 'N', ' ', ' ', '|', ' ', ' ', ' ', 'o', 'N', ' ', ' ', '|', ' ', ' ', '\\', '0', '/', 'N', ' ', ' ', '|', ' ', ' ', '/', ' ', '\\', 'N', '_', '_', '|', '_', '_', '_', '_', '_','N', '\0'};

    while( (asciiGallowStage6[i] != '\0') ){

      if( (asciiGallowStage6[i] == 'N') ){
        cout << endl;
      }
      else{
        cout << asciiGallowStage6[i];
      }
      i++;

    }//end while for stage 6
    break;}

  default:
    cout << "Gallows did not draw for some reason..." << endl;

  }//end switch
  
}//end drawGallows

//A function to display the blanks and correct guesses, will use guessDisplayArray
void HangmanBoard::displayCorrectGuesses(){

  cout << "Word: ";
  //The following while loop will iterate through the guessDisplayArray and
  //display all values stored
  int i = 0;
  while( (guessDisplayArray[i] != '\0') ){

    cout << guessDisplayArray[i];
    i++;
    if( (guessDisplayArray[i] == '\0') ){
	  cout << endl;
	}

  }//end while

}//End displayCorrectGuesses

//A function to display guess misses, will use missedGuessList array
void HangmanBoard::displayMissedGuesses(){

  cout << "Misses: ";
  //The following while loop will iterate thrrough missedGuessList
  //and display all values stored
  int i = 0;
  while( (missedGuessList[i] != '\0') ){

    cout << missedGuessList[i]<< "  ";
    i++;
    if( (missedGuessList[i] == '\0')){
      cout << endl;
    }

  }//end while


}//end displayMissedGuesses

//A function to initialize the array that holds all of the blanks
//The int will represent the number of blanks to store
void HangmanBoard::initializeDisplayArray(int blanks){

  for(int i = 0; i < blanks; i++){

    guessDisplayArray[i] = '_';

    if( (i == (blanks - 1)) ){
      guessDisplayArray[(i + 1)] = '\0';
    }

  }//end for loop

}//end initializeDisplayArray

//A function to display the last guess made
void HangmanBoard::displayLastGuess(){

  cout << "Last guess was: " << lastGuess;

}//end displayLastGuess

//A function to clear the gameboard
void HangmanBoard::clearBoard(){

  //Initialize all values to zero or initial state
  setNumberOfBlanks(0);
  setNumberOfMisses(0);
  currentStage = 0;
  missedGuessList[0] = '\0';
  correctGuessList[0] = '\0';
  guessDisplayArray[0] = '\0';

}//end clearBoard

//The following will add the appropriate new char to the designated array
void HangmanBoard::updateMissedGuessList( char miss){
    
  int i = 0;
  int x = 0;
  //While iterating through the missedGuessList array search for the first empty spot
  //Then exchange the end with the new miss and add the escape sequence to the end
  do{

    if( (missedGuessList[i] == '\0') ){
       
      missedGuessList[i] = miss;
      missedGuessList[(i + 1)] = '\0';
      //if the above operation is completed we can change our flag so we can exit the loop
      x = 1;

    }

    i++;

  }while( (x == 0) );
  
}//end updateMissedGuessList

void HangmanBoard::updateCorrectGuessList( char correct){

  int i = 0;
  int x = 0;
  //While iterating through the correctGuessList array search for the first empty spot
  //Then exchange the end with the new correct guess and add theescape sequenceto the end
  do{

    if( (correctGuessList[i] == '\0') ){

      correctGuessList[i] = correct;
      correctGuessList[(i + 1)] = '\0';
      //if the above operation is completed we can change our flag so we can exit the loop
      x = 1;

    }

    i++;

  }while( (x == 0) );


}//end updateCorrectGuessList

void HangmanBoard::updateDisplayArray( char newLetter, int position){

  guessDisplayArray[ (position - 1) ] = newLetter;

}//end updateDisplayArray
 
//SETTERS
void HangmanBoard::setLastGuess( char currentGuess ){

  lastGuess = currentGuess;

}//end setLastGuess

void HangmanBoard::setNumberOfBlanks( int blanks){

  if(blanks != 0){
    initializeDisplayArray(blanks);
  }
  numberOfBlanks = blanks;

}//end setNumberOfBLanks

void HangmanBoard::setNumberOfMisses( int misses){

  numberOfMisses = misses;

}//end setNumberOfMisses

void HangmanBoard::setCurrentStage( int stage){

  currentStage = stage;

}//end setCurrentStage

//Getters
char HangmanBoard::getLastGuess(){

  return lastGuess;

}// end getLastGuess

int HangmanBoard::getNumberOfBlanks(){

  return numberOfBlanks;

}// end getNumberOfBlanks

int HangmanBoard::getNumberOfMisses(){

  return numberOfMisses;

}//end getNumberOfMisses

int HangmanBoard::getCurrentStage(){

  return currentStage;

}//end getCurrentStage

