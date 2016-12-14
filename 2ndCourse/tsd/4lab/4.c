#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
/*
Система массового обслуживания состоит из обслуживающего аппарата (ОА) 
и очереди заявок.
Заявки  поступают в "хвост" очереди по случайному закону с интервалом времени Т1,
равномерно распределенным от 0 до 6 единиц времени  (е.в.). В ОА они поступают 
из "головы" очереди по одной и обслуживаются также равновероятно за время Т2 
от 0 до 1 е.в., 

Каждая заявка после ОА   вновь поступает в "хвост" очереди, совершая всего 5 циклов 
бслуживания, после чего покидает систему. (Все времена – вещественного типа) 

В начале процесса в системе заявок нет.

Смоделировать процесс обслуживания до ухода из системы первых 1000 заявок, 
выдавая после обслуживания каждых 100 заявок информацию о текущей и средней 
длине очереди, а в конце процесса - общее время моделирования и количестве 
вошедших в систему и вышедших из нее заявок, количестве срабатываний ОА, время 
простоя аппарата. 

По требованию пользователя выдать на экран адресов элементов очереди при удалении 
и добавлении элементов. Проследить, возникает ли при этом фрагментация памяти.
*/

/* GLOBAL */
	float t1 = 0, t2 = 6, t3 = 0, t4 = 1;
	float idle = 0;
	float model = 0;
	int N = 0; 
	int count_in = 0; 
	int Nwork = 0;  
	float twait = 0; 

#define MAX_SIZE 100

struct request
{
	float arrival_time;
	float process_time;
	float down_time;
	struct request *next;
};

struct queue_arr
{
	struct request queue[MAX_SIZE];
	int first;
	int last;
};

struct queue_list
{
	int length;
	struct request *in, *out;
};

void init_queue_arr(struct queue_arr *que)
{
	que->first = 0;
	que->last = 0;
}

void init_queue_list(struct queue_list *que)
{
	que->length = 0;
	que->in = NULL;
	que->out = NULL;
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

int empty_queue_arr(struct  queue_arr *que)
{
	return (que->last <= que->first) ? 1 : 0;
}

int empty_queue_list(struct queue_list *que)
{
	return (que->length == 0) ? 1 : 0;
}

struct request qout_arr(struct queue_arr *que)
{
	struct request x = que->queue[que->first];
	for (int i = que->first; i < que->last; i++)
		que->queue[i] = que->queue[i+1];
	que->last--;
	return x;
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

float randomfloat(float minimum, float maximum)
{
	return (float) rand() / RAND_MAX * (maximum - minimum) + minimum;
}

struct request create_new_request_arr(float t1, float t2, float t3, float t4)
{
	struct request new;
	new.arrival_time = randomfloat(t1, t2);
	new.process_time = randomfloat(t3, t4);
	new.down_time = 0;
	return new;
}

void create_new_request_list(struct  request *new, float t1, float t2, float t3, float t4)
{
	new->arrival_time = randomfloat(t1, t2);
	new->process_time = randomfloat(t3, t4);
	new->down_time = 0;	
}

void waiting_in_queue(struct queue_arr *que, float t)
{
	for (int i = que->first; i < que->last; i++)
		que->queue[i].down_time += t;
}

void waiting_in_queue1(struct queue_list *que, float t)
{
	for (struct request *i = que->out; i; i = i->next)
		i->down_time += t;
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


	printf("t=%f idle=%f ta= %f\n", t, idle, ta);
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
				{
					printf("Обработано заявок - %d\n", N);
					printf("Текущая длина очереди - %d\n", q1->last - q1->first);
					printf("Средняя длина очереди - %.2f\n",length/iterations);
				}
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

	printf("\nВремя моделирования - %.2f\n", model);
	printf("Вошедших заявок - %d\n", count_in);
	printf("Вышедших заявок - %d\n", N);
	if (N != 0)
		printf("Среднее время пребывания заявки в очереди - %.2f\n", twait/N);
	printf("ОА работал %d раз\n", Nwork);

	float aver_in = (t1+t2)/2;
	float aver_out = (t3+t4)/2;
	printf("Погрешность по входу - %.2f процентов\n", 100*fabs(count_in - model/aver_in)/(model/aver_in));
	printf("Погрешность по выходу - %.2f процентов\n", 100*fabs(Nwork*aver_out + idle - model)/(Nwork*aver_out + idle));

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

	printf("t=%f idle=%f ta= %f\n", t, idle, ta);

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
				{
					printf("Обработано заявок - %d\n", N);
					printf("Текущая длина очереди - %d\n", q2->length);
					printf("Средняя длина очереди - %.2f\n",length/iterations);
				}
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
}

int main(void)
{
	srand(time(NULL));
	int menu = -1;
	do
	{

		idle = 0;
		model = 0;
		N = 0; 
		count_in = 0; 
		Nwork = 0;  
		twait = 0;

		printf("(1) Очередь в виде массива\n");
		printf("(2) Очередь в виде списка\n");
		printf("(0) Завершение работы\n");
		printf("Выберите пункт меню: ");
		scanf("%d", &menu);
		switch(menu)
		{
			case 1:
				array();
				break;
			case 2:
				list();
				break;
			case 0:
				break;
			default:
				printf("Неверно выбран пункт меню!\n");
				break;
		}
	}
	while (menu != 0);
}

