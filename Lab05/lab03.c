#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
void handlerInicio(int sinal);
void handlerFinal(int sinal);
time_t tempo;
int main (void)
{

signal(SIGUSR1, handlerInicio);
signal(SIGUSR2, handlerFinal);
while(1)
{}


return 0;
}
void handlerInicio(int sinal)
{
	printf ("Chamada iniciada\n");
	tempo=time(NULL);

}
void handlerFinal(int sinal)
{
	time_t tempoFinal=time(NULL);
	
	float tempoChamada = (float)difftime(tempoFinal,tempo); 
	float valor;
	
	if(tempoChamada<=60)
		valor=(tempoChamada*2)/100;
	else
		valor=120+(tempoChamada-60)/100;
	printf("Chamada terminada, Valor a ser cobrado: R$%f\n",valor);
	tempo=0;

}
