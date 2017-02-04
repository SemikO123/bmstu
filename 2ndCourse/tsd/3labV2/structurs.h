#ifndef _STRUCTURS_H_
#define _STRUCTURS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 50
#define MAXCOUNT 45

typedef struct 
{
	int number;
	char adress[N];
	int area;
	int rooms;
	int floor;
	int floors;
	int permeter;
	union
	{
		struct
		{
			int isbasement;	
		} first;
		struct
		{
			int isbalcony;
			int balarea;
		} notfirstorlast;
		struct
		{
			int isattic;
			int attarea;
			int isprivate;
		} last;
	} annex;
} apartment_t;

typedef struct 
{
	int number;
	int area;
}key_t;

#endif