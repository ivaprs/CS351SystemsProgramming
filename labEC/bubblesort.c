#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void bubblesort(int [], int);
void swap(int*,int*);

int main()
{
	int BUFF = 50;
	int list[10];
	FILE *file;
	file = fopen("pp2.txt","r");
	char str[BUFF];
	fgets(str, BUFF, file);
	char * split = strtok(str," ");
	int i=0;
	while(split != NULL){
		list[i]=atoi(split);
		i++;
		split = strtok(NULL," ");
	}
	int size = sizeof(list)/sizeof(list[0]);
	printf("INPUT: ");
	for(i=0; i<10; i++){
		printf("%d ",list[i]);
	}
	printf("\n");
	bubblesort(list, size);
	printf("OUTPUT: ");
	for(i=0; i<10; i++){
		printf("%d ",list[i]);
	}
	printf("\n");
	return 0;
}

void bubblesort(int list[], int i){
	for(int j = 0; j<i-1; j++){
		for(int k = 0; k<i-j-1; k++){
			if(list[k+1]<list[k]){
				swap(&list[k+1], &list[k]);
			}
		}
	}
}

void swap(int *first, int *second){
	int temp = *first;
	*first = *second;
	*second = temp;
}
