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
int segmento,segmento2,segmento3, *pids,*vetor;
char *sigPos; 
// aloca a memória compartilhada
segmento = shmget (IPC_PRIVATE, sizeof (int)*MAXFILA, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
// associa a memória compartilhada ao processo
vetor = (int *) shmat (segmento, 0, 0);

segmento2 = shmget (IPC_PRIVATE, sizeof (int)*2, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
// associa a memória compartilhada ao processo
//pid[0]= pid_produtor
//pid[1]=pid_consumidor
pids = (int*) shmat (segmento2, 0, 0);

segmento3 = shmget (IPC_PRIVATE, sizeof (char)*4, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
// associa a memória compartilhada ao processo
sigPos = (char*) shmat (segmento3, 0, 0);
sigPos[0]=0;//flag para impedir concorrencia ao gravar na memoria
//0->ninguem usando memoria 1->memoria em uso
sigPos[1]=0; //proxima posiçao a ser lida
sigPos[2]=0; //proxima posição a ser escrita
sigPos[3]=0;//numero de elementos no vetor
	
	pid_produtor=fork();	
	if (pid_produtor != 0) {
			pids[0]=pid_produtor;
			pid_consumidor=fork();			
			if (pid_consumidor != 0){	
			/*	Tinha colocado o pids[1]=pid_consumidor e deu erro porque o pai e o filho estavam alterando
				simultaneamente e o pids[1] ficava sempre 0, acho que porque o filho alterava depois do pai
				assim quando o consumidor era pausado ele pausava o programa inteiro porque passava 0 como pid
				pro kill()*/
				pids[1]=pid_consumidor;
				waitpid( -1, &status, 0);/* wait for child to exit */
				printf("1o terminado\n");
				waitpid( -1, &status, 0);/* wait for child to exit */
				printf("tudo terminado\n");
			}else{ //consumidor 
				int i;	
				int aux;//auxiliar para guardar o valor lido da memoria e libera-la para escrita antes de dar print			
				for(i=0;i<MAXPRODUZIDO;i++)
				{	

					//sleep(2);								
					
					if(sigPos[3]== 0 ) //se tiver poucos elementos pauso o consumidor
					{	
						
						//para garantir que ele nao pausa na ultima iteracao()
						if( i<MAXPRODUZIDO-2){
							//printf("Consumidor sera pausado\n");

							kill(pids[0],SIGCONT);//(pids[0]=pid_produtor)										
							kill(pids[1],SIGSTOP);//parando o processo consumidor (pid[1]=pid_consumidor)
						}
						else{
							kill(pids[0],SIGCONT);//(pids[0]=pid_produtor)
						}
					} 
					//se estiver na metade me certifico que o produtor esta produzindo
					else if(sigPos[3]<MAXFILA/2 - 1)
					{
						//printf("Produtor sinalizando para acordar\n");
						kill(pids[0],SIGCONT);//(pids[0]=pid_produtor)
					}

					if(sigPos[3]> 0 || i==MAXPRODUZIDO-1) //tem mais que 0 elementos ou eh a ultima iteracao
					{
						if(sigPos[0])//alguem usando memoria
						{
							printf("Consumidor Nao consegue acessar\n");
							i--;
							continue;
						}
						else
						{							
							sigPos[0]=1; //trava o acesso ao vetor
							aux=vetor[sigPos[1]];	//pega a memoria											
							vetor[sigPos[1]]=-1;
							sigPos[3]--; //numero de elementos no vetor -1
							sigPos[1]=(sigPos[1]+1)%MAXFILA;
							sigPos[0]=0; //desbloqueia o vetor
							printf("consumido %d\n",aux);
						}
					}
					else{
						i--;
						continue;
					}

				}
			
			
				printf("Consumidor terminou trabalho\n");
				kill(pids[0],SIGCONT);//(pids[0]=pid_produtor)
				exit(1);
			}
	} else { //produtor
		
		int i;
				for(i=0;i<MAXPRODUZIDO;i++)
				{
					//sleep(1);
					if(sigPos[3]==MAXFILA)
					{	
						
						//para garantir que ele nao pausa na ultima iteracao(necessario realmente no consumidor)
						if( i<MAXPRODUZIDO-1){
							//printf("Produtor sera pausado\n");		
							kill(pids[1],SIGCONT);//(pid[1]=pid_consumidor)									
							kill(pids[0],SIGSTOP);//(pids[0]=pid_produtor)
						}
						else{
							kill(pids[1],SIGCONT);//(pid[1]=pid_consumidor)	
						}
					}
					//se estiver muito cheio, vou garantir que o consumidor esta trabalhando
					else if(sigPos[3]>MAXFILA-2) 
					{
						//printf("Consumidor sinalizado  para acordar\n");
						kill(pids[1],SIGCONT);//(pid[1]=pid_consumidor)
					}
					
					if(sigPos[3]<MAXFILA) //testando se o numero de elementos ainda eh menor que o max
					{
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
							sigPos[3]++; //numero de elementos no vetor +1
							sigPos[2]=(sigPos[2]+1)%MAXFILA;
							sigPos[0]=0;
						}
						
					}
					else
					{
						i--;
						continue;
					}
					
				}
				printf("produdor terminou trabalho\n");
				kill(pids[1],SIGCONT);
		exit(1);
	}

	

	return 0;
}
