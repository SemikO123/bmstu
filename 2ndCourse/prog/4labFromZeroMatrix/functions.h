#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#define OK 0 
#define BADPARAMETERS -1
#define NOFILE -2
#define BADOPERATION -3
#define MEMORYPROBLEM -4


// запись матрицы в файл
void print_to_file(int n, int m, double **matrix, FILE *file);
// печать матрицы на экран
void print_matrix(int n, int m, double **matrix);

// выделение памяти под матрицу
double **allocate_memory(int n, int m);
// заполнение матрицы из файла
double **filling_matrix(int n, int m, double **matrix, FILE *file);

// поиск обратной матрицы
double **inverse(int n, double **matrix, double **result);
// сумма двух матриц
double **addition(int n, int m, double **matrix1, double **matrix2, double **result);
// произведение двух матриц
double **multiplication(int n, int t, int m, double **matrix1, double **matrix2, double **result);

// добавление единичной матрицы справа
double **add_identity_matrix(int n, double **matrix);
// копирование квадратной матрицы в прямоугольную
double **copy(int n, int m, double **matrix, double **new_matrix);
// выполнение преобразований до единичной матрицы
double **transformation(int n, int m, double **matrix);
// копирование в квадратную матрицу из прямоугольной
double **get_result(int n, double **matrix, double **result);

#endif