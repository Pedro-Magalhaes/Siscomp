#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define F 2

void sinalfilho (int signal);


int main (void)
{

	int segmento, *flag;
	int fd[2];
	int i;
	int aux;
	
	segmento = shmget(8182,sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
	flag= (int*) shmat (segmento,0,0);
	*flag=0;
	pipe(fd);
	if (fork()==0) //filho
	{
		close(fd[0]);
		dup2(fd[1],1);
		
		close(fd[1]);
		execl("./esc", "/esc", NULL);
			
	}else{
		if (fork()==0) 
		{
			close(fd[1]);			
			dup2(fd[0],0);
			//vi na internet falando pra fechar depois de dar dup, mas já tentei sem fechar nada
			close(fd[0]); 
			execl("./lei", "/lei", NULL);
		}
		else{			
			close(fd[0]);
			close(fd[1]);
			waitpid(-1,&aux,0);
		}
	}
	
	// libera a memória compartilhada do processo
	shmdt(flag);
	
	// libera a memória compartilhada (esta sendo feito no outro processo)
	shmctl(segmento, IPC_RMID, 0);
	return 0;
}
