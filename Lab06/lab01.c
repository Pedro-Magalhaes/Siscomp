#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main (void)
{
	int fd[2];
	int i;
	int aux;
	pipe(fd);
	if (fork()==0) //filho
	{
		close(fd[0]);
		for(i=0;i<10;i++)
		{
			aux=i*10;
			write(fd[1],&aux,sizeof(int));
		}
			
	}else{
		
		close(fd[1]);
		for(i=0;i<10;i++)
		{
			read(fd[0],&aux,sizeof(int));
			printf("numero lido %d\n",aux);
		}
	
	}
	
	
	return 0;
}
