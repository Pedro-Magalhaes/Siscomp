#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 

void printStat (struct stat sb);

int main (void)
{
    struct stat sb;
    
    stat("./sc/a/meuArquivoA.txt",&sb);

    printf("File type do meuArquivo A:                ");
    printStat(sb);
    
    stat("./sc/a",&sb);
    printf("File type do diretorio a:                ");
    printStat(sb);
       

    // algoritimo de busca  ming/36300-how-write-code-c-search-file.html

    return 0;
}


void printStat (struct stat sb)
{
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

}