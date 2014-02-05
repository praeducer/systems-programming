/*
 * Title: apue.h
 * Author: Paul Prae, Richard Stevens, and Stephen Rago
 * Last Edited: November 3rd, 2010
 * 
 * Purpose of this file:
 *     This file is presented in the course textbook for Unix 
 * programming. It provided many useful tools and libraries. I
 * used this file to practice many of the code examples in the 
 * book. It is very helpful and also provides definitions for some
 * error handling a logging. I will use it as needed on future projects.
 * I may also add things to this file over time.
 *
 * Limitations of development resources:
 *     This code was written using concepts, ideas, and code presented
 * in class, on the eLC section for the class, from the textbook 
 * C++: How To Program Seventh Edition by Deitel and Deitel and its 
 * official online resources, and from the textbook Advanced Programming 
 * in the UNIX Environment Second Edition by Stevens and Rago.
 *
 * Statement of Academic Honesty:
 *     This code is directly copied out of the course textbook. It does
 * not contain code from anywhere not listed above.  
 *     The following code represents my own work and that of the textbook 
 * authors. I have neither received nor given inappropriate assistance.
 * I have not copied or modified code from any source other than the course
 * webpage, eLC, or the course textbook and materials. I recognize that any 
 * unauthorized assistance or plagiarism will be handled in accordance
 * with the University of Georgia's Academic Honesty Policy and the
 * policies of this course.
 *
 * This code was created using Emacs
 */

#ifndef _APUE_H
#define _APUE_H

#if defined(SOLARIS) /* Solaris 9 */
#define _XOPEN_SOURCE 500 /* Single UNIX Specification, Version 2 */
#define CMSG_LEN(x) _CMSG_DATA_ALIGN(sizeof(struct cmsghdr) + (x))
#elif !defined(BSD)
#define _XOPEN_SOURCE 600 /* Single UNIX Specification, Version 3 */
#endif

//Some systems require this
#include <sys/types.h>
//Contains the stat function to determine attributes
#include <sys/stat.h>
//for winsize
#include <sys/termios.h>
#ifndef TIOCGWINSZ
#include <sys/ioctl.h>
#endif

#ifdef MACOS
#include <sys/uio.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

//For error signal SIG_ERR
#include <signal.h>

//Max line length
#define MAXLINE 4096

//Default file access permissions for new files.
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

//Default permissions for new directories.
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

//For signal handlers
typedef void Sigfunc(int);

#if defined(SIG_IGN) && !defined(SIG_ERR)
#define SIG_ERR ((Sigfunc *)-1)
#endif

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

//Prototypes for functions from figures I tested in the textbook
//Figure 2.15
char *path_alloc(int *);
//Figure 2.16
long open_max(void);

//Figure 3.11
void clr_fl(int, int);
void set_fl(int, int);

//Prototypes for standard error routines.
//For Appendix B. Outputs to standard error
void err_dump(const char *, ...);
void err_msg(const char *, ...);
void err_quit(const char *, ...);
void err_exit(int, const char *, ...);
void err_ret(const char *, ...);
void err_sys(const char *, ...);

void log_msg(const char *, ...);
void log_open(const char *, int, int);
void log_quit(const char *, ...);
void log_ret(const char *, ...);
void log_sys(const char *, ...);

#endif //_APUE_H
