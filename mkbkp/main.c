/*
 
 PROJECT NOTE
 
 *  CREATE BACKUP:     mkbkp -c -f<nomeArchivio> /pathBkp
 *  EXTRACT BACKUP:    mkbkp -x -f<nomeArchivio> /directoryCorrente
 *  SHOW BACKUP:       mkbkp -t -f<nomeArchivio>
 
 
 */


#include "fun.h"

int main(int argc, char**argv){
    
    char *logString = (char*)malloc(200*sizeof(char));
    
    if(argc<2){
        printf("$$?Bad shell command. 3 argumets request.  mkbkp -c[-t][-x] -f <fileName> [path] \n\n");
        return -1;
    }
    
    //index for getopt()
    int index;
    
    if(strncmp(argv[1],"-c",2)==0 || strncmp(argv[1],"-x",2)==0 || strncmp(argv[1],"-t",2)==0){  //control that the second argument is correct!
        if(strncmp(argv[2],"-f",2)==0){     //control third argument is "-f"
            while((index = getopt(argc,argv,"cxtf:")) != -1){
                //flag option
                switch(index){
                        //call the function according to the choice socket
                    case 'c':
                        
                        //log file - create backup file
                        strcat(logString,"correct choice for create backup file: ");
                        doLog(logString);
                        free(logString);
                        logString=(char*)malloc(200*sizeof(char));

                        if(doBkp2(argc,argv)==-1){
                            printf("error to create .bkp\n");
                            return -1;
                        }else{
                            printf("\n - backup file properly executed\n");
                        }
                        break;
                        
                    case 'x':
                        
                        //log file - extract from bkp file
                        strcat(logString,"correct choice for extract from bkp file: ");
                        doLog(logString);
                        free(logString);
                        logString=(char*)malloc(200*sizeof(char));
                        
                        
                        if(exbkp(argv[3])==0){
                            printf("finish to extract\n");
                            return 0;
                        }else{
                            printf("Fail to extract! \n");
                            return -1;
                        }
                        break;
                    case 't':
                        if(showMyBkp(argv[3])==0){
                            return 0;
                        }
                        else{
                            printf("Wrong number or name \n");
                            return -1;
                        }
                        break;
                    default:
                        break;
                }
            }
        }else{
            
            //log file - bad command
            strcat(logString,"$$?Bad shell command. Second choice must be '-f'");
            doLog(logString);
            free(logString);
            logString=(char*)malloc(200*sizeof(char));
            printf("$$?Bad shell command. Second choice must be '-f'"); }
    }
    else{
        //log file - bad command
        strcat(logString,"$$?Bad shell command. Correct instruction is   mkbkp -c[-t][-x] -f <fileName> [path]");
        doLog(logString);
        free(logString);
        logString=(char*)malloc(200*sizeof(char));

        printf("$$?Bad shell command. Correct instruction is   mkbkp -c[-t][-x] -f <fileName> [path]"); }
    
    printf("\n");
    
    return 0;
}

