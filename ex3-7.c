#include "stdio.h"
#include "unistd.h"
#include "sys/shm.h"
#include "sys/wait.h"


int main(){

	int n, pid, shmid, *count, status;
    shmid = shmget(IPC_PRIVATE, sizeof(*count), 0666);
	count = (int *)shmat(shmid, NULL, 0);
    *count = 0;
    pid = fork();
    if(pid>0){
        for(n = 0; n<100000; n++)
            *count = *count+1;
        wait(&status);
        printf("count=%d\n", *count);
        shmdt(count);
        shmctl(shmid, IPC_RMID, NULL);

    }

    else if(pid==0){
        for (n=0; n<10000; n++)
            *count = *count-1;
    }    
    
    
}
