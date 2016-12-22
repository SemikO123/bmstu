#include "tree.h"
#include "htable.h"


void print_tree(tree_node *head, int down, int lr, int flag)
{
    if (head)
    {
        print_tree(head->right, down+1, 2, flag);
        for (int i = 0; i < down; i++)
            printf("         ");
        switch(lr)
        {
            case 0:
                printf("➙");
                break;
            case 1:
                printf("➘");
                break;
            case 2:
                printf("➚");
                break;
        }
        if (flag)
            printf(" %d(%d)\n",head->info, head->height-1);
        else
            printf(" %d\n", head->info);
        print_tree(head->left, down+1, 1, flag);
    }
}

#define N 10

int main(void)
{
    FILE *in = fopen("input.txt", "r");
    
    tree_node *tree = NULL;
    tree_node *bst_tree = NULL;
    hmap_cl *table = NULL;
    hmap_op *table_op = NULL;
    unsigned long long t1, t2;
    int count = 0;
    int menu = -1;
    do
    {
        printf("%sМЕНЮ:\n", YELLOW);
        printf("(1) Загрузить информацию из файла\n");
        printf("(2) Вывести на экран деревья и хеш-таблицы\n");
        printf("(3) Добавить элемент \n");
        printf("(4) Удалить элемент \n");
        printf("(5) Найти элемент и провести сравнение в различных структурах\n");
        printf("(6) Подсчитать среднее количество сравнений для поиска\n");
        printf("(0) Завершение работы программы%s\n", RESET);
        printf("Выберите пункт меню: ");
        scanf("%d", &menu);
        fflush(stdin);
        getchar();

        switch(menu)
        {
            case 1:
                free_tree(tree);
                tree = read_tree_from_file(in);
                if (tree)
                    printf("%s     Сбалансированное дерево создано!%s\n", PINK, RESET);
                bst_tree = bst_read_tree_from_file(in, &count);
                if (bst_tree)
                    printf("%s     Бинарное дерево поиска создано!%s\n", PINK, RESET);

                free_table_cl(table);
                table = load_table_from_file_cl(in);
                if (table)
                    printf("%sХеш-таблица с закрытой адресацией создана!%s\n", PINK, RESET);

                free_table_op(table_op);
                table_op = load_table_from_file_op(in);
                if (table_op)
                    printf("%sХеш-таблица с открытой адресацией создана!%s\n", PINK, RESET);
                break;
            case 2:
                if (bst_tree)
                {
                    printf("%sБинарное дерево поиска\n%s", RED, RESET);
                    print_tree(bst_tree, 0, 0, 0);
                }

                if (tree)
                {
                    printf("%sСбалансированное бинарное дерево\n%s", RED, RESET);
                    print_tree(tree, 0, 0, 1);
                }
                
                if (table)
                {
                    printf("%sХеш-таблица с закрытой адресацией%s\n", RED, RESET);
                    print_table_cl(table);

                }
                
                if (table_op)
                {
                    printf("%sХеш-таблица с открытой адресацией%s\n", RED, RESET);
                    print_table_op(table_op);

                }
                break;
            case 3:
                printf("Введите число:");
                int elem = 0;
                scanf("%d", &elem);

                tree_node *tmp = create_node(elem);
                tree = insert(tree, tmp);
                //printf("%sЭлемент добавлен в сбалансированное дерево\n%s", PINK, RESET);

                tmp = create_node(elem);
                bst_tree = bst_insert(bst_tree, tmp, &count);
                //printf("%sЭлемент добавлен в бинарное дерево поиска\n%s", PINK, RESET);

                if (!table)
                    table = new_hmap_cl(START_SIZE);
                table = add_cl(table, elem);
                //printf("%sЭлемент добавлен в хеш-таблицу с закрытой адресацией\n%s", PINK, RESET);

                if (!table_op)
                    table_op = new_hmap_op(START_SIZE_OP);
                table_op = add_op(table_op, elem);
                //printf("%sЭлемент добавлен в хеш-таблицу с открытой адресацией\n%s", PINK, RESET);
                printf("%s Готово %s\n", PINK, RESET);  
                break;
            case 4:
                printf("Введите число:");
                elem = 0;
                scanf("%d", &elem);

                if ( tree )
                    tree = remove_tree(tree, elem);

                if (bst_tree)
                    bst_tree = bst_remove_tree(bst_tree, elem);

                if (table)
                    table = delete_cl(table, elem);
                else
                    puts("ne vishlo!");

                if (table_op)
                    table_op = delete_op(table_op, elem);
                printf("%s Готово %s\n", PINK, RESET); 
                break;
            case 5:
                printf("Введите число:");
                elem = 0;
                scanf("%d", &elem);

                zero_count_made();
                printf("%s       Структура        | Время(тик) | Сравнений %s\n", RED, RESET);
                t1 = tick();
                tree_node *looked_up_1 = lookup(bst_tree, elem); 
                if (looked_up_1 == NULL)
                    printf("%sНе найдено!%s\n",PINK, RESET);
                else
                {
                    printf("      Дерево поиска     | %10lld |    ", tick()-t1);
                    show_count();
                }

                zero_count_made();
                t1 = tick();
                tree_node *looked_up = lookup(tree, elem); 
                if (looked_up == NULL)
                    printf("%sНе найдено!%s\n",PINK, RESET);
                else
                {
                    printf("Cбалансированное дерево | %10lld |    ", tick()-t1);
                    show_count();
                }

                t1 = tick();
                int tmp1 = search_cl(table, elem);
                if (tmp1 == 0)
                    printf("%sНе найдено!%s\n",PINK, RESET);
                else
                    printf(" Хеш-таблица (Закрытая) | %10lld |    %d\n", tick()-t1, tmp1);

                t1 = tick();
                tmp1 = search_op(table_op, elem);
                if (tmp1 == 0)
                    printf("%sНе найдено!%s\n",PINK, RESET);
                else
                    printf(" Хеш-таблица (Открытая) | %10lld |    %d\n", tick()-t1, tmp1);
                break;
            case 6:
                {
                    printf("%s      Структура   | Среднее время поиска | Среднее количество сравнений %s\n",RED, RESET);
                    int array[N];
                    int t = 0;
                    rewind(in);
                    while (fscanf(in, "%d", &array[t]) == 1)
                        t++;
                    rewind(in);
                    for (int i = t; i < N; i++)
                        array[i] = array[i-t];
                    // for (int i = 0; i < N; i++)
                    //     printf("%d ", array[i]);

                    float c = 0;
                    t1 = tick();
                    for (int i = 0; i < N; i++)
                    {
                        zero_count_made();
                        lookup(bst_tree, array[i]);
                        c += get_count_made();
                       //printf("\n%d ",c);
                    }
                    t2 = tick() - t1;
                    printf("  Дерево поиска   |            %lld       |        %.2f\n", 2*t2/N, c/N);
                    //printf("time %lld, count = %f", t2, c);

                    c = 0;
                    t1 = tick();
                    for (int i = 0; i < N; i++)
                    {
                        zero_count_made();
                        lookup(tree, array[i]);
                        c += get_count_made();
                       //printf("\n%d ",c);
                    }
                    t2 = tick() - t1;
                    printf(" Сбалансир.дерево |            %lld       |        %.2f\n", 2*t2/N, c/N);

                    int tmp1;
                    c = 0;
                    t1 = tick();
                    for (int i = 0; i < N; i++)
                    {
                        tmp1 = search_cl(table, array[i]);
                        c += tmp1;
                    }
                    t2 = tick() - t1;
                    printf(" Хеш-таблица(cl)  |            %lld       |        %.2f\n", 2*t2/N, c/N);

                    c = 0;
                    t1 = tick();
                    for (int i = 0; i < N; i++)
                    {
                        tmp1 = search_op(table_op, array[i]);
                        //printf("%d %d\n", i, tmp1);
                        c += tmp1;
                    }
                    t2 = tick() - t1;
                    printf(" Хеш-таблица(op)  |            %lld       |        %.2f\n", 2*t2/N, c/N);

                    
                }
            case 0:
                break;
        }
    }
    while (menu != 0);
                
}


