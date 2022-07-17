#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_QUEUE 100
#pragma warning(disable: 4996)
typedef enum { false, true } bool;
typedef char Data;
typedef struct {
	int front, rear;
	Data items[MAX_QUEUE];
}Queue;

typedef Queue Deque;


void InitQueue(Queue*pqueue);
bool IsFull(Queue*pqueue);
bool IsEmpty(Queue*pqueue);
Data Peek(Queue*pqueue);
void EnQueue(Queue*pqueue, Data item);
void DeQueue(Queue*pqueue);

void AddFront(Queue*pqueue, Data item);
void AddRear(Queue*pqueue, Data item);
void RemoveFront(Queue*pqueue);
void RemoveRear(Queue*pqueue);
Data PeekFront(Queue*pqueue);
Data PeekRear(Queue*pqueue);

int checkPalindrome(char*str, int len);

void main()
{
	int result;
	char str[100];
	scanf("%s", str);

	result = checkPalindrome(str, strlen(str));

	printf("%d", strlen(str)-result-1);

}

int checkPalindrome(char*str, int len)
{
	Deque deq;
	InitQueue(&deq);
	int count = 0;
	
	for (int i = 0; i < len; i++)
		AddRear(&deq, str[i]);
	deq.items[len] = '\0';

	while (len > 1)
	{
		if (PeekFront(&deq) == PeekRear(&deq))
		{
			RemoveFront(&deq), RemoveRear(&deq);
			len -= 2;
			count += 2;

		}
		else return count;
	}
	return count;
}


void InitQueue(Queue*pqueue)
{
	pqueue->front = pqueue->rear = 0;
}

bool IsFull(Queue*pqueue)
{
	return pqueue->front == (pqueue->rear + 1);
}

bool IsEmpty(Queue*pqueue)
{
	return pqueue->front == pqueue->rear;
}

Data Peek(Queue*pqueue)
{
	if (IsEmpty(pqueue))
		exit(1);
	return pqueue->items[pqueue->front];
}

void EnQueue(Queue*pqueue, Data item)
{
	if (IsFull(pqueue))
		exit(1);
	pqueue->items[pqueue->rear] = item;
	pqueue->rear = (pqueue->rear + 1);
}

void DeQueue(Queue*pqueue)
{
	if (IsEmpty(pqueue))
		exit(1);
	pqueue->front = (pqueue->front + 1);
}

void AddFront(Queue*pqueue, Data item)
{
	if (IsFull(pqueue))
		exit(1);
	pqueue->items[pqueue->front] = item;
	pqueue->front = (pqueue->front - 1);
}
void AddRear(Queue*pqueue, Data item)
{
	if (IsFull(pqueue))
		exit(1);
	pqueue->items[pqueue->rear] = item;
	pqueue->rear = (pqueue->rear + 1);
}
void RemoveFront(Queue*pqueue)
{
	if (IsEmpty(pqueue))
		exit(1);
	pqueue->front = (pqueue->front + 1);
}
void RemoveRear(Queue*pqueue)
{
	if (IsEmpty(pqueue))
		exit(1);
	pqueue->rear = (pqueue->rear - 1);
}
Data PeekFront(Queue*pqueue)
{
	if (IsEmpty(pqueue))
		exit(1);
	return pqueue->items[pqueue->front];
}
Data PeekRear(Queue*pqueue)
{
	if (IsEmpty(pqueue))
		exit(1);
	return pqueue->items[(pqueue->rear)-1];
}
