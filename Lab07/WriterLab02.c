#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define OPENMODE (O_WRONLY)
#define FIFO "minhaFifo"
int main (void)
    {
    int fpFIFO;
    char mensagem[50] = "Melancia sem caroço";
    if (access(FIFO, F_OK) == -1)
    {
        if (mkfifo (FIFO, S_IRUSR | S_IWUSR) != 0)
        {
            fprintf (stderr, "Erro ao criar FIFO %s\n", FIFO);
            return -1;
        }
    }
    puts ("Abrindo FIFO");
    if ((fpFIFO = open (FIFO, OPENMODE)) < 0)
    {
        fprintf (stderr, "Erro ao abrir a FIFO %s\n", FIFO);
        return -2;
    }
    //puts ("Começando a escrever...");
    while(strcmp(mensagem,"done")!=0)
    {
        printf("Digite algo, termina com 'done'\n");
        scanf("%s",mensagem);
        write(fpFIFO, mensagem, strlen(mensagem)+1);

    }
    
    puts ("Fim da escrita");
    close (fpFIFO);
    return 0;
}