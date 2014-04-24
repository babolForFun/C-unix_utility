
/*
 La funzione prende in input due argomenti che devono essere confrontati
 
        Tre casi possibili:
            1. file - file
            2. file - cartella
            3. cartella - cartella
 
*/


#include "lib.h"

int main(int argc, char** argv){
    
    //log array msg
    char *logString = (char*)malloc(200*sizeof(char));
    
    //log file - input argv[1]
    strcat(logString,"take in input ");
    strcat(logString,argv[1]);
    doLog(logString);
    logString=(char*)malloc(200*sizeof(char));
    
    //log file - input argv[2]
    strcat(logString,"take in input ");
    strcat(logString,argv[2]);
    doLog(logString);
    free(logString);
    logString=(char*)malloc(200*sizeof(char));
    

    
    //path folder
    getcwd(homeDirectory, sizeof(homeDirectory));
    
    //array where I save the name of different file
    char *notEqual = (char*)malloc(100*sizeof(char));
    
    //stat of two file passed from command line
    stat(argv[1], &forfirst);
    stat(argv[2], &forsecond);
    
    //from the command line if there are more argument it's wrong
    if(argc!=3){
        printf("$$: Bad shell. Error number of argument\n");
      
        //log file - wrong number of argument
        strcat(logString,"$$: Bad shell. Error number of argument");
        doLog(logString);
        free(logString);
        logString=(char*)malloc(200*sizeof(char));
        
        return -1;
    }
    else{
        
        //allocate memory for path
        char*DirectoryFirst = (char*)malloc(200*sizeof(char));
        char*DirectorySecond = (char*)malloc(200*sizeof(char));
        
        //creat first file path
        strcat(DirectoryFirst,homeDirectory);
        strcat(DirectoryFirst, "/");
        strcat(DirectoryFirst, argv[1]);

        //creat second file path
        strcat(DirectorySecond,homeDirectory);
        strcat(DirectorySecond, "/");
        strcat(DirectorySecond, argv[2]);
        
        //control what kind are the arguments
        int res = control(DirectoryFirst, DirectorySecond);
        
        //if '0' are two folder
        if(res == 0){
            doubleFolder(argv[1], argv[2],notEqual);
            
        //if '1' one is folder and one is file
        }else if(res ==1){
            
            printf("A file is a folder and a file is a simply file\n");
                
            //log file - different ype file
                strcat(logString,"A file is a folder and a file is a simply file - ");
                strcat(logString,argv[1]);
                strcat(logString," and ");
                strcat(logString,argv[2]);
                doLog(logString);
                free(logString);
                logString=(char*)malloc(200*sizeof(char));

        //if '2' are both file
        }else if(res == 2){
            //check if are equal
            if(doubleFile(argv[1], argv[2])==0){

                printf(" - both file insert from command line are equal\n");

                //log file - control file resul positive
                strcat(logString,"control file resul positive ");
                strcat(logString,argv[1]);
                strcat(logString," and ");
                strcat(logString,argv[2]);
                doLog(logString);
                free(logString);
                logString=(char*)malloc(200*sizeof(char));
            
            }else{
                
                //log file - control file resul negative
                strcat(logString,"control file resul negative ");
                strcat(logString,argv[1]);
                strcat(logString," and ");
                strcat(logString,argv[2]);
                doLog(logString);
                free(logString);
                logString=(char*)malloc(200*sizeof(char));            }
        }
        free(DirectoryFirst);
        free(DirectorySecond);
    }
    
    //return correct execution
    return 0;
}












