#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "func.h"

// Вариант 3 Задача 2
int my_strlen(char *str)
{
	int count = 0;
	while (*str != '\0' && ++str)
		++count;
	return count;
}

char *get_substr(char *str)
{
	int n = my_strlen(str);
	char *n_str = malloc((n + 1) * sizeof(char));
	for (int i = 0; i < n; ++i)
		n_str[i] = str[i];
	n_str[n]= '\n';
	return n_str;
}


struct list *take_words(FILE *f)
{
	struct list *head = NULL;
	char str[N+1];
	while (fgets(str, N+1, f) != NULL)
	{
		//char *words[N+1];
		//int k = 0;
		//printf("STRING = %sLEN = %d MY_LEN = %d\n", str, (int)strlen(str), my_strlen(str));
		/*
		char *c = str;
		printf("%d\n", '\n');
		while(*c != '\0')
		{
			printf("%d ", *c);
			++c;
		}
		printf("|\n");
		*/
		int lenght = my_strlen(str);
		for (int i = 0; i < lenght; i++)
		{
			//printf("symb=%c\n",str[i]);
			if (strchr(" ", str[i]))
				str[i] = '\0';
			else 
			{
				if ((str[i-1] == '\0'))
				{
					head = add(head, new(get_substr(str+i)));
					//words[k++] = str + i;
					//printf("Bitches %s", head->data);
				}

			}
		}
		/*
		//printf("k=%d ",k);
		for (int i = 0; i < k; i++)
		{
			struct list *new_elem = new(words[i]); 
			head = add(head, new_elem);
			printf("%d. %s\n",i ,words[i]);
			printf("v func %s\n", head->data);
		}
		*/

	}
	return head;			
}

int main (int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Bad parameters with names of file");
		return BADPARAMETERS;
	}
	else
	{
		FILE *in = fopen(argv[1],"r");
		if (in != NULL)
		{
			// take_words(in);

			struct list *head = take_words(in);
			print_list(head,stdout);
			/*
			printf("vne %s\n", head->data);
			FILE *out = fopen(argv[2],"w");
			printf("vne %s\n", head->data);
			print_list(head, out);*/
			// 
			// if (out != NULL)
			// {
			// 	print_list(head, out);
			// }
			// else
			// {
			// 	printf("Output file doesn't found");
			// 	return NOFILE;
			// }
			// free_list(head);
			//fclose(out);
			
		}
		else 
		{
			printf("Input file doesn't found");
			return NOFILE;
		}
		fclose(in);
	}
	return OK;
	
}
