#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define EVER ;;
#define BUFFER 16

union semun
{
	int	val;
	struct semid_ds *buf;
	ushort *array;
};
// inicializa o valor do semáforo
int setSemValue(int semId);
// remove o semáforo
void delSemValue( int semId);
// operação P
int semaforoP( int semId);
//operação V
int semaforoV( int semId);

int main ( int argc, char* argv[])
{
	int i;
	int	semId;
	int pid,segmento;
	int *variavel;
	
	// aloca a memória compartilhada
	segmento = shmget (IPC_PRIVATE, sizeof (int), IPC_CREAT | 											IPC_EXCL | S_IRUSR | S_IWUSR);
	// associa a memória compartilhada ao processo
	variavel = (int *) shmat (segmento, 0, 0);
	*variavel=0; 
		semId = semget (8752, 1, 0666 | IPC_CREAT);
		if (semId != 0)
		{
			setSemValue(semId);
		}
		else
		{
			printf("saindo erro, semId= %d \n",semId);
			exit(-1);
		}
			

	if((pid=fork())==0) //filho-soma 1
	{
		for(EVER)
		{		
			semaforoP(semId);
			printf("vou somar 1 a variavel, valor anterior= %d\n",*variavel);
			*variavel+=1;
			printf("resultado= %d\n",*variavel);
			fflush(stdout);
			semaforoV(semId);
			sleep (rand() %2);
		}
	}
	else
	{//pai-soma 5
		for(EVER)
		{
			semaforoP(semId);
			printf("vou somar 5 a variavel, valor anterior= %d\n",*variavel);
			*variavel+=5;
			printf("resultado= %d\n",*variavel);
			fflush(stdout);
			semaforoV(semId);
			sleep (rand() %2);
			
		}
	}
	return 0;
}
int setSemValue(int semId)
{
	union semun semUnion;
	semUnion.val = 1;
	return semctl(semId, 0, SETVAL, semUnion);
}
void delSemValue(int semId)
{
	union semun semUnion;
	semctl(semId, 0, IPC_RMID, semUnion);
}
int semaforoP( int semId)
{
	struct
	sembuf semB;
	semB.sem_num = 0;
	semB.sem_op = -	1;
	semB.sem_flg = SEM_UNDO;
	semop(semId, &semB, 1);
	return	0;
}
int semaforoV(int semId)
{
	struct sembuf semB;
	semB.sem_num = 0;
	semB.sem_op = 1;
	semB.sem_flg = SEM_UNDO;
	semop(semId, &semB, 1);
	return	0;
}
