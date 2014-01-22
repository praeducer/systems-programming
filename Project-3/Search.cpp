/*
 * Title: Search.cpp
 * Author: Paul Prae
 * Last Edited: September 30th, 2010
 * Project 3 for CSCI 1730 with Doc Plaue
 * 
 * Purpose of this file and associated program:
 *
 *     This is the file Search.cpp which is part of Project 3 titled 
 * "Practice with File Input/Output." This file will not begin program 
 * execution. This file holds the class function definitions. The purpose 
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

#include "Search.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cctype>

using namespace std;

//CONSTRUCTORS
// Constructor that initializes the object
Search::Search(vector< char > &newPhoneNumber){

	
	//Store phone number
	userPhoneNumber = newPhoneNumber;

	//Initialize all values to zero except those regarding the user entered phone number
	setPhoneNumberSize(0);
	//NOTE: This function sets phoneNumberSize
	//to actual length
	setPhoneNumber(newPhoneNumber);
	
	solutions.clear();
	currentCharMatches.clear();

	setMatchFound(false);
	setIsTwoLines(false);

	setNumberOfMatches(0);
	setCurrentLineIndex(0);
	setCurrentLineNumber(1);
	

}//end single arg constructor
  
//FUNCTIONS
//A function to search through a vector and find a mnemonic
void Search::vectorSearch(vector< char > &searchSpace)
{
	//A vector iterator to search through the search space one character at a time
	vector< char >::iterator mainIterator;
	//Assign the beginning of the vector to the iterator
	mainIterator = searchSpace.begin();
	
	//Set the first line iterator to the beginning of the vector
	setCurrentLineIterator( mainIterator );

	//A vector iterator to search through a possible sequence of characters that
	//are matching the phoneNumber
	vector< char >::iterator subSearchIterator;

	//A vector iterator to store the location of the first match in a mnemonic
	vector< char >::iterator mnemonicLocation;	
	
	/* While EOF has not been reached iterate through all characters and find 
	 * mnemonic matches with all alphabet characters found. The end of the vector
	 * can be found by making sure the current memory location does not equal the
	 * end of the vector
	 */
	while( ( mainIterator != searchSpace.end() ) )
	{
		
		//If the current char is the next line then update the next line index
		if( *mainIterator == '\n' )
		{
			//To find the current index of the searchSpace vector we are 
			//accessing we simply need to subtract begin() from the
			//iterator
			setCurrentLineIndex( (mainIterator - searchSpace.begin()) );
			++currentLineNumber;
			//We also need to stare the memory location of the iterator
			setCurrentLineIterator( mainIterator );
	
		}//end if
		
		//Check if character is nextline, passing in true because this is the outerloop
		if( !(*mainIterator == '\n') )
		{		
			
			//If the current char is a part of the alphabet
			//then see if it is match to the first char of a mnemonic
			if( isalpha( *mainIterator ) )
			{
				//If it is a match then store the current index of the 
				// vector in mnemonicLocation
				//Since this is the first char to check we will check index 0		
				if( isCharAMatch( *mainIterator, 0 ) )
				{
					
					//If the current char is a match then add it to the matched char list
					appendCurrentCharMatches( *mainIterator );

					
					//Set location of match found
					mnemonicLocation = mainIterator;

					//Set the subSearchIterator location to the location following the 
					//mainIterator. This new iterator will continue to check for a possible
					//mnemonic match.
					subSearchIterator = ( mainIterator + 1 );

					/* If there is a first char match then loop through the following chars
					 * and see if there is a full mnemonic match.
					 * Loop until there is a complete match or the matching fails or we have
					 * checked all possible chars in the phoneNumber or we have reached
					 * an EOF(end of our search space).
					 * The match must be a alphabetic character and a match.
					 * The loop will ignore symbols.
					 * It will stop at digits and nonmatching alphabet characters
					 */
					for( size_t indexToCheck = 1; ( subSearchIterator != searchSpace.end() ) &&
						( indexToCheck < getPhoneNumberSize() ) &&
						( 
							( !isdigit( *subSearchIterator ) ) && 
							(
								( ( isalpha( *subSearchIterator ) ) && ( isCharAMatch( *subSearchIterator, indexToCheck ) ) ) ||
								( ( !isalpha( *subSearchIterator ) ) && ( !isCharAMatch( *subSearchIterator, indexToCheck ) ) )
							 )
						 )
						; )
					{

							//If the current char is an alphabet character and a match
							if ( ( isalpha( *subSearchIterator ) ) &&
								( isCharAMatch( *subSearchIterator, indexToCheck ) ) )
							{
								//If the current char is a match then add it 
								//to the matched char list
								appendCurrentCharMatches( *subSearchIterator );						
								
								//If a full mnemonic match was found set boolean to say so
								//If everything up to current char is a match
								//and we have checked as many values as there are numbers
								//then we have a match
								if( (indexToCheck + 1) == getPhoneNumberSize() )
								{
									setMatchFound(true);

								}//end if
								
								indexToCheck++;

							}//end if
							
						
						
							//Increment subSearchIterator to next char to check
							
							++subSearchIterator;


					}//end for loop

					//If there was a full match, then check to see if there is a char after 
					//the last matched char. If so, append the rest of the word until a 
					//blank to the mnemonic vector
					if( getMatchFound() )
					{
						while( ( subSearchIterator != searchSpace.end() ) &&
							( isalpha( *subSearchIterator ) )
							)
						{
							appendCurrentCharMatches( *subSearchIterator );

							//Increment subSearchIterator to next char to check
							++subSearchIterator;

						}//end while loop
						

					}//end if getMatchFound 1st

					//If there was a complete mnemonic match then add everything necessary
					//to solutions vector and increase match counter
					//Add line number
					//Add context. This will be the current line and the next line if needed
					//Add the full mnemonic, this includes finishing the last word if needed
					if( getMatchFound() )
					{
						numberOfMatches++;

						/* appendNewSolutions will be able to access all information through
						 *current object data. It will only need a context vector.
						 *We must copy the searchSpace vector from the last next line to 
						 *up to 100 characters
						 */
						vector< char > contextVector;
						
						
						//Creat an iterator that will start at the last line found in searchSpace
						vector< char >::iterator contextIterator;
						contextIterator = getCurrentLineIterator();
						//Increment it past the next line character
						++contextIterator;
											
						//create a contexx vector by taking all characters from the searchVector from the 
						//beginning of the last next line all the way up to 30 characters passed the last 
						//menmonic match
						//Make sure not to go out of bounds
						while( ( contextIterator != searchSpace.end() ) && ( contextIterator < (mnemonicLocation + 30 ) ) )
						{
							
							//First check to make sure that we do not go out of bounds
							if( ( contextIterator != searchSpace.end() ) )
							{
								contextVector.push_back( *contextIterator );
								
							}//end if
							
							//Increment to next char.
							++contextIterator;
							
						}//end while loop
						
						//! check what happens here and see if could possibly reset iterators
						appendNewSolutions( contextVector );					

					}//end if getMatchFound 2nd

				}//if isCharAMatch

			}// end if isalpha

		}//end most outer if 

		//Make sure iterator is where it needs to be for next char by incrementing
		++mainIterator;

		//Reset all values for sub set solution search
		currentCharMatches.clear();
		setMatchFound(false);
		

	}//end while
	

}//end vectorSearch



