#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

// пт 17-25 327
// чт 13-50 327

/*
Обход дерева, включение,  исключение и поиск узлов.
2. Построить двоичное дерево поиска, в вершинах которого находятся слова из 
текстового файла. Вывести его на экран в виде дерева. Определить количество 
вершин дерева, содержащих слова, начинающиеся на указанную букву. Выделить 
эти вершины цветом. Сравнить время поиска начинающихся на указанную букву слов 
в дереве и в файле. \
*/


int main(void)
{	
	int menu = -1;
	struct BinaryTree *def_head = NULL;
	do
	{
		printf("\n%s+++++++++++++++++++++++++++++++++++++++++++\n", YELLOW);
		printf("Меню работы с бинарным деревом:\n");
		printf("(1) Добавить элемент (слово) в дерево\n");
		printf("(2) Удалить элемент (слово) из дерева\n");
		printf("(3) Поиск узла\n");
		printf("(4) Печать текущего дерева\n");
		printf("(5) Обход текущего дерева\n");
		printf("(6) Выполнение задания лабораторной работы\n");
		printf("(7) Печать текущего дерева в формате .png\n");
		printf("(0) Завершение работы программы%s\n",RESET);
		printf("Выберите пункт меню: ");
		scanf("%d", &menu);
		switch(menu)
		{
			case 1:
				printf("Введите информацию для узла (не более 15 символов): ");
				char data[20];
				scanf("%s", data);
				def_head = insert_element(def_head, add_new(data));
				printf("%sЭлемент %s добавлен%s\n", RED, data, RESET);
				break;	
			case 2:
				{
					printf("Введите информацию для узла: ");
					char data2[20];
					scanf("%s", data2);
					if (def_head == NULL)
						printf("Дерево пусто!\n");
					def_head = delete_element(def_head, data2);
					//printf("%sЭлемент %s удален%s\n", RED, data2, RESET);
				}

				break;
			case 3:
					printf("Введите информацию, которую нужно найти: ");
					char data1[20];
					scanf("%s", data1);
					struct BinaryTree *element = search_element(def_head, data1);
					if (element == NULL)
						printf("%s Не найдено%s\n", RED, RESET);
					else
					{	
						element->color = 1;
						print_tree(def_head, 0, 0);
						element->color = 0;
					}
				break;
			case 4:
				if (def_head == NULL)
					printf("%s Дерево пусто\n %s", RED, RESET);
				else
					print_tree(def_head, 0, 0);
				break;
			case 5:
				if (def_head == NULL)
					printf("%s Дерево пусто\n %s", RED, RESET);
				else
					tree_traversal(def_head);
				break;
			case 6:
				task();
				break;
			case 0:
			{
				if (def_head)
				{
				FILE *graph = fopen("graph.gv", "w");		
				fprintf(graph, "digraph G{\n");
				make_graph(def_head, NULL, graph);
				fprintf(graph, "}");
				fclose(graph);
				}
				//free_tree(def_head);
				break;
			}
			case 7:
			{
				FILE *graph = fopen("graph.gv", "w");		
				fprintf(graph, "digraph G{\n");
				fprintf(graph, "%s\n", def_head->data);
				make_graph(def_head, NULL, graph);
				fprintf(graph, "}");
				fclose(graph);
				system("/bin/bash /home/irina/Документы/bmstu/2ndCourse/tsd/6lab/file.sh");
				break;
			}
			default:
				printf("Пункт меню выбран неверно\n");
				break;
		}
	}
	while (menu != 0 && menu != 6); 



}