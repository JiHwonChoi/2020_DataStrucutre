
#include <stdio.h> 
#include <stdlib.h> 

typedef struct node {
	int data;
	struct node *left, *right;
}node;


struct node* newNode(int item)
{
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}

void leftViewUtil(struct node* root, int level, int* max_level)
{
	// Base Case 
	if (root == NULL)
		return;

	// If this is the first node of its level 
	if (*max_level < level) {
		printf("%d ", root->data);
		*max_level = level;
	}

	// Recur for left and right subtrees 
	leftViewUtil(root->left, level + 1, max_level);
	leftViewUtil(root->right, level + 1, max_level);
}

// A wrapper over leftViewUtil() 
void leftView(struct node* root)
{
	int max_level = 1;
	leftViewUtil(root, 1, &max_level);
}

void rightViewUtil(struct node* root, int level, int* max_level)
{
	// Base Case 
	if (root == NULL)
		return;

	// If this is the first node of its level 
	if (*max_level < level) {
		printf("%d ", root->data);
		*max_level = level;
	}

	// Recur for left and right subtrees 
	rightViewUtil(root->right, level + 1, max_level);
	rightViewUtil(root->left, level + 1, max_level);
}

// A wrapper over leftViewUtil() 
void rightView(struct node* root)
{
	int max_level = 1;
	rightViewUtil(root, 1, &max_level);
}

struct node* insertLevelOrder(int arr[], node* root,
	int i, int n)
{
	// Base case for recursion 
	if (i < n)
	{
		if (arr[i] == 120)
			return NULL;
		node* temp = newNode(arr[i]);
		root = temp;

		// insert left child 
		root->left = insertLevelOrder(arr,
			root->left, 2 * i + 1, n);

		// insert right child 
		root->right = insertLevelOrder(arr,
			root->right, 2 * i + 2, n);
	}
	return root;
}
int intonumber(char*str)
{
	int j = 0,temp=0;
	while (str[j] != NULL)
	{
		if (str[j] == 'x')
		{
			return 120;
		}
		temp *= 10;
		temp += str[j] - '0';
		j++;

	}
	return temp;
}
 
int main()
{
	int arr[31];
	int i, num;
	scanf("%d", &num);
	char str[1000];
	struct node *NodeArr = (struct node*) malloc(sizeof(struct node) * 31);
	for (i = 0; i < num; i++)
	{
		scanf("%s", str);
		arr[i] = intonumber(str);
	}
	node * root = NULL;
	root = insertLevelOrder(arr, root, 0, num);

	/*
	for (i = 1; i < num; i++)
	{
		if (NodeArr[i].data != 120)
		{
			//left sub tree 에 연결해야 할 때
			if (i % 2 == 0)
			{
				CreateLeftSubtree(&NodeArr[i / 2], &NodeArr[i]);
			}
			else
				CreateRightSubtree(&NodeArr[i / 2], &NodeArr[i]);
		}
	}
	*/
	
	struct node* root2 = root;

	leftView(root);
	printf("\n");
	rightView(root2);

	return 0;
}