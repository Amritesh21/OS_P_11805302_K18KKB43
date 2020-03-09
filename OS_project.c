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
	pthread_mutex_unlock(&read_m);
	printf("\nReaders Wating : %d",read_t_counter);
	int wait_time=rand()%10;
	sleep(wait_time);
	printf("\nEnter Number of time you want to read R%d: \n",n);
	//sleep(1);
	int read_op;
	scanf("%d",&read_op);
	sleep(wait_time);
	while(read_op>0)
	{
	printf("\n%d The value of shared data is: %d\n",read_op,shared_data);
	read_op--;
	}
	pthread_mutex_lock(&read_m);
	//if(read_t_counter==3)
	
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
