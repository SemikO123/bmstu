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


// zero_count_made();
/*t1 = tick();
for (int i = 0; i < N; i++)
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
    printf(" Хеш-таблица (Открытая) | %10lld |    %d\n", tick()-t1, tmp1);*/


// int main(void)
// {
//     FILE *fin = fopen("input.txt", "r");
//     FILE *ftmp = fopen("tmp.txt", "w");
//     unsigned long long t1;
//     memory_check(fin, EXIT_FAILURE, "File opening failure!");
//     tree_node *tree = NULL;
//     tree_node *bst_tree = NULL;
//     hmap_cl *table = NULL;
//     hmap_op *table_op = NULL;
//     int n = 0;
//     int elem = 0;
//     int *lvl_counts = NULL;
//     FILE *fout;

//     int menu = 0;
//     int tmp1 = 0;
// 	int flag = 1;
// 	do
// 	{
// 		puts("\nMENU:");
// 		puts(" [1] Load tree from file"); //done
// 		puts(" [2] Show tree");
// 		puts(" [3] Add element in tree");
// 		puts(" [4] Remove element from tree");
// 		puts(" [5] Find element in tree"); 
// 		puts(" [6] Count nodes on each tree level"); 
// 		puts(" [7] Compare adding in file and in tree"); 
// 		puts(" [8] Free tree"); 
// 		puts(" [9] Walk through all tree"); 
// 		puts("[10] Add element in hash table"); 
// 		puts("[11] Remove element from hash table"); 
// 		puts("[12] Load hash table"); 
// 		puts("[13] Get element from hash table"); 
// 		puts("[14] Print table"); 
// 		puts("[15] Free table"); 
// 		puts("[16] Exit"); 
// 		do
// 		{
// 			menu = menu_infoue();
// 		} while (menu < 1 || menu > 16);
// 		switch(menu)
// 		{
// 			case 1:
// 			    free_tree(tree);
// 			    tree = read_tree_from_file(fin);
// 			    puts("[AVL]Tree has been loaded.");
// 			    bst_tree = bst_read_tree_from_file(fin);
// 			    puts("[BST]Tree has been loaded.");
// 			    break;
//             case 2:
//                 fout = fopen("output.gv", "w");
//                 memory_check(fout, EXIT_FAILURE, "File opening failure!");
//                 export_to_dot(fout, "My_tree", tree);
//                 fclose(fout);
//                 system("output.gv");
//                 fout = fopen("output1.gv", "w");
//                 memory_check(fout, EXIT_FAILURE, "File opening failure!");
//                 export_to_dot(fout, "Bst_tree", bst_tree);
//                 fclose(fout);
//                 system("output1.gv");
//                 break;
//             case 3:
//                 puts("Input element:");
//                 elem = menu_infoue();
//                 tree_node *tmp = create_node(elem);
//                 tree = insert(tree, tmp);
//                 puts("[AVL]Element added.");
//                 tmp = create_node(elem);
//                 bst_tree = bst_insert(bst_tree, tmp);
//                 puts("[BST]Element added.");
//                 break;
//             case 4:
//                 puts("Input element:");
//                 elem = menu_infoue();
//                 tree = remove_tree(tree, elem);
//                 puts("[AVL]Element deleted!");
//                 bst_tree = bst_remove_tree(bst_tree, elem);
//                 puts("[BST]Element deleted!");
//                 break;
//             case 5:
//                 puts("Input element:");
//                 elem = menu_infoue();
//                 zero_count_made();
//                 t1 = tick();
//                 tree_node *looked_up_1 = lookup(bst_tree, elem); 
//                 printf("[BST]Tree: %lld ticks\n", tick()-t1);
//                 if (looked_up_1 != NULL)
//                     {
//                         //printf("[BST]Found element: %d with address: %d and count:%d\n", looked_up_1->info, looked_up_1, looked_up_1->count);
//                         show_count();
//                     }
//                 else
//                     puts("[BST]Nothing was found!");
//                 zero_count_made();
//                 t1 = tick();
//                 tree_node *looked_up = lookup(tree, elem); 
//                 printf("[AVL]Tree: %lld ticks\n", tick()-t1);
//                 if (looked_up != NULL)
//                     {
//                         //printf("[AVL]Found element: %d with address: %d and count:%d\n", looked_up->info, looked_up, looked_up->count);
//                     }
//                 else
//                     puts("[AVL]Nothing was found!");
//                 break;
//             case 6:
//                 lvl_counts = count_levels(tree, &n);
//                 puts("[AVL]");
//                 print_array(lvl_counts, n);
//                 lvl_counts = count_levels(bst_tree, &n);
//                 puts("[BST]");
//                 print_array(lvl_counts, n);
//                 break;
//             case 7:
//                 puts("Input element:");
//                 elem = menu_infoue();
//                 rewind(ftmp);
//                 t1 = tick();
//                 fprintf(ftmp, "%d ", elem);
//                 printf("File: %lld ticks\n", tick()-t1);
//                 t1 = tick();
//                 tree = insert(tree, create_node(elem));
//                 printf("[AVL]Tree: %lld ticks\n", tick()-t1);
//                 tree = remove_tree(tree, elem);
//                 t1 = tick();
//                 bst_tree = bst_insert(bst_tree, create_node(elem));
//                 printf("[BST]Tree: %lld ticks\n", tick()-t1);
//                 bst_tree = bst_remove_tree(bst_tree, elem);
//             case 8:
//                 free_tree(tree);
//                 free_tree(bst_tree);
//                 tree = NULL;
//                 bst_tree = NULL;
//                 break;
//             case 9:
//                 puts("Choose type of walk:");
//                 puts("1)In\n2)Pre\n3)Post");
//                 do
//                     elem = menu_infoue();
//                 while (elem < 1 && elem > 3);
//                 t1 = tick();
//                 print_tree(tree, elem);
//                 printf("[AVL]Wasted time: %lld ticks\n", tick()-t1);
//                 t1 = tick();
//                 print_tree(bst_tree, elem);
//                 printf("[BST]Wasted time: %lld ticks\n", tick()-t1);
//                 break;
//             case 10:
//                 puts("Input element:");
//                 elem = menu_infoue();
//                 table = add_cl(table, elem);
//                 memory_check(table, EXIT_FAILURE, "Memory allocation failure!");
//                 puts("[Closed] Element added");
//                 table_op = add_op(table_op, elem);
//                 memory_check(table_op, EXIT_FAILURE, "Memory allocation failure!");
//                 puts("[Open] Element added");
//                 break;
//             case 11:
//                 puts("Input element:");
//                 elem = menu_infoue();
//                 table = delete_cl(table, elem);
//                 memory_check(table, EXIT_FAILURE, "Deleting failure!");
//                 puts("[Closed] Element deleted");
//                 table_op = delete_op(table_op, elem);
//                 memory_check(table_op, EXIT_FAILURE, "Deleting failure!");
//                 puts("[Open] Element deleted");
//                 break;
//             case 12:
//                 free_table_cl(table);
//                 table = load_table_from_file_cl(fin);
//                 puts("[Closed] Table was loaded.");
//                 memory_check(table, EXIT_FAILURE, "Memory allocation failure!");
//                 free_table_op(table_op);
//                 table_op = load_table_from_file_op(fin);
//                 memory_check(table_op, EXIT_FAILURE, "Memory allocation failure!");
//                 puts("[Open] Table was loaded.");
//                 break;
//             case 13:
//                 puts("Input element:");
//                 elem = menu_infoue();
//                 t1 = tick();
//                 tmp1 = search_cl(table, elem);
//                 printf("Closed: %lld ticks\n", tick()-t1);
//                 if (tmp1 != 0)
//                     printf("[Closed] Element was found with %d comparisons\n", tmp1);
//                 else
//                     puts("[Closed] Nothing was found!");
//                 t1 = tick();
//                 tmp1 = search_op(table_op, elem);
//                 printf("Open: %lld ticks\n", tick()-t1);
//                 if (tmp1 != 0)
//                     printf("[Open] Element was found with %d comparisons\n", tmp1);
//                 else
//                     puts("[Open] Nothing was found!");
//                 break;
//             case 14:
//                 puts("Closed:");
//                 print_table_cl(table);
//                 puts("Open:");
//                 print_table_op(table_op);
//                 break;
//             case 15:
//                 free_table_cl(table);
//                 table = NULL;
//                 puts("[Closed] Freed successfully");
//                 free_table_op(table_op);
//                 table_op = NULL;
//                 puts("[Open] Freed successfully");
//                 break;
//             case 16:
//                 flag = 0;
//                 break;
//             default:
//                 puts("Unknown operation.");
// 		}
// 	} while (flag);
//     free_tree(tree);
//     free_tree(bst_tree);
//     tree = NULL;
//     bst_tree = NULL;
//     fclose(fin);
//     fclose(ftmp);
//     free_table_cl(table);
//     free_table_op(table_op);
// 	return EXIT_SUCCESS;
// }
