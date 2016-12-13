#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define PINK    "\033[1;35m"
#define WHITE   "\033[1;37m"

#define INF 10000

int **allocate_memory(int n, int m);
int **filling_matrix(FILE *file, int **matrix, int count);
void print_matrix(int **matrix, int count, int flag);
void get_graph(int **matrix, int count);
void get_graph_prim(int count, int **matrix, int *vector);
int *dijkstra(int count, int **matrix, int v0, int *min_rasst);
int minimum(int a, int b);
int **floyd_warshall(int n, int **matrix, int **matr);
int connected_graph(int **matr, int **matrix, int count);
int firstzero(int *mass, int n);
int *prim(int **matrix, int *result, int count, int v0);


#endif