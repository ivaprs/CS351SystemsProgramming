#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8081

double multiply(double a, double b){ return a*b;}
double divide(double a, double b){ if(b == 0.0) return 0; else return a/b;}
double add(double a, double b){ return a+b;}
double subtract(double a, double b){ return a-b;}

int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char msg[20];
	double ret_val = 0.0;
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0){
		perror("listen");
		exit(EXIT_FAILURE);
	}
	new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
	if (new_socket<0){
		perror("accept");
		exit(EXIT_FAILURE);
	}
	while(1){
		valread = recv(new_socket, buffer, 1024, 0);
		if(!strcmp("add", buffer)){
			ret_val = add((double)rand()/RAND_MAX,(double)rand()/RAND_MAX);		
		} else if (!strcmp("subtract", buffer)){	
			ret_val = subtract((double)rand()/RAND_MAX,(double)rand()/RAND_MAX);		
		} else if (!strcmp("multiply", buffer)){
			ret_val = multiply((double)rand()/RAND_MAX,(double)rand()/RAND_MAX);		
		} else if (!strcmp("divide", buffer)){
			ret_val = divide((double)rand()/RAND_MAX,(double)rand()/RAND_MAX);		
		} else {
			break;
		}
		snprintf(msg, 20, "%f", ret_val);
		send(new_socket, msg, strlen(msg), 0);
	}
	return 0;
}
