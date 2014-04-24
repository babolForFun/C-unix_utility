



#ifndef Sysop___equal_lib_h
#define Sysop___equal_lib_h

#include <sys/stat.h>
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


char homeDirectory[255];


//struct for file and directory
struct dirent **folder1;
struct dirent **folder2;
struct stat forfirst;
struct stat forsecond;
struct tm* myTime;


int doubleFile(char*,char*);
int doubleFolder(char*,char*,char*);
int control(char*, char*);
void doLog(char* );




#endif
