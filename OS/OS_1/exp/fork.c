#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main() 
{
	pid_t pid;
	pid = fork();
	printf("one\n");
	printf("pid = %d\n", pid);
	printf("two\n");


	if(pid == -1)
		printf("error!\n");
	else if(pid == 0){
		int j;
		pid_t pid2 = fork();	
		for(j=0; j<5; j++) {
			printf("Child:%d\n",j);
			sleep(1);
		}
		printf("--------\n");
		exit(0);
	}
	else {
		int i;
		for(i=0; i<5; i++) {
			printf("Parent!%d\n",i);
			sleep(1);
		}
		exit(1);
	}
	
	return 0;
}
