#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main (void)
{
	int fd,fd2;
	int retorno;
	int valorLido;
	if ((fd = open("dados.txt", O_RDONLY))==-1)
	{
		perror("Error open(dados)");
		return -1;
	}
	
	if ((fd2 = open("saida.txt", O_WRONLY | O_CREAT))==-1)
	{
		perror("Error open(saida)");
		return -1;
	}
	
	
	if((retorno = dup2(fd,0))==-1)
	{
		perror("Error open()");
		return -1;
		
	}
	
	if((retorno = dup2(fd2,1))==-1)
	{
		perror("Error open()");
		return -1;
		
	}
	
	while(scanf("%d",&valorLido)==1)
		printf("valor lido = %d\n",valorLido);
	return 0;
}
