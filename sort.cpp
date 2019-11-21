#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


struct table_tag
{
	float key;
	char *line;
};

int floatEqual(float a, float b) 
{
	float eps = 0.001, temp;
	if (a > b) temp = a - b;
	else temp = b - a;

	if (temp < eps) return 1; 
	else return 0;
}

void fileSize(FILE *text, int &lines, int &max) 
{
	int c, length;
	max = length = lines = 0;
	c = fgetc(text);
	while (c != EOF)
	{
		if (c == '\n')
		{
			length++;
			lines++;
			if (max < length) max = length;
			length = 0;
		}
		else length++;
		c = fgetc(text);
	}
	rewind(text);
}

int stateDetect(table_tag *table, int n)
{
	int state = 1, i = 1;
	while (i != n && floatEqual(table[i-1].key, table[i].key)) i++;

	if (table[i-1].key > table[i].key && !floatEqual(table[i-1].key, table[i].key))
		state = 2;

	if (i == n) return state;

	if (state == 1)
	{
		for (i++; i < n; i++)
			if (table[i-1].key > table[i].key && !floatEqual(table[i-1].key, table[i].key)) 
			{
				state = 3; break;
			}
	}
	else if (state == 2)
		for (i++; i < n; i++)
			if (table[i-1].key < table[i].key && !floatEqual(table[i-1].key, table[i].key))
			{
				state = 3; break;
			}
	return state;
}

void quicksort(table_tag *table, int l, int r)
{
	int i = l, j = r;
	float mid = table[(l+r)/2].key;
	table_tag w;
	while (i <= j)
	{
		while (!floatEqual(table[i].key, mid) && table[i].key < mid) i++;
		while (!floatEqual(table[j].key, mid) && mid < table[j].key) j--;
		if (i <= j)
		{
			w=table[i]; table[i] = table[j]; table[j] = w;
			i++; j--;
		}
	}
	if (l<j) quicksort(table, l, j);
	if (i<r) quicksort(table, i, r);
}

void quicksortReverse(table_tag *table, int l, int r)
{
	int i = l, j = r;
	float mid = table[(l+r)/2].key;
	table_tag w;
	while (i <= j)
	{
		while (!floatEqual(table[i].key, mid) && table[i].key > mid) i++;
		while (!floatEqual(table[j].key, mid) && mid > table[j].key) j--;
		if (i <= j)
		{
			w=table[i]; table[i] = table[j]; table[j] = w;
			i++; j--;
		}
	}
	if (l<j) quicksortReverse(table, l, j);
	if (i<r) quicksortReverse(table, i, r);
}

void shuffle(table_tag *table, int n)
{
	int j; table_tag k;
	for (int i = 0; i < n-1; i++)
	{
		j = i+1 + rand() % (n-1-i);
		k = table[i];
		table[i] = table[j];
		table[j] = k;
	}
}

float searchBinary(table_tag *table, int n, int state)
{
	float val; int l = 0, r = n-1, mid;
	printf("Значение ключа: ");
	scanf("%f", &val);
	if (state == 1)
		while (l < r)
		{
			mid = (l+r)/2;
			if (table[mid].key<val) l = mid + 1;
			else r = mid;
		}
	else
		while (l < r)
		{
			mid = (l+r)/2;
			if (table[mid].key>val) l = mid + 1;
			else r = mid;
		}
	if (floatEqual(table[l].key, val)) printf("Строка найдена:\n%s", table[l].line);
	else printf("Не найдено такого ключа\n");
}

void searchLinear(table_tag *table, int n)
{
	float val;
	printf("Значение ключа: ");
	scanf("%f", &val);
	for (int i = 0; i < n; i++)
		if (floatEqual(table[i].key, val))
		{
			printf("Строка найдена:\n%s", table[i].line);
			return;
		}
	printf("Не найдено такого ключа\n");
	return;
}

int main(int argc, char *argv[])
{
	int i, lines, max, state;
	FILE *text, *keys;
	table_tag *table;

	switch (argc)
	{
		case 1 :	
			if((text = fopen("prose.txt","r")) == NULL)
			{
				printf("Не удаётся открыть prose.txt\n");
				return 1;
			}
			if((keys = fopen("prosekeys.txt","r")) == NULL)
			{
				printf("НЕ удаётся открыть prosekeys.txt\n");
				return 2;
			}
			break;
		case 2 :
			if((text = fopen(argv[1],"r")) == NULL)
			{
				printf("Не удаётся открыть %s\n", argv[1]);
				return 1;
			}
			if((keys = fopen("prosekeys.txt","r")) == NULL)
			{
				printf("Не удаётся открыть prosekeys.txt\n");
				return 2;
			}
			break;
		case 3 :
			if((text = fopen(argv[1],"r")) == NULL)
			{
				printf("Не удаётся открыть %s\n", argv[1]);
				return 1;
			}
			if((keys = fopen(argv[2],"r")) == NULL)
			{
				printf("Не удаётся открыть %s\n", argv[2]);
				return 2;
			}
			break;
		default : 
			printf("Слишком много аргументов\n");
			return 3;
	}

	fileSize(text, lines, max);
	printf("Пoлучено %d строк, максимальная длина: %d\n", lines, max);

	table = new table_tag [lines];
	for (i = 0; i < lines; i++)
		table[i].line = new char [max+1];
	for (i = 0; i < lines; i++)
	{
		fgets(table[i].line, max+1, text);
		fscanf(keys,"%f", &table[i].key);
	}

	state = stateDetect(table, lines);

	srand(time(NULL));
	printf("Введите 9 для печати меню\n");
	int menu = 1;
	while(menu)
	{
		printf("\nДействие: ");
		scanf("%d", &menu);
		switch (menu)
		{
			case 1 :
				if (state == 1)
					printf("Текст уже отсортирован\n");
				else
				{
					quicksort(table, 0, lines-1);
					state = 1;
				}
				break;
			case 2 :
				if (state == 2)
					printf("Текст уже отсортирован\n");
				else
				{
					quicksortReverse(table, 0, lines-1);
					state = 2;
				}
				break;
			case 3 :
				shuffle(table, lines);
				state = 3;
				break;
			case 4 :
				for (i = 0; i < lines; i++)
					printf("%.3f %s", table[i].key, table[i].line);
				break;
			case 5 :
				if (state == 3) printf("Невозможно произвести бинарный поиск по неотсортированным ключам\n");
				else
					searchBinary(table, lines, state);
				break;
			case 6 :
				searchLinear(table, lines);
				break;
			case 9 :
				printf("\nДействия:\n\n"
					"0. Выйти из программы\n"
					"1. Отсортировать текст\n"
					"2. Реверсивная сортировка\n"
					"3. Перемешать\n"
					"4. Печать текущего текста\n"
					"5. Бинарный поиск\n"
					"6. Линейный поиск\n"
					"9. Печать меню\n");
				break;
			case 0 :
				break;
			default :
				printf("Нет такого пункта меню\n");
		}
	}
}
