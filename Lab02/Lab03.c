#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

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

int main (int argc, char** argv)
{
	for(;;){		
		char* aux;
		char input[100];
		char *arg[10];//vou reservar 10 a principio
		int pid_filho,status,i=0;
		
		printf("aguardando comando: $ ");
		fgets_wrapper(input,sizeof(input),stdin); //pega toda a linha digitada
			aux=strtok(input," "); //vai separar palavra a palavra quebrando a linha nos espacos
		while(aux!=NULL)
		{
			arg[i]=strdup(aux);
			aux=strtok(NULL," ");//vai "andando" palavra a palavra
			i++;
			if(i>8)//tamanho max elementos = size-2
				break;
		}
		arg[i]=NULL; //ultimo elemento null

		pid_filho=fork();
		if(pid_filho!=0)
		{
			waitpid(-1,&status,0);		
		}
		else{
			
			execvp(arg[0],arg);
		}
	}
	

	return 0;
}
