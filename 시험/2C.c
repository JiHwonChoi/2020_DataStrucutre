#include <stdio.h> 
#include <stdlib.h>

typedef struct _Node 
{ 
	int coef;
	int exp;
	struct _Node* next; 
}Node;

typedef struct
{
	Node* tail;
	int len;
}Polynomial;

void printPoly(Polynomial* poly) 
{
	Node* ptr = poly->tail;
	int i;
	for (i = 0; i < poly->len; i++)
	{
		ptr = ptr->next; 
		if(i == 0)
			printf("%dx^%d", ptr->coef, ptr->exp);
		else if(ptr->coef > 0)
			printf("+%dx^%d", ptr->coef, ptr->exp);
		else if(ptr->coef < 0)
			printf("%dx^%d", ptr->coef, ptr->exp);
	}
	printf("\n");
}

void InsertInitItem(Polynomial* poly, int coef, int exp)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->coef = coef;
	newNode->exp = exp;
	newNode->next = newNode;

	poly->tail = newNode;
	poly->len++;
}

void InsertFirst(Polynomial* poly, int coef, int exp) 
{ 
	if (poly->len == 0)
		InsertInitItem(poly, coef, exp);
	else
	{
		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->coef = coef;
		newNode->exp = exp;
		newNode->next = poly->tail->next;
		
		poly->tail->next = newNode;
		poly->len++;
	}
}

void InsertLast(Polynomial* poly, int coef, int exp)
{
	if (poly->len == 0)
		InsertInitItem(poly, coef, exp);
	else
	{
		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->coef = coef;
		newNode->exp = exp;
		newNode->next = poly->tail->next;

		poly->tail->next = newNode;
		poly->tail = newNode;
		poly->len++;
	}
}

void PolyToList(Polynomial* poly, char* list)
{
	int i = 0;
	int coef, exp;

	while (list[i])
	{
		coef = 0;
		exp = 0;
		if (list[i] == '-')
		{
			i++;
			while (list[i] != 'x')
			{
				coef = coef * 10;
				coef += list[i] - '0';
				i++;
			}
			coef = coef * -1;
		}
		else
		{
			if (list[i] == '+')
				i++;
			while (list[i] != 'x')
			{
				coef = coef * 10;
				coef += list[i] - '0';
				i++;
			}
		}
		i++;
		i++;
		exp = list[i++] - '0';
		InsertLast(poly, coef, exp);
	}
}

void printAddingPoly(Polynomial* poly1, Polynomial* poly2)
{
	Polynomial result;
	int len1, len2;
	Node* node1 = (Node*)malloc(sizeof(Node));
	Node* node2 = (Node*)malloc(sizeof(Node));
	Node* renode = (Node*)malloc(sizeof(Node));

	result.len = 0;
	len1 = poly1->len;
	len2 = poly2->len;
	node1 = poly1->tail->next;
	node2 = poly2->tail->next;

	while (len1 != 0 || len2 != 0)
	{
		if (len1 == 0)
		{
			InsertLast(&result, node2->coef, node2->exp);
			node2 = node2->next;
			len2--;
		}
		else if (len2 == 0)
		{
			InsertLast(&result, node1->coef, node1->exp);
			node1 = node1->next;
			len1--;
		}
		else if (node1->exp == node2->exp)
		{
			renode->coef = node1->coef + node2->coef;
			renode->exp = node1->exp;
			if(renode->coef != 0)
				InsertLast(&result, renode->coef, renode->exp);
			node1 = node1->next;
			node2 = node2->next;
			len1--;
			len2--;
		}
		else if (node1->exp > node2->exp)
		{
			InsertLast(&result, node1->coef, node1->exp);
			node1 = node1->next;
			len1--;
		}
		else if (node1->exp < node2->exp)
		{
			InsertLast(&result, node2->coef, node2->exp);
			node2 = node2->next;
			len2--;
		}
	}
	printPoly(&result);
}

int main() 
{
	char arr1[100];
	char arr2[100];
	Polynomial poly1;
	Polynomial poly2;
	poly1.len = 0;
	poly2.len = 0;

	scanf("%s", arr1);
	scanf("%s", arr2);

	PolyToList(&poly1, arr1);
	PolyToList(&poly2, arr2);
	printAddingPoly(&poly1, &poly2);

	return 0;
}