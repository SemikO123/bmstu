#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

/*
Проверить правильность расстановки скобок трех типов 
(круглых, квадратных и фигурных) в выражении.
**/


static char *error_names[]=
{
	"Ок\n",
	"Скобки в выражении расставлены верно\n",
	"Ошибка в расстановке скобок в выражении\n",
	"Стек пуст\n",
	"Стек переполнен\n",
	"Неверный ввод\n"
};


int main(void)
{
	struct stack_ta stack;
	stack.size = 0;
	struct stack_tl *head = NULL;
	printf("Введите выражение со скобками ");
	printf("(например 1/[(5+6)*{7-6})]) :");
	char string[LENGTH];
	scanf("%s", string);
	if (strlen(string) >= LENGTH-1)
	{
		error = INCORRECT;
		printf("В выражении должно быть не более %d символов\n", LENGTH-1);
		exit(INCORRECT); 
	}
	else
	{
		int flag = 0;
		for (int i = 0; string[i] != '\0'; i++)
			if (strchr("(){}[]", string[i]))
				flag = 1;
		if (flag == 1)
		{
		char *array_free[N];
		int time11 = clock();
		if (filling_stack_l(&head, string) != INCORRECT)
		{
			printf("\nВыполнение задания с реализацией стека СПИСКОМ:\n");
			print_stack_l(head);
			task_l(head, array_free);
			printf("%s%s%s",RED ,error_names[error], RESET);
			int time12 = clock();
			printf("%s* Используемая память - %d байт%s\n",YELLOW, (int)(size_l(head)*sizeof(struct stack_tl)), RESET);
			printf("%s* Времени потребовалось - %d тактов%s\n",YELLOW, time12-time11, RESET);
			printf("Напечатать свободные области памяти? (y/n)?: ");
			char answer[2];
			scanf("%s",answer);
			if (*answer == 'y')
			{
				printf("%s* Cвободные области: %s\n", YELLOW, RESET);
				for (int i = 0; i < size_l(head); i++)
					printf("       %p \n", (void*)array_free[i]);
			}
		}
		printf("_________________________________________________________\n");
		int time21 = clock();
		int size = 0;
		if (filling_stack_a(&stack, string, &size) != INCORRECT)
		{
			printf("\nВыполнение задания с реализацией стека МАССИВОМ:\n");
			print_stack_a(&stack);
			task_a(&stack);
			printf("%s%s%s",RED ,error_names[error], RESET);
			int time22 = clock();
			printf("%s* Используемая память - %d байт%s\n",YELLOW, size+(int)sizeof(stack.size), RESET);
			printf("%s* Времени потребовалось - %d тактов%s\n",YELLOW, time22-time21, RESET);
		}
		else
			printf("%s",error_names[INCORRECT]);

			
		}
		else
			printf("%sВы не ввели ни одной скобки. Нечего проверять%s\n", RED, RESET);
	}
	free_all(&head);
	
	return 0;
}
