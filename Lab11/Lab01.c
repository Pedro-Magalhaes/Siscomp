#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 

int main (void)
{
    FILE *arqA, *arqB, *arqC;
    mkdir("sc",0777);
    mkdir("sc/a",0777);
    mkdir("sc/b",0777);
    mkdir("sc/c",0777);

    arqA = fopen("./sc/a/meuArquivoA.txt", "w");
    arqB = fopen("./sc/b/meuArquivoB.txt", "w");
    arqC = fopen("./sc/c/meuArquivoC.txt", "w");

    fprintf(arqA,"Ola nobre colega, \n o senhor esta no arquivo A.txt \n Obrigado, de nada.\n");
    fprintf(arqB,"Ola colega, \n Voce esta no arquivo B.txt \n de nada.\n");
    fprintf(arqC,"Fala ai, \n ta no arquivo C.txt \n ta ta...\n");

    fclose(arqA);fclose(arqB);fclose(arqC);
    return 0;
}