#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#define MAXFILA 8
#define MAXPRODUZIDO 12

typedef struct mymsg {
    long int    mtype;     /* message type */
    int        	meu_int;  /* message */
} mymsg;

int main (void)
{
	

	int pid_consumidor,pid_consumidor2,id_fila_msg,status;	
	mymsg m;
	struct msqid_ds buf;
	m.mtype = 1; 
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
		//consumidor 1 -- imprime impares
		int i;					
		for(i=0;i<MAXPRODUZIDO/2;i++)
		{	
			sleep(2);
			status = msgrcv( id_fila_msg, &m, sizeof(m.meu_int), 1, 0); 
			if(status != -1){
                    printf("CONSUMIDOR Impar: Mensagem recebida %d , status:%d \n",m.meu_int,status);
                }else{
                    printf("CONSUMIDOR Impar: ERRO AO LER MSG\n");
                }
        }	
        exit(0);
	
	} 
	else { //pai
		
		pid_consumidor2=fork();
		if (pid_consumidor2 == 0) //consumidor 2 - imprime pares
		{
			int i,status;	
            sleep(2); // pra deixar evidente que estão pegando msgs especificas
			for(i=0;i<MAXPRODUZIDO/2;i++)
			{	
				sleep(2);
				status = msgrcv( id_fila_msg, &m, sizeof(m.meu_int), 2, 0);
				if(status != -1){
                    printf("CONSUMIDOR Par: Mensagem recebida %d , status:%d \n",m.meu_int,status);
                }else{
                    printf("CONSUMIDOR Par: ERRO AO LER MSG\n");
                }			 
				    
            }
             exit(0);
		}
		else
		{ //pai produtor
			int i;
			for(i=0;i<MAXPRODUZIDO;i++)
			{
                if(i%2 == 0)
                { //mensagem par é tipo 2
                    m.mtype=2;
                }
                else{ //impar tipo 1
                    m.mtype=1;
                }
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