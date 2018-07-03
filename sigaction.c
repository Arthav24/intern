#define _GNU_SOURCE

#include <poll.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>


volatile int flag=0;
char cstr[100];
int iret,ret,p[2],f1;
void *thread_1(void *ptr);
char str[] = "start";
char str1[] = "end";
void handle(int sig)
{
    printf("reading pipe");
    read(p[0], &cstr, 6);
    
	
		
}
struct sigaction sg;
 
int main(){
	
if (pipe(p)==-1)
    {
        printf("Pipe Failed" );
        return 1;
    }

if(wiringPiSetup()==-1){
		exit(0);}
		pinMode(15,OUTPUT);
		char *led1="15";

pthread_t t1;
iret = pthread_create( &t1, NULL, thread_1,(void*)led1);
if(iret<0){
     printf("Error starting thread 1");}
 char c;  
       

 while(1){
 printf("enter\n");    
 scanf("%c",&c);
 switch(c){
	 case '1': ret=write(p[1], str, strlen(str)+1);
	 printf("%d",ret);
	 break;
	 case '2':write(p[1], str1, strlen(str1)+1);
			  pthread_join( t1, NULL);
			  printf("Thread stopped");
			  delay(5000);
			  exit(0);
			  break;
	 default:break;
	 
	 
	 }    }
     
     
     
     
return 0;}     
     
 
void *thread_1( void *ptr)
{
	int pin=atoi(ptr);
	sg.sa_handler=handle;
	sg.sa_flags=0;
	
	
	int pid=getpid();
	
	f1=fcntl(p[0],F_GETFL);
	f1|= O_ASYNC|O_NONBLOCK;
	fcntl(p[0],F_SETFL,f1);
	fcntl(p[0], F_SETSIG,SIGIO);
	sigemptyset(&sg.sa_mask);
	sigfillset(&sg.sa_mask);
	fcntl(p[0], F_SETOWN,pid );
	sigaction(SIGIO,&sg,NULL);
	
	
	while(1){
	

	if(strncmp(cstr,str,6)==0){flag=1;}
	else if (strncmp(cstr,str1,3)==0){pthread_exit(NULL);}
	
	if(flag==1){		
	digitalWrite(pin,1);
	delay(100);
	digitalWrite(pin,0);
	delay(100);
}}
} 

