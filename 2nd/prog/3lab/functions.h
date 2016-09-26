#ifndef _FUNCTIONS_H_

#define _FUNCTIONS_H_

#define OK 0
#define BADPARAMETERS -1
#define NOFILE -2
#define EMPTYFILE -3
#define BADINPUT -4

struct list
{
	int number;
	struct list *next;
};

#endif // #ifndef _FUNCTIONS_H_