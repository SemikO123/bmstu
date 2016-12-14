#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_SIZE 100

#define RESET   "\033[0m"
#define YELLOW     "\033[1;33m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m" 

	float idle;
	float model;
	int N; 
	int count_in; 
	int Nwork;  
	float twait; 
	float t1, t2, t3, t4;

unsigned long long int tick(void);
float randomfloat(float minimum, float maximum);
void compare(int n);
void fragmentation(void);


struct queue_list
{
	int length;
	struct request *in, *out;
};

void init_queue_list(struct queue_list *que);
void qin_list(struct queue_list *que, struct request *new);
int empty_queue_list(struct queue_list *que);
void create_new_request_list(struct  request *new, float t1, float t2, float t3, float t4);
void waiting_in_queue1(struct queue_list *que, float t);
void print_table(struct queue_list *que);
struct request qout_list(struct queue_list *que);


void list(void);



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


void init_queue_arr(struct queue_arr *que);
int qin_arr(struct queue_arr *que, struct request new);
int empty_queue_arr(struct  queue_arr *que);
struct request qout_arr(struct queue_arr *que);
struct request create_new_request_arr(float t1, float t2, float t3, float t4);
void waiting_in_queue(struct queue_arr *que, float t);

void array(void);

#endif