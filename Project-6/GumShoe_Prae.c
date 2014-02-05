/*
 * Title: GumShoe_Prae.c
 * Author: Paul Prae
 * Last Edited: November 7th, 2010
 * Project 6 for CSCI 1730 with Doc Plaue
 * 
 * Purpose of this file and associated program:
 *
 *	This is the file GumShoe_Prae.c which is part of Project 6 titled
 * "Where in UGA is Carmen Sandiego." The file will be the executable file.
 * It will be used to take in a file from the command prompt. This program
 * will search through the data and recover dereferenced JPEG image files.
 *
 * Limitations of development resources:
 *     This code was written as directed by the instructions for Project
 * 6 posted by Dr. Plaue on eLC at the University of Georgia.
 *     It was written using concepts, ideas, and code presented
 * in class, on the eLC section for the class, from the textbook 
 * C++: How To Program Seventh Edition by Deitel and Deitel and its 
 * official online resources, and from the textbook Advanced Programming 
 * in the UNIX Environment Second Edition by Stevens and Rago.
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
 * This project was created using Emacs, Vi, and Xcode
 */

//The following header file include is from the UNIX text
//It includes all of the C libraries I will need
//It will also help with error processing
#include "apue.h"

int
main(int argc, char *argv[])
{

  //First make sure that the correct number of arguments were passed in
  if(argc != 2)
    {
      //print instructions to the user. Output error
      err_quit("usage: %s filename", argv[0]);
    }

  //Variable to hold the file descriptor of the raw image file
  //int rawFd;
  //Variable to hold the pointer to the raw image file
  FILE *rawFile;
  //Variable to hold the size of the block to be read in bytes
  const int BLOCKSIZE = 512;
  //Variable to hold the block of bytes being read
  unsigned char blockBuff[BLOCKSIZE];
  //A variable to hold the current offset of the rawFile
  long int currentPosition;

  //A variable to hold the number of integers that have been found
  int jpgCount = 0;
  //A char array to hold part of the jpeg file name
  //char jpgName[] = "Prae_Image";
  //A char array to hold the jpg extension
  //char jpgExtension[] = ".jpg";
  //A buffer to hold the image data
  unsigned char imageBuff[(BLOCKSIZE * 2048)];


  //Open the raw file as read only. It should be the first comand line argument
  //If the rawFile is null then there was an error opening the file
  if((rawFile = fopen(argv[1], "r")) == NULL)
    err_sys("Raw file was not able to be opened. Open error");

  printf("Raw file was opened successfully.\n");

  //Record the point/offset of the rawFile
  currentPosition = ftell(rawFile);

  //Print the current position in the rawFile
  printf("First offset of the raw file is %d.\n", currentPosition);

  //Get one block of data from the file at a time
  //Each block is 512 bytes. JPEGs are stored at the start of a block
  //blockBuff is a char array of BLOCKSIZE.
  while(fread(blockBuff, 1, BLOCKSIZE, rawFile) > 0)
    {
    
      //printf("Raw file was read successfully.\n");

      //Record the point/offset where the blockBuff began on the rawFile
      //This will be used for when a jpg is found as the starting point
      // to copy the correct total blocks
      currentPosition = ftell(rawFile);
      
      //Print the current position in the rawFile
      //printf("Current offset of the raw file is %d.\n", currentPosition);

      //A boolean to hold whether a jpg was found in the current block
      //Assume false
      int jpgFound = 0;

      //Check to see if the current block could be the start of a jpg
      //Compare to the decimal version of the hexidecimals we are looking for
      //Check all of the  first four bytes of the block stored in 
      //the blockBuff array
      if( (blockBuff[0] == 0xFF) && (blockBuff[1] == 0xD8) && (blockBuff[2] == 0xFF) && ( (blockBuff[3] == 0xE0) || (blockBuff[3] == 0xE1) ) )
	jpgFound = 1;

      //If all are a match
      //Create and write the jpg file
      //Increment the jpg amount found
      if(jpgFound)
	{
	  
	  //Output to user
	  printf("JPG number %d found.\n", jpgCount); 
	  //Print the current position in the rawFile
	  currentPosition = ftell(rawFile);
	  printf("Current offset of the raw file is %d.\n", currentPosition);

	  //printf("The char buffer reads: ");
	  //printf(blockBuff);
	  //printf("\n\n");

	  //Create the string where the file will be stored
	  //Prae_imageX.jpg where X is the first images
	  char *jpgFileName;

	  asprintf(&jpgFileName, "./Prae_Image%d.jpg", jpgCount);
	  printf("It will be saved as ");
	  printf(jpgFileName);
	  printf(".\n");

	  //Put the offset back to the beginning of this block 
	  //So to read and write correctly for the jpg image
	  if(fseek(rawFile, -512, SEEK_CUR) == -1)
	     err_sys("Not able to set the offset back to the start of the block. lseek error");
	  
	  //Print the current position in the rawFile
	  currentPosition = ftell(rawFile);
          printf("Current offset of the raw file is %d.\n", currentPosition);

	  //First we must read the full iamge data
	  if(fread(imageBuff, 1, (BLOCKSIZE * 2048), rawFile) < 0)
	    err_sys("Not able to read the data for the image. read error");

	  printf("Image data stored in buffer.\n");

          //Print the current position in the rawFile
          currentPosition = ftell(rawFile);
          printf("Current offset of the raw file is %d.\n", currentPosition);

	  //A variable to hold the pointer for the file
	  FILE *jpgFilePtr;

	  //Create the image file
	  if( (jpgFilePtr = fopen(jpgFileName, "w")) == NULL)
	     err_sys("Not able to create the image file. fopen error");	    

	  //Write block to the jpg file
	  if(fwrite(imageBuff, 1, (BLOCKSIZE * 2048), jpgFilePtr) < 0)
	    err_sys("Not able to write the buffer to the new jpg file. Write error");

	  //close file
	  if(fclose(jpgFilePtr) != 0)
	    err_sys("Image file did not close properly. fclose error");

	  //Increment the lseek offset in the main rawFile to where the next jpg should start
	  //A photo takes up 1,048,576 bytes or 2048 blocks
	  //Since the current offset should be a block from the last buffer set we just 
	  //need to be 512 from where we first began reading the block
	  if(fseek(rawFile, (-(BLOCKSIZE * 2047)), SEEK_CUR) == -1)
	    err_sys("Not able to set the offset back to 512 bytes after the last block. lseek error");

	  printf("Image file written and closed. Offset of raw file set back to next block from last checked.\n");

	  //Print the current position in the rawFile
	  currentPosition = ftell(rawFile);
          printf("Current offset of the raw file is %d.\n", currentPosition);

          printf("JPG number %d saved.\n\n", jpgCount);

	  //Increment the jpgFound
	  jpgCount++;

	}


    }//end while

    if(ferror(rawFile) < 0)
      err_sys("Raw file was not able to be read. Read error");


  //Close the raw file
  if(fclose(rawFile) != 0)
    err_sys("File did not close properly before exiting. fclose error");

  printf("%d images were found.\n", jpgCount);

  printf("Program has terminated successfully.\n");
  exit(0);

}//end main
