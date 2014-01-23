/*
 * Title: Array.cpp
 * Author: Paul Prae
 * Last Edited: October 26th, 2010
 * Project 5 for CSCI 1730 with Doc Plaue
 * 
 * Purpose of this file and associated program:
 *
 *		This is the file Array.cpp which is part of Project 5 titled
 * "Templates." This file will not begin program execution. This file
 * holds the class prototypes. The purpose of this array class is to 
 * enable Array objects to be instantiated with a specified number
 * of elements of a specified element type at compile time.
 *
 * Limitations of development resources:
 *     This code was written as directed by the instructions for Project
 * 5: Templates posted by Dr. Plaue on eLC at the University
 * of Georgia. It was written using concepts, ideas, and code presented
 * in class, on the eLC section for the class, from the textbook 
 * C++: How To Program Seventh Edition by Deitel and Deitel and its 
 * official online resources, and from http://www.cplusplus.com's 
 * Reference Libraries.
 * 
 * Statement of Academic Honesty:
 *     The following code represents my own work. I have neither
 * received nor given inappropriate assistance. I have not copied
 * or modified code from any source other than the course webpage,
 * eLC, or the course textbook and materials. I recognize that any 
 * unauthorized assistance or plagiarism will be handled in accordance
 * with the University of Georgia's Academic Honesty Policy and the
 * policies of this course.
 *
 *		As described in the Project 5 description, this project will
 * use code from the lecture slides. These slides have code from the
 * textbook which is under the following copyright:
 * (C) Copyright 1992-2010 by Deitel & Associates, Inc. and
 * Pearson Education, Inc. All Rights Reserved. 
 *
 * This project was created using Emacs and Xcode
 */

// Array class member- and friend-function definitions.
#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <cstdlib> // exit function prototype
#include "Array.h" // Array class definition
using namespace std;

//Constructor
template<typename elementType, int numberOfElements>
Array<elementType, numberOfElements>::Array()
{
	//Output the array type that is being created
	cout << "The constructor has been called for an Array of elementType: " << endl;
	cout << elementType().name() << endl;
	
	//Add default elements in the array to make sure space is allocated
	for( int count = 0; count < numberOfElements ; count++)
	{
			//Go through each elememnt in the array up to the array size
		elements[ count ] = elementType();
		
	}//end for
	
	//We must increment the number of Array objects that have been instantiated
	++arrayCount;
	cout << "arrayCount is now: " << arrayCount << "." << endl;
	
}//end constructor

//Destructor for class Array
template<typename elementType, int numberOfElements>
Array<elementType, numberOfElements>::~Array()
{
	//Output the array type that is being destroyed
	cout << "The destructor has been called for an Array of elementType: " << endl;
	cout << elementType().name() << endl;
	
	//We must decrement the number of Array objects in existence
	--arrayCount;
	cout << "arrayCount is now: " << arrayCount << "." << endl;
	
} // end destructor

// return number of elements of Array
template<typename elementType, int numberOfElements>
int Array<elementType, numberOfElements>::getSize() const
{
	return numberOfElements; // number of elements in Array
} // end function getSize
	
// determine if two Arrays are equal and
// return true, otherwise return false
template<typename elementType, int numberOfElements>	
bool Array<elementType, numberOfElements>::operator!=( const Array &right ) const
{

	//Take advantage of the opposite function
	return ! ( *this == right );
	
} // end function operator==	

// determine if two Arrays are equal and
// return true, otherwise return false
template<typename elementType, int numberOfElements>	
bool Array<elementType, numberOfElements>::operator==( const Array &right ) const
{
	//First check to make sure they are the same size
	if ( numberOfElements != right.numberOfElements )
		return false; // arrays of different number of elements
	
	for ( int i = 0; i < numberOfElements; i++ )
		if ( elements[ i ] != right.elements[ i ] )
			return false; // Array contents are not equal
	
	return true; // Arrays are equal
} // end function operator==

// overloaded subscript operator for non-const Arrays;
// reference return creates a modifiable lvalue
template<typename elementType, int numberOfElements>
elementType &Array<elementType, numberOfElements>::operator[]( int subscript )
{
	// check for subscript out-of-range error
	if ( subscript < 0 || subscript >= numberOfElements )
	{
		cerr << "\nError: Subscript " << subscript 
		<< " out of range" << endl;
		exit( 1 ); // terminate program; subscript out of range
	} // end if
	
	return elements[ subscript ]; // reference return
} // end function operator[]

// overloaded subscript operator for const Arrays
// const reference return creates an rvalue
template<typename elementType, int numberOfElements>
elementType Array<elementType, numberOfElements>::operator[]( int subscript ) const
{
	// check for subscript out-of-range error
	if ( subscript < 0 || subscript >= numberOfElements )
	{
		cerr << "\nError: Subscript " << subscript 
		<< " out of range" << endl;
		exit( 1 ); // terminate program; subscript out of range
	} // end if
	
	return elements[ subscript ]; // returns copy of this element
} // end function operator[]

//Might not use
/*
// overloaded input operator for class Array;
// inputs values for entire Array
template<typename elementType, int numberOfElements>
istream &operator>>( istream &input, Array &a )
{
	for ( int i = 0; i < a.numberOfElements; i++ )
		input >> a.elements[ i ];
	
	return input; // enables cin >> x >> y;
} // end function 

// overloaded output operator for class Array 
template<typename elementType, int numberOfElements>
ostream &operator<<( ostream &output, const Array &a )
{
	int i;
	
	// output private ptr-based array 
	for ( i = 0; i < a.numberOfElements; i++ )
	{
		output << setw( 12 ) << a.elements[ i ];
		
		if ( ( i + 1 ) % 4 == 0 ) // 4 numbers per row of output
			output << endl;
	} // end for
	
	if ( i % 4 != 0 ) // end last line of output
		output << endl;
	
	return output; // enables cout << x << y;
} // end function operator<<
*/	

//A function to input elements into the array from the user
template<typename elementType, int numberOfElements>
void Array<elementType, numberOfElements>::inputArray()
{
	bool endOfArray = false;
	
	//A variable to hold user input
	elementType userInput;
	
	//If there are no elements then there is no space
	if(numberOfElements == 0)
		endOfArray = true;
	
	//A loop to get all of the input from the user for each spot in the array
	for( int i = 0; i < numberOfElements ; i++ )
	{
		if(endOfArray)
		{
			cout << "There is no more space in the array. Input will stop." << endl;
		}else{
			cout << "Please enter a value for the element in position ";
			cout << i << ": " << endl;
		
			cin << userInput;
			elements[ i ] = userInput;
				
		}
		if( (i + 1) == numberOfElements )
			endOfArray = true;
		
	}//end for
	
	
		
}//end function input array

//A function to output elements of the array to the user
template<typename elementType, int numberOfElements>
void Array<elementType, numberOfElements>::outputArray() const
{

	int i;

	//Output the array type that is being printed
	cout << "The outputArray function has been called for an Array of elementType: " << endl;
	cout << elementType().name() << endl;
	
	// output array 
	for ( i = 0; i < numberOfElements; i++ )
	{
		cout << setw( 12 ) << elements[ i ];
		
		if ( ( i + 1 ) % 4 == 0 ) // 4 numbers per row of output
			cout << endl;
	} // end for
	
	if ( i % 4 != 0 ) // end last line of output
		cout << endl;
	
}//end function output array




//This will hold the number of Array objects that have been instantiated
//Each class-template specialization will have its own copy.
template<typename elementType, int numberOfElements>
int Array<elementType, numberOfElements>::arrayCount = 0;
