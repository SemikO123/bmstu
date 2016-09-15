#include <stdio.h>
#include <stdlib.h>
#define N 32

void InputNumbers(char *IntNum, char *Mant, char *ZnakPoryad, int *Poryadok);
void Normalize(char *Mant, char *ZnakPoryad, int *Poryadok);

int main(void)
{
	char IntNum[N];
	char Mant[N+2];
	char ZnakPoryad;
	int Poryadok;
	InputNumbers(IntNum, Mant, &ZnakPoryad, &Poryadok);
	// Normalize(Mant,&ZnakPoryad,&Poryadok);



}

void InputNumbers(char *IntNum, char *Mant, char *ZnakPoryad, int *Poryadok)
{
	do
	{
		printf("Целое число со знаком (+123 -987) :");
		scanf("%s",IntNum);
	}
	while (IntNum[0] != '-' && IntNum[0] != '+'); 

	printf("\nВведенное целое число: %s\n",IntNum);

	do
	{
		printf("Мантиса со знаком (+12.5 -.015) :");
		scanf("%s",Mant);
	}
	while (Mant[0] != '-' && Mant[0] != '+') ;
	printf("Порядок вещественного числа со знаком (+99999 -01) :");
	do
	{
		scanf("%c", &*ZnakPoryad);
		scanf("%d",&*Poryadok);

	}
	while ((*ZnakPoryad != '-' && *ZnakPoryad != '+') && (*Poryadok > 99999));
	
	printf("ZNAK=%c PORYADOK=%d\n",*ZnakPoryad,*Poryadok);
	printf("Введенное вещественное число : %sE%c%d",Mant,*ZnakPoryad,*Poryadok);

}

void Normalize(char *Mant, char *ZnakPoryad, int *Poryadok)
{
	int i=0;
	while (Mant[i] != '0');
		i +=1;
	printf("MANT count=%d",i);
}