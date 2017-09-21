#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAXFILA 8
#define MAXPRODUZIDO 64
int main (void)
{
	

int pid_produtor,pid_consumidor,status;
int meu_pid;
int i;
int segmento,segmento2,segmento3, *pids,*vetor;
char *sigPos; 
// aloca a memória compartilhada
segmento = shmget (IPC_PRIVATE, sizeof (int)*MAXFILA, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
// associa a memória compartilhada ao processo
vetor = (int *) shmat (segmento, 0, 0);

segmento2 = shmget (IPC_PRIVATE, sizeof (int)*2, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
// associa a memória compartilhada ao processo
pids = (int*) shmat (segmento2, 0, 0);

segmento3 = shmget (IPC_PRIVATE, sizeof (char)*3, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
// associa a memória compartilhada ao processo
sigPos = (char*) shmat (segmento3, 0, 0);
sigPos[0]=0;//ninguem usando memoria
sigPos[1]=0; //proxima posiçao a ser lida
sigPos[2]=0; //proxima posição a ser escrita
	
	pid_produtor=fork();	
	if (pid_produtor != 0) {
			pids[0]=pid_produtor;
			pid_consumidor=fork();
			pids[1]=pid_consumidor;
			if (pid_consumidor != 0){	
				waitpid( -1, &status, 0);/* wait for child to exit */
				waitpid( -1, &status, 0);/* wait for child to exit */
			}else{ //consumidor
				int i;
				for(i=0;i<MAXPRODUZIDO;i++)
				{	
					sleep(2);
					if(sigPos[0])//alguem usando memoria
					{
						printf("Consumidor Nao consegue acessar\n");
						i--;
						continue;
					}
					else
					{
						sigPos[0]=1;
						
						printf("consumido %d\n",vetor[sigPos[1]]);
						vetor[sigPos[1]]=-1;
						sigPos[1]=(sigPos[1]+1)%MAXFILA;
						sigPos[0]=0;
					}
									
					
				/*	if((sigPos[1]-sigPos[2])%MAXFILA < 2)
					{	
						printf("Consumidor sera pausado\n");
						pause();
					} */
					/*else*/ if(sigPos[1]!=sigPos[2])
					{
						printf("Produtor<%d> sinalizando para acordar\n",pids[0]);
						kill(pids[0],SIGCONT);
					}
				}
			
			
			
				exit(1);
			}
	} else { //produtor
		
		int i;
				for(i=0;i<MAXPRODUZIDO;i++)
				{
					sleep(1);
					printf("meu pid:%d pid recebido %d\n",getpid(),pids[0]);
					if(sigPos[0])
					{
						printf("Produtor Nao consegue acessar\n");
						i--;
						continue;
					}
					else
					{
						sigPos[0]=1;
						vetor[sigPos[2]]=i;
						sigPos[2]=(sigPos[2]+1)%MAXFILA;
						sigPos[0]=0;
					}
					
					
					if((sigPos[1]==sigPos[2]))
					{	
						printf("Produtor sera pausado\n");
						pause();
					}
					else if(sigPos[1]!=sigPos[2])
					{
						printf("Consumidor sinalizado  para acordar\n");
						kill(pids[1],SIGCONT);
					}
				}
		exit(1);
	}

	

	return 0;
}
