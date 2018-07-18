#include <wiringPiSPI.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int chan=0,t;
int speed=10000000; 
unsigned char buf[3];
int main(){
	
	if(wiringPiSPISetupMode(chan,speed,0)==-1){
			printf("Cannot initialise SPI \n");
			return 1;}
			buf[0]=0x55;
			buf[1]=0x30;
			buf[2]=0x05;
			wiringPiSPIDataRW (chan,buf,3) ;
			
			while(1){
				printf("Enter a Temperature between 700-1800\n");
				scanf("%d",&t);
				t=((65535*(t-700))/1100);
				
				buf[0]=0x01;
				buf[1]=t>>8;
				buf[2]=t & 0x00FF;
								
			wiringPiSPIDataRW (chan,buf,3) ;
			delay(100);
 }
	return 0;}
	
