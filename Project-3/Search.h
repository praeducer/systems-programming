/*
 * Title: Search.h
 * Author: Paul Prae
 * Last Edited: September 30th, 2010
 * Project 3 for CSCI 1730 with Doc Plaue
 * 
 * Purpose of this file and associated program:
 *
 *     This is the file Search.h which is part of Project 3 titled 
 * "Practice with File Input/Output." This file will not begin program 
 * execution. This file holds the class prototypes. The purpose 
 * of the Search class is to implement the functionality and logic of 
 * searching through the data structure that is passed to it given
 * an element to find.
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

#include <vector>
#include <iterator>
#include <cctype>

using namespace std;

//Search class definition
class Search
{
public:	

	//CONSTRUCTORS
	// Constructor that initializes the object
	Search(vector< char > &newPhoneNumber);

	//FUNCTIONS
	//A function to search through a vector and find a mnemonic
	void vectorSearch(vector< char > &searchSpace);

	
	//A function that will check a given char against a number in the phone number
	//Will return a bool, if it is true then a match was found
	bool isCharAMatch(char checkChar, int rowIndex);

	//Add a char to currentCharMatches
	void appendCurrentCharMatches(char charMatch);

	//A function to append new results to the solutions vector
	//If this is the first match found initialize the vector
	void appendNewSolutions(vector< char > &context);

	//A function to print the results of a search 
	void printResults();

	//A function to print vectors
	template < typename T > void printVector( const vector< T > &vector1 );

	//Mutators
	//The following will set the amount of character digits used in the phone number
	void setPhoneNumberSize(size_t size);

	//Set the phone number to a two dimensional vector
	//The row will be the phone number
	//The column will be the acceptable letters for the corresponding number
	void setPhoneNumber(vector< char > &newPhoneNumber);

	//A function to set the status of the matching process
	void setMatchFound(bool status);

	//A function to set the number of matches that have been found
	void setNumberOfMatches(int matches);

	//A function to set the index location of the last next line encountered
	void setCurrentLineIndex(int index);

	//A function to set the line number that is being processed
	void setCurrentLineNumber( int lineNumber );
	
	//A function to set any iterator to currentLineIterator
	//Will be used to mark placement of last next line encountered
	void setCurrentLineIterator( vector< char >::iterator );

	//A function to set a value that represents that the mnemonic is on two lines
	void setIsTwoLines( bool value);

	//Accessors
	//A function to return the number of chars that have been matched as a mnemonic
	size_t getCharMatchesSize();

	//A function to return the number of character numbers in phone number
	size_t getPhoneNumberSize();

	//A function to get the status of the matching process
	bool getMatchFound();

	//A function to set the number of matches that have been found
	int getNumberOfMatches();

	//A function to get the vector index of the last time a next line was found
	int getCurrentLineIndex();

	//A function to get the current line number that is being processed
	int getCurrentLineNumber();

	//A function to get any iterator to currentLineIterator
	//Will be used to return placement of last next line encountered
	vector< char >::iterator getCurrentLineIterator();	
	
	//A function to get a value that represents that the mnemonic is on two lines
	bool getIsTwoLines();

private:

	//A vector to store the users phone number
	vector < char > userPhoneNumber;
	//A 2-dim vector to hold the alphabet character representations
	//The users phoen number
	vector < vector < char > > phoneNumber;
	//A vector to hold the mnemonic matches
	vector < char > solutions;
	//A vector to hold the current character matches
	vector < char > currentCharMatches;
	
	//An iterator to hold the nextLine place
	vector< char >::iterator currentLineIterator;
	
	//A boolean to hold whether a match was just found
	bool matchFound;
	//A boolean to hold whether the mnemonic covered two lines
	bool isTwoLines;
	
	//An int to hold the size of the phone number
	size_t phoneNumberSize;
	//An integer to hold the amount of full matches found
	int numberOfMatches;
	//A number to hold the current line index of the main vector
	int currentLineIndex;
	//A number to hold the line number that is being processed
	int currentLineNumber;
	
	
	

};//end class Search
