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

void sort(char*str, int len);
bool Compare(Queue*pqueue);
bool isalpha(char n);


void main()
{
	int DEQlen=0;
	char str[100];
	Deque deq,DEQ,DEQ2;
	char mid ='\0';
	char*pmid = &mid;
	InitQueue(&deq); InitQueue(&DEQ); InitQueue(&DEQ2);

	
	scanf("%s", str);
	if (str == '\0')
		exit(1);
	int len = strlen(str);

	sort(str, len);
	
	for (int i = 0; i < len; i++)
		AddRear(&deq, str[i]);
	deq.items[len] = '\0';

	for (int i = 0; i < len; i++)
	{
		if (Compare(&deq))
		{
			AddRear(&DEQ, Peek(&deq));
			RemoveFront(&deq);
			RemoveFront(&deq);
			i++;
			DEQlen++;
		}
		else
		{
			*pmid = Peek(&deq);
			RemoveFront(&deq);
		}
	}
	DEQ.items[DEQlen] = '\0';
	DEQ2 = DEQ;

	char result[100] = { 0, };

	for (int i = 0; i < DEQlen; i++)
	{
		result[i] = PeekFront(&DEQ);
		RemoveFront(&DEQ);
	}

	if (isalpha(mid))
	{
		result[DEQlen] = mid;
		for (int i = DEQlen + 1; i < DEQlen*2+1; i++)
		{
			result[i] = PeekRear(&DEQ2);
			RemoveRear(&DEQ2);
		}
	}
	else
	{
		for (int i = DEQlen; i < DEQlen*2; i++)
		{
			result[i] = PeekRear(&DEQ2);
			RemoveRear(&DEQ2);
		}
	}

	printf("%s", result);




}

bool isalpha(char n)
{
	if ((65 <= n))
		return true;
	else
		return false;
}

bool Compare(Queue*pqueue)
{
	if (pqueue->items[pqueue->front] == pqueue->items[pqueue->front + 1])
		return true;
	else return false;
}

void sort(char*str, int len)
{
	for (int i = 1; i < len; i++) {
		int target = str[i];  // 기준
		int cur = i - 1;   // 비교할 대상
		while (cur >= 0 && target < str[cur]) {
			str[cur + 1] = str[cur];   // 비교대상이 큰 경우 오른쪽으로 밀어냄
			cur--;
		}
		str[cur + 1] = target;  // 기준값 저장
	}
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
