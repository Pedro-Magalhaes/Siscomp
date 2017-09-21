#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
//vou definir o numero de filhos/[lin][col] a serem criados
#define FILHOS 3

int main(void){
int pid_filho,status;
int meu_pid;
int i;
int M1[FILHOS][FILHOS]={{1,7,10},{4,8,3},{4,5,6}};
int M2[FILHOS][FILHOS]={{1,1,1},{1,1,1},{1,1,1}};

for(i=0;i<FILHOS;i++)
{
	int soma;
	
	pid_filho=fork();	
	if (pid_filho != 0) {
				
			waitpid( -1, &status, 0);/* wait for child to exit */
			
	} else {
		pid_filho = getpid();
		int fim=FILHOS;
		int linha[FILHOS]={0,0,0};
		int j;
		soma=0;
		for (j=0;j<fim;j++)
		{
			linha[j]=linha[j]+M1[i][j]+M2[i][j];

		}
		sleep(i);
		printf("linha [%d] = %d\t%d\t%d\n",i,linha[0],linha[1],linha[2]);
		exit(-1);
	}
}

	return 0;
}
