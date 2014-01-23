/*
 * Title: Array.h
 * Author: Paul Prae
 * Last Edited: October 26th, 2010
 * Project 5 for CSCI 1730 with Doc Plaue
 * 
 * Purpose of this file and associated program:
 *
 *		This is the file Array.h which is part of Project 5 titled
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

// Array template class definition with overloaded operators.
#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
using namespace std;

template<typename elementType, int numberOfElements>
class Array
{
	//Probably will not convert these to template form
	//friend ostream &operator<<( ostream &, const Array & );
	//friend istream &operator>>( istream &, Array & );
	
public:

	//Constructor and destructor will also contain an output statement
	//that indicates which definition version is being called.
	Array(); 
	~Array(); // destructor
	int getSize() const; // return size
	
	bool operator==( const Array & ) const; // equality operator
	
	// inequality operator; returns opposite of == operator
	bool operator!=( const Array &right ) const;
	
	// subscript operator for non-const objects returns modifiable lvalue
	elementType &operator[]( int );              
	
	// subscript operator for const objects returns rvalue
	elementType operator[]( int ) const;  
	
	void inputArray(); //input the array elements
	//outputArray will also contain an output statement
	//that indicates which definition version is being called.
	void outputArray() const; //output the array elements
	
private:

	elementType elements[ numberOfElements ];
	static int arrayCount; // # of Arrays instantiated
	
}; // end class Array

#endif
