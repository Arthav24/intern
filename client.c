#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
	int fd = 0;
	char buff[1024];
	
	

	
	memset(buff, '0',sizeof(buff));	

	
	fd = socket(AF_INET, SOCK_STREAM, 0);
    	if(fd<0)
	{
		perror("Client Error: Socket not created succesfully");
		return 0;
	}
	
	struct sockaddr_in server; 
	memset(&server, '0', sizeof(server)); 

		
	server.sin_family = AF_INET;
	server.sin_port =  htons(8080);

	int in = inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
	if(in<0)
	{
		perror("Client Error: IP not initialized succesfully");
		return 0;
	}

	in = connect(fd, (struct sockaddr *)&server, sizeof(server));
	if(in<0)
	{
		perror("Client Error: Connection Failed.");
		return 0;
	}    	

	 while(1)
	{
		printf("message: ");
    		bzero(buff,256);
    		fgets(buff,255,stdin);
    		
		    printf("\nSending %s ",buff);
	
    		in = send(fd,buff,strlen(buff),0);
		   
		    bzero(buff,256);
		    in = recv(fd,buff,255,0);
		    
		    printf("\nReceived %s ",buff);
	}
	close(fd);
	return 0;
}
