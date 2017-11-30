#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 

int main (void)
{
    struct stat sb;
    FILE *arqA, *arqB, *arqC;
    mkdir("sc",0777);
    mkdir("sc/a",0777);
    mkdir("sc/b",0777);
    mkdir("sc/c",0777);

    arqA = fopen("./sc/a/meuArquivoA.txt", "w");
    arqB = fopen("./sc/b/meuArquivoB.txt", "w");
    arqC = fopen("./sc/c/meuArquivoC.txt", "w");

    stat("./sc/a/meuArquivoA.txt",&sb);

    printf("File type do meuArquivo A:                ");

           switch (sb.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }
    stat("./sc/a",&sb);
    printf("File type do diretorio a:                ");

           switch (sb.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }


    // algoritimo de busca  ming/36300-how-write-code-c-search-file.html

    return 0;
}