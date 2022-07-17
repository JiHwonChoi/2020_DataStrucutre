#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
	int data;
	struct _Node* next;
}Node;

void printList(Node* head)
{
	Node* ptr = head;
	while (ptr)
	{
		printf("%d ", ptr->data);
		printf("-> ");
		ptr = ptr->next;
	}
    printf("NULL");
	printf("\n");
}

void push(Node** head, int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = *head;
	*head = newNode;
}

Node* Reserve(Node* head, int g)
{
    Node* prev = NULL;
	Node* current = head;
    Node* next = NULL;
    int count = 0;

    while (current != NULL && count < g)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }
    
    if (next != NULL)
        head->next = Reserve(next, g);

    return prev;
}

int main()
{
	int N, list[100], g;
	scanf("%d", &N);
	for(int i=0; i<N; i++)
		scanf("%d", &list[i]);

	Node* head = NULL;

    scanf("%d", &g);

	for (int i = N-1; i >= 0; i--)
		push(&head, list[i]);

	printList(head);
	head = Reserve(head, g);
	printList(head);

	return 0;
}

