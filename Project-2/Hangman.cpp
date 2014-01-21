/*
 * Title: Hangman.cpp
 * Author: Paul Prae
 * Last Edited: September 14th, 2010
 * Project 2 for CSCI 1730 with Doc
 * 
 * Purpose of this file and associated program:
 *
 *     This is the file Hangman.cpp which is part of Project 2 titled
 * "Hangman++." This file will begin program execution. This is the 
 * file HangmanGame.cpp which holds the main class. 
 * The purpose of the Hangman class is to use the main method
 * to run Hangman++ the game.
 *     The main program is to serve the following purpose:
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
#include <stdlib.h>
#include <fstream>

using namespace std;

//function main begins program execution

int main(int argc, char* argv[]){

  cout << "Welcome to Hangman++!!!" << endl;

  //Draw Board
  char asciiGallowStage0[] = {' ', ' ', ' ', '_', '_', '_', 'N', ' ', ' ', '|', ' ', ' ', ' ', '|', 'N', ' ', ' ', '|', 'N', ' ', ' ', '|', 'N', ' ', ' ', '|', 'N', '_', '_', '|', '_', '_', '_', '_', '_', '\
N', '\0'};
  int count = 0;
  while( (asciiGallowStage0[count] != '\0') ){

    if( (asciiGallowStage0[count] == 'N') ){
      cout << endl;
    }
    else{
      cout << asciiGallowStage0[count];
    }
    count++;

  }//end while for stage 0

  //Variable to hold user input
  int operatorBlanks = 0;
  int currentIntInput = 0;
  char currentCharInput = 'n';
  //A string to hold the type of guesser, default human
  string guesserType("human");
  //A boolean to hold whether to log the file, default is false
  bool logFile = false;


  //A for loop that will look for command line prompts
  //The values detected will be stored appropriately
  for(int i = 1; i < argc; i++){

    string tempString(argv[i]);
    //First check to see if the value is for the human call for a guesser
    if( (tempString.compare("human") == 0) ){
      guesserType = "human";

    }else{//Then maybe it is the user telling the computer to guess
      if( (tempString.compare("computer") == 0) ){
	guesserType = "computer";

      }else{//Then maybe it is the flag to log the file
	if( (tempString.compare("-L") == 0) ){
	  logFile = true;

	}else{//Then it must be a number representing blanks
	  //convert string to int
	  operatorBlanks = atoi(argv[i]);

	}//end inner most else
      }
    }//end outmost else
  }//end for

  cout << "Logging the file has been set to: ";
  if(logFile){
    cout << "true." << endl;
  }else{ cout << "false." << endl; }

  cout << "Always enter \"-L\" in the command line when running the executable program" << endl;
  cout << "if you need to log the file." << endl;
  if(logFile){

    //ofstream constructor opens file
    ofstream outLogFile( "Hangman.log", ios::out );

    // exit program if unable to creat file
    if( !outLogFile ){

      cerr << "File could not be opened" << endl;
      exit( 1);

    }//end if

  }//end if logfile

  cout << endl;
  cout << "According to my data, the " << guesserType << " will be doing the guessing." << endl;
  cout << "Operator, is this ok? Please enter a lowercase character value y or n." << endl;

  cin >> currentCharInput;

  if(currentCharInput == 'y'){
    cout << "Great! We will continue then." << endl;

  }else{

    cout << "Operator, please enter which type of guesser there will be." << endl;
    cout << "You may only enter the exact lowercase string of \"computer\" OR\" human\":" << endl;
    cin >> guesserType;
    cout << "Thank you! We will continue." << endl << endl;

    operatorBlanks = currentIntInput;

  }


  cout << "Operator, currently your blanks are set to = " << operatorBlanks << "." << endl;
  cout << "Operator, is this ok? Please enter a lowercase character value y or n." << endl;

  cin >> currentCharInput;

  if(currentCharInput == 'y'){
    cout << "Great! We will continue then." << endl;

  }else{

    cout << "Operator, please enter an integer value that represents the amount of" << endl;
    cout << "characters in your word for the game Hangman:" << endl;
    cin >> currentIntInput;
    cout << "Thank you! We will begin." << endl << endl;

    operatorBlanks = currentIntInput;

  }

  //Creat a new game
  HangmanGame currentGame(guesserType, operatorBlanks);

  //Creat a new board to begin
  HangmanBoard newBoard(operatorBlanks);

  //Start the game, while keepPlaying is true the game will be played again
  bool keepPlaying = true;
  while(keepPlaying){

    cout << "Are both players ready to play Hangman++?" << endl;
    cout << "Please enter a lowercase character of y or n: " << endl;
    cin >> currentCharInput;

    if(currentCharInput == 'y'){

      currentGame.setContinueGame( true );
      
      //Decide which type of game to play, then play it
      if( (guesserType.compare("human") == 0) ){
	currentGame.playHumanGame(newBoard);
      }else{currentGame.playComputerGame(newBoard);}

      cout << "Wonderful game! Would you like to keep playing?" << endl;
      cout << "Please enter a lowercase character of y or n: " <<endl;
      cin >> currentCharInput;

      if(currentCharInput== 'n'){
	keepPlaying = false;
      }//end if
    }//end if
    else{
      keepPlaying = false;
    }//end else

  }//end while

  string guesserWon("false");

  if(currentGame.checkForWin(newBoard)){
    guesserWon = "true";
  }

  //Attempt to output to log file
  //outLogFile << "Guesser: " <<  guesserType << ". Blanks: " << operatorBlanks <<  ". Guesser won?: " << guesserWon << endl << "end-of-file";

  cout << "GAMEOVER" << endl;

}//end main
