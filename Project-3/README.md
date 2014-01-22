Project 3: Practice with File Input and Output
===============================================

+ CSCI-1730
+ C++ and Systems Programming
+ Fall 2010
+ University of Georgia


Goals
------

1. Practice implementing recursion and pointers
2. Practice command-line arguments
3. Practice using arrays and string manipulation in C++



Programming Assignment 
-----------------------

Many people like to have their phone number to spell something. For example, the number 932-734-7328 spells "we are great". Your assignment is to write a program that is given as input a phone number of 10 digits that finds all the matches for the mnemonics of the phone number in the text of a document that we’ll provide. For the purposes of you testing your programming assignment, you should use Moby Dick by Herman Melville (available http://www.textlibrary.com/download/moby-‐dic.txt).


Another example, suppose the phone is: 626-428-8637. One mnemonic for this phone number is "Manhattoes." Manhattoes is a string that appears in the first chapter of the text at line number 36 of the file you will use as input. Upon a match, you should print out the following:

1.	The line number of the match (line 36 for "Manhattoes")
2.	The context of the match, which in this example is the 36th line of the text, i.e.: "There now is your insular city of the Manhattoes, belted round by wharves”
3.	The resulting mnemonic, i.e. "Manhattoes".


You should find all the matches of all the mnemonics for the phone number in the text. White space, hyphen and punctuation in the text (Moby Dick) are not significant. For example, the phone number: 246‐625-3744 with mnemonic "Ah noble shi" should display "Ah, noble ship," at line 1544 as one of the matches for the number.


Further, if your number contains 0's or 1's you should discard them from the pattern. For example, if the phone number is 843‐269-0000 the number should be reduced to the number to 843‐269. Examples of mnemonics of this number that occur in the text include:
+ "the bow"
+ "the cow"
+ " the an"


There are at least 57 matches for "the bow", at least 2 matches of the mnemonic "the cow".
Hence, your program needs to solve:
1.	What is the mnemonic or mnemonics
2.	Where does it (or they) appear in the text
3.	What is the context of the match


Note:

+ If a mnemonic wraps two lines, print out both lines.
+ You should read the Moby Dick text from standard input (i.e. it enables you to use cin). i.e. if your text is in file Moby-Dick.txt, you can read the text from standard by redirecting input via "<" operator. For example, your executable should be called CS1730Mnemonic, and you would type:
+++ ./CS1730Mnemonic 706-867-5309 < MobyDick.txt
+++ ./CS1730Mnemonic 7068675309 < MobyDick.txt


These above commands would take as input the text MobyDick.txt just as it would take it as if you were to type the text on your terminal.




Input and Output Requirements
-------------------------------------------
+ Your program should be able to detect when improper input is fed into the program
+ The only argument taken to the program is the phone number; the data file is given through input redirection
+ Your code should be properly documented
+ Your code should be well-‐modularized
+ The very first three lines of output of running your program should always be:
> There are X mnemonic matches for the number (XXX-XXX-XXXX)
Where the X’s are replaced with the appropriate numbers; following this header, you will output the results as specified above. 
+ You should have four code-related files to submit including your driver, source code/header, and makefile.



Error Handling
--------------------
Your program should never crash or hang. Your program should also respond in a reasonable amount of time. In the instance of Moby Dick, your program should finish operating within 5 minutes.
