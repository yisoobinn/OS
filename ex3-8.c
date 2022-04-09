#include "stdio.h"
#include "unistd.h"
#include "sys/shm.h"
#include "sys/sem.h"
#include "sys/wait.h"


int main(){

	int n, pid, shmid, *count, status, semid;

    struct sembuf p_op = {0, -1, SEM_UNDO},
                v_op = {0,1, SEM_UNDO};

    shmid = shmget(IPC_PRIVATE, sizeof(*count), 0666);
	count = (int *)shmat(shmid, NULL, 0);

    semid = semget (IPC_PRIVATE, 1, 0666);
    semctl(semid, 0, SETVAL , 1);
    *count = 0;
    pid = fork();
    if(pid>0){
        for(n = 0; n<100000; n++)
        semop(semid, &p_op, 1);
            *count = *count+1;
        semop(semid, &v_op,1);
    
        wait(&status);
        printf("count=%d\n", *count);
        shmdt(count);
        semctl(shmid, 0, IPC_RMID, NULL);

    }

    else if(pid==0){
        for (n=0; n<10000; n++)
        semop(semid, &p_op, 1);
            *count = *count-1;
        semop(semid, &v_op,1);
    }    
    
    
}
