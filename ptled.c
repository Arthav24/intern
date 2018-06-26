#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <wiringPi.h>


void *thread_1( void *ptr );
void *thread_2( void *ptr );

int main()

{
	if(wiringPiSetup()==-1){
		exit(0);}
		pinMode(15,OUTPUT);
		pinMode(16,OUTPUT);
     pthread_t t1, t2;
     char *led1="15";
     char *led2 = "16";
     int  iret1, iret2;

     iret1 = pthread_create( &t1, NULL, thread_1, (void*)led1);
     iret2 = pthread_create( &t2, NULL, thread_2, (void*)led2);


     pthread_join( t1, NULL);
     pthread_join( t2, NULL); 

     printf("Thread 1 returns: %d\n",iret1);
     printf("Thread 2 returns: %d\n",iret2);
     
     
     exit(0);
     
}

void *thread_1( void *ptr )
{
	int p=atoi(ptr);
	while(1){
	digitalWrite(p,1);
	delay(500);
	digitalWrite(p,0);
	delay(500);
}}
void *thread_2( void *ptr )
{
	int pin=atoi(ptr);
	while(1){
	digitalWrite(pin,1);
	delay(100);
	digitalWrite(pin,0);
	delay(100);
}}

