#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#pragma warning(disable: 4996)

typedef enum { false, true } bool;

typedef struct
{
	int num;
	int coef;
	char op;
	bool oper;
}Node;

struct Stack
{
	int top;
	unsigned capacity;
	Node* array;
};

int M;

// Stack Operations 
struct Stack* createStack(unsigned capacity)
{
	struct Stack* stack = (struct Stack*) malloc(sizeof(Node)*capacity+1);

	if (!stack)
		return NULL;

	stack->top = -1;
	stack->capacity = capacity;

	stack->array = (Node*)malloc(stack->capacity * sizeof(Node) + 1);

	return stack;
}

int peekcoef(struct Stack* stack)
{
	return stack->array[stack->top].coef;
}
int peeknum(struct Stack* stack)
{
	return stack->array[stack->top].num;
}
char peekop(struct Stack* stack)
{
	return stack->array[stack->top].op;
}

int isEmpty(struct Stack*stack)
{
	return stack->top == -1;
}
bool isFull(struct Stack*stack)
{
	return (stack->top == stack->capacity - 1);
}
void pop(struct Stack* stack)
{
	if (!isEmpty(stack))
		stack->top--;
	return;
}

void InitNode(struct Stack*stack)
{
	stack->array[stack->top + 1].coef = 0;
	stack->array[stack->top + 1].num = 0;
	stack->array[stack->top + 1].op = '\0';
	stack->array[stack->top + 1].oper = false;
}

void pushcoef(struct Stack* stack, int op)
{
	InitNode(stack);
	stack->array[++stack->top].coef = op;
}
void pushnum(struct Stack* stack, int op)
{
	InitNode(stack);
	stack->array[++stack->top].num = op;
}
void pushop(struct Stack* stack, char op)
{
	InitNode(stack);
	stack->array[++stack->top].op = op;
	stack->array[stack->top].oper = true;
}

int Prec(char ch)
{
	switch (ch)
	{
	case '+':
	case '-':
		return 1;

	case '*':
	case '/':
		return 2;

	}
	return -1;
}

int isNum(char ch)
{
	return (ch >= '0' && ch <= '9');
}

struct Stack* intopostfix(char*exp, int P);

Node evaluation(struct Stack*postfix, struct Stack*resul);

int main()
{
	char example[1001];
	int  P;
	;

	scanf("%s", &example);
	scanf("%d", &P);
	scanf("%d", &M);


	struct Stack*Postfix = createStack(strlen(example));
	struct Stack*resul = createStack(strlen(example));

	Postfix = intopostfix(example, P);
	Node result = evaluation(Postfix, resul);

	int num = result.num;
	int coef = result.coef;

	for (long long i = 1; i < 10; i++)
	{
		if ((num + coef * i) % M == P)
		{
			printf("%d", i);
			break;
		}
	}

	return 0;
}

Node evaluation(struct Stack*postfix, struct Stack*resul)
{
	int i = 0;
	Node tmp, tmp2;
	for (i = 0; i < postfix->top + 1; i++)
	{
		if (!(postfix->array[i].oper))//포스트 픽스에서 나온게 숫자이면
		{
			if (postfix->array[i].coef != 0)//나온게 coef라면
			{
				pushcoef(resul, postfix->array[i].coef);
			}
			else
			{
				pushnum(resul, postfix->array[i].num);
			}
		}
		else//숫자가 아니라면
		{
			tmp = resul->array[resul->top];
			pop(resul);
			tmp2 = resul->array[resul->top];
			pop(resul);

			if (postfix->array[i].op == '+')
			{
				tmp.coef = (tmp.coef + tmp2.coef)%M;
				tmp.num = (tmp.num + tmp2.num)%M;
				resul->array[++resul->top] = tmp;
			}
			else if (postfix->array[i].op == '-')
			{
				tmp.coef = (tmp2.coef - tmp.coef+M)%M;
				tmp.num = (tmp2.num - tmp.num+M)%M;
				resul->array[++resul->top] = tmp;
			}
			else if (postfix->array[i].op == '*')
			{
				if (tmp2.coef == 0)//곱하는게 num이다
				{
					tmp.coef = (long long)tmp.coef * tmp2.num %M;
					tmp.num = (long long)tmp.num * tmp2.num %M;
				}
				else
				{
					tmp.coef = (long long)tmp2.coef * tmp.num %M;
					tmp.num = (long long)tmp2.num * tmp.num %M;
				}
				resul->array[++resul->top] = tmp;
			}
		}
	}
	return resul->array[resul->top];
}

struct Stack* intopostfix(char*exp, int P)
{
	int i = 0;
	struct Stack*postfix = createStack(strlen(exp));
	struct Stack*stack = createStack(strlen(exp));
	int temp = 0;

	for (i = 0; i < strlen(exp); i++)
	{
		if (isNum(exp[i]))
		{
			temp *= 10;
			temp += exp[i] - '0';
			temp %= M;

		}
		else if (exp[i] == 'x')
		{
			if (temp == 0)
			{
				temp = 1;
			}
			pushcoef(postfix, temp);
			temp = 0;

		}
		else
		{
			if (i&&isNum(exp[i - 1]))
			{
				pushnum(postfix, temp);
				temp = 0;
			}

			if (exp[i] == '(')
			{
				pushop(stack, exp[i]);
			}
			else if (exp[i] == ')')
			{
				while (stack->array[stack->top].op != '(')
				{
					pushop(postfix, stack->array[stack->top].op);
					pop(stack);
				}
				pop(stack);
			}
			else if (exp[i] == '*')
			{
				pushop(stack, '*');
			}
			else if (exp[i] == '+' || exp[i] == '-')
			{
				while (!isEmpty(stack) && stack->array[stack->top].op == '*')
				{
					pushop(postfix, stack->array[stack->top].op);
					pop(stack);
				}
				pushop(stack, exp[i]);
			}
		}
	}

	while (!isEmpty(stack))
	{
		pushop(postfix, stack->array[stack->top].op);
		pop(stack);
	}

	return postfix;
}