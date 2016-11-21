Что напечатает программа?

#include <stdio.h>
int main(void)
{
	struct site
	{
		char name[] = "bmstu.ru";
		int no_of_pages = 200;
	};
	struct site *ptr;
	printf("%d ", ptr->no_of_pages);
	printf("%s", ptr->name);
	return 0;
}
//Программа не скомпилируется
//Структура объявлена неверно
struct site
{
	char name[100];
	int no_of_pages;
};
struct site site1 = {"bmstu.ru", 200};
struct site *ptr = &site1;
/*-------------------------------------------*/
Предположим sizeof(int) = 4. Что напечатает программа?

#include <stdio.h>
struct st
{
	int x;
	static int y; 
};

int main(void)
{
	printf("%ld", sizeof(struct st));   
	return 0;
}
// Программа не скомпилируется. использовать static внутри структуры нельзя
// ответ 8
/*---------------------------------------------*/
Задано следующее определение 

struct 
{
	short s[5];
	union 
	{
		double y;
		long z;
	}u;
}t;

short  2
double 8
long   4
// 10 + 8 = 18
// так как объединение, то память выделяется под максимальное поле 
/*---------------------------------------------*/
Что напечатает программа?

#include <stdio.h>
struct st
{
	int x;
	struct st next;                // struct st *next;
};

int main()
{
	struct st temp;                
	temp.x = 10;
	temp.next = temp;              // temp.next = &temp;    
	printf("%d", temp.next.x);     // printf("%d", temp.next->x);
	return 0;
}
/*---------------------------------------------*/
Какая из следующих операций применима к переменным структурного типа?
а. =         // верно
b. ==
с. обе 
d. ни одной 
/*---------------------------------------------*/
Что напечатает программа если sizeof(int) = 4

#include <stdio.h>
union test
{
	int x;
	char arr[8];
	int y;
};

int main(void)
{
	printf("%d", sizeof(union test));     // 8
	return 0;
}

/*---------------------------------------------*/
Что напечатает программа?

#include <stdio.h>
union test
{
	int x;
	char arr[8];
	int y;
};

int main(void)
{
	union test t;
	t.x=0;
	t.arr[1] = 'G';
	printf("%s", t.arr);  // ничего  0 G 0 0   
	return 0;
}
/*---------------------------------------------*/
Что напечатает программа?

#include <string.h>
struct test
{
	char str[20];
};

int main(void)
{
	struct test st1, st2;
	strcpy(st1.str, "moscow");
	st2=st1;
	st1.str[0] = 'M';
	printf("%s", st2.str);  // moscow
	return 0;
}
/*---------------------------------------------*/
Что напечатает программа?

#include <stdio.h>
struct point
{
	int x,y,z;
};
int main(void)
{
	struct point p1 = {.y=0, .z=1, .x=2}; 
	printf("%d %d %d",p1.x, p1.y, p1.z); // 2 0 1
	return 0;
}
