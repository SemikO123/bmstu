#include "structurs.h"
#include "functions.h"

/*
КОСТЫЛИ,БАГИ,НЕДОФИКСЫ:
0. Это говнокод, я не отрицаю, но это лучше чем ничего, так что критику 
	воспринимаю негативно, за исключением ну оооочень конструктивной.
1. Адреса вводятся без пробелов
2. Сортировка пузырьком не войдовая - их две идентичных под разные типы(sorry)
3. На утечки не чекала
4. На превышение количества записей не чекала, но должно работать
5. В структурах все поля - инты, так считать удобнее. Но Силантьева может
	прикопаться к площади и стоит исправить на float/double
6. 7 строка кода - два сайзофа, под убунтой там 88 и 8, если под вин это не
	так, то в отчете в конце надо чутка подфиксить.
7. Время для отчета измерено тиками это 6-ти значные числа. (функция ломы).
	В отчете тоже 6-ти значные числа - на скрине и в таблице. В таблице
	стоит исправить, только подогнать бы под процентное соотношение.
8. По файловой структуре: table.txt тот который юзает программа, прописан
	в коде константой, tablebackup.txt на случай если что то сломается.
9. Удалить комментарии в коде и перечитать пункт 0.
*/

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


int main(void)
{
	char filename[] = "table.txt";

		apartment_t apartments[MAXCOUNT];
		key_t keys[MAXCOUNT];
		printf("key %ld, apartment %ld\n", sizeof(apartment_t), sizeof(key_t));
		int count_of_records = 0;
		if (load_table(apartments, keys, &count_of_records, filename) == -1)
		{
			printf("Incorrect load of table!\n");
			return -1;
		}
		int menu;
		unsigned long long int time1;
		unsigned long long int bub = 0, quick = 0, bub_keys = 0, quick_keys = 0;
		// -------- MENU ----------- // 
		do
		{
			printf("(1) Print table\n");
			printf("(2) Sort table\n");
			printf("(3) Sort table with the key\n");
			printf("(4) Info about sorting\n");
			printf("(5) Add record\n");
			printf("(6) Delete record\n");
			printf("(7) Task\n");
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
					// 
					time1 = tick();
					bubblesort_a(apartments, &count_of_records);
					bub = tick() - time1;
					count_of_records = 0;
					load_table(apartments, keys, &count_of_records, filename);
					time1 = tick();
					qsort(apartments, count_of_records+1, sizeof(apartment_t), (int(*) (const void *, const void *)) comp);
					quick = tick() - time1;
					printf("############ APARTMENTS ############\n");
					for (int i = 0; i < count_of_records; i++)
					{
						print_table(apartments, i); 
						puts("####################################\n");
					}
					count_of_records = 0;
					load_table(apartments, keys, &count_of_records, filename);
					break;
				case 3:
					time1 = tick();
					bubblesort_k(keys, &count_of_records);
					bub_keys = tick() - time1;
					count_of_records = 0;
					load_table(apartments, keys, &count_of_records, filename);
					time1 = tick();
					qsort(keys, count_of_records+1, sizeof(key_t), (int(*) (const void *, const void *)) comp_k);
					quick_keys = tick() - time1;
					printf("############ APARTMENTS ############\n");
					for (int i = 0; i < count_of_records; i++)
					{
						print_table(apartments, keys[i].number);  ///////// !!!!!!!!!!!!!!!!!1
						puts("####################################\n");
					}
					count_of_records = 0;
					load_table(apartments, keys, &count_of_records, filename);
					break;
				case 4:
					printf("####### SORTING TIME #######\n");
					if (bub)
						printf("[Bubble sort] TABLE: %lld\n", bub);
					if (quick)
						printf("[Quick sort]  TABLE: %lld\n", quick);
					if (bub_keys)
						printf("[Bubble sort]  KEYS: %lld\n", bub_keys);
					if (quick_keys)
						printf("[Quick sort]   KEYS: %lld\n", quick_keys);
					printf("\n");
					break;
				case 5:
					if (count_of_records < MAXCOUNT)
						add_record(apartments, keys, &count_of_records, filename);
					else
						puts("Can't add new record!\n");
					break;
				case 6:
					printf("Input number of deleting record: ");
					int num;
					scanf("%d",&num);
					if (num <= count_of_records)
						del_record(apartments, keys, num, &count_of_records, filename);
					else
						puts("Can't delete record!");
					break;
				case 7:
					task(apartments, count_of_records);
					break;
				case 0:
					//fclose(table);
					break;
			}
		}
		while (menu != 0);
}