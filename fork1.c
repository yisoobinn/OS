#include "stdio.h"
#include "unistd.h"

int main(){

	pid_t ret;
	
	printf("my process %d\n", getpid());

	ret = fork();
	
	printf("my process %d\n", getpid());
	printf("parents process %d\n", getppid());


}
