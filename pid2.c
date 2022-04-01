#include "stdio.h"
#include "unistd.h"
#include "sys/wait.h"

int main(void){

	int pid = fork(), status;

	if (pid==0){

		printf("My(child) process %d\n", getpid());
		printf("parent process %d\n", getppid());
		return 0;
	}

	else {
		while(!waitpid(pid, &status, WNOHANG));
		printf("My(parent) process %d\n", getpid());
		printf("child peocess = %d\n", pid);
	}
	return 0;

}
