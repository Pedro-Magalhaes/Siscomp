#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
void printConteudo (char* filepath);
void printdir(char *dir, char* filename ,char * root)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            /* Found a directory, but ignore . and .. */
            if(strcmp(".",entry->d_name) == 0 ||
                strcmp("..",entry->d_name) == 0)
                continue;
            
            /* Recurse at a new indent level */
            printdir(entry->d_name,filename,root);
        }
        else if(S_ISREG(statbuf.st_mode))
            {//eh arquivo vou comparar com o nome buscado
                if(strcmp(filename,entry->d_name) == 0)
                {                                        
                    printf("Found %s at dir %s\n",filename,dir);
                    printConteudo(filename);
                }
            }
    }
    chdir("..");
    closedir(dp);
}

int main()
{
    char file[] = "meuArquivoA.txt";
    printf("search file: %s -- Directory scan of /sc:\n",file);
    printdir(".", file ,"sc");
    printf("done.\n");
    exit(0);
}

void printConteudo (char* filepath)
{
    FILE* arq;    
    int c;
    arq = fopen(filepath,"r");
    if(arq==NULL)
    {
        printf("erro abrindo arquivo\n\n");
        return;
    }
    printf("conteudo do arquivo**********\n\n");
    while((c=fgetc(arq) )!=EOF )
    {

        putchar(c);
        
    }
    printf("\nFinal do conteudo*********\n");
    fclose(arq);

}