#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main (void)
{
	int fd[2];
	int fd2;
	int retorno;
	int valorLido;	
	
	pipe(fd);
	
	if (fork()==0) //filho
	{
		close(fd[0]);
		dup2(fd[1],1);
		const char path[]= "/bin/ls";
		const char arg[]= "/bin/ls";
		execl(path,arg,NULL);
		printf("alo\n");
			
	}else{
		close(fd[1]);
		dup2(fd[0],0);
		const char path[]= "/bin/cat";
		const char arg[]= "/bin/cat";
		execl(path,arg,NULL);
		
	}
	
	return 0;
}
