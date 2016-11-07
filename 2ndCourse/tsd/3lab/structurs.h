#ifndef _STRUCTURS_H_
#define _STRUCTURS_H_

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define WHITE   "\033[1;37m"
#define N 50
#define MAXCOUNT 45

typedef struct
{
	int number;
	char author[N];
	char title[N];
	char publisher[N];
	int pages;
	int type;
	union 
	{
		struct
		{
			char sector[N];
			int place;
			int year;
		} technical;
		struct 
		{
			int kind;
		} art;
	} book_type;
} book_t;

typedef struct 
{
	int number;
	int pages;
} key;

static char *tech[] = 
{
	"Отечественная", 
	"Переведенная"
};

static char *art[] = 
{
	"Роман",
	"Пьеса",
	"Стихи"
};


#endif // _STRUCTURS_H_
