#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <sys/time.h>
#include <string.h>
#include <fcntl.h>
#include <malloc.h>

#define MSG "* running fileio %s workload with %s blocks and %s process(es) with each file size of %s for a total of %d bytes\n"

#define USAGE "usage: ./fileio <workload> <block_size> <num_procs> <file_size>\n" \
"     - workload: WS / WR / RS / RR \n" \
"     - block_size: 4K / 64K / 1M / 16M \n" \
"     - num_procs: 1 / 2 / 4 / 8\n" \
"     - file_size: 524288 / 1048576 / 2097152 / 4194304 / 134217728 / 268435456 / 536870912 / 1073741824 \n" \
"     - WS = write-sequential \n" \
"     - WR = write-random \n" \
"     - RS = read-sequential \n" \
"     - RR = read-random \n"

int main(int argc, char **argv)
{
	if (argc != 5) {
		printf(USAGE);
		exit(1);
	} else {
		printf(MSG, argv[1], argv[2], argv[3], argv[4], atoi(argv[3])*atoi(argv[4]));
	}


	struct timeval start;
	struct timeval end;
	int fd;
	size_t block_size;
	int bytes_read=0;
	int status;
	
	if(!strcmp(argv[2], "4K")){
		block_size=4*1024;
	} else if(!strcmp(argv[2],"64K")){
		block_size=64*1024;
	} else if(!strcmp(argv[2], "1M")){
		block_size=1024*1024;
	} else if(!strcmp(argv[2], "16M")){
		block_size=16*1024*1024;
	}
	gettimeofday(&start,NULL);	
	for(int i=0; i<atoi(argv[3]); i++){
		if((fork())==0){
			char BUFFER[20];
			if(atoi(argv[4])==1073741824){
				snprintf(BUFFER, 20, "files/1G%d.txt",(i+1));
			} else if (atoi(argv[4])==536870912){
				snprintf(BUFFER, 20, "files/512M%d.txt",(i+1));
			} else if (atoi(argv[4])==268435456){
				snprintf(BUFFER, 20, "files/256M%d.txt",(i+1));
			} else if (atoi(argv[4])==134217728){
				snprintf(BUFFER, 20, "files/128M%d.txt",(i+1));
			} else if (atoi(argv[4])==4194304){
				snprintf(BUFFER, 20, "files/4M%d.txt",(i+1));
			} else if (atoi(argv[4])==2097152){
				snprintf(BUFFER, 20, "files/2M%d.txt",(i+1));
			} else if (atoi(argv[4])==1048576){
				snprintf(BUFFER, 20, "files/1M%d.txt",(i+1));
			} else if (atoi(argv[4])==524288){
				snprintf(BUFFER, 20, "files/512K%d.txt",(i+1));
			}
			if(!strcmp(argv[1], "WS")||!strcmp(argv[1], "WR")){
				fd=open(BUFFER, O_WRONLY|O_DIRECT);
			} else if(!strcmp(argv[1], "RS")||!strcmp(argv[1], "RR")){
				fd=open(BUFFER, O_RDONLY|O_DIRECT);
			}
			char *BUFF=memalign(4096, block_size);
			while(bytes_read<atol(argv[4])){
				if(!strcmp(argv[1], "RR")||!strcmp(argv[1], "WR")){
					size_t random =(unsigned long int)((double)rand()/(double)RAND_MAX)*(atol(argv[4])-block_size);
					lseek(fd, random, SEEK_SET);
				}
				if(!strcmp(argv[1], "WS")||!strcmp(argv[1], "WR")){
					bytes_read+=write(fd,BUFF,block_size);
				} else if(!strcmp(argv[1], "RS")||!strcmp(argv[1], "RR")){
					bytes_read+=read(fd,BUFF,block_size);
				}
			}
		exit(0);
		}
	}
	for(int i=0; i<atoi(argv[3]); i++){
		wait(&status);
	}
	gettimeofday(&end,NULL);
	double time = (double)(end.tv_sec-start.tv_sec)+((double)(end.tv_usec-start.tv_usec)/1000000);
	if(!strcmp(argv[2],"4K")){
		printf("Latency is %f Operations/Second\n", 4194304/block_size/time);
	} else {
		printf("Throughput is %f MiB/Second\n",  1024.0/time);
	}
	return 0;
}
