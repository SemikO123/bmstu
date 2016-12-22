#include "htable.h"

hmap_op *new_hmap_op(size_t size)
{
    hmap_op *table = malloc(sizeof(hmap_op));
    table->size = size;
    table->data = new_ht_op(table->size);
    table->limit = 0;
    return table;
}

ht_op *new_ht_op(size_t size)
{
    ht_op *res = malloc(sizeof(ht_op)*size);
    if (res != NULL)
    {
        for (int i = 0; i < size; i++)
        {
            res[i].next = NULL;
            res[i].info = 0;
        }
    }
    return res;
}

hmap_op *add_op(hmap_op *table, int info)
{
    if (table == NULL)
        return NULL;
    while (table->limit >= COL_LIMIT)
        table = restruct_op(table);
    if (search_op(table, info))
        return table;
    unsigned int tmp = hash(info, table->size);
    int cols = 0;
    ht_op *res = malloc(sizeof(ht_op));
    if (res != NULL)
    {
        res->next = NULL;
        res->info = info;
    }
    else
        return NULL;
    table->data[tmp].next = add_end(table->data[tmp].next, res, &cols);

    table->limit += cols;
    return table;
}

ht_op *add_end(ht_op *head, ht_op *node, int *cols)
{
    if (head == NULL)
        return node;
    ht_op *cur = head;
    for ( ; cur->next; cur = cur->next)
        ;
    cur->next = node;
    (*cols) = 1;
    return head;
}

int search_op(hmap_op *table, int info)
{
    if (table == NULL)
        return 0;
    unsigned int tmp = hash(info, table->size);
    int num = 0;
    ht_op *cur = table->data[tmp].next;
    for ( ; cur; cur = cur->next)
    {
        num++;
        if (cur->info == info)
            return num;
    }
    return 0;
}

hmap_op *delete_op(hmap_op *table, int info)
{
    if (table == NULL)
        return NULL;
    if (search_op(table, info) == 0)
    {
        printf("%sНе найдено%s\n", PINK, RESET);
        return table;
    }
    unsigned int tmp = hash(info, table->size);
    ht_op *cur = table->data[tmp].next->next;
    ht_op *prev = table->data[tmp].next;
    if (prev->info == info)
    {
        table->data[tmp].next = cur;
        free(prev);
        return table;
    }
    else
    {
        for (; cur; cur = cur->next, prev = prev->next)
        {
            if (cur->info == info)
            {
                prev->next = cur->next;
                free(cur);
                return table;
            }
        }
    }
    return table;
}

void print_table_op(const hmap_op *table)
{
    if (table == NULL)
        return;
    printf("  Коллизий - %d\n", (int)table->limit);
    printf("   Хеш  |  Элементы\n");
    for (int i = 0; i < table->size; i++)
    {
        if (table->data[i].next != NULL)
        {
            printf("%6d  |", i);
            for (ht_op *cur = table->data[i].next; cur; cur = cur->next)
                printf("%5d ", cur->info);
            puts("");
        }
    }
}

hmap_op *load_table_from_file_op(FILE *f)
{
    hmap_op *table = new_hmap_op(START_SIZE_OP);
    rewind(f);
    int tmp;
    while (fscanf(f, "%d", &tmp) == 1)
    {
        table = add_op(table, tmp);
    }
    return table;
}

void free_table_op(hmap_op *table)
{
    if (table == NULL)
        return;
    for (int i = 0; i < table->size; i++)
        free_all(&table->data[i]);
    free(table);
}

void free_all(ht_op *head)
{
    if (head == NULL)
        return;
    ht_op *next;

    for (; head; head = next)
    {
        next = head->next;
        free(head);
    }
    head = NULL;
}


hmap_op *restruct_op(hmap_op *table)
{
    if (table == NULL)
        return NULL;
    printf("Реструктуризация таблицы!\n");
    printf("%d -> %d \n", (int)table->size, (int)table->size+3);
    hmap_op *new = new_hmap_op(table->size + 3);
    for (int i = 0; i < table->size; i++)
    {
        if (table->data[i].next != NULL)
            for (ht_op *cur = table->data[i].next; cur; cur = cur->next)
                new = add_op(new, cur->info);
    }
    return new;
}

