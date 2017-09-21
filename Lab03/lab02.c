#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
int main (int argc, char *argv[])
{
	int segmento;
	char lido[256];
	char* msg;
	printf("Digite a ms do dia: ");
	scanf("%s",lido);
	
	
	// aloca a memória compartilhada
	segmento = shmget (8180, sizeof (char)*256, IPC_CREAT | S_IRUSR | S_IWUSR);
	// associa a memória compartilhada ao processo
	msg = (char *) shmat (segmento, 0, 0); // comparar o retorno com -1
	strcpy(msg,lido);
	
	
	
	
	// libera a memória compartilhada do processo
	shmdt(msg);
	// libera a memória compartilhada
	//shmctl(segmento, IPC_RMID, 0);
	return 0;
}
