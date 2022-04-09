#include "stdio.h"
#include "unistd.h"
#include "pthread.h"
#include "semaphore.h"


int count = 0;
sem_t s;

void *thread (void *unused){
	int i,j;
		for(i=0; i<10000; i++)
			for(j=0; j<10000; j++){
				
                sem_wait(&s);
				count++;
				count--;
				sem_post(&s);
	}

}

int main(){

	int n;
	sem_init(&s, 0, 1);
    pthread_t tid[10];
	for(n=0; n<10; n++)
		pthread_create(&tid[n], NULL, &thread, NULL);
	for (n=0; n<10; n++)
		pthread_join(tid[n], NULL);
	printf("count=%d\n", count);
}
