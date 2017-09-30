#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
void handler(int sinal);
int main (void)
{
	float a,b;
	float soma,dif,mult,div;
	signal(SIGFPE, handler);
	puts ("Digite dois numeros:");
	scanf("%f",&a);
	scanf("%f",&b);
	soma=a+b;
	dif=a-b;
	mult=a*b;
	div=a/b;
	printf("soma: %f,sub: %f,mult: %f,Div: %f\n",soma,dif,mult,div);
	
	return 0;
}
void handler(int sinal)
{
	printf ("Segundo operando igual a Zero!\n");
	exit(-1);

}
