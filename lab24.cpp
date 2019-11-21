#include<stdio.h>

char ch;

struct Node
{
	char data;
	struct Node *left, *right;
} *root;

int isSymbol(char c)
{
	return ( (c>='a')&&(c<='z') ) || ( (c>='0')&&(c<='9') );
}

int isNum(char c)
{
	return (c>='0')&&(c<='9');
}

Node * nodeCreate(char c, Node *l, Node *r)
{
	Node *temp;
	temp = new Node;
	temp->data = c;
	temp->left = l;
	temp->right = r;
	return temp;
}


Node * parseExpr();

Node * parseFact()
{
	Node *temp = NULL;
	scanf("%c", &ch);
	if (ch == '(')
	{
		temp = parseExpr();
		if (ch != ')')
			printf("Ощибка: ожидалась закрывающая скобка ')'\n");
	}
	else
	{
		if (isSymbol(ch)) temp = nodeCreate(ch, NULL, NULL);
		else printf("Ошибка: неподходящий символ '%c'\n", ch);
	}
	return temp;
}

Node * parseTerm()
{
	int done = 0;
	Node *temp = parseFact();
	while (ch != '\n' && !done)
	{
		scanf("%c", &ch);
		if (ch == '*' || ch == '/')
		{
			char ch1 = ch;
			temp = nodeCreate(ch1, temp, parseFact());
		}
		else done = 1;
	}
	return temp;
}

Node * parseExpr()
{
	int done = 0;
	Node *temp = parseTerm();
	while (ch != '\n' && !done)
	{
		if (ch == '+' || ch == '-')
		{
			char ch1 = ch;
			temp = nodeCreate(ch1, temp, parseTerm());
		}
		else done = 1;
	}
	return temp;
}

void treePrint(Node *temp)
{
	if (!root)
	{
		printf("Ещё нету дерева\n");
		return;
	}
	static int depth = 0;
	if (temp->right)
	{
		depth++;
		treePrint(temp->right);
		depth--;
	}
	for (int i = 0; i < depth; i++) printf("   ");
	printf("\\__%c\n",temp->data);
	if (temp->left)
	{
		depth++;
		treePrint(temp->left);
		depth--;
	}
}

void treeResult(Node *temp)
{
	if (temp)
	{
		if (temp->data == '+' || temp->data == '-') printf("(");
		treeResult(temp->left);
		printf("%c", temp->data);
		treeResult(temp->right);
		if (temp->data == '+' || temp->data == '-') printf(")");
	}
}

void parenthesesMultiply(Node **temp, char num)
{
	Node *hold = *temp;
	if (!hold) return;
	if (!isSymbol(hold->data))
	{
		parenthesesMultiply(&hold->left, num);
		parenthesesMultiply(&hold->right, num);
		return;
	}
	Node* buff = nodeCreate('*', nodeCreate(hold->data, NULL, NULL), nodeCreate(num, NULL, NULL));
	delete hold;
	*temp = buff;
}

void treeRemoveParenthesis(Node **in)
{
	if (!(*in)) return;
  Node *temp = *in;
	treeRemoveParenthesis(&temp->left);
	treeRemoveParenthesis(&temp->right);
	if (temp->data == '*')
	{
		if (temp->right->data == '-' && isSymbol(temp->left->data))
		{
			parenthesesMultiply(&temp->right, temp->left->data);
			Node* buff = temp->right;
			delete (*in)->left;
			delete *in;
			*in = buff;
		}
		else if (temp->left->data == '-' && isSymbol(temp->right->data))
		{
			parenthesesMultiply(&temp->left, temp->right->data);
			Node* buff = temp->left;
			delete (*in)->right;
			delete *in;
			*in = buff;
		}
	}
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
	printf("Выражение: ");
	root = parseExpr();
	printf("\nПостоенное дерево:\n");
	treePrint(root);
	printf("\n\nВыражение из дерева:\n");
	treeResult(root);
	printf("\n");
	treeRemoveParenthesis(&root);
	printf("\nОбработанное дерево:\n");
	treePrint(root);
	printf("\n\nВыражение из обработанного дерева:\n");
	treeResult(root);
	printf("\n");
	treeWipeWrapper();
	return 0;
}
