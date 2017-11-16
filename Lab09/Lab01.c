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
	

	int pid_produtor,id_fila_msg;	
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
	
	pid_produtor=fork();	
	if (pid_produtor != 0) {			
		//consumidor 
		int i,status;					
		for(i=0;i<MAXPRODUZIDO;i++)
		{	
			sleep(2);
			status = msgrcv( id_fila_msg, &m, sizeof(m.meu_int)
, 1, 0); 
			printf("Mensagem recebida, meu i eh %d , e i do produtor era %d , deveriam ser iguais. status: %d \n",i,m.meu_int,status);
		}	
	
	} 
	else { //produtor
		
		int i,status;
		for(i=0;i<MAXPRODUZIDO;i++)
		{
			m.meu_int = i;
			status = msgsnd( id_fila_msg, &m, sizeof(m.meu_int), 0);
			printf("\n\nPRODUTOR: enviado %d, status: %d\n\n",m.meu_int,status);
				
			sleep(1);
		}

		printf("produtor acabou\n");
	}
	
	return 0;
}
