#include <pthread.h>
#include <stdio.h>
#include<unistd.h>
#define NUM_THREADS 2
static int cont=0;

void *Acr(void* threadid)
{
	int i;
	for(i=1;i<=20;i++)
	{
		printf("cont=%d\ttid=%d\n",cont,threadid);
		cont++;
		sleep(1);
	}
		
	pthread_exit(NULL); //dispensavel
}

void *Dec(void* threadid)
{
	int i;
	for(i=30;i>=1;i--)
	{
		printf("cont=%d\ttid=%d\n",cont,threadid);
		cont--;
		sleep(1);
	}
		
	pthread_exit(NULL); //dispensavel
}


int main (void)
{
	pthread_t threads[NUM_THREADS];
	int t;
	
	for (t=0;t<NUM_THREADS;t++)
	{
		printf("Creating thread %d\n",t);
		if(t==0){
			pthread_create(&threads[t],NULL,Acr,(void*)t);
			
			}
		else
			pthread_create(&threads[t],NULL,Dec,(void*)t);
		
	}
	for (t=0;t<NUM_THREADS;t++)
	{	
		pthread_join(threads[t],NULL);
	}
	
}
