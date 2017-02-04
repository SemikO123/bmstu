#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

int load_table(apartment_t *apartments, key_t *keys, int *count, char *filename);
void print_table(apartment_t *ap, int count);
int reload(apartment_t *ap, int count, char *filename);
int add_record(apartment_t *ap, key_t *keys, int *count, char *filename);
void del_record(apartment_t *ap, key_t *keys, int num, int *count, char *filename);
void task(apartment_t *ap, int count);

int thatfloor(int floor, int floors);

unsigned long long int tick(void);

void bubblesort_a(apartment_t *ap, int *count);
void bubblesort_k(key_t *keys, int *count);
int comp(const apartment_t *i, const apartment_t *j);
int comp_k(const key_t *i, const key_t *j);

#endif