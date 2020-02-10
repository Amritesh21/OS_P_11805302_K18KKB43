#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
void *writer(void * args)
{

	return NULL;
}
void *reader(void *args)
{
	return NULL;
}
int main()
{
	pthread_t thread_wrt[5];
	pthread_t thread_read[5];
	int i=0;
	for(i;i<5;i++)
	{
	pthread_create(&thread_wrt[i],NULL,writer,NULL);
	printf("\n%d ",thread_wrt[i]);
	pthread_create(&thread_read[i],NULL,reader,NULL);
	}
	int j=0;
	for(j;j<5;j++)
	{
	pthread_join(thread_wrt[j],NULL);
	pthread_join(thread_read[j],NULL);
	}
	return 0;
}
//pOSIx thread
