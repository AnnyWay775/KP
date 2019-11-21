struct stack;

stack * stackCreate();
int stackIsEmpty(stack *S);
void stackDestroy(stack *S);

void stackPush(stack *S, int v);
int stackPop(stack *S);

int stackTop(stack *S);
int stackSize(stack *S);

void stackDisplay(stack *S);
