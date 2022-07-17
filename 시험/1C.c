#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK 100

typedef enum {false , true} bool;

typedef struct {
    char small;
    char large;

    // *Variable "operator" only used in ConvInfixToPostfix function
    char operator;
}Penta_num;

typedef struct {
    Penta_num items[MAX_STACK];
    int top;
}Stack;

Penta_num add(Penta_num b1,Penta_num b2);
Penta_num subtract(Penta_num b1,Penta_num b2);
Penta_num multiply(Penta_num b1,Penta_num b2);
Penta_num division(Penta_num b1,Penta_num b2);

void InitStack (Stack *pstack);
bool IsFull(Stack *pstack);
bool IsEmpty(Stack *pstack);
Penta_num Peek(Stack *pstack);
void Push(Stack *pstack,Penta_num item);
void Pop(Stack *pstack);

void ConvInfixToPostfix(char* exp,char* convExp, int len);
Penta_num EvalPostfix(char* exp,int len);
void print_Penta_num(Penta_num result);


int main() {
    char infix_exp[100];
    char postfix_exp[100];
    Penta_num result;

    scanf("%s",infix_exp);
    ConvInfixToPostfix(infix_exp,postfix_exp,strlen(infix_exp));
    printf("%s\n%s\n",infix_exp,postfix_exp);
    result = EvalPostfix(postfix_exp,strlen(postfix_exp));
    print_Penta_num(result);
    return 0;
}

void InitStack(Stack *pstack){
    pstack->top=-1;
}

bool IsFull(Stack *pstack){
    return pstack->top == MAX_STACK -1;
}

bool IsEmpty(Stack *pstack){
    return pstack->top == -1;
}

Penta_num Peek(Stack *pstack){
    if(IsEmpty(pstack))
        exit(1);
    return pstack->items[pstack->top];
}

void Push(Stack *pstack, Penta_num item){
    if(IsFull(pstack))
        exit(1);
    pstack->items[++(pstack->top)] = item;
}

void Pop(Stack *pstack){
    if(IsEmpty(pstack))
        exit(1);
    --(pstack->top);
}


bool isdigit(char value){
    if(value=='+' || value == '-' || value == '*' || value == '/')
        return false;
    else
        return true;
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



void ConvInfixToPostfix(char* exp, char* convExp, int len)
{
    Stack stack;
    int idx = 0;
    InitStack(&stack);
    
    //For push operator value
    //op only contains operator
    Penta_num op;

    for (int i = 0; i < len; i++)
    {
        if (isdigit(exp[i]))
            convExp[idx++] = exp[i]; // Print an operand.
        else {
            //If current values is operator,
            while (!IsEmpty(&stack) && ComparePriority(Peek(&stack).operator, exp[i])) {
                convExp[idx++] = Peek(&stack).operator; // Print an operator.
                Pop(&stack); // Pop an operator.
            }
            op.operator = exp[i]; //Set operator value in Penta_num form
            Push(&stack, op); // Push an operator.
        }
    }
    while (!IsEmpty(&stack)) {
        convExp[idx++] = Peek(&stack).operator; // Print an operator.
        Pop(&stack); // Pop an operator.
    }
    convExp[idx]='\0';//Add string end value
}

Penta_num ConvInttoPenta(int N){
    Penta_num ret;
    if(N%15<=9)
        ret.small=N%15+'0';
    else
        ret.small=N%15+'A'-10;

    N/=15;

    if(N%15<=9)
        ret.large=N%15+'0';
    else
        ret.large=N%15+'A'-10;

    return ret;
}
int ConvPentatoInt(Penta_num val){
    int ret=0;
    if(val.small>='A')
        ret+=val.small-'A'+10;
    else
        ret+=val.small-'0';

    if(val.large>='A')
        ret+=(val.large-'A'+10)*15;
    else
        ret+=(val.large-'0')*15;
    return ret;
}

Penta_num add(Penta_num b1,Penta_num b2){
    int val1=ConvPentatoInt(b1);
    int val2=ConvPentatoInt(b2);
    return ConvInttoPenta(val1+val2);
}

Penta_num subtract(Penta_num b1,Penta_num b2){
    int val1=ConvPentatoInt(b1);
    int val2=ConvPentatoInt(b2);
    return ConvInttoPenta(val1-val2);
}

Penta_num multiply(Penta_num b1,Penta_num b2){
    int val1=ConvPentatoInt(b1);
    int val2=ConvPentatoInt(b2);
    return ConvInttoPenta(val1*val2);
}
Penta_num division(Penta_num b1,Penta_num b2){
    int val1=ConvPentatoInt(b1);
    int val2=ConvPentatoInt(b2);
    return ConvInttoPenta(val1/val2);
}


Penta_num EvalPostfix(char* exp, int len)
{
    Stack stack;
    Penta_num op1, op2;
    Penta_num operand;
    InitStack(&stack);
    for (int i = 0; i < len; i++) {
        if (isdigit(exp[i])) {
            // Push an operand.
            operand.large=exp[i];
            operand.small=exp[++i];
            Push(&stack, operand);
        }else {
            // Evaluate an operator.
            op2 = Peek(&stack); Pop(&stack);
            op1 = Peek(&stack); Pop(&stack);
            if (exp[i] == '+')
                Push(&stack,add(op1,op2));
            else if (exp[i] == '-')
                Push(&stack,subtract(op1,op2));
            else if (exp[i] == '*')
                Push(&stack,multiply(op1,op2));
            else if (exp[i] == '/')
                Push(&stack,division(op1,op2));
        }
    }
    return Peek(&stack);
}

void print_Penta_num(Penta_num result){
    printf("%c%c\n",result.large,result.small);
}
