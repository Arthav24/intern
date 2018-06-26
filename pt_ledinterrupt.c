#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <wiringPi.h>

int flag=0,ret1,ret2;
void *thread_1( void *ptr );
void *thread_2( void *ptr );
void myInterrupt(void);
int main()

{
	if(wiringPiSetup()==-1){
		exit(0);}
		pinMode(15,OUTPUT);
		pinMode(16,OUTPUT);
		pinMode(1,OUTPUT);
		digitalWrite(1,HIGH);
		pinMode(4,INPUT);
		pullUpDnControl(4,PUD_DOWN);
		
     pthread_t t1, t2;
     char *led1="15";
     char *led2="16";
     int  iret1, iret2;
	 int *ptr[2];
     iret1 = pthread_create( &t1, NULL, thread_1, (void*)led1);
     iret2 = pthread_create( &t2, NULL, thread_2, (void*)led2);

	if ( wiringPiISR (4, INT_EDGE_RISING, &myInterrupt) < 0 ) {
      return 1;
  }
	if(iret1<0){
     printf("Error starting thread 1");}
    if(iret2<0){ 
     printf("error starting thread 2");}
     
     
		pthread_join( t1, (void **)&(ptr[0]));
		 printf("Thread1 stoped\n");
		pthread_join( t2, (void **)&(ptr[1]));
		 printf("Thread2 stoped");
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
	if(flag==1)
		pthread_exit(&ret1);
	else
		continue;
}}
void *thread_2( void *ptr )
{
	int pin=atoi(ptr);
	while(1){
	digitalWrite(pin,1);
	delay(100);
	digitalWrite(pin,0);
	delay(100);
	if(flag==2)
		pthread_exit(&ret2);
	else
		continue;
}}
void myInterrupt(void) {
   flag+=1;

}

