#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void *convert();
int chan=0,t,flag=9,i=0,fd[2];
int ch;
int speed=10000000;
char instr[10]; 
unsigned char buf[3];
int tbuf[]={700,710,730,750,800,850,900,960,1000,1010,700,750,1100,1200,1400,1500,1600,1700,1800,1750,1700,1650,1600,1550,1400,1300,1200,1100
	,1000,800,700,710,730,750,800,850,900,960,1000,1010,700,750,1100,1200,1400,1500,1600,1700,1800,1750,1700,1650,1600,1550,1400,1300,1200,1100
	,1000,800};
pthread_t t1;
char m[]="stop";

int main(){
	printf("Initializing DAC\n");
	if(wiringPiSPISetupMode(chan,speed,0)==-1){
			printf("Cannot initialise SPI \n");
			return 1;}
			buf[0]=0x55;
			buf[1]=0x30;
			buf[2]=0x05;
			wiringPiSPIDataRW (chan,buf,3);
			delayMicroseconds(50);
			
			pipe(fd);
			pthread_create( &t1, NULL, convert, NULL);
			
	printf("Enter Command\n");
	printf("1.Start Analog O/P\n");
	printf("2.Stop Analog O/P\n");
	printf("3.Exit\n");
	while(1){
	scanf("%i",&ch);
	switch(ch){
		case 1: printf("Starting O/P\n");
					flag=0;				  
					break;
		case 2: printf("Stopping O/P\n");
				flag=3;
				pthread_join( t1,NULL );
				printf("stopped\n");	
					break;
		case 3: printf("Stopping Main\n");
					delay(100);
					exit(0);
					break;
		}		
	}
			
	
	return 0;}

void *convert()
{	
	
	while(1){
	if(flag==0){
	for(i=0;i<(sizeof(tbuf)/sizeof(tbuf[0]));i++){
	
	t=((65535*(tbuf[i]-700))/1100);
				
	buf[0]=0x01;
	buf[1]=t>>8;
	buf[2]=t & 0x00FF;
								
	wiringPiSPIDataRW (chan,buf,3) ;
	delay(100);
	
	if(flag==3){
	pthread_exit(NULL);}
	
	}}
	
	if(i==(sizeof(tbuf)/sizeof(tbuf[0]))-1){i=0;}
	}
	
 
}
