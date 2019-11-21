#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct Node {
	float value;
	int num;
	struct Node *left;
	struct Node *right;
} *root, *buff;

int floatEqual(float a, float b)
{
	float eps = 0.001, temp;
	if (a > b) temp = a - b;
	else temp = b - a;

	if (temp < eps) return 1;
	else return 0;
}

Node* treeAdd(Node *temp, float input)
{
	if (!temp)
	{
		temp = new Node;
		temp->value = input;
		temp->num = 1;
		temp->left = NULL;
		temp->right = NULL;
		if (!root) root = temp;
	}
	else if (input < temp->value) temp->left = treeAdd(temp->left, input);
	else if (input > temp->value) temp->right = treeAdd(temp->right, input);
	return temp;
}

void treeGen(int num)
{
	for (int i = 0; i < num; i++) treeAdd(root, ( 50 * ((float) rand()/RAND_MAX )));
}

void treePrint(Node *temp)
{
	static int depth = 0;
  if (!temp) return;
  depth++;
  treePrint(temp->right);

	for (int i = 0; i < depth - 1; i++) printf(" _ ");
	printf("%.3f \n", temp->value);
 
  treePrint(temp->left);
  depth--;
}

void treeDelete(float i)
{
	struct Node *nodePrev, *nodeFind, *nodeFindPrev;
	int del = 1;
	buff = root;
	while (buff && !floatEqual(buff->value, i))
	{
		nodePrev = buff;
		if (i < buff->value) buff = buff->left;
		else if (i > buff->value) buff = buff->right;
	}
	if (!buff)
	{
		printf("Такого элемента нет\n");
		return;
	}
	else if (buff->num > 1)
	{
		printf("%d элементов найдено. Сколько удалить? (0 для отмены): ", buff->num);
		do
		{
		scanf("%d", &del);
		if (del > buff->num || del < 0) printf("Некорректный ввод. ");
		} while (del > buff->num || del < 0);
	}
	if (buff->num == del)
	{
		int i = 1;
		if (buff->right && buff->left)
		{
			printf("Элемент имеет два поддерева. Заменить его левым(1) или правым(2) поддеревом?");
			scanf(" %d", &i);
		}
		if (buff->left && i == 1)
		{
			nodeFind = buff->left; nodeFindPrev = nodeFind;
			if (nodeFind->right)
			{
				while (nodeFind->right)
				{
					nodeFindPrev = nodeFind;
					nodeFind = nodeFind->right;
				}
				if (nodeFind->left)
					nodeFindPrev->right = nodeFind->left;
				else
					nodeFindPrev->right = NULL;
				nodeFind->left = buff->left;
			}
			if (buff->right) nodeFind->right = buff->right;
			if (buff == root) root = nodeFind;
			else
				if (nodePrev->left == buff) nodePrev->left = nodeFind;
				else if (nodePrev->right == buff) nodePrev->right = nodeFind;
		}
		else if (buff->right)
		{
			nodeFind = buff->right; nodeFindPrev = nodeFind;
			if (nodeFind->left)
			{
				while (nodeFind->left)
				{
					nodeFindPrev = nodeFind;
					nodeFind = nodeFind->left;
				}
				if (nodeFind->right)
					nodeFindPrev->left = nodeFind->right;
				else
					nodeFindPrev->left = NULL;
				nodeFind->right = buff->right;
			}
			if (i == 2) nodeFind->left = buff->left; 
			if (buff == root) root = nodeFind;
			else
				if (nodePrev->left == buff) nodePrev->left = nodeFind;
				else if (nodePrev->right == buff) nodePrev->right = nodeFind;
		}
		else
			if (nodePrev->left == buff) nodePrev->left = NULL;
			else if (nodePrev->right == buff) nodePrev->right = NULL;
		if (buff == root) root = NULL;
		delete buff;
	}
	else buff->num -= del;
}

int treeLeaves(Node *temp)
{
  if (!temp) return 0;
	return treeLeaves(temp->left) + treeLeaves(temp->right) + 1;
}

void treeWipe(Node *temp)
{
	if (!temp) return;
	treeWipe(temp->left);
	treeWipe(temp->right);
	delete temp;
}

void treeWipeWrapper()
{
	treeWipe(root);
	root = NULL;
}

int main()
{
	srand(time(NULL));

	int num, menu;
	float in;
	printf("Введите 9 для вывода меню\n");
	do
	{
		printf("\nДействие: ");
		scanf("%d", &menu);
		switch (menu)
		{
		case 1 :
			printf("Значение: ");
			scanf("%f", &in);
			treeAdd(root, in);
			break;
		case 2 :
			printf("Количество элементов: ");
			scanf("%d", &num);
			if (num > 0) treeGen(num);
			else printf("Некорректное число элементов\n");
			break;
		case 3 :
			if (!root) printf("Дерево нету\n");
			else
			{
				printf("Значение элемента: ");
				scanf("%f", &in);
				treeDelete(in);
			}
			break;
		case 4 :
			treePrint(root);
			break;
		case 5 :
			if (!root)
				printf("Дерева нет в данный момент\n");
			else
				printf("У дерева %d вершин\n", treeLeaves(root));
			break;
		case 6 :
			if (!root)
				printf("Дерева нет в данный момент\n");
			else
			{
				treeWipeWrapper();
				printf("Дерево удалено\n");
			}
			break;
		case 9 :
			printf("\nДействие:\n\n"
				"0. Выйти из программы\n"
				"1. Добавить элемент в дерево\n"
				"2. Сгенерировать дерево\n"
				"3. Удалить элемент\n"
				"4. Печать дерева\n"
				"5. Количество вершин дерева\n"
				"6. Удалить дерево целиком\n"
				"9. Печать меню\n");
			break;
		case 0 :
			if (root) treeWipeWrapper();
			break;
		default :
			printf("Нет такого пункта меню\n");
		}
	} while (menu);
}
