#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef int Data;
#define MAX_STACK 100
#define MAX_STRING 100

typedef enum {false, true} bool;

typedef struct {
	Data items[MAX_STACK];
	int top;
}Stack;

void InitStack(Stack* pstack) {
	pstack->top = -1;
}

bool IsEmpty(Stack* pstack) {
	return (pstack->top == -1);
}

bool IsFull(Stack * pstack) {
	return (pstack->top == (MAX_STACK - 1));
}

void Push(Stack * pstack, Data item) {
	if (IsFull(pstack))
        exit(1);
    pstack->items[++(pstack->top)] = item;
}

Data Peek(Stack * pstack) {
	if (IsEmpty(pstack))
        exit(1);
    return pstack->items[(pstack->top)];

}

Data Pop(Stack * pstack) {
	if (IsEmpty(pstack))
        exit(1);
    return pstack->items[(pstack->top)--];
}

int palidrome(char in_str[]) {
	Stack pstack;
	int i;
	char ch, chs;
	int count_noMatch = 0;
	int len = strlen(in_str);
	InitStack(&pstack);

	for (i = 0; i < len; i++) {
		ch = in_str[i];
		ch = toupper(ch);
		Push(&pstack, ch);
	}

	for (i = 0; i < len; i++) {
		ch = in_str[i];
		ch = toupper(ch);
		chs = Pop(&pstack);
		if (ch != chs)
			count_noMatch++;
	}
	return count_noMatch;

}


int main() {
	Stack pstack;
	char str[MAX_STRING];
	int check = 0;

    scanf("%s",str);
	check = palidrome(str);
	printf("%d \n",check);
}
