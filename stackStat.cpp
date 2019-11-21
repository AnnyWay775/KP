#include "stack.h"
#include <stdio.h>
#define N 100

struct stack
{
	int first;
	int value[N];
};

stack * stackCreate()
{
	stack *S = new stack;
	S->first = 0;
	return S;
}

int stackIsEmpty(stack *S)
{
	return S->first == 0;
}

void stackDestroy(stack *S)
{
	delete S;
}

void stackPush(stack *S, int v)
{
	if (S->first == N) printf("Стэк переполнен\n");
	else
	{
		S->value[S->first] = v;
		S->first++;
	}
}

int stackPop(stack *S)
{
	if (stackIsEmpty(S)) printf("Стэк пуст\n");
	else 
	{
		S->first--;
		return S->value[S->first];
	}
}

int stackTop(stack *S)
{
	if (stackIsEmpty(S)) printf("Стэк пуст\n");
	else return S->value[S->first-1];
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
		printf("[ ");
		for (int i = 0; i < S->first; i++)
			printf("%d ", S->value[i]);
		printf("]\n");
	}
}

