#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    int fa,fb,fc;
    char a[]="ESCREVENDO NO INICIO";
    char b[]="ESCREVENDO NO MEIO";
    char c[]="ESCREVENDO NO FINAL";
    fa=open("sc/a/meuArquivoA.txt",O_RDWR);  
    fb=open("sc/b/meuArquivoB.txt",O_RDWR);
    fc=open("sc/c/meuArquivoC.txt",O_RDWR);
    if((fa < 0) || (fb < 0) || (fc < 0))
    {
        printf("erro abrindo arquivos\n");
        return -1;
    }
    write(fa,a,strlen(a)); //ja abre no inicio entao vou escrever
    lseek(fb,20,SEEK_SET); //levando arquivo b até uma posição no "meio" do arquivo
    write(fb,b,strlen(b));
    lseek(fc,0,SEEK_END); //colocando arquivo c no final
    write(fc,c,strlen(c));

    return 0;
    
}

