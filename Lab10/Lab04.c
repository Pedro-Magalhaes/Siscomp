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
#define  N_THREADS 2


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int pthread_mutex_init(pthread_mutex_t *mutex, 
                        const pthread_mutexattr_t *mutexattr);

int pthread_mutex_lock (pthread_mutex_t *mutex);
int pthread_mutex_unlock (pthread_mutex_t *mutex);
int pthread_mutex_destroy (pthread_mutex_t *mutex);

int minhaFila[MAXFILA];
int proxPosConsumidor = 0;
int proxPosProdutor = 0;

void* Produtor (void *produtor){
    int i;
    for(i=0;i<MAXPRODUZIDO;i++)
    {        
       
        pthread_mutex_lock( &mutex );        
        minhaFila[proxPosProdutor] = i; //não estou usando numeros aleatorios
        proxPosProdutor = (proxPosProdutor + 1) % MAXFILA;
        printf("\nPRODUTOR %d : enviado %d\n",(int)produtor,i);
        
        pthread_mutex_unlock( &mutex );    
        sleep(1);
    }

    printf("produtor acabou\n");
    pthread_exit(NULL);
}


void* Consumidor (void *consumidor){
        int i;
        int aux;					
		for(i=0;i<MAXPRODUZIDO;i++)
		{	
			sleep(2);
            
            pthread_mutex_lock( &mutex );   
            aux=minhaFila[proxPosConsumidor];
            printf("Consumidor %d recebeu %d \n",(int)consumidor,aux);
            proxPosConsumidor = (proxPosConsumidor + 1) % MAXFILA;
            
            pthread_mutex_unlock( &mutex );
		}	
        pthread_exit(NULL);
}

int main (void)
{
	pthread_t t_produtor[2];
    pthread_t t_consumidor[2];
    int t;

    // criando threads
    for (t = 0; t < N_THREADS; t++)
    {sleep(1);
        pthread_create(&t_produtor[t], NULL, Produtor, (void *) t);
    }
    for (t = 0; t < N_THREADS; t++)
    {sleep(1);
        pthread_create(&t_consumidor[t], NULL, Consumidor, (void *) t);
    }
    // threads criadas

    // join
    for(t=0;t < 2; t++)  {
        pthread_join(t_produtor[t],NULL); 
    }
    for(t=0;t < 2; t++)  {
        pthread_join(t_consumidor[t],NULL); 
    }
    // endJoin
	
    printf("\nTudo terminado\n");	
	
	return 0;
}


