#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(void){
int pid_filho,status;
int meu_pid;
int meu_inteiro=0;
int i;

meu_pid = getpid();
pid_filho=fork();


if (pid_filho != 0) {
	

	for(i=0;i<100;i++){
		printf("PAI<%d> - <%d>\n",meu_pid,meu_inteiro);
		meu_inteiro+=5;
	}
	waitpid( -1, &status, 0);/* wait for child to exit */

	
} else {
	pid_filho = getpid();
	
	for(i=0;i<100;i++){
		printf("FILHO<%d> - <%d>\n",pid_filho ,meu_inteiro);
		meu_inteiro+=10;

	}
	

	exit(1);

}

	return 0;
}
