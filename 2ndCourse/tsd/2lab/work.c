#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

static char *error_names[]=
{
	"Ок\n",
	"Скобки в выражении расставлены верно\n",
	"Ошибка в расстановке скобок в выражении\n",
	"Стек пуст\n",
	"Стек переполнен\n",
	"Неверный ввод\n"
};

int main()
{
	printf("%sСтек массивом(1) или стек списком(2): %s", WHITE, RESET);
	int answer;
	scanf("%d", &answer);
	switch(answer)
	{
	case 1:
		{
			struct stack_ta stack;
			stack.size = 0;
			int flag = 1;
			do
			{
				printf("Push(1) Pop(2) Print(3) Info(4) Exit(0): ");
				int answer1 = 0;
				scanf("%d",&answer1);
				switch(answer1)
				{
					case 1:
					{
						char new;
						printf("%sВведите данные: %s", RED, RESET);
						scanf("%c", &new);
						scanf("%c", &new);
						push_a(&stack, new);
						if (error != OK)
							printf("%s",error_names[error]);
						break;
					}
					case 2:
						pop_a(&stack);
						if (error != OK)
							printf("%s",error_names[error]);
						break;
					case 3:
						print_stack_a(&stack);
						break;
					case 4:
						printf("%s* Используемая память - %d байт%s\n",YELLOW, stack.size+(int)sizeof(stack.size), RESET);
						break;
					case 0:
						flag = 0;
						break;
					default:
						printf("Неверный запрос\n");
						flag = 0;
						break;
				}

			}
			while (flag);
			break;
		}
	case 2:
		{
			struct stack_tl *head = NULL;
			int flag = 1;
			int key = 0;
			int count = 0;
			char *array_free[N] = {NULL};
			do
			{
				printf("Push(1) Pop(2) Print(3) Info(4) Exit(0): ");
				int answer1 = 0;
				scanf("%d",&answer1);
				switch(answer1)
				{
					case 1:
					{
						char new;
						printf("%sВведите данные: %s", RED, RESET);
						scanf("%c", &new);
						scanf("%c", &new);
						push_l(&head, new);
						if (array_free[count-1] == stack_adr_l(head) && key == 1)
						{
							stack_adress_del(head, array_free, &count);
						}
						if (error != OK)
							printf("%s",error_names[error]);
						break;
					}
					case 2:
						key = 1;
						stack_adress_add(head, array_free, &count);
						pop_l(&head);
						if (error != OK)
							printf("%s",error_names[error]);
						break;
					case 3:
						print_stack_l(head);
						break;
					case 4:
						printf("%s* Используемая память - %d байт%s\n",YELLOW, (int)(size_l(head)*sizeof(struct stack_tl)), RESET);
						if (count != 0)
						{
							printf("%s* Свободные области: %s\n", YELLOW, RESET);
							for (int i = 0; i < count; i++)
							{
								printf("   %p\n", array_free[i]);
							}
						}
						break;
					case 0:
						flag = 0;
						break;
					default:
						printf("Неверный запрос\n");
						flag = 0;
						break;
				}
			}
			while (flag);
			free_all(&head);
			break;
		}

	default:
		printf("Не выбран способ реализации стека\n");
		break;
	}
}