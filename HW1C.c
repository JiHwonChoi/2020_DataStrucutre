#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STACK 100
typedef enum { false, true } bool;
typedef struct {
	char small;
	char large;
	// *Variable "operator"
	// used in ConvInfixToPostfix function
	char operator;
}Penta_num;
typedef struct {
	Penta_num items[MAX_STACK];
	int top;
}Stack;

/* Modify from here */

bool isdigit(char n);
int ptd(char a);
int PtD(Penta_num n);
Penta_num DtP(int c);
int GetPriority(char op);
bool ComparePriority(char op1, char op2);
bool isalpha(char n);

/* Modify to here */
Penta_num add(Penta_num b1, Penta_num b2);
Penta_num subtract(Penta_num b1, Penta_num b2);
Penta_num multiply(Penta_num b1, Penta_num b2);
Penta_num division(Penta_num b1, Penta_num b2);
void InitStack(Stack *pstack);
bool IsFull(Stack *pstack);
bool IsEmpty(Stack *pstack);
Penta_num Peek(Stack *pstack);
void Push(Stack *pstack, Penta_num item);
void Pop(Stack *pstack);
void ConvInfixToPostfix(char* exp, char* convExp, int len);
Penta_num EvalPostfix(char* exp, int len);
void print_Penta_num(Penta_num result);

int main() {
	char infix_exp[100];
	char postfix_exp[100];
	Penta_num result;
	scanf("%s", infix_exp);
	ConvInfixToPostfix(infix_exp, postfix_exp, strlen(infix_exp));
	printf("%s\n%s\n", infix_exp, postfix_exp);
	result = EvalPostfix(postfix_exp, strlen(postfix_exp));
	print_Penta_num(result);
	return 0;
}

/* Modify from here */
bool isdigit(char n)
{
	if ((48 <= n) && (57 >= n))
		return true;
	else
		return false;
}

bool isalpha(char n)
{
	if ((65 <= n) && (69 >= n))
		return true;
	else
		return false;
}

int ptd(char a)
{
	if (isdigit(a))
		return (a - '0');
	else
		return(a - '7');
}

int PtD(Penta_num n)
{

	int c = ptd(n.small); int d = ptd(n.large);
	int k = 15 * c + d;
	return k;
}

Penta_num DtP(int c)
{
	Penta_num n;
	if ((c / 15) < 10)
		n.small = c / 15 + '0';
	else
		n.small = c / 15 + '7';
	if ((c % 15) < 10)
		n.large = c % 15 + '0';
	else
		n.large = c % 15 + '7';
	return n;
}

void InitStack(Stack*pstack)
{
	pstack->top = -1;
}
bool IsFull(Stack*pstack)
{
	return pstack->top == MAX_STACK - 1;
}
bool IsEmpty(Stack*pstack)
{
	return (pstack->top == -1);
}
Penta_num Peek(Stack*pstack)
{
	if (IsEmpty(pstack))
		exit(1);
	return pstack->items[pstack->top];
}
void Push(Stack *pstack, Penta_num item)
{
	if (IsFull(pstack))
		exit(1);
	pstack->items[++(pstack->top)] = item;
}
void Pop(Stack *pstack)
{
	if (IsEmpty(pstack))
		exit(1);
	--(pstack->top);
}

	Penta_num add(Penta_num b1, Penta_num b2)
	{
		int x, y;
		x = PtD(b1); y = PtD(b2);
		x += y;
		Penta_num c;
		c = DtP(x);
		return c;
	}
	
	
	Penta_num subtract(Penta_num b1, Penta_num b2)
	{
		int x, y;
		x = PtD(b1); y = PtD(b2);
		x -= y;
		Penta_num c;
		c = DtP(x);
		return c;
	}
	Penta_num multiply(Penta_num b1, Penta_num b2)
	{
		int x, y;
		x = PtD(b1); y = PtD(b2);
		x *= y;
		Penta_num c;
		c = DtP(x);
		return c;
	}
	
	Penta_num division(Penta_num b1, Penta_num b2)
	{
		int x, y;
		x = PtD(b1); y = PtD(b2);
		x /= y;
		Penta_num c;
		c = DtP(x);
		return c;
	}

	void ConvInfixToPostfix(char* exp, char* convExp, int len)
	{
		Stack stack;
		int idx = 0;
		Penta_num temp;
		InitStack(&stack);
		for (int i = 0; i < len; i++)
		{
			if (isdigit(exp[i]))
				convExp[idx++] = exp[i];
			else if (isalpha(exp[i]))
				convExp[idx++] = exp[i];
			else
			{
				while (!IsEmpty(&stack) && ComparePriority((Peek(&stack).operator), exp[i]))
				{
					convExp[idx++] = (Peek(&stack).operator);
					Pop(&stack);
				}
				temp.operator = exp[i];
				Push(&stack, temp);
			}

		}
		while (!IsEmpty(&stack))
		{
			convExp[idx++] = (Peek(&stack).operator);
			Pop(&stack);
		}
		convExp[idx] = '\0';
	}



int GetPriority(char op)
{
	if (op == '*' || op == '/')
		return 2;
	else if (op == '+' || op == '-')
		return 1;
	else
		return 0;
}

bool ComparePriority(char op1, char op2)
{
	int op1_pr = GetPriority(op1);
	int op2_pr = GetPriority(op2);
	
	if (op1_pr >= op2_pr)
		return true;
	else
		return false;
}

Penta_num EvalPostfix(char* exp, int len)
{
	Stack stack;
	InitStack(&stack);
	Penta_num temp1, temp2;
	for (int i = 0; i < len; i++)
	{
		if (isdigit(exp[i]))
		{
			temp1.small = exp[i]; temp1.large = exp[i + 1];
			Push(&stack, temp1); i++;
		}
		else if (isalpha(exp[i]))
		{
			temp1.small = exp[i]; temp1.large = exp[i + 1];
			Push(&stack, temp1); i++;
		}
		else 
		{
			temp2 = Peek(&stack); Pop(&stack);
			temp1 = Peek(&stack); Pop(&stack);
			if (exp[i] == '+')
			{
				temp1 = add(temp1, temp2);
				Push(&stack, temp1);

			}
			else if (exp[i] == '-')
			{
				temp1 = subtract(temp1, temp2);
				Push(&stack, temp1);

			}
			else if (exp[i] == '*')
			{
				temp1 = multiply(temp1, temp2);
				Push(&stack, temp1);

			}
			else if (exp[i] == '/')
			{
				temp1 = division(temp1, temp2);
				Push(&stack, temp1);

			}
		}
	}
	return Peek(&stack);
}
void print_Penta_num(Penta_num result)
{
	printf("%c%c", result.small, result.large);
}


/* Modify to here */