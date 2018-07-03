#include<stdio.h>
#include<signal.h>

void handle(int sig)
{
    printf("Caught signal %d\n", sig);
}
 
int main()
{
    signal(SIGINT, handle);
    while (1) ;
    return 0;
}
