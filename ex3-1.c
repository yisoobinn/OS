#include "stdio.h"
#include "unistd.h"
#include "pthread.h"

int count = 0;
void *thread (void *unused){

	int i,j;
		for(i=0; i<10000; i++)
			for(j=0; j<10000; j++){
				count++;
				count--;
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
