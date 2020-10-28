#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,char *argv[])
{	
	int i;
	int length = 0;
	if(argc>1){
		if(!isdigit(*argv[1])){
			printf("The first argument should be an integer.\n");
			exit(0);
		}
		/*for(i=2; i<argc; i++){
			length+=strlen(argv[i])+1;
		}
		char cmd[length];
		int j;
		int k=0;
		for(i=2; i<argc; i++){
			for(j=0; j<strlen(argv[i]); j++){
				cmd[k]=argv[i][j];
				k++;
			}
			cmd[k]=' ';
			k++;
		}
		cmd[k-1]=NULL;*/
		// This was from when I tried to use the system() command but it just didn't work right with fork()
		char *args[argc-1];
		int k=0;
		for(i=2; i<=argc; i++){
			args[k] = argv[i]; 
			k++;
		}
		args[k-1]=NULL;
		pid_t pid;
		int status;
		for(i=0; i<atoi(argv[1]); i++){
			if((pid=fork())==0){
				if(execvp(args[0],args)==-1){
					exit(EXIT_FAILURE);
				}
			}
		}
		for(i=0; i<atoi(argv[1]); i++){
			pid = wait(&status);	
			if(!status){
				printf("Process: %d has executed successfully\n", pid);
			} else {
				printf("Process: %d did not execute successfully. Exit status: %d\n", pid, status);
			}
		}
		
		} else {
		printf("Error: Command needs arguments\n");
		exit(0);
	}
	return 0;
}

