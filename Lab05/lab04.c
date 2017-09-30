#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define FILHOS 3
#define EVER ;;

int main (int argc, char *argv[])
{
	int pid[FILHOS],i;
	char comando[100]="./spammer_";
	
	for(i=0;i<FILHOS;i++)
		pid[i]=0;
		
	for(i=0;i<FILHOS;i++)
	{
		pid[i]=fork();
		if(pid[i]==0)
		{
			char numero_processo[21];
			char *argv[3];
			argv[3]=NULL;
			sprintf(numero_processo,"%d",i+1);//passando i para char
			strcat(comando,numero_processo);//tenho o comando preciso do parametro
			argv[0]=strdup(comando);
			argv[1]=strdup(numero_processo);
			execvp(argv[0],argv);
			printf("erro,nao executei o comando filho<%d>\n",i);
			exit(1);
		}
		printf("filho<%d> criado\n",i+1);
		kill(pid[i],SIGSTOP);//todos começam parados
		
	}
	i=0;
	for(EVER)
	{
		printf("acordando filho<%d>\n",i+1);
		kill(pid[i],SIGCONT);
		if(i==0)
		{
			sleep(1);
		}
		else
		{
			sleep(2);
		}
		kill(pid[i],SIGSTOP);
		i=(i+1)%3;
	}
	
	return 0;
}
