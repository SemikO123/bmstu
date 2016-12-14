#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void init_queue_arr(struct queue_arr *que)
{
	que->first = 0;
	que->last = 0;
}

int qin_arr(struct queue_arr *que, struct request new)
{
	if (que->last < MAX_SIZE)
	{
		que->queue[que->last] = new;
		que->last++;
		return 0;
	}
	else
		return 1;
}

int empty_queue_arr(struct  queue_arr *que)
{
	return (que->last <= que->first) ? 1 : 0;
}

struct request qout_arr(struct queue_arr *que)
{
	struct request x = que->queue[que->first];
	for (int i = que->first; i < que->last; i++)
		que->queue[i] = que->queue[i+1];
	que->last--;
	return x;
}

struct request create_new_request_arr(float t1, float t2, float t3, float t4)
{
	struct request new;
	new.arrival_time = randomfloat(t1, t2);
	new.process_time = randomfloat(t3, t4);
	new.down_time = 0;
	return new;
}

void waiting_in_queue(struct queue_arr *que, float t)
{
	for (int i = que->first; i < que->last; i++)
		que->queue[i].down_time += t;
}

void array(void)
{
	int iterations = 0;
	float length = 0;
	float t = 0, ta = 0;
	int P = 0; 

	struct queue_arr *q1 = malloc(sizeof(struct queue_arr ));
	init_queue_arr(q1);
	struct request new = create_new_request_arr(t1, t2, t3, t4);
	qin_arr(q1, new);
	struct request old = qout_arr(q1);
	t = old.process_time;
	idle = old.arrival_time;
	new = create_new_request_arr(t1, t2, t3, t4);
	ta = new.arrival_time;


	//printf("t=%f idle=%f ta= %f\n", t, idle, ta);
	printf("%sОбработано       Текущая длина     Средняя длина\n", GREEN);
	printf("  заявок            очереди            очереди%s\n", RESET);
	while (N != 1000)
	{
		iterations++;
		length += (q1->last - q1->first);
		if (t < ta)
		{
			waiting_in_queue(q1, t);
			if (empty_queue_arr(q1) == 0)
			{
				model += t;
				ta -= t;
			}
			else
			{
				idle += ta-t;
				model += ta;
				if(qin_arr(q1, new))
				{
					printf("Очередь переполнена!\n");
					return;
				}
				count_in++;
				new = create_new_request_arr(t1, t2, t3, t4);
				ta = new.arrival_time;
			}
			old = qout_arr(q1);
			t = old.process_time;
			Nwork++;

			P = rand() % 100;
			if (P < 80)
			{
				old. down_time = 0;
				if (qin_arr(q1, old))
				{
					printf("Очередь переполнена!\n");
					return;
				}
			}
			else
			{
				twait += old.down_time;
				N++;
				if (N % 100 == 0 && N != 0)
					printf(" %5d               %3d                 %.2f\n", N, q1->last - q1->first, length/iterations);
			}
		}
		else
		{
			if (qin_arr(q1, new))
			{
				printf("Очередь переполнена!\n");
				return;
			}
			count_in++;
			model += ta;
			new = create_new_request_arr(t1, t2, t3, t4);
			t -= ta;
			ta = new.arrival_time;
		}
	}
	free(q1);

	printf("\n Время моделирования - %s%.2f%s\n",GREEN, model, RESET);
	if (N != 0)
		printf(" Среднее время пребывания заявки в очереди - %s%.2f%s\n",GREEN, twait/N, RESET);
	printf("\n Вошедших заявок - %s%d%s\n",GREEN, count_in, RESET);
	printf(" Вышедших заявок - %s%d%s\n",GREEN, N, RESET);
	printf(" ОА проработал %s%d%s раз\n",GREEN, Nwork, RESET);
	//printf(" Простой ОА - %s%.2f%s",GREEN, idle, RESET);

	float aver_in = (t1+t2)/2;
	float aver_out = (t3+t4)/2;
	printf("\n%sПогрешность по входу -  %.2f процентов\n",GREEN, 100*fabs(count_in - model/aver_in)/(model/aver_in));
	printf("Погрешность по выходу - %.2f процентов\n%s", 100*fabs(Nwork*aver_out + idle - model)/(Nwork*aver_out + idle), RESET);

	}




