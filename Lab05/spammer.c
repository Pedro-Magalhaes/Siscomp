#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>

#define EVER ;;

int main (int argc, char *argv[])
{
	if(argc<2)
	{
		printf("erro, nenhum parametro recebido\n");
		exit(-1);
	}
	for (EVER)
	{
		printf("Oi, eu sou o programa do processo<%d>\n",atoi(argv[1]));
		sleep(1);
	}
	return 0;
}
