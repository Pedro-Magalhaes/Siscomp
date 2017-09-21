#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(void){
int pid_filho,status;
int meu_pid;


meu_pid = getpid();
pid_filho=fork();


if (pid_filho != 0) {
	
	printf("Processo Pai iniciado,meu pid %d pid filho %d\n\n",meu_pid,pid_filho);
	waitpid( -1, &status, 0);/* wait for child to exit */
	
	printf("Processo Pai finalizado\n");
} else {
	pid_filho = getpid();

	printf("Processo Filho iniciado,meu pid %d pid pai %d\n\n",pid_filho,meu_pid);
	
	printf("Processo Filho finalizado\n\n");

	exit(1);

}

	return 0;
}
