
#ifndef FUN_H
#define FUN_H

//library
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <time.h>

//struct for file and directory
struct dirent **folderInfo;
struct stat fileInfo;
struct tm* myTime;


//my function
int doBkp2(int ,char**);
int exbkp(char *);
int showMyBkp(char *);
void doLog(char*);

#endif


