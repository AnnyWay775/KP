#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int size = 0;

struct Unit {
	float data;
	struct Unit *next, *prev;
} *it, *barrier;

void listAdd(float in)
{
	Unit *buff = new Unit;
	buff->data = in;
	buff->next = it->next;
	buff->prev = it;
	if (it->next != barrier) it->next->prev = buff;
	it->next = buff;
	++size;
}

void listAddFirst(float in)
{
	Unit *temp = it;
  it = barrier;
	listAdd(in);
	it = temp;
}
void listAddLast (float in)
{
	Unit *temp = it;
	while (it->next != barrier) it = it->next;
	listAdd(in);
	it = temp;
}

void listDelete()
{
	if (it == barrier)
	{
		printf("Выбран неверный элемент\n");
		return;
	}
	it->prev->next = it->next;
	if (it->next != barrier) it->next->prev = it->prev;
	Unit *temp = it->next;
	delete it;
	it = temp;
	--size;
}

void advance(int num)
{
	if (num > 0)
		while (it->next != barrier && num)
		{
			it = it->next;
			--num;
		}
	else if (num < 0)
		while (it->prev != barrier && num)
		{
			it = it->prev;
			++num;
		}
	return;
}

void listPrint()
{
  if (barrier->next == barrier)
  {
    printf("Список пуст\n");
    return;
  }
	Unit *temp = barrier->next;
  printf("Текущий список: \n");
  while (temp != barrier)
  {
    printf("%f\n", temp->data);
    temp = temp->next;
  }
}

void listWipe(Unit *itTemp)
{
	if (itTemp == barrier) return;
	listWipe(itTemp->next);
	delete itTemp;
}

void listWipeWrapper()
{
	if (barrier->next == barrier) return;
	listWipe(barrier->next);
	barrier->next = barrier;
}

void listGen(int amount)
{
	float temp;
	for (int i = 0; i < amount; i++)
	{
		temp = 50 * ((float) rand()/RAND_MAX);
		listAdd(temp);
	}
}

void listSpecial(Unit *temp)
{
	if (temp == barrier) return;
	listSpecial(temp->next);
	Unit *buff = temp->next;
	temp->next = temp->prev;
	temp->prev = buff;
}

void listSpecialWrapper()
{
  if (barrier->next == barrier)
  {
    printf("Список пуст\n");
    return;
  }
  Unit *temp = barrier->next;
  while (temp->next != barrier) temp = temp->next;
  listSpecial(barrier->next);
  barrier->next = temp;
}

int main() {
	srand(time(NULL));

	int menu, num;
	float value;
  
  barrier = new Unit;
  barrier->data = 0;
  barrier->next = barrier->prev = barrier;
  it = barrier;

	printf("Введите 10 для вывода меню\n");
	do {
		printf("Действие: "); scanf("%d", &menu);

		if (menu == 1)
		{
			printf("Введите число (float): ");
			scanf("%f", &value);
			listAdd(value);
      if (it == barrier) it = barrier->next;
		}
		else if (menu == 2)
		{
			printf("Введите число (float): ");
			scanf("%f", &value);
			listAddFirst(value);
      if (it == barrier)
      {
        it = barrier->next;
        printf("Итератор указывает на: %f\n", it->data);
      }
		}
		else if (menu == 3)
		{
			printf("Введите число (float): ");
			scanf("%f", &value);
			listAddLast(value);
      if (it == barrier)
      {
        it = barrier->next;
        printf("Итератор указывает на: %f\n", it->data);
      }
		}
		else if (menu == 4)
		{
			if (size > 0) listDelete();
			else printf("Из списка нечего удалять \n");
		}
		else if (menu == 5)
		{
      if (it == barrier) printf("Некуда двигать итератор\n");
      else
      {
        printf("Подвинуть итератор на: ");
        scanf("%d", &num);
        advance(num);
        printf("Итератор указывает на: %f\n", it->data);
      }
		}
		else if (menu == 6) listPrint();

		else if (menu == 7)
		{
			if (size > 0) listWipeWrapper();
			else printf("Список и так пустой\n");
		}
		else if (menu == 8)
		{
			printf("Кол-во элементов: ");
			scanf("%d", &num);
			listGen(num);
      if (it == barrier)
      {
        it = barrier->next;
        printf("Итератор указывает на: %f\n", it->data);
      }
		}
		else if (menu == 9) listSpecialWrapper();

		else if (menu == 10)
			printf("\nВыберите действие:\n\n"
				"1. Добавить после выбранного элемента\n"
				"2. Добавить элемент, как первый\n"
				"3. Добавить элемент, как последний\n"
				"4. Удалить выбранный элемент\n"
				"5. Подвинуть итератор\n"
				"6. Печать списка\n"
				"7. Удалить весь список\n"
				"8. Сгенерировать элементы после выбранного\n"
				"9. Переставть элементы списка в обратном порядке\n"
				"10. Печать меню\n"
				"0. Выйти из программы\n");
	} while (menu);
}
