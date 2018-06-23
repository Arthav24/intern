#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>

#define LED_PIN 0
#define BUTTON_PIN 2

int flag=1;
void myInterrupt(void) {
   flag=!flag;

}
int main(void) {
  if (wiringPiSetup () < 0) {
      return 1;
  }
pinMode(0,OUTPUT);
pinMode(3,OUTPUT);
digitalWrite(3,1);
pinMode(BUTTON_PIN,INPUT);

  if ( wiringPiISR (BUTTON_PIN, INT_EDGE_RISING, &myInterrupt) < 0 ) {
      return 1;
  }


 while ( 1 ) {
	if(flag==0){digitalWrite(LED_PIN,1);
		delay(100);
		digitalWrite(LED_PIN,0);
		delay(100);}
  }
  

  return 0;
}

