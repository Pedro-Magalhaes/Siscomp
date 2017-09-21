#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
//vou definir o numero de filhos a serem criados
#define FILHOS 4

int main(void){
int pid_filho,status;
int meu_pid;
int i;
int c[]={1,7,10,4,8,3,4,5,6,12,13,14,15};
int size=13;//tamanho do vetor
int passo,inicio=0;
passo=size/FILHOS;//passo é o numero de posições que cada filho procura
int sobra=size%FILHOS; //se há sobra, o ultimo filho vai procurar passo+sobra posições

for(i=0;i<FILHOS;i++)
{
	inicio=i*passo; //posição no vetor que cada fiho procura
	int procurado=7; //numero procurado
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
				printf("Encontrado PID<%d> numero: %d filho numero:%d procurado=%d  \n",pid_filho,c[inicio],i,procurado);
		}
		exit(-1);
	}
}

	return 0;
}
