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
	int n=(int)args;
	printf("\nWait for few seconds......");
	sleep(1);
	printf("\nReaders wating  : %d ",read_t_counter);
	printf("\nEnter number of times you want to write operation by 'Write Thread' %d: ",(n));
	int repeat;
	scanf("%d",&repeat);
	int i=0;
	for(i=0;i<repeat;i++)
	{
		int tempvar;
		printf("\nEnter value to be updated: ");
		scanf("%d",&tempvar);
		shared_data=tempvar;
		printf("\nUpdated value is : %d",shared_data);
	}
	pthread_mutex_unlock(&write_m);
	return NULL;
}
void *reader(void *args)
{
	pthread_mutex_lock(&read_m);
	int n=(int)args;
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
	pthread_t read_th[5];
	pthread_t write_th[5];
	int i=0,j=0;
	int interrupt=3;
	int interrupt_no=0;
	int distress=0;
	//printf("\nEnter the number of interrupt you want: ");
	//scanf("%d",&interrupt_no);
	int int_ps[interrupt_no];
	int k=0,x=0;
	int beg,mid,end;
	A:
	printf("\nEnter number of read interrupt at begning : ");
	scanf("%d",&beg);
	printf("\nEnter number of read interrupt at middle : ");
	scanf("%d",&mid);
	printf("\nEnter number of read interrupt at end: ");
	scanf("%d",&end);
	if((mid+end+beg)!=5)
	{
		goto A;
	}
	printf("\nWe are at begning of process\n ...Waiting for %d read threads",beg);
	for(k;k<beg;k++)
	{
		
		pthread_create(&read_th[k],NULL,reader,(int *)k);
		//pthread_create(&write_th[i],NULL,writer,(int *)i);
	}
	for(x;x<beg;x++)
	{
		//pthread_join(write_th[j],NULL);
		pthread_join(read_th[j],NULL);
	}
	if(beg==0)
	{
		distress=2;
		beg=2;
		//printf("******************");
	}
	for(i;i<beg;i++)
	{
		//pthread_create(&read_th[i],NULL,reader,(int *)i);
		pthread_create(&write_th[i],NULL,writer,(int *)i);
	}
	for(j;j<beg;j++)
	{
		pthread_join(write_th[j],NULL);
		//pthread_join(read_th[j],NULL);
	}
	printf("\nWe are at middle of process\n ...Waiting for %d read threads",k);
	int ctn=1;
	if(mid ==0|| mid ==5 )
	{
		ctn=0;
	}
	for(k;k<mid+ctn;k++)
	{
		pthread_create(&read_th[k],NULL,reader,(int *)k);
	}
	for(x;x<mid+ctn;x++)
	{
		pthread_join(read_th[j],NULL);
	}
	for(i;i<5;i++)
	{
		pthread_create(&write_th[i],NULL,writer,(int *)i);
	}
	for(j;j<5;j++)
	{
		pthread_join(write_th[j],NULL);
	}
	printf("\nProcess has completed all write operation\n ...Waiting for %d read threads comming at end",end);
	//x=k;
	for(k;k<5;k++)
	{
		pthread_create(&read_th[k],NULL,reader,(int *)k);
	}
	for(x;x<5;x++)
	{
		pthread_join(read_th[x],NULL);
	}
	return 0;
}
//pOSIx thread
