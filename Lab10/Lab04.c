#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <ctype.h>

#define MAXFILA 8
#define MAXPRODUZIDO 20
#define  N_THREADS 2

int mypow(int , int);
int pthread_mutex_init(pthread_mutex_t *mutex, 
                        const pthread_mutexattr_t *mutexattr);
int pthread_mutex_lock (pthread_mutex_t *mutex);
int pthread_mutex_unlock (pthread_mutex_t *mutex);
int pthread_mutex_destroy (pthread_mutex_t *mutex);

int minhaFila[MAXFILA];
int proxPosConsumidor = 0;
int proxPosProdutor = 0;
int estoque = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t can_prod = PTHREAD_COND_INITIALIZER;
pthread_cond_t can_consume = PTHREAD_COND_INITIALIZER;


void* Produtor (void* produtor){
    int i;
    for(i=0;i<MAXPRODUZIDO / N_THREADS ;i++)
    {        
        int enviando = (i+1) * mypow(-1,(int)produtor+1) ;//não estou usando numeros aleatorios

        pthread_mutex_lock( &mutex ); // inicio area critica
        if (estoque >= MAXFILA)
        {
            printf("Produtor %d indo dormir\n",(int)produtor);
            pthread_cond_wait(&can_prod,&mutex);
        }else if (estoque > MAXFILA / 2){//acorda consumidor
           pthread_cond_signal(&can_consume);
        }   
        estoque++;     
        minhaFila[proxPosProdutor] = enviando; 
        proxPosProdutor = (proxPosProdutor + 1) % MAXFILA;
        printf("\nPRODUTOR %d : enviado %d\n",(int)produtor,enviando);        
        pthread_mutex_unlock( &mutex ); // fim area critica    
        sleep(1);
    }

    printf("produtor %d acabou ****\n",(int)produtor);
    pthread_exit(NULL);
}


void* Consumidor (void* consumidor){
        int i;
        int aux;        				
		for(i=0;i<MAXPRODUZIDO / N_THREADS;i++)
		{	
			sleep(2);
            
            pthread_mutex_lock( &mutex );  // inicio area critica
            if(estoque == 0)
            {
                pthread_cond_wait(&can_consume,&mutex);
                //return;
            }else if (estoque < MAXFILA / 2){ //acorda produtor
                pthread_cond_signal(&can_prod);
            }
            estoque--;
            aux=minhaFila[proxPosConsumidor];
            proxPosConsumidor = (proxPosConsumidor + 1) % MAXFILA;
            printf("Consumidor %d recebeu %d \n",(int)consumidor,aux);
            
            pthread_mutex_unlock( &mutex );// fim area critica
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


int mypow(int base, int expoente){
    int result;
    if (base == 0)
    {
        return 0;
    }
    if (expoente == 0)
    {
        return 1;
    }
    if (expoente == 1)
    {
        return base;
    }
    result = base;
    expoente--;
    for (;expoente>0;expoente--){
        result = result * result;
    }

    return result;
}