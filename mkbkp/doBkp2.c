
#include "fun.h"

int readFile(FILE* fdw,FILE* fdr,char* Directory,int lungFile,char* NameFile);
int doBkp2(int argc,char** argv){

  
    //files descriptor
    FILE* fdr;  // read
    FILE* fdw;  // write
    int fdf;    // folder
    
    //iterator index
    int i;
    int lungFile;
    char *logString = (char*)malloc(200*sizeof(char));
    
    //path folder
    char Directory[255];
    char homeDirectory[255];
    getcwd(homeDirectory, sizeof(homeDirectory));
    
    
    //log file .bkp
    strcat(logString,"creat my backup file: ");
    strcat(logString, argv[3]);
    doLog(logString);
    free(logString);
    logString=(char*)malloc(200*sizeof(char));
    
    if ((creat(argv[3], 0777))<0) {
        printf("error to creat()");
        return -1;
    }
    //fopen file.bkp with error handling
    if((fdw = fopen(argv[3],"wb"))<0){
        doLog("error to open fdw ");
        printf("error to open fw\n");
        return -1;
    }
    
    
    //cycle on my input
    for (i=4; i<argc; i++) {
        
        //log file input
        strcat(logString,"take input argument: ");
        strcat(logString, argv[i]);
        doLog(logString);
        free(logString);
        logString=(char*)malloc(200*sizeof(char));

        //if isFolder
        if((fdf = scandir(argv[i],&folderInfo, 0, alphasort))!=-1){
            int numeroFile=0;
            
            //write 'f' for extract.c
            fwrite("f", 1, sizeof(char), fdw);

            //Number of Content Files
            DIR *myDir = opendir(argv[i]);
            while(( readdir(myDir))!= NULL) {
                numeroFile++;
            }
            
            //change WorkDirectory
            chdir(argv[i]);
            //get actual Directory
            getcwd(Directory, sizeof(Directory));
    
            //write of directory an a '.'
            fwrite(Directory, strlen(Directory), 1, fdw);
            fwrite(".", 1, sizeof(char), fdw);
            
            //count on file for count effective them
            int y;
            for (y=0; y<numeroFile; y++) {
                //if found invalid file skip them and don't do readFile()
                if((strcmp(folderInfo[y]->d_name,".")!=0) && (strcmp(folderInfo[y]->d_name,"..")!=0)){
                    //call readFile()
                    readFile(fdw,fdr,Directory,lungFile,folderInfo[y]->d_name);}
                else
                    continue;
            }
            //close my WorkDirectory
            closedir(myDir);
            //return to mainDirectory
            chdir(homeDirectory);
            
        }
        //if isFile
        else{
            //get Directory
            getcwd(Directory, sizeof(Directory));
            //found file length
            lungFile = (int)strlen(argv[i]);
            
            //fopen for the argument
            if((fdr = fopen(argv[i],"rb"))<0){
                
                //log file fopen fail
                strcat(logString,"error to open fr in argument: ");
                strcat(logString,argv[i]);
                doLog(logString);
                free(logString);
                logString=(char*)malloc(200*sizeof(char));
                
                printf("error to open fr in argument %s\n\n",argv[i]);
                return -1;
            }
            else{
                //call the readFile() function
                if(readFile(fdw,fdr,Directory,lungFile,argv[i])==-1){
                    //log file execute correct
                    strcat(logString,"error during mkbkp");
                    doLog(logString);
                    free(logString);
                    logString=(char*)malloc(200*sizeof(char));
                    return -1;
                }
            }
        }
    }
    
    //log file execute correct
    strcat(logString,"execution dobkp correct");
    doLog(logString);
    free(logString);
    logString=(char*)malloc(200*sizeof(char));

    //close file descriptor
    close(fdf);
    fclose(fdr);
    fclose(fdw);
    
    return 0;
}



int readFile(FILE* fdw,FILE* fdr,char* Directory,int lungFile,char* NameFile){
    
    
    
    //PARAMETER
    //Path Length
    int lungPath = (int)strlen(Directory);
    //log String
    char *logString = (char*)malloc(200*sizeof(char));

    //Path
    fwrite(Directory, lungPath, 1, fdw);
    fwrite(".", 1, sizeof(char), fdw);
    
    //Name file length
    lungFile = (int)strlen(NameFile);
    char lungFileBuffer [50];
    //save in a char* lungfile
    sprintf (lungFileBuffer,"%d",lungFile);
    strcat(lungFileBuffer, ".");
    
    //write on my buffer the Name-file-length
    fwrite(lungFileBuffer,strlen(lungFileBuffer), 1, fdw);
    
    //Write() FileName
    fwrite(NameFile, lungFile, 1, fdw);
    
    
    
    
    //open with file descriptor the File in "rb"mode for opening file in a Bunary format.
    if((fdr = fopen(NameFile,"rb"))<0){
        
        //log file error to open fdr to file
        strcat(logString,"error to open fdr to file");
        strcat(logString,NameFile);
        doLog(logString);
        free(logString);
        logString=(char*)malloc(200*sizeof(char));
        
        printf("error to open fr in argument %s\n\n",NameFile);
        return -1;
    }else{
        //buffer
        char* buffer = (char*)malloc(100*sizeof(char));;
        
        //stat for set buffer dimension
        if((stat(NameFile,&fileInfo))==-1){  //stat of my n-file
            
            //log file execute correct
            strcat(logString,"error associed struct FileInfo at");
            strcat(logString,NameFile);
            doLog(logString);
            free(logString);
            logString=(char*)malloc(200*sizeof(char));
            
            printf("error to open a new file stat in argument!");
            return -1;
        }
        
        //length of File
        int s = (int)fileInfo.st_size;
        char lungFileBuffer[50];
        //copy length-of-File into a char*
        sprintf (lungFileBuffer,"%d",s);
        strcat(lungFileBuffer, ".");
        //write() length file
        fwrite(lungFileBuffer, strlen(lungFileBuffer), 1, fdw);
        
        //new malloc for free buffer inside
        free(buffer);
        buffer = (char*)malloc(100*sizeof(char));

        //read all file
        while(!feof(fdr)){        //fill the buffer with file's charter
            fread(buffer,1,s,fdr);
        }
        //write the file
        fwrite(buffer, s, 1, fdw);
    }
    
    return 0;
}
