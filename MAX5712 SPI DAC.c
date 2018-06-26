#include <wiringPiSPI.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
int chan=0;
int speed=10000000; 
unsigned char buf[2];

int main(){printf("0");
	if(wiringPiSPISetupMode(chan,speed,0)==-1){
			printf("Cannot initialise SPI \n");
			return 1;}
			
			
			buf[0]=0xF0;
			buf[1]=0x00;
			wiringPiSPIDataRW (chan,buf,2) ;
			
			printf("1");
			
			while(1){
			buf[0]=0x07;
			buf[1]=0xD0;
			wiringPiSPIDataRW (chan,buf,2) ;
			
			delay(100);
 }

// 7FF is 1.67
// 7EE is 1.63
// 7D0 is 1.60 
	
	return 0;}