//A function that will check a given char against a number in the phone number
//Will return a bool, if it is true then a match was found
bool Search::isCharAMatch(char checkChar, int rowIndex)
{
	
	//Search through the two dimensional vector and compare the checkChar
	//to all possible characters of the given index from phoneNumber
	for( int columnIndex = 0; columnIndex < phoneNumber[ rowIndex ].size(); columnIndex++ )
	{	
		//If there is a char match in the column of the number return true
		if( phoneNumber[ rowIndex ][ columnIndex ] == checkChar )
		{

			return true;

		}//end if
	}//end for loop
	
	//If true was not returned then there was not match
	return false;

}//end isCharAMatch

//Add a char to currentCharMatches
void Search::appendCurrentCharMatches(char charMatch)
{	
	currentCharMatches.push_back( charMatch );

}//end appendCurrentCharMatches

//A function to append new results to the solutions vector
//If this is the first match found initialize the vector
void Search::appendNewSolutions(vector< char > &context)
{
	
	//Creat an iterator that will be used to navigate through vectors to copy them
	vector< char >::iterator tempIterator;	
	
	//Add current line number to solutions vector with correct formatting
	solutions.push_back( '\n');
	solutions.push_back( '1');
	solutions.push_back( '.');
	solutions.push_back( ' ');
	
	//convert int line number to char
	ostringstream tempStream;
	tempStream << getCurrentLineNumber();
	string integerString = tempStream.str();
	
	//For the length of the line number add each character digit to vector
	for(int index = 0; index < integerString.length(); index++)
	{
		solutions.push_back( integerString[index] );
	

	}//end for loop
	solutions.push_back( '\n');

	//Add the context vector to the solutions vector
	solutions.push_back( '\n');
	solutions.push_back( '2');
	solutions.push_back( '.');
	solutions.push_back( ' ');
	//Set temp iterator to start at the beginning of context vector
	//Copy context iterator onto back of solutions
	tempIterator = context.begin();
	solutions.push_back( '~');
	while( ( tempIterator != context.end() ) )
	{
		solutions.push_back( *tempIterator );
		tempIterator++;
		
	}//end for loop
	solutions.push_back( '~');
	
	//Add the mnemonic vector to the solutions vector
	solutions.push_back( '\n');
	solutions.push_back( '\n');
	solutions.push_back( '3');
	solutions.push_back( '.');
	solutions.push_back( ' ');
	//Set temp iterator to start at the beginning of currentCharMatches
	//Copy currentCharMatches iterator onto back of solutions
	tempIterator = currentCharMatches.begin();
	while( ( tempIterator != currentCharMatches.end() ) )
	{
		solutions.push_back( *tempIterator );	
		tempIterator++;
		
	}//end for loop
	
	solutions.push_back( '\n');
	

}//end appendNewSolutions

