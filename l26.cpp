#include "stack.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int stackSorted(stack *S)
{
	if (stackIsEmpty(S) || stackSize(S) == 1) return 1;

	int v = stackPop(S); short state;
	if (!stackIsEmpty(S) && v < stackTop(S))
	{
		stackPush(S, v);
		return 0;
	}
	else
		state = stackSorted(S);
	stackPush(S, v);
	return state;
}

void bubbleSwitch(stack *S, int i)
{
	stack *H; H = stackCreate();
	int j, v = stackPop(S);
	for (j = stackSize(S); j > i; j--)
	{
		if (v >= stackTop(S))
		{
			stackPush(H, v);
			v = stackPop(S);
		}
		else stackPush(H, stackPop(S));
	}
	stackPush(S, v);
	while (!stackIsEmpty(H))
		stackPush(S, stackPop(H));
	stackDestroy(H);
}

void bubbleSort(stack *S)
{
	for (int i = 0; i < stackSize(S); i++)
	{
		if (stackSorted(S)) break;
		bubbleSwitch(S, i);
	}
}

int main()
{
	srand(time(NULL));

	stack *S = stackCreate();
	int val, menu = 1;
	printf("Введите 9 для печати меню\n");
	while(menu)
	{
		printf("\nДействие: ");
		scanf("%d", &menu);
		switch (menu)
		{
			case 1 :
				printf("Значение: "); scanf("%d", &val);
				stackPush(S, val);
				break;
			case 2 :
				stackPop(S);
				break;
			case 3 :
				if (stackIsEmpty(S)) printf("Стэк пуст\n");
				else
				{
					stackDestroy(S);
					S = stackCreate();
				}
				break;
			case 4 :
				printf("Кол-во элементов: "); scanf("%d", &val);
				for (int i = 0; i < val; i++)
					stackPush(S, rand()%51);
				break;
			case 5 :
				stackDisplay(S);
				break;
			case 6 :
				printf("Размер стэка - %d", stackSize(S));
				break;
			case 7 :
				if (stackIsEmpty(S)) printf("Стэк пуст\n");
				else if (stackSorted(S)) printf("Стэк уже отсортирован");
				else bubbleSort(S);
				break;
			case 8 :
				if (stackIsEmpty(S)) printf("Стэк пуст\n");
				else if (stackSorted(S)) printf("Стэк уже отсортирован");
				else bubbleSwitch(S, 0);
				break;
			case 9 :
				printf("\nДействие:\n\n"
					"0. Выйти из программы\n"
					"1. Добавить элемент в стэк\n"
					"2. Удалить элемент из стэка\n"
					"3. Удалить целый стэк\n"
					"4. Сгенерировать рандомные элементы\n"
					"5. Печать стэка\n"
					"6. Печать размера стэка\n"
					"7. Сортировка пузырьком\n"
					"8. Процедура\n"
					"9. Печать меню\n");
				break;
			case 0 :
				stackDestroy(S);
				return 0;
			default :
				printf("Нет такого пункта меню\n");
		}
	}
		
}
