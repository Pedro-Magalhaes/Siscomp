#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

char *fgets_wrapper(char *buffer, size_t buflen, FILE *fp)
{/*peguei essa funcao da internet porque o gets tava me dando warnings*/
    if (fgets(buffer, buflen, fp) != 0)
    {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n')
            buffer[len-1] = '\0';
        
        return buffer;
    }
    return 0;
}


int main (void)
{
	int segmento, *flag;
	int i;
	int aux;
	char msg[80];
	segmento = shmget (8182, sizeof (int), S_IRUSR);
	// associa a memória compartilhada ao processo
	flag = (int*) shmat (segmento, 0, 0); // comparar o retorno com -1
	
	for(i=0;i<5;i++)
	{
			//printf("Digtie numero: \n");
			fgets_wrapper(msg,79,stdin);
			//scanf("%79[^\n]",msg);
			//fflush(stdin);			
			//aux=i;
			write(1,msg,strlen(msg)+1);
			*flag=1;
			//fflush(stdout);
	}	
	// libera a memória compartilhada do processo
	shmdt(flag);
	return 0;
}
