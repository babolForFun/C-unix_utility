/*

 This function take in input two char* relative to path of files
        return 0  -  file are equals
        return 1  -  file are different

 */

#include "lib.h"

int doubleFile(char* first,char* second){

    char *logString = (char*)malloc(200*sizeof(char));

    //file descriptor for binary files
    FILE* fd1 = NULL;
    FILE* fd2 = NULL;
    
    
    //log file - compare file
    strcat(logString,"call to doublefile() with argument ");
    strcat(logString,first);
    strcat(logString," - and - ");
    strcat(logString,second);
    doLog(logString);
    free(logString);
    logString=(char*)malloc(200*sizeof(char));
    
    // fopen with error handling
    if(((fd1 = fopen(first,"rb"))!=NULL) && ((fd2=fopen(second,"rb"))!=NULL)){
        
        //stat to first and second with error handling
        if(stat(first,&forfirst)<0){

            //log file - error stat first
            strcat(logString,"$bash error stat:-");
            strcat(logString,first);
            doLog(logString);
            free(logString);
            logString=(char*)malloc(200*sizeof(char));
        }
        if(stat(second,&forsecond)<0){

            //log file - error stat second
            strcat(logString,"$bash error stat:-");
            strcat(logString,second);
            doLog(logString);
            free(logString);
            logString=(char*)malloc(200*sizeof(char));
        }
        
        // size of two files
        int dimFirst = (int)forfirst.st_size;
        int dimSecond = (int)forsecond.st_size;
        
        // check. If files have different dimension they will never equal
        if(dimFirst != dimSecond){
            printf(" - file insert from command line haven't same contain\n");
            return 1;
        }
        
        //allocate memory for the content of files
        char* contentFirst = (char*)malloc(dimFirst*sizeof(char));
        char* contentSecond = (char*)malloc(dimSecond*sizeof(char));
        
        // fread. Read file as large as dimFirst and put the contain in contentFirst
        fread(contentFirst, dimFirst, 1, fd1);
        while(!feof(fd1))
            fread(contentFirst,1,dimFirst,fd1);

        // fread. Read file as large as dimSecond and put the contain in contentFirst
        fread(contentSecond, dimSecond, 1, fd2);
        while(!feof(fd2))
            fread(contentSecond,1,dimSecond,fd2);
  
        // control that every byte is equals else return 1
        int i=0;
        for (i=0; i<dimFirst; i++) {
            if(contentFirst[i] != contentSecond[i]){
                //log file - not same
                strcat(logString,"file insert from command line haven't same contain");
                doLog(logString);
                free(logString);
                logString=(char*)malloc(200*sizeof(char));
                printf(" - file insert from command line haven't same contain\n");        
                return 1;
            }
            break;
        }
        free(contentFirst);
        free(contentSecond);
    }else{
        //log file - error fopen
        strcat(logString,"$bash error fopen.");
        doLog(logString);
        free(logString);
        logString=(char*)malloc(200*sizeof(char));
    }
  


    //return 0 means that files have identical content
    return 0;
}
