void init_queue_list(struct queue_list *que)
{
	que->length = 0;
	que->in = NULL;
	que->out = NULL;
}

void qin_list(struct queue_list *que, struct request *new)
{
	if (que->out == NULL && que->in == NULL)
	{
		que->in = new;
		que->out = que->in;
	}
	else
	{
		que->in->next = new;
		que->in = new;
	}
	new->next = NULL;
	que->length++;
}

int empty_queue_list(struct queue_list *que)
{
	return (que->length == 0) ? 1 : 0;
}

struct request qout_list(struct queue_list *que)
{
	struct request *tmp;
	struct request x;
	x = *(que->out);
	tmp = que->out;
	que->out = que->out->next;
	if (que->out == NULL)
		que->in = NULL;
	free(tmp);
	que->length--;
	return x;
}

void create_new_request_list(struct  request *new, float t1, float t2, float t3, float t4)
{
	new->arrival_time = randomfloat(t1, t2);
	new->process_time = randomfloat(t3, t4);
	new->down_time = 0;	
}

void waiting_in_queue1(struct queue_list *que, float t)
{
	for (struct request *i = que->out; i; i = i->next)
		i->down_time += t;
}

void list(void)
{
	int iterations = 0;
	float length = 0;
	float t = 0, ta = 0;
	int P = 0;

	struct queue_list *q2 = malloc(sizeof(struct queue_list ));
	init_queue_list(q2);
	struct request *new = (struct request*)malloc(sizeof(struct request));
	create_new_request_list(new,t1, t2, t3, t4);
	qin_list(q2, new);
	struct request *old = (struct request*)malloc(sizeof(struct request));
	*old = qout_list(q2);
	t = old->process_time;
	idle = old->arrival_time;
	new = (struct request*)malloc(sizeof(struct request));
	create_new_request_list(new, t1, t2, t3, t4);
	ta = new->arrival_time;

	printf("%sОбработано       Текущая длина     Средняя длина\n", GREEN);
	printf("  заявок            очереди            очереди%s\n", RESET);
	while (N != 1000)
	{
		iterations++;
		length += q2->length;

		if (t < ta)
		{
			waiting_in_queue1(q2, t);
			if (empty_queue_list(q2) == 0)
			{
				model += t;
				ta -= t;
			}
			else
			{
				model += ta;
				idle += ta-t;
				qin_list(q2, new);
				count_in++;
				new = (struct request*)malloc(sizeof(struct request));
				create_new_request_list(new, t1, t2, t3, t4);
				ta = new->arrival_time;
			}
			old = (struct request*)malloc(sizeof(struct request));
			*old = qout_list(q2);
			t = old->process_time;
			Nwork++;
			P = rand() % 100;
			if (P < 80)
			{
				old->down_time = 0;
				qin_list(q2, old);
			}
			else
			{
				free(old);
				twait += old->down_time;
				N++;
				if (N % 100 == 0 && N != 0)
					printf(" %5d               %3d                 %.2f\n", N, q2->length, length/iterations);
			}
		}
		else
		{
			qin_list(q2, new);
			count_in++;
			model += ta;
			new = (struct request*)malloc(sizeof(struct request));
			create_new_request_list(new, t1, t2, t3 ,t4);
			t -= ta;
			ta = new->arrival_time;
		}
	}
	while (empty_queue_list(q2) != 1)
		*old = qout_list(q2);
	free(q2);
	free(new);
	free(old);


	printf("\n Время моделирования - %s%.2f%s\n",GREEN, model, RESET);
	if (N != 0)
		printf(" Среднее время пребывания заявки в очереди - %s%.2f%s\n",GREEN, twait/N, RESET);
	printf("\n Вошедших заявок - %s%d%s\n",GREEN, count_in, RESET);
	printf(" Вышедших заявок - %s%d%s\n",GREEN, N, RESET);
	printf(" ОА проработал %s%d%s раз\n",GREEN, Nwork, RESET);
	//printf(" Простой ОА - %s%.2f%s",GREEN, idle, RESET);

	float aver_in = (t1+t2)/2;
	float aver_out = (t3+t4)/2;
	printf("\n%sПогрешность по входу -  %.2f процентов\n",GREEN, 100*fabs(count_in - model/aver_in)/(model/aver_in));
	printf("Погрешность по выходу - %.2f процентов\n%s", 100*fabs(Nwork*aver_out + idle - model)/(Nwork*aver_out + idle), RESET);
}

