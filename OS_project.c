#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
pthread_mutex_t read_m;
pthread_mutex_t write_m;
sem_t wrt;
int shared_data=5,read_t_counter=0;
void *writer(void * args)
{

	pthread_mutex_lock(&write_m);
	pthread_mutex_unlock(&write_m);
	return NULL;
}
void *reader(void *args)
{
	pthread_mutex_lock(&read_m);
	read_t_counter++;
	if(read_t_counter ==1)
	{
		pthread_mutex_lock(&write_m);
		
	}
	pthread_mutex_lock(&read_m);
	read_t_counter=read_t_counter-1;
	if(read_t_counter ==0)
	{
		pthread_mutex_unlock(&write_m);
	}
	pthread_mutex_unlock(&read_m);
	return NULL;
}
int main()
{
	pthread_mutex_init(&read_m,0);
	pthread_mutex_init(&write_m,0);
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
