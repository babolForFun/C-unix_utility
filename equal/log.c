


#include "lib.h"


void doLog(char* msg){
    
    //file descriptor
    int fdw;
    
    //make directory for log
    mkdir("/var/log/utility", 0777);
    
    //months array
    char *month[] = {"Jan.", "Feb.", "Mar.", "Apr.", "May.", "Jun.","Jul.", "Aug.", "Sept", "Oct","Nov", "Dec."};
    
    //open with |O_CREAT flag in mkbkp.log
    if ((fdw=open("/var/log/utility/equal.log", O_RDWR | O_APPEND | O_CREAT,0777))<0) { //error handling
        printf("error open file and creat a new .log \n");
        exit(-1);
    }else{
        
        //get the time
        time_t rawtime;
        time (&rawtime);
        
        //struct tm for time
        myTime = localtime(&rawtime);
        
        //array with buffer to write in .log and other support array
        char* logMsg = (char*)malloc(200*sizeof(char));
        char* tmp = (char*)malloc(100*sizeof(char));
        
        //build string
        strcat(logMsg, month[myTime->tm_mon]);
        strcat(logMsg, " ");
        
        sprintf (tmp,"%d",myTime->tm_mday);
        strcat(tmp, "  ");
        strcat(logMsg,tmp);
        
        sprintf (tmp,"%d",myTime->tm_hour);
        strcat(tmp, ":");
        strcat(logMsg,tmp);
        
        sprintf (tmp,"%d",myTime->tm_min);
        strcat(tmp, ":");
        strcat(logMsg,tmp);
        
        sprintf (tmp,"%d",myTime->tm_sec);
        strcat(tmp, "  [root] - ");
        strcat(logMsg,tmp);
        strcat(logMsg,msg);
        strcat(logMsg,"\n");
        
        
        //write my sting in .log
        write(fdw, logMsg, strlen(logMsg));
    }
    
    //close file descriptor
    close(fdw);
    
}



















