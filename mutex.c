#include "stdio.h"
#include"pthread.h"
#include "semaphore.h"
#include "unistd.h"
#include"stdlib.h"
pthread_mutex_t M = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_has_space = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_has_data = PTHREAD_COND_INITIALIZER;

int buf[4];
int counter=0;
int loop;

void* producer(void *unused){
    int i;
    int in=0;

    for(i=0; i<loop; i++){
        pthread_mutex_lock(&M);
        if(counter==4) pthread_cond_wait(&buffer_has_space, &M);
        buf[in]=i;
        in=(in+1)%4;
        counter++;
    in = (in+3)%4;
    pthread_cond_signal(&buffer_has_data);
    pthread_mutex_unlock(&M);
    }
    printf("\tproducer: last_in[%d] = %d\n", in, buf[in]);
}

 

void* consumer(void *unused){
    int i, j;
    int out=0;
    for(i=0; i<loop; i++){
        pthread_mutex_lock(&M);
        if(counter ==0)
            pthread_cond_wait(&buffer_has_data, &M);
        j=buf[out];
        out=(out+1)%4;
        counter--;
        out=(out+3)%4;
            pthread_cond_signal(&buffer_has_space);
        pthread_mutex_unlock(&M);
    }
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
    printf("\tmain: last_counter=%d\n", counter);
}
