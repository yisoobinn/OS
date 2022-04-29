#include "stdio.h"
#include"pthread.h"
#include "semaphore.h"
#include "unistd.h"
#include"stdlib.h"

sem_t R_empty;
sem_t W_full;

int buf[4];
int counter=0;
int loop;

void* producer(void *unused){
    int i;
    int in=0;

    for(i=0; i<loop; i++){
        if (counter == 4)
        sem_wait(&R_empty);
        buf[in]=i;
        in=(in+1)%4;
        counter++;
        in = (in+3)%4;
        sem_post(&W_full);
    }
    printf("\tproducer: last_in[%d] = %d\n", in, buf[in]);
}

 

void* consumer(void *unused){
    int i, j;
    int out=0;
    for(i=0; i<loop; i++){
        if(counter == 0)
        sem_wait(&W_full);
        j=buf[out];
        out=(out+1)%4;
        counter--;
        
        sem_post(&R_empty);
    }
    out=(out+3)%4;
    printf("\tconsumer: last_out[%d]=%d\n", out, j);
}


void main(int argc, char* argv[]){
    int i;
    loop = atoi(argv[1]);
    pthread_t tid[2];
    pthread_create(&tid[0], NULL, producer, NULL);
    pthread_create(&tid[1], NULL, consumer, NULL);
    for(i=0; i<2; i++)
        pthread_join(tid[i], NULL);
    pthread_exit(NULL);

    sem_destroy(&R_empty);
    sem_destroy(&W_full);
    printf("\tmain: last_counter=%d\n", counter);
}