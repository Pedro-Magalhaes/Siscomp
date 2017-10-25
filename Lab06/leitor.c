#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main (void)
{
	int segmento, *flag;
	int i;
	int aux;
	char msg[81];
	msg[80]='\0';
	segmento = shmget (8182, sizeof (int), S_IRUSR);
	// associa a memória compartilhada ao processo
	flag = (int*) shmat (segmento, 0, 0); // comparar o retorno com -1
	for(i=0;i<5;i++)
		{
			if(*flag==1){
				read(0,msg,79);	
				*flag=0;		
				printf(" leitor: lido %s\n",msg);
				
			}
			else{
				//printf("nada pra ler vou dormir\n");
				sleep(1);
				i--;
			}
			
		}	
	// libera a memória compartilhada do processo
	shmdt(flag);
	return 0;	
}