//A function to print the results of a search
void Search::printResults()
{
	cout << "-------------------" << endl;
	cout << "There are " << getNumberOfMatches() << " mnemonic matches ";
	cout << "for the number (";
	printVector( userPhoneNumber );
	cout  << ")" << endl;
	cout << "-------------------" << endl << endl;
	cout << "The mnemonic matches were as follows-" << endl;
	cout << "FORMAT" << endl;
	cout << "1. The line number of the match." << endl;
	cout << "2. The context of the match." << endl;
	cout << "3. The resulting mnemonic." << endl;
	cout << "-------------------" << endl;
	printVector( solutions );
	cout << "-------------------" << endl;

}//end printResults

//A function to print vectors
template < typename T > void Search::printVector( const vector< T > &vector1 )
{
	//const iterator
	typename vector< T >::const_iterator constIterator;
	
	//display vector elements using const_iterator
	for( constIterator = vector1.begin(); constIterator != vector1.end(); ++constIterator )
	{	
		cout << *constIterator;

	}//end for loop

}//end printVector

//Mutators

//The following will set the amount of character digits used in the phone number
void Search::setPhoneNumberSize( size_t size )
{
	phoneNumberSize = size;

}//end setPhoneNumberSize

//Set the phone number to a two dimensional vector
//The row will be the phone number
//The column will be the acceptable letters for the corresponding number
void Search::setPhoneNumber(vector< char > &newPhoneNumber)
{
	//For the length of the user inputted phone number array
	//Create a more useful array for searching and comparing
	for ( size_t i = 0; i < newPhoneNumber.size(); i++ )
	{
		
		//Create an empty vector to push onto 2-dim array of vectors
		//This vector will be pushed onto the next row each time loop
		//iterates. Initialized to size one because it will dynamically
		//expand to fit more chars
		vector < char > tempVector(1);
		
		//This switch statement will store ONLY the numbers
		//that will be used for comparisons and then the 
		//alphabetic characters that go with that number. 
		switch ( newPhoneNumber[ i ] )
		{

			case '2':
				phoneNumber.push_back( tempVector );
				phoneNumber[ phoneNumberSize ].push_back( 'a' );
				phoneNumber[ phoneNumberSize ].push_back( 'b' );
				phoneNumber[ phoneNumberSize ].push_back( 'c' );
				phoneNumber[ phoneNumberSize ].push_back( 'A' );
				phoneNumber[ phoneNumberSize ].push_back( 'B' );
				phoneNumber[ phoneNumberSize ].push_back( 'C' );
				//A new number is stored so increment size
				phoneNumberSize++;
				break;

			case '3':
				phoneNumber.push_back( tempVector );
				phoneNumber[ phoneNumberSize ].push_back( 'd' );
				phoneNumber[ phoneNumberSize ].push_back( 'e' );
				phoneNumber[ phoneNumberSize ].push_back( 'f' );
				phoneNumber[ phoneNumberSize ].push_back( 'D' );
				phoneNumber[ phoneNumberSize ].push_back( 'E' );
				phoneNumber[ phoneNumberSize ].push_back( 'F' );
				//A new number is stored so increment size
				phoneNumberSize++;
				break;

			case '4':
				phoneNumber.push_back( tempVector );				
				phoneNumber[ phoneNumberSize ].push_back( 'g' );
				phoneNumber[ phoneNumberSize ].push_back( 'h' );
				phoneNumber[ phoneNumberSize ].push_back( 'i' );
				phoneNumber[ phoneNumberSize ].push_back( 'G' );
				phoneNumber[ phoneNumberSize ].push_back( 'H' );
				phoneNumber[ phoneNumberSize ].push_back( 'I' );
				//A new number is stored so increment size
				phoneNumberSize++;
				break;

			case '5':
				phoneNumber.push_back( tempVector );
				phoneNumber[ phoneNumberSize ].push_back( 'j' );
				phoneNumber[ phoneNumberSize ].push_back( 'k' );
				phoneNumber[ phoneNumberSize ].push_back( 'l' );
				phoneNumber[ phoneNumberSize ].push_back( 'J' );
				phoneNumber[ phoneNumberSize ].push_back( 'K' );
				phoneNumber[ phoneNumberSize ].push_back( 'L' );
				//A new number is stored so increment size
				phoneNumberSize++;
				break;

			case '6':
				phoneNumber.push_back( tempVector );
				phoneNumber[ phoneNumberSize ].push_back( 'm' );
				phoneNumber[ phoneNumberSize ].push_back( 'n' );
				phoneNumber[ phoneNumberSize ].push_back( 'o' );
				phoneNumber[ phoneNumberSize ].push_back( 'M' );
				phoneNumber[ phoneNumberSize ].push_back( 'N' );
				phoneNumber[ phoneNumberSize ].push_back( 'O' );
				//A new number is stored so increment size
				phoneNumberSize++;
				break;

			case '7':
				phoneNumber.push_back( tempVector );
				phoneNumber[ phoneNumberSize ].push_back( 'p' );
				phoneNumber[ phoneNumberSize ].push_back( 'q' );
				phoneNumber[ phoneNumberSize ].push_back( 'r' );
				phoneNumber[ phoneNumberSize ].push_back( 's' );
				phoneNumber[ phoneNumberSize ].push_back( 'P' );
				phoneNumber[ phoneNumberSize ].push_back( 'Q' );
				phoneNumber[ phoneNumberSize ].push_back( 'R' );
				phoneNumber[ phoneNumberSize ].push_back( 'S' );
				//A new number is stored so increment size
				phoneNumberSize++;
				break;

			case '8':
				phoneNumber.push_back( tempVector );
				phoneNumber[ phoneNumberSize ].push_back( 't' );
				phoneNumber[ phoneNumberSize ].push_back( 'u' );
				phoneNumber[ phoneNumberSize ].push_back( 'v' );
				phoneNumber[ phoneNumberSize ].push_back( 'T' );
				phoneNumber[ phoneNumberSize ].push_back( 'U' );
				phoneNumber[ phoneNumberSize ].push_back( 'V' );
				//A new number is stored so increment size
				phoneNumberSize++;
				break;

			case '9':
				phoneNumber.push_back( tempVector );
				phoneNumber[ phoneNumberSize ].push_back( 'w' );
				phoneNumber[ phoneNumberSize ].push_back( 'x' );
				phoneNumber[ phoneNumberSize ].push_back( 'y' );
				phoneNumber[ phoneNumberSize ].push_back( 'z' );
				phoneNumber[ phoneNumberSize ].push_back( 'W' );
				phoneNumber[ phoneNumberSize ].push_back( 'X' );
				phoneNumber[ phoneNumberSize ].push_back( 'Y' );
				phoneNumber[ phoneNumberSize ].push_back( 'Z' );
				//A new number is stored so increment size
				phoneNumberSize++;
				break;

			default:
				//Do nothing, all other characters are not needed
				break;

		}//end switch statement	

	}//end for loop

	
}//end setPhoneNumber

