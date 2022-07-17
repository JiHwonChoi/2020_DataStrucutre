#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_STACK 1000000

typedef enum{ false, true} bool; 

typedef struct expr {
	int ef;
	int cons;
	char op;
	bool isOper;
}expr;

typedef struct{
	expr items[MAX_STACK];
	int top;
} Stack;

void InitStack(Stack *pstack){
	pstack->top = -1;
}

bool IsFull(Stack *pstack){
	return pstack->top == MAX_STACK-1;
}
bool IsEmpty(Stack *pstack){
	return pstack->top == -1;
}

expr Peek(Stack *pstack){
	if(IsEmpty(pstack)){
		exit(1);
	}
	return pstack->items[pstack->top];
}

void Push(Stack *pstack, expr item){
	if(IsFull(pstack)){
		exit(1); //error: stack full
	}
	pstack->items[++(pstack->top)] = item;
}

void Pop(Stack *pstack){
	if(IsEmpty(pstack))
		exit(1);
	--(pstack->top);
}

expr evaluate(expr num1, expr num2, char op,int M) {
	expr ret;
	ret.isOper = false;
	if (op == '+') {
		ret.ef = (num1.ef + num2.ef)%M;
		ret.cons = (num1.cons + num2.cons)%M;
		return ret;
	}
	else if (op == '-') {
		ret.ef = (num1.ef - num2.ef+M)%M;
		ret.cons = (num1.cons - num2.cons+M)%M;
		return ret;
	}
	else if (op == '*') {
		ret.ef = (num1.ef * num2.cons + num1.cons * num2.ef)%M;
		ret.cons = (num1.cons * num2.cons)%M;
		return ret;
	}

}

int main() {
	char A[100001];
	expr postfix[100001];
	expr num1,num2,temp;
	int P,M,ef,cons;
	int len,i,post_idx=0,number=0;
	Stack *s = (Stack*)malloc(sizeof(Stack));
	Stack *result = (Stack*)malloc(sizeof(Stack));
	
	scanf("%s",A);
	scanf("%d %d",&P,&M);

	InitStack(s);
	InitStack(result);
	len = strlen(A);

	for (i = 0; i <len ; i++) {
		temp.op = '0';
		temp.isOper = false;
		if (A[i] == 'x') {
			temp.ef = 1;
			temp.cons = 0;
			postfix[post_idx++]=temp;
		}
		else if (isdigit(A[i])) {
			while(isdigit(A[i])){
				number *= 10;
				number += A[i] - '0';
                number %=M;
				i++;
			}
			i--;
			temp.ef = 0;
			temp.cons = number;
			postfix[post_idx++]=temp;
			number = 0;
		}
		else {
			if (A[i] == '(') {
				temp.isOper = true;
				temp.op = '(';
				Push(s,temp);
			}
			else if (A[i] == ')') {
				while (Peek(s).op != '(') {
					postfix[post_idx++]=Peek(s);
					Pop(s);
				}
				Pop(s);
			}
			else if (A[i] == '*') {
				temp.isOper = true;
				temp.op = A[i];
				Push(s,temp);
			}
			else {
				while (!IsEmpty(s) && Peek(s).op != '(') {
					postfix[post_idx++]=Peek(s);
					Pop(s);
				}
				temp.op = A[i];
				temp.isOper = true;
				Push(s,temp);
			}
		}
	}
	 while(!IsEmpty(s)){
		 postfix[post_idx++]=Peek(s);
		 Pop(s);
	 }

	for (i = 0; i < post_idx; i++) {
		if (!postfix[i].isOper) {
			Push(result,postfix[i]);
		}else {
			num2 = Peek(result); Pop(result);
			num1 = Peek(result); Pop(result);
			temp = evaluate(num1,num2,postfix[i].op,M);
			Push(result,temp);
		}
	}

	ef = Peek(result).ef;
	cons = Peek(result).cons;

	for (i = 0; i < M; i++) {
		if ((ef * i + cons) % M == P) {
			printf("%d\n",i);
			break;
		}
	}

}