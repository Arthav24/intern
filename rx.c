#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>

int main ()
{
  int serial_port ;
  char dat;
  if ((serial_port = serialOpen ("/dev/ttyS0", 9600)) < 0)	
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiSetup () == -1)
  {
    return 1 ;
  }

  

	while(1)  
	 
	  
	//if(serialDataAvail (serial_port) )
	{  serialPrintf(serial_port,"hi");
		delay(10);
		dat = serialGetchar (serial_port);		
		printf ("%c", dat) ;
		
		//fflush (stdout) ;
		//serialPutchar(serial_port, dat);	
		}	
	
	

}
