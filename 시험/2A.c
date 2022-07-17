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

void Remove(Node* head)
{
	Node* current = head;
	Node* tmp = current;
	if (current == NULL) return;
	int data = current->data;
	while(current->next!=NULL){
		if(data == current->next->data){
			Node* nextNext = current->next->next;
			free(current->next);
			current->next = nextNext;
		}
		else{
			current = current->next;
		}
	}
	Remove(tmp->next);
}

int main()
{
	int N, list[100];
	scanf("%d", &N);
	for(int i=0; i<N; i++)
		scanf("%d", &list[i]);

	Node* head = NULL;

	for (int i = N-1; i >= 0; i--)
		push(&head, list[i]);

	printList(head);
	Remove(head);
	printList(head);

	return 0;
}

