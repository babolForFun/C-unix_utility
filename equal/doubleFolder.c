
#include "lib.h"

//int max(int x,int y);
int doubleFolder(char* first,char*second, char* notEqual){
    
    char *logString = (char*)malloc(500*sizeof(char));
    
    //file descripto once for file
    int fdf1;
    int fdf2;
    
    //number of files in directory
    int numeroFile1=0;
    int numeroFile2=0;
   
    //array with file directory
    char *tmpDirectory1 = (char*)malloc(400*sizeof(char));
    char *tmpDirectory2 = (char*)malloc(400*sizeof(char));
    
    //associate a dirent struct to my folder with alphasort
    if((fdf1 = scandir(first,&folder1, 0, alphasort))!=-1 &&
       (fdf2 = scandir(second,&folder2, 0, alphasort))!=-1 ){
        
        //number of file inside first folder
        DIR *myDir1 = opendir(first);
        //log file stat not correct
        strcat(logString,"take in input ");
        strcat(logString,first);
        doLog(logString);
        logString=(char*)malloc(500*sizeof(char));
        
        while(( readdir(myDir1))!= NULL) {
            numeroFile1++;
        }
        
        //number of file inside second folder  
        DIR *myDir2 = opendir(second);  
        //log file - get the folder
        strcat(logString,"get the folder ");
        strcat(logString,second);
        doLog(logString);
        logString=(char*)malloc(500*sizeof(char));
        
        while(( readdir(myDir2))!= NULL) {
            numeroFile2++;
        }
        
        //String that will contain the name of the equal files 
        char *equalFiles = (char*)malloc(5000*sizeof(char));
        
        int m=0;
        int l=0;
        
        //For every file in the first folder we'll check if there's a file in the second folder with the same name.
        for (m=0; m<numeroFile1; m++) {
            //we'll use that variable to check if the files in the first folder has a file with the same name in the second one.
            int checked=0;
            
            for (l=0; l<numeroFile2; l++) {
                
                //if found invalid file skip them
                if(((strcmp(folder1[m]->d_name,".")==0) || (strcmp(folder1[m]->d_name,"..")==0) || (strcmp(folder1[m]->d_name,".DS_Store")==0)) ||
                   ((strcmp(folder2[l]->d_name,".")==0) || (strcmp(folder2[l]->d_name,"..")==0) || (strcmp(folder2[l]->d_name,".DS_Store")==0)) ) {
                    
                    
                } else

                    //If the name is valid and there's a file with the same name in both folders, we'll check if the two files are equals.
                    if (strcmp(folder1[m]->d_name,folder2[l]->d_name)==0) {
                        
                        
                        //if the file of the first folder that we are checking has a file with the same name in the second folder we set it as checked.
                        checked=1;
                        
                        //create complete path for the first file
                        strcat(tmpDirectory1, homeDirectory);
                        strcat(tmpDirectory1, "/");
                        strcat(tmpDirectory1, first);
                        //create complete path for the second file
                        strcat(tmpDirectory2, homeDirectory);
                        strcat(tmpDirectory2, "/");
                        strcat(tmpDirectory2, second);
                        
                        //name of the contains files
                        char* fileFirst = (char*)malloc(strlen(folder1[m]->d_name)*sizeof(char));
                        char* fileSecond = (char*)malloc(strlen(folder2[l]->d_name)*sizeof(char));
                        
                        //insert them in tmpDirectory
                        strcat(tmpDirectory1,folder1[m]->d_name);
                        strcat(tmpDirectory2,folder2[l]->d_name);
                        
                        //log file - compare file
                        strcat(logString,"compare the file: ");
                        strcat(logString,folder1[m]->d_name);
                        strcat(logString," with the file: ");
                        strcat(logString,folder2[l]->d_name);
                        doLog(logString);
                        free(logString);
                        logString=(char*)malloc(500*sizeof(char));
                        
                        //if are two folders call recursively this function (it doesen't wotk correctly)
                        if (control(tmpDirectory1, tmpDirectory2) == 0) {
                            char *notEqual2=(char*)malloc(500*sizeof(char));
                            doubleFolder(fileFirst, fileSecond,notEqual2);
                        }
                        else{
                            //check if files are equals
                            int doConfront = doubleFile(tmpDirectory1,tmpDirectory2);
                                                        
                            //if the files are equal
                            if(doConfront == 0){
                                //log file - success
                                strcat(logString,"compare file return successfully ");
                                strcat(logString,first);
                                doLog(logString);
                                free(logString);
                                logString=(char*)malloc(500*sizeof(char));
                                
                                //copy the file name in array of equal file
                                printf("both file have the same content  \n");
                                strcat(equalFiles, folder1[m]->d_name);
                                strcat(equalFiles, "\n - ");
                                
                            }
                            //if not equal add the name in notEqual array
                            else if(doConfront == 1){
                                strcat(notEqual, "\n - ");
                                strcat(notEqual, tmpDirectory1);
                                
                                //log file - construct not equal array
                                strcat(logString," add at: ");
                                strcat(logString,notEqual);
                                strcat(logString," string -: ");
                                strcat(logString, tmpDirectory1);
                                doLog(logString);
                                free(logString);
                                logString=(char*)malloc(500*sizeof(char));
                                
                            }
                        }
                        
                        free(fileFirst);
                        free(fileSecond);
                    
                    
                    //malloc new memory
                    tmpDirectory1 = (char*)malloc(400*sizeof(char));
                    tmpDirectory2 = (char*)malloc(400*sizeof(char));
                    
                    //when i found a match between the file in the first folder and a file in the second one, i'll switch to the next file
                    // in the first folder by breaking out of the for loop
                    break;
                }
            }
            
            
            //if there are files in the first folder that have no match in the second one, i'll put them in the notEqual string
            //first of all i'm checking if the name of the file is valid
            if(((strcmp(folder1[m]->d_name,".")!=0) && (strcmp(folder1[m]->d_name,"..")!=0) && (strcmp(folder1[m]->d_name,".DS_Store")!=0)) ) {
                
            if (checked==0) {
                
                //create complete path for the file
                strcat(tmpDirectory1, homeDirectory);
                strcat(tmpDirectory1, "/");
                strcat(tmpDirectory1, first);
                
                //name of the contains files
                char* fileFirst = (char*)malloc(strlen(folder1[m]->d_name)*sizeof(char));
                
                //insert them in tmpDirectory
                strcat(tmpDirectory1,folder1[m]->d_name);
                
                //if not equal add the name in notEqual array
                strcat(notEqual, "\n - ");
                strcat(notEqual, tmpDirectory1);
                
                //log file - construct not equal array
                strcat(logString," add at: ");
                strcat(logString,notEqual);
                strcat(logString," string -: ");
                strcat(logString, tmpDirectory1);
                doLog(logString);
                free(logString);
                logString=(char*)malloc(500*sizeof(char));
            } }
            
            tmpDirectory1 = (char*)malloc(400*sizeof(char));
            tmpDirectory2 = (char*)malloc(400*sizeof(char));
            checked=0;
        }
                
        
        //Now in the same way we did it before i'm going to check if there are files in the second folder that have no match
        //in the first one. Then, if there are, i'll put them in the notEqual string
        for (l=0; l<numeroFile2; l++) {
            int checked=0;
            
            for (m=0; m<numeroFile1; m++) {
                
                //if found invalid file skip them
                if(((strcmp(folder1[m]->d_name,".")==0) || (strcmp(folder1[m]->d_name,"..")==0) || (strcmp(folder1[m]->d_name,".DS_Store")==0)) ||
                   ((strcmp(folder2[l]->d_name,".")==0) || (strcmp(folder2[l]->d_name,"..")==0) || (strcmp(folder2[l]->d_name,".DS_Store")==0)) ) {
                    
                    
                } else if (strcmp(folder2[l]->d_name,folder1[m]->d_name)==0) {
                    
                    checked=1;
                }
            }
            
            if(((strcmp(folder2[l]->d_name,".")!=0) && (strcmp(folder2[l]->d_name,"..")!=0) && (strcmp(folder2[l]->d_name,".DS_Store")!=0)) ) {
                
                if (checked==0) {

                    //create complete path for the file
                    strcat(tmpDirectory2, homeDirectory);
                    strcat(tmpDirectory2, "/");
                    strcat(tmpDirectory2, second);
                    
                    //name of the contains files
                    char* fileSecond = (char*)malloc(strlen(folder2[l]->d_name)*sizeof(char));
                    
                    //insert them in tmpDirectory
                    strcat(tmpDirectory2,folder2[l]->d_name);
                    
                    //if not equal add the name in notEqual array
                    strcat(notEqual, "\n - ");
                    strcat(notEqual, tmpDirectory2);
                    
                    //log file - construct not equal array
                    strcat(logString," add at: ");
                    strcat(logString,notEqual);
                    strcat(logString," string -: ");
                    strcat(logString, tmpDirectory2);
                    doLog(logString);
                    free(logString);
                    logString=(char*)malloc(500*sizeof(char));
                } }
            
            tmpDirectory1 = (char*)malloc(400*sizeof(char));
            tmpDirectory2 = (char*)malloc(400*sizeof(char));
            checked=0;
        }
    }

    free(logString);
    free(tmpDirectory1);
    free(tmpDirectory2);
    tmpDirectory1 = (char*)malloc(400*sizeof(char));
    tmpDirectory2 = (char*)malloc(400*sizeof(char));

    
    logString=(char*)malloc(500*sizeof(char));
    
    //print result
    if (strcmp(notEqual,"")==0) {
        printf(" - all files insert from command line are equal\n");
        //log file - result
        strcat(logString," final result: all files insert from command line are equal ");
        doLog(logString);
        free(logString);
        logString=(char*)malloc(500*sizeof(char));

    }
    else{
        printf("\n- file insert that are not equal are: ");
        printf("\n\t-%s\n",notEqual);
        //log file - result
        strcat(logString," final result: some file are not equal ");
        doLog(logString);
        free(logString);
        logString=(char*)malloc(500*sizeof(char));

    }
    
    //free the memory
    free(notEqual);
    free(tmpDirectory1);
    free(tmpDirectory2);

    return 0;
 }












