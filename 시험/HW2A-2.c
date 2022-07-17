#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

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
	Node* newNode =
		(Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = *head;
	*head = newNode;
}
void Remove(Node* head)
{
	/* Modify from here */
	Node *ptr1, *ptr2, *tmp;
	ptr1 = head;

	while (ptr1 != NULL && ptr1->next != NULL)
	{
		ptr2 = ptr1;

		
		while (ptr2->next != NULL)
		{
			if (ptr1->data == ptr2->next->data)
			{
			
				tmp = ptr2->next;
				ptr2->next = ptr2->next->next;
				free(tmp);
			}
			else
				ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
	/* Modify to here */
}
int main()
{
	int N, list[100];
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &list[i]);
	Node* head = NULL;
	for (int i = N - 1; i >= 0; i--)
		push(&head, list[i]);
	printList(head);
	Remove(head);
	printList(head);
	return 0;
}