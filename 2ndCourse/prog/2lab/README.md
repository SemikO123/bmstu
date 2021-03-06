## Лабораторная работа №1.1
### Динамическая память, адресная арифметика.

*Написать программу, которая считывает из текстового файла целые числа в массив и выполняет обработку этого массива (см. распределение вариантов). 

Память под массив выделяется динамически. Число элементов в массиве определяется в первом проходе по текстовому файлу, во время второго прохода числа считываются в массив.

Имя файла передается через параметры командной строки.

Модульные тесты реализуются в отдельном проекте.

При защите лабораторной работы необходимо продемонстрировать отчет утилиты Doctor Memory, свидетельствующий об отсутствии ошибок при работе с памятью.*

Вариант 4.
Вычислить значение **min(x[0]*x[1], x[1]*x[2],x[2]*x[3], ..., x[n-3]*x[n-2], x[n-2]*x[n-1]), где x[i]** - элементы массива x из n элементов.

## Лабораторная работа №1.2
###  Динамическая память, адресная арифметика.

*Написать программу, которая упорядочивает массив.

Данные в массив считываются из файла (можно и нужно взять функцию чтения массива из предыдущей лабораторной работы). Полученный после сортировки массив записывается в файл.

Возможно, что перед сортировкой элементы массива могут быть отфильтрованы с помощью функции-фильтра.

Функция-фильтр работает следующим образом:

определяет количество элементов массива, которые удовлетворяют заданному условию;
выделяет память под соответствующее количество элементов;
копирует элементы, удовлетворяющие условию, из старого массива в новый.
Функция сортировки реализуется универсальной (т.е. имеет одинаковый прототип с функцией qsort из стандартной библиотеки (stdlib.h)).

Все параметры (имена файлов, необходимость фильтрации) передаются через аргументы командной строки.

Для функции сортировки и функции-фильтра реализуются модульные тесты (отдельный проект).

При защите лабораторной работы необходимо продемонстрировать отчет утилиты Doctor Memory, свидетельствующий об отсутствии ошибок при работе с памятью.

Кроме того, необходимо сравнить время работы реализованного алгоритма сортировки и qsort. Постараться найти примеры, когда ваша реализация лучше. Результаты представить в виде графиков (рисунки в формате PNG, оси подписаны). Графики можно строить любыми средствами (например, в Excel).*

Сортировка: **Модифицированная сортировка пузырьком III. Идеи первой и второй модифицированной сортировки пузырьком объединяются.**
Фильтр: **Расположенные между минимальным и максимальным элементами массива.**
