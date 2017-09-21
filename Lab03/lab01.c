#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#define LIN 3

#define COL 3

void printMvetor(int*m,int lin,int col)
{
	int i,j,w=0;
	for (i=0;i<lin;i++)
	{
		for(j=0;j<col;j++)
			printf(" %d",m[i*w+j]);
		w++;
		printf("\n");
	}
}

void preenche (int* m1,int* m2,int* m3,int tam)
{
	int i;
	for(i=0;i<tam;i++)
	{
		m1[i]=1;
		m2[i]=2;
		m3[i]=0;
	}
	return;
}

int main (int argc, char *argv[])
{
int segmento1,segmento2,segmento3, *matrizA,*matrizB,*matrizC, id, pid, status;
int i;
int tam=(int)LIN * (int)COL;

// aloca a memória compartilhada
segmento1 = shmget (IPC_PRIVATE, sizeof (int)*(int)LIN*(int)COL, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

// associa a memória compartilhada ao processo
matrizA = (int *) shmat (segmento1, 0, 0); // comparar o retorno com -1

segmento2 = shmget (IPC_PRIVATE, sizeof (int)*(int)LIN*(int)COL, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

matrizB=(int *) shmat (segmento2, 0, 0); // comparar o retorno com -1

segmento3 = shmget (IPC_PRIVATE, sizeof (int)*(int)LIN*(int)COL, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

matrizC=(int *) shmat (segmento3, 0, 0); // comparar o retorno com -1

preenche (matrizA,matrizB,matrizC,(int)LIN*(int)COL);
printMvetor(matrizA,(int)LIN,(int)COL);

for(i=0;i<(int)LIN;i++)
{
	id=fork();
	if (id < 0)
	{
		puts ("Erro na criação do novo processo");
		exit (-2);
	}
	else if(id==0)
		break;
}

if (id == 0)
{
	int j;
	int inicio=i*(int)LIN;
	
	for(j=inicio;j<inicio+(int)COL;j++)
	{
		printf("hello sou filho<%d> meu inicio=%d: \n",i,inicio);
		matrizC[j]=matrizA[j]+matrizB[j];
	}	
}
else
{
	waitpid(-1,&status,0);
	waitpid(-1,&status,0);
	waitpid(-1,&status,0);
	printMvetor(matrizC,(int)LIN,(int)COL);
}
// libera a memória compartilhada do processo
shmdt(matrizA);
// libera a memória compartilhada
shmctl(segmento1, IPC_RMID, 0);
// libera a memória compartilhada do processo
shmdt(matrizB);
// libera a memória compartilhada
shmctl(segmento2, IPC_RMID, 0);
// libera a memória compartilhada do processo
shmdt(matrizC);
// libera a memória compartilhada
shmctl(segmento3, IPC_RMID, 0);
return 0;
}
