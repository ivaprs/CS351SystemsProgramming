#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#define MSG "* running cpubench %s using %s with size %s and %s threads...\n"

#define USAGE "usage: ./cpubench <mode> <type> <size> <threads> \n" \
"     - mode: flops / matrix \n" \
"     - type: single / double \n" \
"     - size: 10 / 100 / 1000 / 1024 / 4096 / 16386 \n" \
"     - threads: 1 / 2 / 4 \n"

#define GIGAFLOPS 1000000000
#define GIGABYTES 1024*1024*1024

typedef struct targ{
	int size;
	int tid;
	int threads;
	int** mat1;
	int** mat2;
	int** res;
	double** matd1;
	double** matd2;
	double** resd;
};

// This function multiplies mat1[][] and mat2[][],
// and stores the result in res[][]
void *multiply_int(void *arg)
{
	struct targ *t = (struct targ *) arg;
	int i, j, k;
	for(i=(t->tid)*(t->size)/(t->threads); i<(1+(t->tid))*(t->size)/(t->threads); i++){
		for(j=0; j<t->size; j+=2){
			for(k=0; k<t->size; k++){
				t->res[i][j] += t->mat1[i][k] * t->mat2[i][k];
			}
		}
	}
	return NULL;	
}

// This function multiplies mat1[][] and mat2[][],
// and stores the result in res[][]
void *multiply_double(void *arg)
{
	struct targ *t = (struct targ *) arg;
	int i, j, k;
	for(i=(t->tid)*(t->size)/(t->threads); i<(1+(t->tid))*(t->size)/(t->threads); i++){
		for(j=0; j<t->size; j+=2){
			for(k=0; k<t->size; k++){
				t->resd[i][j] += t->matd1[i][k] * t->matd2[i][k];
			}
		}
	}
	return NULL;
}


void *compute_flops_int(void *arg)
{
	struct targ *t = (struct targ *) arg;
	unsigned long long index;
	unsigned long long loops = (unsigned long long)(t->size)*GIGAFLOPS/(t->threads);
	int a,b,c,d = 1;
	for (index=0;index<loops/10;index++)
	{
		d = a+b*c;	
		d = a+b*c;	
		d = a+b*c;	
		d = a+b*c;	
		d = a+b*c;
		asm("");	
	}
	return NULL;
}

void *compute_flops_double(void *arg)
{
	struct targ *t = (struct targ *) arg;
	unsigned long long index;
	unsigned long long loops = (unsigned long long)(t->size)*GIGAFLOPS/(t->threads);
	double a,b,c,d = 1.0;
	for (index=0;index<loops/10;index++)
	{
		d = a+b*c;	
		d = a+b*c;	
		d = a+b*c;	
		d = a+b*c;	
		d = a+b*c;
		asm("");	
	}	
	return NULL;
}

