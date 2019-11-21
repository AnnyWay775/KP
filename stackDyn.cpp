#include "stack.h"
#include <stdio.h>

struct list
{
	int val;
	list *up, *down;
};

struct stack
{
	int first;
	list *last;
};

stack * stackCreate()
{
	stack *t = new stack;
	t->first = 0;
	t->last = NULL;
	return t;
}

int stackIsEmpty(stack *S)
{
	return S->first==0; 
}

void stackDestroy(stack *S)
{
	list *t1 = S->last, *t2;
	while (t1)
	{
		t2 = t1->down;
		delete t1;
		t1 = t2;
	}
	delete S;
}

void stackPush(stack *S, int v)
{
	if (!S->last) 
	{
		S->last = new list;
		S->last->down = NULL;
	}
	else
	{
		S->last->up = new list;
		S->last->up->down = S->last;
		S->last = S->last->up;
	}
	S->last->up = NULL; S->last->val = v;
	S->first++;
}

int stackPop(stack *S)
{
	if (S->first == 0) printf("Стэк пуст\n");
	else
	{
		int v = S->last->val;
		if (S->last->down)
		{
			S->last = S->last->down;
			delete S->last->up;
			S->last->up = NULL;
		}
		else
		{
			delete S->last;
			S->last = NULL;
		}
		S->first--;
		return v;
	}
}

int stackTop(stack *S)
{
	if (stackIsEmpty(S)) printf("Стэк пуст\n");
	else return S->last->val;
}

int stackSize(stack *S)
{
	return S->first;
}
void stackDisplay(stack *S)
{
	if (stackIsEmpty(S)) printf("Стэк пуст\n");
	else
	{
		list *t = S->last;
		while (t->down) t = t->down;
		printf("[ ");
		for (int i = 0; i < S->first; i++)
		{
			printf("%d ", t->val);
			t = t->up;
		}
		printf("]\n");
	}
}
