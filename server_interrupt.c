#define _GNU_SOURCE

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <wiringPi.h>
#include <fcntl.h>
#include <signal.h>

int iret,ret,f1;
void *thread_1();
struct sigaction sg;
int in,n,fd=0;
char buff[1024];
char nbuff[1024];
struct sockaddr_in server; 


void handle(int sig)
{
	printf("executing handle\n");
	close (fd);
	bzero(buff,256);
	//bzero(nbuff,256);
    n = recv(in, buff, 256,0);
	printf("Received: %s",buff);
	bzero(buff,256);
		
}

int main(){
memset(&server, '0', sizeof(server));
memset(buff, '0',sizeof(buff));


	fd = socket(AF_INET, SOCK_STREAM, 0);
    	if(fd<0)
	{
		perror("Client Error: Socket not created succesfully");
		return 0;
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(8080); 
        server.sin_addr.s_addr = htonl(INADDR_ANY);
   	bind(fd, (struct sockaddr*)&server, sizeof(server)); 
	
	listen(fd, 10); 
	in = accept(fd, (struct sockaddr*)NULL, NULL);

	pthread_t t1;
	iret = pthread_create( &t1, NULL, thread_1,NULL);
	if(iret<0){
		printf("Error starting thread 1");}
		
	pthread_join(t1,NULL);
			
	close(in);
			exit(0);
}

void *thread_1()
{
	sg.sa_handler=handle;
	sg.sa_flags=0;
	int pid=getpid();
	f1=fcntl(in,F_GETFL);
	f1|= O_ASYNC|O_NONBLOCK;
	fcntl(in, F_SETFL,f1);
	fcntl(in, F_SETSIG,SIGIO);
	fcntl(in, F_SETOWN,pid );
	sigemptyset(&sg.sa_mask);
	sigfillset(&sg.sa_mask);

	sigaction(SIGIO,&sg,NULL);
	while(1);
	
	
	
} 