int main(int argc, char **argv)
{
	time_t t;
	srand((unsigned) time(&t));
    if (argc != 5) 
    {
        printf(USAGE);
        exit(1);
    } 
    else 
    {
		int mode = -1;
        if(strcmp(argv[1],"flops") == 0)
        	mode = 0;
        else if(strcmp(argv[1],"matrix") == 0)
        	mode = 1;
        else
        	mode = -1;

		int type = -1;
        if(strcmp(argv[2],"single") == 0)
        	type = 0;
        else if(strcmp(argv[2],"double") == 0)
        	type = 1;
        else
        	type = -1;


        int size = atoi(argv[3]);
        int num_threads = atoi(argv[4]);
	pthread_t tid[num_threads];
	int i,j;
	struct targ thr[num_threads];
		struct timeval start, end;

		if (mode == 0 && type == 0)
		{
			for(i=0; i<num_threads; i++){
				thr[i].threads = num_threads;
				thr[i].size = size;
				thr[i].tid = i;
			}
			gettimeofday(&start, NULL);
			for(i=0; i<num_threads; i++){
				pthread_create(&tid[i], NULL, compute_flops_int, &thr[i]);
			}
			for(i=0; i<num_threads; i++)
				pthread_join(tid[i],NULL);
			gettimeofday(&end, NULL);
		}
		else if (mode == 0 && type == 1)
		{
			for(i=0; i<num_threads; i++){
				thr[i].threads = num_threads;
				thr[i].size = size;
				thr[i].tid = i;
			}
			gettimeofday(&start, NULL);
			for(i=0; i<num_threads; i++){
				thr[i].tid = i;
				pthread_create(&tid[i], NULL, compute_flops_double, &thr[i]);
			}
			for(i=0; i<num_threads; i++)
				pthread_join(tid[i],NULL);
			gettimeofday(&end, NULL);
		}		
		else if (mode == 1 && type == 0)
		{	
			int **A, **B, **C;
			A = (int**) malloc(sizeof(int*) * size);
			B = (int**) malloc(sizeof(int*) * size);
			C = (int**) malloc(sizeof(int*) * size);
			for(i = 0; i<size; i++){
				A[i] = (int*) malloc(sizeof(int) * size);
				B[i] = (int*) malloc(sizeof(int) * size);
				C[i] = (int*) malloc(sizeof(int) * size);
				
				for(j=0; j<size; j++){
					A[i][j] = (int)(i*2);
					B[i][j] = (int)(i*2);
				}
			}
			//transpose matrix B
			for(i = 0; i<size; i++){
				for(j = 0; j<size; j++){
					C[i][j] = B[j][i];
				}
			}
			for(i = 0; i<size; i++){
				for(j = 0; j<size; j++){
					B[i][j] = C[i][j];
					C[i][j] = 0;
				}
			}
			for(i=0; i<num_threads; i++){
				thr[i].mat1 = A;
				thr[i].mat2 = B;
				thr[i].res = C;
				thr[i].tid = i;
				thr[i].threads = num_threads;
				thr[i].size = size;
			}
			gettimeofday(&start, NULL);
			for(i=0; i<num_threads; i++){
				pthread_create(&tid[i], NULL, multiply_int, (void *) &thr[i]);
			}
			for(i=0; i<num_threads; i++){
				pthread_join(tid[i], NULL);
			}
			gettimeofday(&end, NULL);
			for(i=0; i<size; i++){
				free(A[i]);
				free(B[i]);
				free(C[i]);
			}
			free(A);
			free(B);
			free(C);
		}
		else if (mode == 1 && type == 1)
		{	
			double **A, **B, **C;
			A = (double**) malloc(sizeof(double*) * size);
			B = (double**) malloc(sizeof(double*) * size);
			C = (double**) malloc(sizeof(double*) * size);
			for(i = 0; i<size; i++){
				A[i] = (double*) malloc(sizeof(double) * size);
				B[i] = (double*) malloc(sizeof(double) * size);
				C[i] = (double*) malloc(sizeof(double) * size);
				
				for(j=0; j<size; j++){
					A[i][j] = (double)(i*size+j);
					B[i][j] = (double)(i*size+j);
				}
			}
			//transpose matrix B
			for(i = 0; i<size; i++){
				for(j = 0; j<size; j++){
					C[i][j] = B[j][i];
				}
			}
			for(i = 0; i<size; i++){
				for(j = 0; j<size; j++){
					B[i][j] = C[i][j];
					C[i][j] = 0.0;
				}
			}
			for(i=0; i<num_threads; i++){
				thr[i].mat1 = A;
				thr[i].mat2 = B;
				thr[i].res = C;
				thr[i].tid = i;
				thr[i].threads = num_threads;
				thr[i].size = size;
			}
			gettimeofday(&start, NULL);
			for(i=0; i<num_threads; i++){
				pthread_create(&tid[i], NULL, multiply_int, (void *) &thr[i]);
			}
			for(i=0; i<num_threads; i++){
				pthread_join(tid[i], NULL);
			}
			gettimeofday(&end, NULL);
			for(i=0; i<size; i++){
				free(A[i]);
				free(B[i]);
				free(C[i]);
			}
			free(A);
			free(B);
			free(C);	
		}
		else
		{
        	printf(USAGE);
			printf("unrecognized option, exiting...\n");
        	exit(1);
		}
		double elapsed_time_sec = (((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)))/1000000.0;
		double num_giga_ops = 0;
		
		if ((unsigned long long)size*GIGAFLOPS < 0)
		{
			printf("error in size, check for overflow; exiting...\n");
			exit(1);
		}
		if (elapsed_time_sec < 0)
		{
			printf("error in elapsed time, check for proper timing; exiting...\n");
			exit(1);
		}
		if (elapsed_time_sec == 0)
		{
			printf("elapsed time is 0, check for proper timing or make sure to increase amount of work performed; exiting...\n");
			exit(1);
		}
			
		
		if (mode == 0)
			num_giga_ops = size;
		else if (mode == 1)
			num_giga_ops = (unsigned long long)size*size*size/(GIGABYTES);
		double throughput = num_giga_ops/elapsed_time_sec;
		printf("mode=%s type=%s size=%d threads=%d time=%lf throughput=%lf\n",argv[1],argv[2],size,num_threads,elapsed_time_sec,throughput);
 
    }

    return 0;
}
