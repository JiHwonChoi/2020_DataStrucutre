#include <stdio.h>q
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable: 4996)

typedef int Data;
#define MAX_SIZE 100
#define MAX_STRING 100

typedef enum {false , true} bool;

/* ------------------ Queue ---------------*/
typedef struct {
	int front, rear;
	Data items[MAX_SIZE];
} Queue;

void InitQueue(Queue* pqueue) {
	pqueue->front = pqueue->rear = 0;
}

int IsFull(Queue* pqueue) {
	return pqueue->front == (pqueue->rear + 1) % MAX_SIZE;
}

int IsEmpty(Queue * pqueue) {
	return pqueue->front == pqueue->rear;
}
Data Peek(Queue * pqueue) {
	if (IsEmpty(pqueue))
        exit(1);
	return pqueue->items[pqueue->front];
}

void EnQueue(Queue * pqueue, Data item) {
	if (IsFull(pqueue))
		exit(1);
	pqueue->items[pqueue->rear] = item;
	pqueue->rear = (pqueue->rear + 1) % MAX_SIZE;
}

Data DeQueue(Queue * pqueue) {
	if (IsEmpty(pqueue))
		exit(1);
	int item = pqueue->items[pqueue->front];
	pqueue->front = (pqueue->front + 1) % MAX_SIZE;
	return item;
}
/* ------------------ STACK ---------------*/
typedef struct {
	Data items[MAX_SIZE];
	Data count[MAX_SIZE];
	int top;

}Stack;

void Init(Stack * pstack) {
	for (int i = 0; i < MAX_SIZE; i++) {
		pstack->count[i] =0;
	}
	pstack->top = -1;
}

int IsEmptyStack(Stack * pstack) {
	return (pstack->top == -1);
}

int IsFullStack(Stack * pstack) {
	return (pstack->top == (MAX_SIZE - 1));
}

void Push(Stack * pstack, Data item) {
	if (IsFullStack(pstack))
        exit(1);
    pstack->items[++(pstack->top)] = item;
}

void Push2(Stack * pstack, Data item) {
	if (IsFullStack(pstack))
        exit(1);
    pstack->items[++(pstack->top)] = item;
    pstack->count[(pstack->top)] ++;
}


Data PeekStack(Stack * pstack) {
	if (IsEmptyStack(pstack))
        exit(1);
    return pstack->items[(pstack->top)];
}

Data Pop(Stack * pstack) {
	if (IsEmptyStack(pstack))
        exit(1);
    return pstack->items[(pstack->top)--];
}

int search_stack(Stack * pstack, char in_str) {
	int i, len;
	char ch = in_str;
	char chs;
	int top = pstack->top;

	if (IsEmptyStack(pstack))
		return false;
	else {
		for (i = 0; i < (pstack->top) + 1; i++) {
			if (pstack->items[i] == ch) {
				pstack->top = top;
				pstack->count[i]++;
				return true;
			}
		}
		return false;
	}
}

void make_palindrome(Stack * s1, Stack * fs, Queue * pqueue) {
	char center = 'c';
	int flag = 0;
	for (int i = 0; i < (s1->top) + 1; i++) {
        if ((s1->count[i])%2 == 1 && flag!=1) {
			flag = 1;
			center = s1->items[i];
		}
		
        for (int j = 0; j < (s1->count[i]) / 2; j++) {
            Push(fs, s1->items[i]);
            EnQueue(pqueue, s1->items[i]);
        }
		
	}
    
	while (IsEmptyStack(fs) == false) {
		printf("%c", Pop(fs));
	}
	if (flag == 1)
		printf("%c", center);

	while (IsEmpty(pqueue) == false) {
		printf("%c", DeQueue(pqueue));
	}
    printf("\n");
}

void count_characters(char in_str[]) {
	Stack s1;
	Stack fs;
	Queue q;

	Init(&s1);
	Init(&fs);
	InitQueue(&q);

	int check;
	int i;
	char ch;
	int count_noMatch = 0;
	int len = strlen(in_str);
	ch = in_str[0];
    
	if (IsEmptyStack(&s1)) {
		Push2(&s1, ch);
	}
	for (i = 1; i < len; i++) {
		ch = in_str[i];
		check = search_stack(&s1, ch);
		if (check == 0) { //스택안에 해당 문자열이  없으면
			Push2(&s1, ch);
		}
	}
	make_palindrome(&s1, &fs, &q);
}

int main() {
	char str[MAX_STRING];
    scanf("%s",str);
	count_characters(str);
}
