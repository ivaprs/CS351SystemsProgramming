#include <stdio.h>
#include <string.h>
int hash(char*);

int main(int argc, char *argv[]){
	if(argc > 2){
		printf("This command uses only one argument. If your argument has spaces please use quotations");
		return(-1);
	} else if(argc == 1){
		printf("This command uses one argument. You inputed no arguments");
		return(-1);
	}
	printf("OUTPUT: %d\n", hash(argv[1]));
	return 0;
}

int hash(char *arr){
	int size = strlen(arr);
	int i;
	int total=0;
	for(i=0;i<size;i++){
		total+=arr[i];
	}
	return total;
}
