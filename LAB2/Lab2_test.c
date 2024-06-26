#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
int main(){
	int pid;
	printf("Original process with PID %d and PPID %d.\n",getpid(),getppid());
	pid=fork();
	if (pid!=0){
		printf("Parent process with PID %d and PPID %d.\n",getpid(),getppid());
		printf("My child's PID is %d\n",pid);
	}
	else{
		printf("Child process with PID %d and PPID %d.\n",getpid(),getppid());
	}
	printf("PID %d terminates\n",pid);
	return 0;
}