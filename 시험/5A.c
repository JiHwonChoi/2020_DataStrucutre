#include <stdio.h>
#include <stdlib.h>

typedef enum {false,true} bool; // 0 == false, 1 == true;

typedef int BData;
typedef struct _bTreeNode
{
    BData item;
    struct _bTreeNode * left_child;
    struct _bTreeNode * right_child;
    bool isTheaded;
} BTreeNode;


BTreeNode *CreateNode(BData item);
void DestroyNode(BTreeNode *node);
void CreateLeftSubtree(BTreeNode *root, BTreeNode *left);
void CreateRightSubtree(BTreeNode *root, BTreeNode *right);
BTreeNode * leftMost(BTreeNode* node);
void inorder(BTreeNode* node);
void Tester();

int main() {
    Tester();
}

void Tester() {
    int n, m, root, child;
    char type;
    BTreeNode **Array;
    BTreeNode *Root = NULL;

    scanf("%d", &n);
    Array = (BTreeNode**)malloc(sizeof(BTreeNode*)*n);
    for (int i = 0; i < n; i++)
        Array[i] = CreateNode(i + 1);

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        while(getchar()!='\n'); // = fflush(stdin) = __fpurge(stdin)
        scanf("%c %d %d", &type, &root, &child);
        if(Root==NULL)
            Root = Array[root-1];
        if (type == 'l') CreateLeftSubtree(Array[root - 1], Array[child - 1]);
        else if (type == 'r') CreateRightSubtree(Array[root - 1], Array[child - 1]);
        else exit(1);
    }
    inorder(Root);

    for (int i = 0; i < n; i++)
        DestroyNode(Array[i]);

    free(Array);
}

BTreeNode *CreateNode(BData item){
    BTreeNode *node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->left_child = NULL;
    node->right_child = NULL;
    node->isTheaded = false;
    node->item = item;
    return node;
}

void DestroyNode(BTreeNode *node){
    free(node);
}

void CreateLeftSubtree(BTreeNode *root, BTreeNode *left){
    if(root->left_child !=NULL)
        exit(1);
    else {
        root->left_child = left;
        if(left->right_child==NULL){
           left->isTheaded = true;
           left->right_child = root;
        }

    }
}

void CreateRightSubtree(BTreeNode *root, BTreeNode *right){
    if(root->right_child !=NULL) {
        if(root->isTheaded){
            right->isTheaded = true;
            right->right_child = root->right_child;
            root->right_child = right;
            root->isTheaded=false;
        }else
            exit(1);
    }else {
        root->right_child = right;
    }
}




void inorder(BTreeNode* node){
    BTreeNode* cur = leftMost(node);
    printf("left most:%d\n",cur->item);
    while (cur != NULL) {
        printf("%d ", cur->item);
        // If the node is a thread node, go to its inorder successor.
        if (cur->isTheaded)
            cur = cur->right_child;
        else // Go to the leftmost child in a right subtree.
            cur = leftMost(cur->right_child);
    }
}
BTreeNode* leftMost(BTreeNode* node) {
    if (node == NULL)
        return NULL;
    while (node->left_child != NULL)
        node = node->left_child; // Go to the leftmost node. return node;
   return node;
}