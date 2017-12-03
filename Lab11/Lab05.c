 #include<fcntl.h> 
#include<sys/stat.h> 
#include<stdio.h> 
#include<string.h> 
#include<errno.h> 
int main(void) 
{ 
    int fd, rt; 
    fd = open("sc/a/meuArquivoA.txt", O_RDWR); 
    if (fd == -1){ 
        printf("Erro arquivo\n");
     }
    rt = fchmod(fd, S_IROTH | S_IWOTH | S_IXOTH); 
    if (rt == -1){ 
        printf("Erro fchmod() \n");
     }
     return 0;
}