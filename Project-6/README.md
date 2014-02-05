Goal:
------

Write a program in C that can reconstruct deleted images off of a flash drive.

Description:
-------------

We have a digital camera that records pictures as JPEGs. These will begin with one of two sequences of bytes. The digital camera that stored these images stored the files contiguously. This Canon G10 uses a FAT file system with block sizes of 512 bytes (B). From the storage card this camera stored some number of images, you must recompose them and store them as separate files.

Class, Input, and Output Requirements:
----------------------------------------------------------

You should create all the necessary classes to take in a user-specified data file as a command-line argument. You can assume that the file will be placed in the current working directory. Your executable file should be named GumShoe_Name.exe where Name is your last name.

The data file we will provide will have several images. Your program should place the recovered images in the current working directory and number the files it outputs by naming each Name_ImageX.jpg, where X starts at 0 and increments. Name is your last name.
You should also provide a makefile with a clean command to remove any jpegs in the current working directory.
Your program should take in the name of the image file to process.