void print_table(struct queue_list *que)
{
	printf("%s         Заявка                 Адрес \n", GREEN);
	printf("пocтупление    обработка       в памяти%s\n", RESET);
	for (struct request *i = que->out; i; i = i->next)
		printf("  %.2f           %.2f          %p\n", i->arrival_time, i->process_time, (void*)i);
	printf("\n");

}



unsigned long long int tick(void)
{
	unsigned long long int time = 0;
	__asm__ __volatile__ ("rdtsc" : "=A" (time));
	return time;
}

float randomfloat(float minimum, float maximum)
{
	return (float) rand() / RAND_MAX * (maximum - minimum) + minimum;
}

void compare(int n)
{
	struct queue_list *que_list = malloc(sizeof(struct queue_list));
	init_queue_list(que_list); 
	struct queue_arr *que_arr = malloc(sizeof(struct queue_arr));
	init_queue_arr(que_arr);
	struct request *list, array;
	unsigned long long timel1, timel2, timel3;
	unsigned long long timea1, timea2, timea3;

	timel1 = tick();
	for (int i = 0; i < n; i++)
	{
		list = (struct request*)malloc(sizeof(struct request));
		create_new_request_list(list, t1, t2, t3, t4);
		qin_list(que_list, list);
	}
	timel2 = tick();
	for (int i = 0; i < n; i++)
		qout_list(que_list);
	timel3 = tick();
	//free(list);
	free(que_list);

	timea1 = tick();
	for (int i = 0; i < n; i++)
	{
		array = create_new_request_arr(t1, t2, t3, t4);
		qin_arr(que_arr, array);
	}
	timea2 = tick();
	for (int i = 0; i < n; i++)
		qout_arr(que_arr);
	timea3 = tick();
	free(que_arr);

	printf("%s                  Время  входа        Время выхода     Используемая\n", GREEN);
	printf("                   %d заявок          %d заявок         память\n%s", n, n, RESET);
	printf(" %s Массив%s           %6lld тик         %8lld тик       %4d байт\n",GREEN, RESET, timea2-timea1, timea3-timea2, (int)sizeof(struct queue_arr));
	printf("  %sСписок%s           %6lld тик         %8lld тик       %4d байт\n", GREEN, RESET, timel2-timel1, timel3-timel2, (int)sizeof(struct queue_list)*MAX_SIZE + (int)sizeof(struct request));
}

void fragmentation(void)
{
	int menu = -1;
	struct queue_list *que = malloc(sizeof(struct queue_list));
	init_queue_list(que);
	struct request *new;
	do
	{
		print_table(que);
		printf("%s(1) Добавление заявки в очередь\n", YELLOW);
		printf("(2) Исключение заявки из очереди\n");
		printf("(0) Выход%s\n", RESET);
		scanf("%d", &menu);
		switch(menu)
		{
			case 1:
				new = (struct request*)malloc(sizeof(struct request));
				create_new_request_list(new, t1, t2, t3, t4);
				qin_list(que, new);
				break;
			case 2:
				if (empty_queue_list(que) == 0)
					qout_list(que);
				else
				{
					printf("%sОчередь пуста!%s\n", RED, RESET);
				}
				break;
			case 0:
				break;
			default:
				printf("%sВыберите пункт меню!%s\n", RED, RESET);
				break;
		}
	} 
	while (menu != 0);

	while (empty_queue_list(que) != 1)
		qout_list(que);
	free(que);
}