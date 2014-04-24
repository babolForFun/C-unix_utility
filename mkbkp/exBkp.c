
#include "fun.h"

int exbkp(char *myBkp){

    //file descriptor to read my buffer
    FILE* in;
    
    //index
    int i=0;
    int y=0;
    char *logString = (char*)malloc(200*sizeof(char));

    //struct for archive size
    stat(myBkp,&fileInfo);
    
    //get the bufferDimension
    long long dimBuffer = fileInfo.st_size;
    
    //open my bkp file
    in = fopen(myBkp,"rb");
    
    //log file - open file .bkp
    strcat(logString,"open file to extract content - ");
    strcat(logString,myBkp);
    doLog(logString);
    free(logString);
    logString=(char*)malloc(200*sizeof(char));
    
    //mybuffer
    char *buf = (char*)malloc(dimBuffer*sizeof(char));
    //read buffer of dimBuffer size once
    fread(buf, dimBuffer, 1, in);
    
    //char* support. using during the code for storing data
    char *path=(char*)malloc(200*sizeof(char)) ;
    char *name=(char*)malloc(200*sizeof(char)) ;
    char *lungName=(char*)malloc(20*sizeof(char)) ;
    char *lungBuffer=(char*)malloc(200*sizeof(char)) ;
    char *folderName=(char*)malloc(20*sizeof(char)) ;
    char *file=(char*)malloc(100*sizeof(char)) ;
    char *fullPath = (char*)malloc(200*sizeof(char));
    //while my buffer is not null read it
    while (buf[i]!='\0'){
        
        //il my character is 'f' the next data is about a folder file
        if(buf[i] == 'f'){
            i++; //skip 'f'
            y=0; //reset y
            
            //while i don't find a '.' that is a name of Folder
            while (buf[i]!='.') {
                folderName[y]=buf[i];
                y++;i++;
            }
            i++;  //skip '.'
            
            
            //log file - create new directory
            strcat(logString,"make new dir in ");
            strcat(logString,folderName);
            doLog(logString);
            logString=(char*)malloc(200*sizeof(char));
            
            //mk dir with error handling
            if(mkdir(folderName, 0777)<0){
            
                //log file - error to create new directory
                strcat(logString,"fail to create new directory in ");
                strcat(logString,folderName);
                doLog(logString);
                logString=(char*)malloc(200*sizeof(char));
                
                printf("$: -  Error to mkDir\n \tFolder already Exist!\n");
                return -1;
            }
            continue;
        }
         
        y=0; //reset y
        
        //get File-path
            while (buf[i]!='.') {
                path[y]=buf[i];
                y++;i++;
            }
            path[y]='/';
            i++;
            y=0;//reset
        //get length
            while (buf[i]!='.') {
                lungName[y]=buf[i];
                i++;y++;
            }
            int ln = atoi(lungName);
            int pln= atoi(path);
            i++;
            y=0;//reset
        //get nameOfFile
            while (y<ln){
                name[y]=buf[i];
                i++;y++;
            }
            y=0;//reset
        
        //full path of file
            fullPath = (char*)malloc(100*sizeof(char));
            strcat(fullPath,path);
            strcat(fullPath,name);
        
        //get buffer dimension
            while (buf[i]!='.') {
                lungBuffer[y]=buf[i];
                i++;y++;
            }
            i++;
            y=0;
        
        //create a new char* in memory with correct size
        file=(char*)malloc(atoi(lungBuffer)*sizeof(char)) ;
        //copy the file into file[]
        while (y<atoi(lungBuffer)) {
            file[y]=buf[i];
            y++;i++;
        }
        y=0;//reset

        //file Descriptor for write()
        FILE *w = NULL;
        
        //log file - create new file
        strcat(logString,"create new file: ");
        strcat(logString,name);
        doLog(logString);
        logString=(char*)malloc(200*sizeof(char));
        
        //if creat()<0 file alredy exist! I give all permission
        if(creat(name, 0777)<0){
            //log file - error in create new file
            strcat(logString,"error to create new file. ");
            doLog(logString);
            free(logString);
            logString=(char*)malloc(200*sizeof(char));
            
            printf("error to creat.");
            return -1;
        }
        else{
            //else fopen() in "wb" WriteByte mode
            w=fopen(fullPath, "wb");
        }
        
        //write the file
        fwrite(file,atoi(lungBuffer),1, w);
        fclose(w);
        
        free(fullPath);
        free(path);
        free(name);
        free(lungName);
        free(lungBuffer);
        free(folderName);
        free(file);
        //new malloc for arrays
        fullPath = (char*)malloc(200*sizeof(char));
        path=(char*)malloc(200*sizeof(char)) ;
        name=(char*)malloc(200*sizeof(char)) ;
        lungName=(char*)malloc(20*sizeof(char)) ;
        lungBuffer=(char*)malloc(200*sizeof(char)) ;
        folderName=(char*)malloc(20*sizeof(char)) ;
        file=(char*)malloc(100*sizeof(char)) ;
    }
    
    
    //log file - return correct execution
    strcat(logString,"return correct execution");
    doLog(logString);
    free(logString);
    logString=(char*)malloc(200*sizeof(char));
    
    free(buf);
    
    return 0;
}














