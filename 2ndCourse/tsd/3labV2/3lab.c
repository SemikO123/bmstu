#include <stdio.h>
#include <string.h>
#define N 50
#define MAXCOUNT 45
/*
Создать таблицу, содержащую не менее 40-ка записей (тип – запись 
с вариантами). Упорядочить данные в ней по возрастанию ключей, 
где ключ – любое невариантное поле (по выбору программиста), используя:  
а) саму таблицу, 
б) массив ключей (возможность добавления и удаления записей в ручном 
режиме обязательна)

Ввести список квартир, содержащий адрес, общую площадь, количество комнат, 
этаж, стоимость квадратного метра (первый – есть ли подвал; последний – 
наличие чердака, его площадь и возможность приватизации; другой – наличие 
балкона и его площадь). Найти все квартиры, с возможностью приватизации 
чердака.
*/

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

int load_table(FILE *in, apartment_t *apartments, int *count)
{
	while (fscanf(in, "%s", apartments[*count].adress) != EOF && *count < MAXCOUNT)
	{
		apartments[*count].number = *count;
		fscanf(in, "%d", &apartments[*count].area);
		fscanf(in, "%d", &apartments[*count].rooms);
		fscanf(in, "%d", &apartments[*count].floor);
		fscanf(in, "%d", &apartments[*count].floors);
		fscanf(in, "%d", &apartments[*count].permeter);
		if (apartments[*count].floor == 1)
			fscanf(in, "%d", &apartments[*count].annex.first.isbasement);
		else if (apartments[*count].floor == apartments[*count].floors)
		{
			fscanf(in, "%d", &apartments[*count].annex.last.isattic);
			if (apartments[*count].annex.last.isattic)
			{
				fscanf(in, "%d", &apartments[*count].annex.last.attarea);
				fscanf(in, "%d", &apartments[*count].annex.last.isprivate);
			}
			else
			{
				apartments[*count].annex.last.attarea = -1;
				apartments[*count].annex.last.isprivate = -1;
			}
		}
		else if (apartments[*count].floor > 1 && apartments[*count].floor < apartments[*count].floors)
		{
			fscanf(in, "%d", &apartments[*count].annex.notfirstorlast.isbalcony);
			if (apartments[*count].annex.notfirstorlast.isbalcony)
				fscanf(in, "%d", &apartments[*count].annex.notfirstorlast.balarea);
			else
				apartments[*count].annex.notfirstorlast.balarea = -1;
		}
		else
		{
			return -1;
		}
		(*count)++;
	}
	return 0;
}

void print_table(apartment_t *ap, int count)
{
	if (ap[count].area)
	{
		printf("   Apartment №%d.\n", ap[count].number+1);
		printf("Adress:          %s\n", ap[count].adress);
		printf("Area (meters):   %d\n", ap[count].area);
		printf("Rooms:           %d\n", ap[count].rooms);
		printf("Floor:           %d/%d\n", ap[count].floor, ap[count].floors);
		printf("Price per meter: %d\n", ap[count].permeter);
		if (ap[count].floor == 1)
			(ap[count].annex.first.isbasement) ? printf("\nBasement: yes\n") : printf("\nBasement: no\n");
		else if (ap[count].floor == ap[count].floors)
		{
			(ap[count].annex.last.isattic) ? printf("\nAttic: yes\n") : printf("\nAttic: no\n");
			if  (ap[count].annex.last.isprivate != -1)
			{
				printf("Attic area (meters): %d\n", ap[count].annex.last.attarea);
				(ap[count].annex.last.isprivate) ? printf("Can be privatized: yes\n") : printf("Can be privatized: no\n");
			}
		}
		else if (ap[count].floor > 1 && ap[count].floor < ap[count].floors)
		{
			(ap[count].annex.notfirstorlast.isbalcony) ? printf("\nBalcony: yes\n") : printf("\nBalcony: no\n");
			if (ap[count].annex.notfirstorlast.balarea != -1)
				printf("Balcony area (meters): %d\n", ap[count].annex.notfirstorlast.balarea);
		}
	}
}

void task(apartment_t *ap, int count)
{
	puts("\n#### APARTMENTS WITH PRIVATIZED ATTIC ####\n");
	for (int i = 0; i < count; i++)
		if (ap[i].floor == ap[i].floors)
			if (ap[i].annex.last.isprivate == 1)
			{
				print_table(ap, i);
				puts("###################################\n");
			}
}

int main(void)
{
	char filename[] = "table.txt";
	FILE *table = fopen(filename, "r");
	if (table)
	{
		apartment_t apartments[MAXCOUNT];
		int count_of_records = 0;
		if (load_table(table, apartments, &count_of_records) == -1)
		{
			printf("Incorrect load of table!\n");
			return -1;
		}
		int menu;
		// -------- MENU ----------- // 
		do
		{
			printf("(1) Print table\n");
			printf("(2) Sort table\n");
			printf("(3) Sort table with the key\n");
			printf("(4) Add record\n");
			printf("(5) Delete record\n");
			printf("(6) Task\n");
			printf("(0) EXIT\n");
			printf("\nChoose number: ");
			scanf("%d", &menu);
			switch(menu)
			{
				case 1:
				{
					printf("############ APARTMENTS ############\n");
					for (int i = 0; i < count_of_records; i++)
					{
						print_table(apartments, i);
						puts("####################################\n");
					}
					break;
				}
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					task(apartments, count_of_records);
					break;
				case 0:
					fclose(table);
					break;
			}
		}
		while (menu != 0);
	}
	else
		puts("File doesn'f found!\n");
}