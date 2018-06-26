#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_1( void *ptr );
void *thread_2( void *ptr );

int main()
{
     pthread_t t1, t2;
     char *message1 = "Message to Thread 1";
     char *message2 = "Message to Thread 2";
     int  iret1, iret2;

     iret1 = pthread_create( &t1, NULL, thread_1, (void*) message1);
     iret2 = pthread_create( &t2, NULL, thread_2, (void*) message2);


     //pthread_join( t1, NULL);
     //pthread_join( t2, NULL); 

     printf("Thread 1 returns: %d\n",iret1);
     printf("Thread 2 returns: %d\n",iret2);
     while(1){}
     exit(0);
     
}

void *thread_1( void *ptr )
{
     char *message;
     message = (char *) ptr;
     printf("%s \n", message);
}
void *thread_2( void *ptr )
{
     char *message;
     message = (char *) ptr;
     printf("%s \n", message);
}

