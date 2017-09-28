#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#define EVER ;;
#define FILHOS 2


int main (int argc, char *argv[])
{	
	int pid[2];
	int i;
	int proximo;
	for(i=0;i<FILHOS;i++)
	{
		if ((pid[i] = fork()) < 0)
		{
			fprintf(stderr, "Erro ao criar filho\n");
			exit(-1);
		}
		if (pid[i] == 0)/* child */
		{ 
			for(EVER){printf("Filho %d\n",i);sleep(1);}
		}
	}
	
	
		for(i=0;i<10;i++)
		{
			proximo=i%FILHOS;
			printf("Vou trocar filhos\n");
			kill(pid[FILHOS-proximo-1],SIGSTOP);
			kill(pid[proximo],SIGCONT);
			sleep(2);
		}

		for(i=0;i<FILHOS;i++)
		{
			kill(pid[i],SIGINT);
		}
		printf("Filhos interrompidos\n");

		
	
	return 0;
}

