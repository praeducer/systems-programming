/*
 * Title: Project5Prae.cpp
 * Author: Paul Prae
 * Last Edited: October 26th, 2010
 * Project 5 for CSCI 1730 with Doc Plaue
 * 
 * Purpose of this file and associated program:
 *
 *		This is the file Project5Prae.cpp which is part of Project 5 titled
 * "Templates." This file will begin program execution. This file will
 * test the Array template class. This is a driver.
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
 * This project was created using Emacs and Xcode
 */

#include <iostream>
#include "Array.h"
using namespace std;

int main()
{

	Array< int, 7 > integers1; // seven-element Array
	Array< int, 10 > integers2; // 10-element Array
	/*
	// print integers1 size and contents
	cout << "Size of Array integers1 is " 
	<< integers1.getSize()
	<< "\nArray after initialization:\n";
	integers1.outputArray();
	
	// print integers2 size and contents
	cout << "\nSize of Array integers2 is " 
	<< integers2.getSize()
	<< "\nArray after initialization:\n";
	integers2.outputArray();
	
	// input and print integers1 and integers2
	integers1.inputArray();
	integers2.inputArray();
	
	integers1.outputArray();
	integers2.outputArray();
	
	// use overloaded inequality (!=) operator
	cout << "\nEvaluating: integers1 != integers2" << endl;
	
	if ( integers1 != integers2 )
		cout << "integers1 and integers2 are not equal" << endl;
	
	cout << "integers1:\n";
	integers1.outputArray;
	<< "integers2:\n";
	integers2.outputArray;
	
	// use overloaded equality (==) operator
	cout << "\nEvaluating: integers1 == integers2" << endl;
	
	if ( integers1 == integers2 )
		cout << "integers1 and integers2 are equal" << endl;
	
	// use overloaded subscript operator to create rvalue
	cout << "\nintegers1[5] is " << integers1[ 5 ];
	
	// use overloaded subscript operator to create lvalue
	cout << "\n\nAssigning 1000 to integers1[5]" << endl;
	integers1[ 5 ] = 1000;
	cout << "integers1:\n";
	integers1.outputArray();
	
	// attempt to use out-of-range subscript
	cout << "\nAttempt to assign 1000 to integers1[15]" << endl;
	integers1[ 15 ] = 1000; // ERROR: out of range
	*/
	
}//end main
