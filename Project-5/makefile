# Compiles the program for Project 5
ArrayTester : Project5Prae.o Array.o
	g++ -g Array.o Project5Prae.o -lm -o Project5Prae

Array.o : Array.h Array.cpp 
	g++ -Wall -g -c Array.h Array.cpp

ArrayTester.o : Array.o
	g++ -Wall -g -c Project5Prae.cpp



# Runs Project5Prae program to test classes and functionality
run: Project5Prae
	./Project5Prae

# Clean up!
clean: 
	rm Project5Prae.o Array.o
