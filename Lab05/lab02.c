#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
void handler(int sinal);
int main (void)
{
	int a,b;
	int soma,dif,mult,div;
	signal(SIGFPE, handler);
	puts ("Digite dois numeros:");
	scanf("%d",&a);
	scanf("%d",&b);
	soma=a+b;
	dif=a-b;
	mult=a*b;
	div=a/b;
	printf("soma: %d,sub: %d,mult: %d,Div: %d\n",soma,dif,mult,div);
	
	return 0;
}
void handler(int sinal)
{
	printf ("Segundo operando igual a Zero!\n");
	exit(-1);

}
