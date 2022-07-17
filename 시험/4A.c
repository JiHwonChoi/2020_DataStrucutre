#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int Power(int n)
{
	int i, result = 1;
	for (i = 0; i < n; i++)
		result *= 2;
	return result;
}

void InputTree(char* arr, int* tree)
{
	int i = 0, j = 0, num;

	while (arr[i] != '\0')
	{
		if (arr[i] == 'x')
		{
			tree[j++] = -1;
			i++;
		}
		else if ('0' <= arr[i] && arr[i] <= '9')
		{
			num = 0;
			while ('0' <= arr[i] && arr[i] <= '9')
			{
				num = 10 * num + arr[i] - '0';
				i++;
			}
			tree[j++] = num;
		}
		else
			i++;
	}
}

void PrintLeftmost(int* tree, int len)
{
	int i, j, n = len, level = 0, *leftmost;

	while (n != 0)
	{
		n = n / 2;
		level++;
	}
	leftmost = (int*)calloc(level, sizeof(int));
	for (i = 1; i < level; i++)
	{
		for (j = Power(i) - 1; j < Power(i + 1) - 1; j++)
		{
			if (tree[j] == -1)
				continue;
			else
			{
				leftmost[i - 1] = tree[j];
				break;
			}
		}
	}
	for (i = 0; i < level - 1; i++)
		printf("%d ", leftmost[i]);
	printf("\n");
}

void PrintRightmost(int* tree, int len)
{
	int i, j, n = len, level = 0, * rightmost;

	while (n != 0)
	{
		n = n / 2;
		level++;
	}
	rightmost = (int*)calloc(level, sizeof(int));
	for (i = 1; i < level; i++)
	{
		for (j = Power(i + 1) - 2; j > Power(i) - 2; j--)
		{
			if (tree[j] == -1)
				continue;
			else
			{
				rightmost[i - 1] = tree[j];
				break;
			}
		}
	}
	for (i = 0; i < level - 1; i++)
		printf("%d ", rightmost[i]);
	printf("\n");
}

int main(void)
{
	int i, num, len;
	char input[200] = { 0 };
	int tree[100];

	for (i = 0; i < 100; i++)
		tree[i] = -1;

	scanf("%d ", &len);
	fgets(input, sizeof(input), stdin);
	InputTree(input, tree);
	PrintLeftmost(tree, len);
	PrintRightmost(tree, len);
}