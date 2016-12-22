#include "htable.h"

hmap_cl *new_hmap_cl(size_t size)
{
    hmap_cl *table = malloc(sizeof(hmap_cl));
    table->size = size;
    table->arr_size = 0;
    table->data = new_ht_cl(table->size);
    table->limit = 0;
    return table;
}

ht_cl *new_ht_cl(size_t size)
{
    ht_cl *res = malloc(sizeof(ht_cl)*size);
    if (res != NULL)
    {
        for (int i = 0; i < size; i++)
        {
            res[i].status = 0;
            res[i].info = 0;
        }
    }
    return res;
}

hmap_cl *resize_cl(hmap_cl *table)
{
    if (table == NULL)
        return NULL;
    size_t tmp = table->size;
    table->size *= multiplier;
    ht_cl *new = new_ht_cl(table->size);
    //memory_check(new, NULL, "");
    for (int i = 0; i < tmp; i++)
    {
        new[i].info = table->data[i].info;
        new[i].status = table->data[i].status;
    }
    free(table->data);
    table->data = new;
    return table;
}

hmap_cl *add_cl(hmap_cl *table, int info)
{
    if (table == NULL)
        return NULL;
    if (table->arr_size == table->size)
    {
        table = resize_cl(table);
    }
    while (table->limit >= COL_LIMIT)
        table = restruct_cl(table);
    if (search_cl(table, info))
        return table;
    unsigned int i = hash(info, table->size);
    int cols = 0;
    while (table->data[i%table->size].status == 1)
    {
        //printf("%d %d\n", table->data[i%table->size].info, table->data[i%table->size].status);
        i++;
        cols++;
        if (cols > table->size)
        {
            panic("Таблица переполнена!\n");
            break;
        }
    }
    table->limit += cols == 0 ? 0 : 1;
    table->data[i].info = info;
    table->data[i].status = 1;
    table->arr_size++;
    return table;
}

int search_cl(hmap_cl *table, int info)
{
    if (table == NULL)
        return 0;
    unsigned int tmp = hash(info, table->size);
    unsigned int i = tmp;
    int cols = 0;
    while (cols < table->size)
    {
        cols++;
        if (table->data[i%table->size].info == info && table->data[i%table->size].status == 1)
            return cols;
        i++;
    }
    return 0;
}

hmap_cl *delete_cl(hmap_cl *table, int info)
{
    if (table == NULL)
        return NULL;
    if (search_cl(table, info) == 0)
    {
        printf("%sНе найдено%s\n", PINK, RESET);
        return table;
    }
    unsigned int tmp = hash(info, table->size);
    unsigned int i = tmp;
    int cols = 0;
    while (cols < table->size)
    {
        if (table->data[i%table->size].status == 1 && table->data[i%table->size].info == info)
            table->data[i].status = 2;
        cols++;
        i++;
    }
    return table;
}

void print_table_cl(const hmap_cl *table)
{
    if (table == NULL)
        return;
    printf("  Коллизий - %d\n", (int)table->limit);
    printf("   Хеш  |  Элемент\n");
    for (int i = 0; i < table->size; i++)
    {
        if (table->data[i].status == 1)
        {
            printf("%6d  | %5d\n", i, table->data[i].info);
        }
    }
}

hmap_cl *load_table_from_file_cl(FILE *f)
{
    hmap_cl *table = new_hmap_cl(START_SIZE);
    rewind(f);
    int tmp;
    while (fscanf(f, "%d", &tmp) == 1)
    {
        table = add_cl(table, tmp);
    }
    return table;
}

void free_table_cl(hmap_cl *table)
{
    if (table == NULL)
        return;
    free(table->data);
    free(table);
}

hmap_cl *restruct_cl(hmap_cl *table)
{
    printf("%sРеструктурирование таблицы %d -> %d\n%s", PINK,(int)table->size,(int)table->size+START_SIZE, RESET);
    hmap_cl *new = new_hmap_cl(table->size + START_SIZE);
    for (int i = 0; i < table->size; i++)
    {
        if (table->data[i].status == 1)
            add_cl(new, table->data[i].info);
    }
    free_table_cl(table);
    return new;
}

