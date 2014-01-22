/*
 * Title: CS1730Mnemonic.cpp
 * Author: Paul Prae
 * Last Edited: September 30th, 2010
 * Project 3 for CSCI 1730 with Doc Plaue
 * 
 * Purpose of this file and associated program:
 *
 *     This is the file Mnemonic.cpp which is part of Project 3 titled 
 * "Practice with File Input/Output." This file will begin program 
 * execution. 
 *     The associated main program is to serve the following purpose:
 * To write a program that is given as input through the command prompt
 * a phone number of 10 digits and a text document. The program will need
 * to find the matches for the mnemonics of the phone number in the text.
 *
 * Limitations of development resources:
 *     This code was written as directed by the instructions for Project
 * 3: Part II-Mnemonics posted by Dr. Plaue on eLC at the University
 * of Georgia. It was written using concepts, ideas, and code presented
 * in class, on the eLC section for the class, in the textbook C++: How
 * To Program Seventh Edition by Deitel and Deitel, and from
 * http://www.cplusplus.com's Reference Libraries.
 * 
 * Statement of Academic Honesty:
 *     The following code represents my own work. I have neither
 * received nor given inappropriate assistance. I have not copied
 * or modified code from any source other than the course webpage,
 * eLC, or the course textbook. I recognize that any unauthorized
 * assistance or plagiarism will be handled in accordance with the
 * University of Georgia's Academic Honesty Policy and the policies 
 * of this course.
 *
 * This project was created using Emacs and Xcode
 */

#include "Search.h"

#include <iostream>
#include <iomanip>
#include <istream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cctype>

using namespace std;


//function main begins program execution

int main(int argc, char* argv[]){
	
	//Check to make sure the user entered only one argument
	//No more and no less
	if( (argc == 1) || (argc > 2) )
	{
		
		cout << "The user has entered an incorrect amount of arguments." << endl;
		cout << "The program will terminate. Please only enter a phone number" << endl;
		cout << "and a file for input." << endl;
		return 1;
		
	}//end if

	//First store the phone number that should have been passed
	//in as a command line argument
	char* newPhoneNumber = argv[1];
	
	//An integer to cound the amount of digits entered into the command line
	int digitCounter = 0;
	
	//A vector to hold the char array from the user
	vector < char > userPhoneNumber;
	
	//A for loop to add the char array elements to the new vector
	for( int index = 0; newPhoneNumber[index] != '\0'; index++)
	{
		if ( isalpha( newPhoneNumber[index] ) )
			{
				cout << "The user entered an alphabetic character into the command line.";
				cout << endl << "This character will be ignored and processing will continue.";
				cout << endl;
			}//
		//if it is a digit then push onto vector
		if( isdigit( newPhoneNumber[index] ) )
		   {
			   digitCounter++;
			   userPhoneNumber.push_back( newPhoneNumber[index] );
		   }//end if
		   
	}//end for loop
			
	//If no digits were detected cancel program
	if( digitCounter == 0)
	{
		cout << "No digits were detected in first command line argument." << endl;
		cout << "Program will terminate. Please try again and specify a number and file." << endl;
		return 1;
		
	}//end if
	
	//Store all of the characters from the input stream
	//provided by the text into a vector for searching
	
	//A vector to hold all of the text file input for easy
	//processing
	vector < char > charVector;
	
	//If no input detected warn user and terminate program
	//First use peek and see if fail bit is set
	
	if( (cin.peek() == cin.eof()) || cin.eof() || !cin.good() || !cin )
	{
		cout << "No input stream detected. Program will terminate." << endl;
		cout << "Please try again and specify a number and correct file." << endl;
		return 1;		
	}//end if
	
	//While there is still input push each character onto vector
	while( cin.good() )
	{
		//Push current char onto the vector
		charVector.push_back( cin.get() );
		
	}//end while
	
	//Create a search object to find the user's mnemonic matches
	//in the text file
	Search newSearch( userPhoneNumber );
	
	//Search the file for the number
	newSearch.vectorSearch( charVector );
	
	//Display results
	newSearch.printResults();

	cout << endl << endl << "END PROGRAM EXECUTION" << endl;
	
}//end main
