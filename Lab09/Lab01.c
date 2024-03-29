#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#define MAXFILA 8
#define MAXPRODUZIDO 64

typedef struct mymsg {
    long int    mtype;     /* message type */
    int        	meu_int;  /* message */
} mymsg;

int main (void)
{
	

	int pid_consumidor,pid_consumidor2,id_fila_msg,status;	
	mymsg m;
	struct msqid_ds buf;
	m.mtype = 1; //sei la o que fazer com esse type
	id_fila_msg = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
	
	if(	msgctl(id_fila_msg,IPC_STAT,&buf) == -1)
	{
		printf("erro msgctl, saindo \n");
		exit(-1);
	}
	buf.msg_qbytes = 8 * sizeof(m.meu_int);
	if (msgctl(id_fila_msg,IPC_SET,&buf)==-1)
	{
		printf("erro setando msgctl, saindo \n");
		exit(-1);
	}
	
	pid_consumidor=fork();	
	if (pid_consumidor == 0) {			
		//consumidor 1 
		int i;					
		for(i=0;i<MAXPRODUZIDO/2;i++)
		{	
			sleep(2);
			status = msgrcv( id_fila_msg, &m, sizeof(m.meu_int), 0, 0); 
			printf("CONSUMIDOR 1: Mensagem recebida %d \n ",m.meu_int);
		}	
	
	} 
	else { //pai
		
		pid_consumidor2=fork();
		if (pid_consumidor2 == 0) //consumidor 2
		{
			int i,status;				
			for(i=0;i<MAXPRODUZIDO/2;i++)
			{	
				sleep(2);
				status = msgrcv( id_fila_msg, &m, sizeof(m.meu_int), 0, 0);
										 
				printf("CONSUMIDOR 2: Mensagem recebida %d \n ",m.meu_int);
			}
		}
		else
		{ //pai produtor
			int i;
			for(i=0;i<MAXPRODUZIDO;i++)
			{
				m.meu_int = i;
				status = msgsnd( id_fila_msg, &m, sizeof(m.meu_int), 0);
				printf("\n\nPRODUTOR: enviado %d, status: %d\n\n",m.meu_int,status);
					
				sleep(1);
			}

			printf("produtor acabou\n");	
			}
		
	}
	waitpid(-1,&status,0);
	waitpid(-1,&status,0);
	return 0;
}
