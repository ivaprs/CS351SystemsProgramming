#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s STRING1 STRING2\n", argv[0]);
    printf("       %s -d STRING\n", argv[0]);
    exit(1);
  }
  int r = strcmp(argv[1], "-d");
  int lenArg1 = strlen(argv[1]);
  int lenArg2 = strlen(argv[2]);
  if(r!=0 && lenArg1 != lenArg2){printf("STRING1 and STRING2 must have the same length\n"); exit(1);}  
  char arg1[lenArg1];
  char arg2[lenArg2];
  for(int i = 0; i<lenArg1; i++){arg1[i]=argv[1][i];}
  for(int i = 0; i<lenArg2; i++){arg2[i]=argv[2][i];}
  int BUFF = 16384;
  char input[BUFF];
  while(fgets(input, BUFF, stdin)){
    bool f;
    char output[BUFF];
    for(int i = 0; i<BUFF; i++){output[i]=0;}    
    int lenIn = strlen(input);
    if(r==0){
      int k = 0;
      for(int i = 0; i<lenIn; i++){
	f=false;
	for(int j = 0; j<lenArg2; j++){
	  if(input[i] == arg2[j]){
	    f=true;
	  }
	}
	if(!f){output[k] = input[i]; k++;}
      }
    }
    else{
    for(int i = 0; i<lenIn; i++){
      f=false;
      for(int j = 0; j<lenArg1; j++){
	if(input[i] == arg1[j]){
	  output[i] = arg2[j];
	  f=true;
	 }
      }
      if(!f){output[i] = input[i];}
    }
    }
    printf("%s", output);
    if(feof(stdin)){return 0;}
  }
  return 0;
}
