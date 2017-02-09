#include "structurs.h"
#include "functions.h"

int load_table(apartment_t *apartments, key_t *keys, int *count, char *filename)
{
	FILE *in = fopen(filename, "r");
	while (fscanf(in, "%s", apartments[*count].adress) != EOF && *count < MAXCOUNT)
	{
		apartments[*count].number = *count;
		keys[*count].number = *count;
		int area;
		fscanf(in, "%d", &area);
		apartments[*count].area = area;
		keys[*count].area = area;
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
	fclose(in);
	return 0;
}

void print_table(apartment_t *ap, int count)
{
	if (ap[count].area)
	{
		printf("   Apartment №%d.\n", ap[count].number+1);
		printf("Address:          %s\n", ap[count].adress);
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

int thatfloor(int floor, int floors)
{
	if (floor == 1)
		return 1;
	else if (floor == floors)
		return 3;
	else if (floor > 1 && floor < floors)
		return 2;
	else
		return -1;
}

int reload(apartment_t *ap, int count, char *filename)
{
	FILE *table = fopen(filename, "w");

	for (int i = 0; i < count; i++)
	{
		switch(thatfloor(ap[i].floor, ap[i].floors))
		{
			case 1:
				fprintf(table,"%s %d %d %d %d %d %d\n", ap[i].adress, ap[i].area, ap[i].rooms, ap[i].floor, ap[i].floors, ap[i].permeter, ap[i].annex.first.isbasement);
				break;
			case 2:
				fprintf(table, "%s %d %d %d %d %d %d ", ap[i].adress, ap[i].area, ap[i].rooms, ap[i].floor, ap[i].floors, ap[i].permeter, ap[i].annex.notfirstorlast.isbalcony);
				if (ap[i].annex.notfirstorlast.isbalcony == 1)
					fprintf(table, "%d",ap[i].annex.notfirstorlast.balarea);
				fprintf(table, "\n");
				break;
			case 3:
				fprintf(table, "%s %d %d %d %d %d %d ", ap[i].adress, ap[i].area, ap[i].rooms, ap[i].floor, ap[i].floors, ap[i].permeter, ap[i].annex.last.isattic);
				if (ap[i].annex.last.isattic == 1)
					fprintf(table, "%d %d", ap[i].annex.last.attarea, ap[i].annex.last.isprivate);
				fprintf(table, "\n");
				break;
			default:
				break;
		}
	}
	fclose(table);
	return 0;
}

int add_record(apartment_t *ap, key_t *keys, int *count, char *filename)
{
	printf("#### ADD NEW RECORD ####\n");
	ap[*count].number = *count;
	keys[*count].number = *count;
	char string[N];
	printf("Input adress: ");
	scanf("%s", string);
	if (strlen(string) < N && strlen(string) > 1)
		strcpy(ap[*count].adress, string);
	else
		return -1; // incorrect input

	printf("Input area of apartment:  ");
	int num;
	scanf("%d", &num);
	if (num > 0)
	{
		ap[*count].area = num;
		keys[*count].area = num;
	}
	else
		return -1;

	printf("Input number of rooms:    ");
	scanf("%d", &num);
	if (num > 0)
		ap[*count].rooms = num;
	else
		return -1;

	printf("Input floor of apartment: ");
	scanf("%d", &num);
	if (num > 0)
		ap[*count].floor = num;
	else
		return -1;

	printf("How many floors in house: ");
	scanf("%d", &num);
	if (num > 0)
		ap[*count].floors = num;
	else
		return -1;	

	printf("Price per meter (rub):    ");
	scanf("%d", &num);
	if (num > 0)
		ap[*count].permeter = num;
	else
		return -1;

	int fl = thatfloor(ap[*count].floor, ap[*count].floors);
	switch(fl)
	{
		case 1:
			printf("Basement there? yes(1) or no(0): ");
			scanf("%d", &num);
			if (num == 1 || num == 0)
				ap[*count].annex.first.isbasement = num;
			else
				return -1;
			break;
		case 2:
			printf("Balcony there? yes(1) or no(0): ");
			scanf("%d", &num);
			if (num == 1 || num == 0)
			{
				ap[*count].annex.notfirstorlast.isbalcony = num;
				if (num == 1)
				{
					printf("Balcony area: ");
					scanf("%d", &num);
					if (num > 0)
						ap[*count].annex.notfirstorlast.balarea = num;
					else
						return -1;
				}
				else
					ap[*count].annex.notfirstorlast.balarea = -1;
			}
			else
				return -1;
			break;
		case 3:
			printf("Attic there? yes(1) or no(0): ");
			scanf("%d", &num);
			if (num == 1 || num == 0)
			{
				ap[*count].annex.last.isattic = num;
				if (num == 1)
				{
					printf("Attic area: ");
					scanf("%d", &num);
					if (num > 0)
						ap[*count].annex.last.attarea = num;
					else
						return -1;
					printf("Can it be privatized? yes(1) or no(0): ");
					scanf("%d", &num);
					if (num == 0 || num == 1)
						ap[*count].annex.last.isprivate = num;
					else
						return -1;
				}
				else
				{
					ap[*count].annex.last.attarea = -1;
					ap[*count].annex.last.isprivate = -1;
				}
			}
			else
				return -1;

			break;
	}

	(*count)++;
	printf("RECORD ADDED!\n\n");
	reload(ap, *count, filename);
	return 0;
}

void del_record(apartment_t *ap, key_t *keys, int num, int *count, char *filename)
{
	for (int i = num-1; i < *count; i++)
	{
		ap[i] = ap[i+1];
		ap[i].number = i;
		keys[i] = keys[i+1];
		keys[i].number = i;
	}
	(*count)--;
	printf("RECORD DELETED!\n\n");
	reload(ap, *count, filename);
}

unsigned long long int tick(void)
{
	unsigned long long int time = 0;
	__asm__ __volatile__ ("rdtsc" : "=A" (time));
	return time;
}

void bubblesort_a(apartment_t *ap, int *count)
{
	for (int i = 0; i < *count; i++)
		for (int j = *count - 1; j > i; j--)
			if (ap[j].area < ap[j-1].area)
			{
				apartment_t tmp = ap[j];
				ap[j] = ap[j-1];
				ap[j-1] = tmp;
			}
}

void bubblesort_k(key_t *keys, int *count)
{
	for (int i = 0; i < *count; i++)
		for (int j = *count - 1; j > i; j--)
			if (keys[j].area < keys[j-1].area)
			{
				key_t tmp = keys[j];
				keys[j] = keys[j-1];
				keys[j-1] = tmp;
			}
}

int comp(const apartment_t *i, const apartment_t *j)
{
	return i->area-j->area;
}

int comp_k(const key_t *i, const key_t *j)
{
	return i->area-j->area;
}
