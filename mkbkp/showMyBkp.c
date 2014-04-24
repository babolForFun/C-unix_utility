#include "fun.h"



//this function has a very similar method to exBkp.c
int showMyBkp(char* myBkp){
    
    

    //file descriptor to read my buffer
    FILE* in;
    
    //index
    int i=0;
    int y=0;
    int count=0;
    char *logString = (char*)malloc(200*sizeof(char));

    //log file .bkp
    strcat(logString,"call function to visit file inside bkp file: ");
    strcat(logString,myBkp);
    doLog(logString);
    free(logString);
    logString=(char*)malloc(200*sizeof(char));
    
    //struct for archve size
    stat(myBkp,&fileInfo);
        
    //dim buffer
    long long dimBuffer = fileInfo.st_size;
        
    //open my file
    in = fopen(myBkp,"rb");
        
    //buffer Array
    char *buf = (char*)malloc(dimBuffer*sizeof(char));
    //fread() all buffer of dimBufferSize once
    fread(buf, dimBuffer, 1, in);
    
    //support arrays
        char *path=(char*)malloc(200*sizeof(char)) ;
        char *name=(char*)malloc(200*sizeof(char)) ;
        char *lungName=(char*)malloc(20*sizeof(char)) ;
        char *lungBuffer=(char*)malloc(200*sizeof(char)) ;
        char *folderName=(char*)malloc(20*sizeof(char)) ;
        char *file=(char*)malloc(100*sizeof(char)) ;
        
    
    //print on video
    printf("\n Il file %s contiene i seguenti file:\n\n",myBkp);
    
    //scroll through the entire array
    while (buf[i]!='\0'){
        //count #File. Increment whenever it's a new fiel
        count++;
        //if is folder
        if(buf[i] == 'f'){
            i++;
            y=0; //reset
            //get folder name
            while (buf[i]!='.') {
                folderName[y]=buf[i];
                y++;i++;
            }
            i++;
            //print my folder array
            printf("\t\t%d° folder: - %s\n",count,folderName);
            continue;
        }
            
        y=0;//reset
        //get Path
        while (buf[i]!='.') {
            path[y]=buf[i];
            y++;i++;
        }
        path[y]='/';
        i++;
        y=0;//reset
        
        //get NameLength
        while (buf[i]!='.') {
            lungName[y]=buf[i];
            i++;y++;
        }
        i++;
        y=0;
        
        //get FileName
        while (y<atoi(lungName)){
            name[y]=buf[i];
            i++;y++;
        }
        y=0;//reset
        
        //get lungBuffer
        while (buf[i]!='.') {
            lungBuffer[y]=buf[i];
            i++;y++;
        }
        i++;
        y=0; //reset
        
        file=(char*)malloc(atoi(lungBuffer)*sizeof(char)) ;
        while (y<atoi(lungBuffer)) {
            file[y]=buf[i];
            y++;i++;
        }
        y=0; //reset
        
        //print result
        printf("\t\t%d° file: - %s\n",count,name);
        
        
        //free
        free(path);
        free(name);
        free(lungName);
        free(lungBuffer);
        free(folderName);
        free(file);
        //new malloc for free support Array
            path=(char*)malloc(200*sizeof(char)) ;
            name=(char*)malloc(200*sizeof(char)) ;
            lungName=(char*)malloc(20*sizeof(char)) ;
            lungBuffer=(char*)malloc(200*sizeof(char)) ;
            folderName=(char*)malloc(20*sizeof(char)) ;
            file=(char*)malloc(100*sizeof(char)) ;
        }

    printf("\n\n");
    
    
    return 0;
}