//A function to set the status of the matching process
void Search::setMatchFound(bool status)
{
	matchFound = status;

}//end setMatchFound

//A function to set the number of matches that have been found
void Search::setNumberOfMatches(int matches)
{
	numberOfMatches = matches;

}//end setNumberOfMatches

//A function to set the index location of the last next line encountered
void Search::setCurrentLineIndex(int index)
{
	currentLineIndex = index;	

}//end setCurrentLineIndex

//A function to acces index of last next line encountered
void Search::setCurrentLineNumber( int lineNumber )
{
	currentLineNumber = lineNumber;

}//end setCurrentLineNumber

//A function to set any iterator to currentLineIterator
//Will be used to mark placement of last next line encountered
void Search::setCurrentLineIterator( vector< char >::iterator lineIterator )
{
	currentLineIterator = lineIterator;
	
}//end setCurrentLineIterator

//A function to set a value that represents that the mnemonic is on two lines
void Search::setIsTwoLines( bool value)
{
	isTwoLines = value;

}//end setIsTwoLines


//Accessors
//A function to return the number of chars that have been matched as a mnemonic
size_t Search::getCharMatchesSize()
{
	return currentCharMatches.size();

}//end getCharMatchNumber

//A function to return the number of character numbers in phone number
size_t Search::getPhoneNumberSize()
{
	return phoneNumber.size();

}//end getPhoneNumberSize

//A function to get the status of the matching process
bool Search::getMatchFound()
{
	return matchFound;

}//end getMatchFound

//A function to set the number of matches that have been found
int Search::getNumberOfMatches()
{
	return numberOfMatches;

}//end getNumberOfMatches

//A function to get the vector index of the last time a next line was found
int Search::getCurrentLineIndex()
{
	return currentLineIndex;	

}//end getCurrentLineIndex

//A function to get the current line number that is being processed
int Search::getCurrentLineNumber()
{
	return currentLineNumber;

}//end getCurrentLineNumber

//A function to get any iterator to currentLineIterator
//Will be used to return placement of last next line encountered
vector< char >::iterator Search::getCurrentLineIterator()
{
	return currentLineIterator;
	
}//end setCurrentLineIterator

//A function to get a value that represents that the mnemonic is on two lines
bool Search::getIsTwoLines()
{
	return isTwoLines;

}//end setIsTwoLines
