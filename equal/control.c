/*
 
 the function control what kind are the argument
 
    return 0  -  the two file are both folder
    return 1  -  the two files are different type
    return 2  -  the two are both file
    return 3  -  erro
 
 */

#include "lib.h"

int control(char* first, char* second){

    char *logString = (char*)malloc(200*sizeof(char));
    int res=0;
    //stat for the two argument
    if(stat(first, &forfirst)<0){
        
        //log file stat not correct
        strcat(logString,"error to associate stat second file");
        strcat(logString,first);
        doLog(logString);
        logString=(char*)malloc(200*sizeof(char));
    }
    if(stat(second, &forsecond)){
        
        //log file stat not correct
        strcat(logString,"error to associate stat second file");
        strcat(logString,first);
        doLog(logString);
        logString=(char*)malloc(200*sizeof(char));
    }
    
    //if S_ISDIR is true for both files res = 0
    if(S_ISDIR (forfirst.st_mode) && S_ISDIR (forsecond.st_mode)){
        res = 0;
    }
    
    //if S_ISDIR is true for one file but not for the other res = 1
    else if(((S_ISDIR (forfirst.st_mode) && !(S_ISDIR (forsecond.st_mode))) || (!(S_ISDIR (forfirst.st_mode)) && S_ISDIR (forsecond.st_mode)))){
        res = 1;
    }
    
    //if S_ISDIR is never true res = 2
    else if (!(S_ISDIR (forfirst.st_mode)) && !(S_ISDIR (forsecond.st_mode))){
        res = 2;
    }

    free(logString);
    //return re
    return res;
}

