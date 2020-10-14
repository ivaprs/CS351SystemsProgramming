#include <stdio.h>
void bubblesort(int arr[], int i){
	for(int a = 0; a < i-1; a++){
		for(int b = 0; b < n-(a+1); b++){
			if(arr[b] > arr[b+1]){
				swap(&arr[b], &arr[b+1]);
			}
		}
	}
}

void swap(int *p1,int *p2){
	int temp = *p1;
	*p1=*p2;
	*p2=temp;
}

int main()
{
	FILE *fp = fopen(argv[1], "r");
	fscanf(fp, "%[^\n]", c);
	
	return 0;
}

