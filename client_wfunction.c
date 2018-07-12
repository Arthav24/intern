#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int init_socket();
int connect_socket();
int fd = 0,in,f=0,ch,flag_connect=0;
	char buff[1024];
	struct sockaddr_in server; 
int main()
{
	memset(buff, '0',sizeof(buff));	
	printf("Initialising\n");
	printf("1. create socket\n");
	printf("2. connect to socket \n");
	while(flag_connect!=1){
	scanf("%d",&ch);
	switch(ch){
		case 1:if (init_socket()==0){
			   printf("Socket Created\n");
		      f=1;}
		      break;
	case 2:	if(f==1){printf("connecting ...... \n");
					if(connect_socket()==0)
						printf("successeful\n");
						flag_connect=1;}
		else{printf("create socket first\n");}
		break;
	default : break;
}}
	
    	
	 while(1)
	{		printf("Enter message\n");
			bzero(buff,256);
    		fgets(buff,255,stdin);
		    printf("\nSending %s ",buff);
		    in = send(fd,buff,strlen(buff),0);    
	}
	close(fd);
	return 0;
}

int init_socket(){
	fd = socket(AF_INET, SOCK_STREAM, 0);
    	if(fd<0)
	{
		perror("Client Error: Socket not created succesfully");
		return 0;
	}
	
	
	memset(&server, '0', sizeof(server)); 

		
	server.sin_family = AF_INET;
	server.sin_port =  htons(8080);

	in = inet_pton(AF_INET, "192.168.1.138", &server.sin_addr);	if(in<0)
	{
		perror("Client Error: IP not initialized succesfully");
		return 0;
	}

	return 0;
	}

int connect_socket(){
	in = connect(fd, (struct sockaddr *)&server, sizeof(server));
	
	if(in<0)
	{
		perror("Client Error: Connection Failed.");
		return 0;
	}
	return 0;
}	
	




