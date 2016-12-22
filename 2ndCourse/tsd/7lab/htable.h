#ifndef HTABLE_H_INCLUDED
#define HTABLE_H_INCLUDED

#include "tree.h"
#define START_SIZE 5 // 10
#define START_SIZE_OP 5 // 15
#define multiplier 2.0
#define COL_LIMIT 5 // 10

typedef struct htable_closed 
{
    int info;
    int status; 
} ht_cl;

typedef struct Hashmap {
    ht_cl *data;       
    size_t arr_size;    
    size_t size;        
    size_t limit;       
                        
} hmap_cl;

typedef struct htable_opened {
    struct htable_opened *next;
    int info;
} ht_op;

typedef struct Hashopen {
    ht_op *data;
    size_t size; 
    size_t limit;
} hmap_op;

hmap_cl *new_hmap_cl(size_t size);
ht_cl *new_ht_cl(size_t size);
hmap_cl *resize_cl(hmap_cl *table);
hmap_cl *add_cl(hmap_cl *table, int info);
int search_cl(hmap_cl *table, int info);
hmap_cl *delete_cl(hmap_cl *table, int info);
void print_table_cl(const hmap_cl *table);
hmap_cl *load_table_from_file_cl(FILE *f);
hmap_cl *restruct_cl(hmap_cl *table);
void free_table_cl(hmap_cl *table);

hmap_op *new_hmap_op(size_t size);
ht_op *new_ht_op(size_t size);
hmap_op *resize_op(hmap_op *table);
hmap_op *add_op(hmap_op *table, int info);
int search_op(hmap_op *table, int info);
hmap_op *delete_op(hmap_op *table, int info);
void print_table_op(const hmap_op *table);
hmap_op *load_table_from_file_op(FILE *f);
hmap_op *restruct_op(hmap_op *table);
void free_table_op(hmap_op *table);
void free_all(ht_op *head);
ht_op *add_end(ht_op *head, ht_op *node, int *cols);

#endif // HTABLE_H_INCLUDED
