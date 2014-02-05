/*
 * Title: apue.c
 * Author: Paul Prae
 * Last Edited: November 7th, 2010
 * 
 * Purpose of this file and associated program:
 *     This file defines apue.h. It will hold many useful functions
 * including error handling functions. It is based off of code from 
 * the course UNIX textbook.
 *
 * Limitations of development resources:
 *     This code was written to help prepare for Project
 * 6 posted by Dr. Plaue on eLC at the University of Georgia.
 *		It was written using concepts, ideas, and code presented
 * in class, on the eLC section for the class, from the textbook 
 * C++: How To Program Seventh Edition by Deitel and Deitel and its 
 * official online resources, and from the textbook Advanced Programming 
 * in the UNIX Environment Second Edition by Stevens and Rago.
 * 
 * Statement of Academic Honesty:
 *     The following code represents my own work and the work of the 
 * textbook authors. I have neither received nor given inappropriate
 * assistance. I have not copied or modified code from any source other
 * than the course webpage, eLC, or the course textbook and materials.
 * I recognize that any unauthorized assistance or plagiarism will be 
 * handled in accordance with the University of Georgia's Academic Honesty
 * Policy and the policies of this course.
 *
 * This project was created using Emacs.
 */

#include "apue.h"
//ERROR handling
//For definition of errno
#include <errno.h>
//ISO C variable arguments
#include <stdarg.h>
#include <syslog.h>

//THIS CONTAINS TWO SECTIONS

//Section 1: error functions that output to standard error

static void err_doit(int, int, const char *, va_list);

//Non fatal error related to a system call.
//Print a messae and return
void
err_ret(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
}//end err_ret

//Fatal error related to a system call.
//Print message and terminate.
void
err_sys(const char *fmt, ...)
{
  va_list ap;
  
  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
  exit(1);
}//end err_sys

//Fatal error unrelated to a system call.
//Error code passed as an explicit parameter
//Print a message and terminate.
void
err_exit(int error, const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, error, fmt, ap);
  va_end(ap);
  exit(1);
}//end err_exit

//Fatal error related to a system call.
//Print a message, dump core, and terminate.
void
err_dump(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
  //Dump core and terminate. Should not get to exit(1)
  abort();
  exit(1);
}//end err_dump

//Non fatal error unrelated to a system call.
//Print message and terminate.
void
err_msg(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  err_doit(0, 0, fmt, ap);
  va_end(ap);
}//end err_msg

//Fatal error unrelated to a system call.
//Printmessageand terminate.
void
err_quit(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  err_doit(0, 0, fmt, ap);
  va_end(ap);
  exit(1);
}//end err_quit

//Print message and return to caller.
//Caller specifies "errnoflag".
static void
err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
  char buf[MAXLINE];
  
  vsnprintf(buf, MAXLINE-1, fmt, ap);
  if(errnoflag)
    {
      snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s", strerror(error));
    }
  strcat(buf, "\n");
  //in case stdout and stderr are the same
  fflush(stdout);
  fputs(buf, stderr);
  //Flushes all stdio output streams
  fflush(NULL);
}//end err_doit


//Section 2: Error functions for daemons

static void log_doit(int, int, const char *, va_list ap);

//Caller must define and set this: nonzero if interactive, zero if daemon
//default to zero
extern int log_to_stderr = 0;

//initialize syslog(), if running as daemon
  void log_open(const char *ident, int option, int facility)
{
  if(log_to_stderr == 0)
    openlog(ident, option, facility);
}//end log_open

//Non fatal error related to a system call.
//Print message and return.
void
log_ret(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  log_doit(1, LOG_ERR, fmt, ap);
  va_end(ap);
 
}//end log_ret

//Fatal error related to a system call.
//Print message and terminate.
void
log_sys(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  log_doit(1, LOG_ERR, fmt, ap);
  va_end(ap);
  exit(2);
}//end log_sys

//Non fatal error unrelated to a system call.
//Print message and return.
void
log_msg(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  log_doit(0, LOG_ERR, fmt, ap);
  va_end(ap);
}//end log_msg

//Fatal error unrelated to a system call.
//Print message and terminate.
void
log_quit(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  err_doit(0, 0, fmt, ap);
  va_end(ap);
  exit(2);
}//end log_quit

//Print a message and return to the caller
//Caller specifies errnoflag and priority
static void
log_doit(int errnoflag, int priority, const char *fmt, va_list ap)
{
  int errno_save;
  char buf[MAXLINE];

  //Value caller might want printed
  errno_save = errno;
  vsnprintf(buf, MAXLINE-1, fmt, ap);
  if(errnoflag)
    snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s", strerror(errno_save));

  strcat(buf, "\n");
  if(log_to_stderr)
    {
      fflush(stdout);
      fputs(buf, stderr);
      fflush(stderr);
    }else{
    syslog(priority, buf);
  }
}//end log_doit
