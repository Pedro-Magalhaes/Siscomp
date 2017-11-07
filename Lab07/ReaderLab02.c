#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define OPENMODE (O_RDONLY)
#define FIFO "minhaFifo"
int main (void)
{
    int fpFIFO;
    char msg[50];
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
    puts ("Começando a ler...");
    while (read (fpFIFO, msg, 50) > 0)
    {
        printf("%s\n",msg);
    }
    
    puts ("Fim da leitura");
    close (fpFIFO);
    return 0;
}