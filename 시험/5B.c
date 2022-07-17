#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_HEAP 100

typedef enum { false, true } bool;

typedef struct {
	char small;
	char middle;
	char large;
} Penta_num;

typedef struct {
    Penta_num data; // This is a priority as well as data
} PNode;

typedef struct {
	PNode items[MAX_HEAP + 1];
	int num;
} Heap;

void InitHeap(Heap *pheap);

bool IsEmpty(Heap *pheap);

bool IsFull(Heap *pheap);

void Insert(Heap *pheap, Penta_num data);

Penta_num Delete(Heap *pheap);

void HeapSort(Penta_num a[], int n);

Penta_num *CreatePentaNum(int n);

void GetInput();

int main() {

	GetInput();
	/*
	5
	0E0
	321
	EEE
	CCC
	3D0
	*/

	return 0;
}

void HeapSort(Penta_num a[], int n) {
	Heap heap;
	InitHeap(&heap);
	// Insert all elements to the heap.
	for (int i = 0; i < n; i++)
		Insert(&heap, a[i]);

	// Remove all elements from the heap.
	for (int i = 0; i <= n-1; i++)
		a[i] = Delete(&heap);

	for (int i = 0; i < n; i++){
		// char str[3];
		// str[0] = a[i].large;
		// str[1] = a[i].middle;
		// str[2] = a[i].small;
		// int value = strtol(str, NULL, 15);
		// printf("%c%c%c :%d \n", a[i].large, a[i].middle, a[i].small,value);
		printf("%c%c%c\n",a[i].large,a[i].middle,a[i].small);
	}
}

Penta_num *CreatePentaNum(int n){
    char a[4];
	Penta_num *res = (Penta_num*)malloc(sizeof(Penta_num)*(n));
	for (int i = 0; i < n; i++) {
        scanf("%s", a);
        res[i].large = a[0];
		res[i].middle = a[1];
		res[i].small = a[2];
	}
	return res;
}

void GetInput() {
    int n;
    Penta_num *data;
    scanf("%d", &n);
    data = CreatePentaNum(n);
	HeapSort(data, n);
}

/* Modify from here */

int GetParent(int idx) {
	return idx / 2;
}

int GetLChild(int idx) {
	return idx * 2;
}

int GetRChild(int idx) {
	return idx * 2 + 1;
}

int GetPriority(Penta_num data) {//숫자 작은게 높아야
	char *ptr;
	char temp[] = {data.large, data.middle, data.small, '\0'};

	int res = (int)strtol(temp, NULL, 15);
	return -res;
}

int GetHighPriorityChild(Heap *pheap, int idx) {
	if (GetLChild(idx) > pheap->num) return 0;
	else if (GetLChild(idx) == pheap->num) return GetLChild(idx);
	else {
		int left = GetLChild(idx), right = GetRChild(idx);
		if (GetPriority(pheap->items[left].data) > GetPriority(pheap->items[right].data)) return left;
		else return right;
	}
}

void InitHeap(Heap *pheap) {
	pheap->num = 0;
}

bool IsEmpty(Heap *pheap) {
	return pheap->num == 0;
}

bool IsFull(Heap *pheap) {
	return pheap->num == MAX_HEAP;
}

void Insert(Heap *pheap, Penta_num data) {
	PNode newNode;
	int idx = pheap->num + 1;
	int priority = GetPriority(data);
	if (IsFull(pheap)) exit(1);
	while (idx > 1) {
		int parent = GetParent(idx);
		if (priority > GetPriority((pheap->items[parent].data))) {
			pheap->items[idx] = pheap->items[parent];
			idx = parent;
		}
		else break;
	}
	newNode.data = data;

	pheap->items[idx] = newNode;
	pheap->num++;
}

Penta_num Delete(Heap *pheap) {
	Penta_num min = pheap->items[1].data;
	PNode last = pheap->items[pheap->num];
	int parent = 1, child;
	int lastP = GetPriority(last.data);
	while (child = GetHighPriorityChild(pheap, parent)) {
		if (lastP < GetPriority(pheap->items[child].data)) {
			pheap->items[parent] = pheap->items[child];
			parent = child;
		}
		else break;
	}

	pheap->items[parent] = last;
	pheap->num--;

	return min;
}

/* Modify to here */