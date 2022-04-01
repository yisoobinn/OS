#include "stdio.h"
#include "unistd.h"
#include "pthread.h"
#include "stdlib.h"

int count = 0;
pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;
void *thread (void *unused){
	int i,j;
		for(i=0; i<10000; i++)
			for(j=0; j<10000; j++){
				
				pthread_mutex_lock(&m);
				count++;
				count--;
				pthread_mutex_unlock(&m);
	}

}

int main(){

	int n;
	pthread_t tid[10];
	for(n=0; n<10; n++)
		pthread_create(&tid[n], NULL, &thread, NULL);
	for (n=0; n<10; n++)
		pthread_join(tid[n], NULL);
	printf("count=%d\n", count);
}
