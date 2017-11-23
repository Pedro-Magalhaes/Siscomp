#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/sem.h>
#define MAXFILA 8
#define MAXPRODUZIDO 20


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int pthread_mutex_init(pthread_mutex_t *mutex, 
                        const pthread_mutexattr_t *mutexattr);

int pthread_mutex_lock (pthread_mutex_t *mutex);
int pthread_mutex_unlock (pthread_mutex_t *mutex);
int pthread_mutex_destroy (pthread_mutex_t *mutex);

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

int minhaFila[MAXFILA];
int proxPosConsumidor = 0;
int proxPosProdutor = 0;
int	semProdId;
int	semConsId;

void* Produtor (void *produtor){
    int i;
    for(i=0;i<MAXPRODUZIDO;i++)
    {        
        semaforoP(semProdId);
        pthread_mutex_lock( &mutex );        
        minhaFila[proxPosProdutor] = i; //não estou usando numeros aleatorios
        proxPosProdutor = (proxPosProdutor + 1) % MAXFILA;
        printf("\nPRODUTOR: enviado %d\n",i);
        semaforoV(semConsId);
        pthread_mutex_unlock( &mutex );    
        sleep(1);
    }

    printf("produtor acabou\n");
    pthread_exit(NULL);
}


void* Consumidor (void *consumidor){
    	int i;					
		for(i=0;i<MAXPRODUZIDO;i++)
		{	
			sleep(2);
            semaforoP(semConsId);	
            pthread_mutex_lock( &mutex );   
			printf("Mensagem recebida, %d \n",i);
            semaforoV(semProdId);
            pthread_mutex_unlock( &mutex );
		}	
        pthread_exit(NULL);
}

int main (void)
{
	pthread_t threads[2];
    int t;

    semProdId = semget (IPC_PRIVATE, 1, 0666 | IPC_CREAT);
	setSemValue(semProdId);
    semConsId = semget (IPC_PRIVATE, 1, 0666 | IPC_CREAT);
	setSemValue(semConsId);

    pthread_create(&threads[0], NULL, Consumidor, (void *) 0);
	pthread_create(&threads[1], NULL, Produtor, (void *) 1);


    for(t=0;t < 2; t++)  {
        pthread_join(threads[t],NULL); 
    }
	
    printf("\nTudo terminado\n");	
	
	return 0;
}


int setSemValue(int semId)
{
	union semun semUnion;
	semUnion.val = MAXFILA;
	return semctl(semId, 0, SETVAL, semUnion);
}
void delSemValue(int semId)
{
	union semun semUnion;
	semctl(semId, 0, IPC_RMID, semUnion);
}
int semaforoP( int semId)
{
	struct sembuf semB;
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