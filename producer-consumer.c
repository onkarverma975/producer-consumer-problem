#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#define MAX 100000
typedef int buffer_item;
int n;
void *consumer(void *param);
void *producer(void *param); 
int count_location[MAX];
int location_write[MAX];
pthread_mutex_t mutex;
int checker[1010][1010];
buffer_item buffer[MAX];
int m;
int counter;
int flag_p;
pthread_attr_t attr; 
pthread_t tid,tid1[MAX];    
void *producer(void *param) {
	buffer_item item;
	while(1==1) 
	{
		flag_p=0;
		sleep(1);
		int i=counter;
		while(i!=(counter-1))
		{
			if(count_location[i]==m || count_location[i]==0)
			{
				pthread_mutex_lock(&mutex);
				item = rand();
				flag_p=1;
				if(item==0)
				{
					item=item+1;
				}
				printf("writer wrote %d\n",item);
				location_write[i] = item;
				buffer[i]=item;
				int j=0;
				while(j<m)
				{
					checker[j][i]=0;
					j++;
				}
				count_location[i]=0;
				pthread_mutex_unlock(&mutex);
				break;
			}
			i++;
			i=i%n;
		}
		counter=i;
	}
}
void *consumer(void *param) {
	buffer_item item;
	int x = *(int *)param;
	while(1==1)
	{
		flag_p=0;
		int i;
		sleep(1);
		while(i<n){
			if(location_write[i]!=0 ){
				if(checker[x][i]==0){
					pthread_mutex_lock(&mutex);
					flag_p=1;
					count_location[i]++;
					item = buffer[i];
					checker[x][i]=1;
					printf("reader number %d read %d\n",x,item);
					pthread_mutex_unlock(&mutex);
					break;
				}
			}
			i++;
		}
	}
}
int main() {
	scanf("%d%d",&n,&m);
	int i,j;
	int pass[m];
	for(i=0;i<=m;i++)
	{
		count_location[i]=0;
		for(j=0;j<=n;j++)
		{
			checker[i][j]=0;
			location_write[j]=0;
		}
	}
	counter=0;
	pthread_attr_init(&attr);
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&tid,&attr,producer,NULL);
	i=0;
	while(i<m) 
	{
		pass[i]=i;
		pthread_create(&tid1[i],&attr,consumer,&pass[i]);
		i++;
	}
	i=0;
	while(i<m) 
	{
		pthread_join(tid1[i],NULL);
		i++;
	}
	return 0;
}
