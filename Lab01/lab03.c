#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
//vou definir o numero de iteraçoes iniciais
#define FILHOS 4

int main(void){
int pid_filho,status;
int meu_pid;
int i;
int c[]={7,10,4,8,3,4,5,6,12};
int size=9;
int passo,inicio=0;
meu_pid = getpid();
passo=size/FILHOS;
int sobra=size%FILHOS;

for(i=0;i<FILHOS;i++)
{
	inicio=i*passo;
	int procurado=12;
	pid_filho=fork();	
	if (pid_filho != 0) {
			printf("criei filho %d\n",i);		
			waitpid( -1, &status, 0);/* wait for child to exit */
			
	} else {
		pid_filho = getpid();
		int fim=inicio+passo;
		if(sobra && i==FILHOS-1)
			fim=fim+sobra;
		for (;inicio<fim;inicio++)
		{
			if(procurado==c[inicio])
				printf("Encontrado PID<%d> numero: %d filho numero:%d \n",pid_filho,c[inicio],i);
		}
		exit(-1);
	}
}

	return 0;
}
