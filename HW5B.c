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
	PNode items[MAX_HEAP
		+ 1];
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
	for (int i = 0; i <= n - 1; i++)
		a[i] = Delete(&heap);
	for (int i = 0; i < n; i++)
		printf("%c%c%c\n", a[i].large, a[i].middle, a[i].small);
}
Penta_num *CreatePentaNum(int n) {
	char a[4];
	Penta_num *res =
		(Penta_num*)malloc(sizeof(Penta_num)*(n));
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
int GetParent(int idx)
{
	return idx / 2;
}

int GetLchild(int idx)
{
	return idx * 2;
}

int GetRchild(int idx)
{
	return idx * 2 + 1;
}

void InitHeap(Heap *pheap)
{
	pheap->num = 0;
}
bool IsEmpty(Heap *pheap)
{
	return pheap->num == 0;
}
bool IsFull(Heap *pheap)
{
	return pheap->num == MAX_HEAP;
}
bool compareAB(Penta_num pentaA, Penta_num pentaB)
{
	
	if (pentaA.large < pentaB.large)
		return true;

	else if(pentaA.large == pentaB.large)
	{
		if (pentaA.middle < pentaB.middle)
			return true;
		else if (pentaA.middle == pentaB.middle)
		{
			if (pentaA.small < pentaB.small)
				return true;
			else return false;
		}
		else return false;
	}

	else return false;
}

void Insert(Heap *pheap, Penta_num data)
{
	PNode newNode;
	int idx = pheap->num + 1;
	if (IsFull(pheap)) exit(1);
	while (idx > 1)
	{
		int parent = GetParent(idx);
		if (compareAB(data, pheap->items[parent].data))//펜타수 데이터끼리 비교하는 함수가 필요함 지금은 자료형이라서 안됨
			// if( 인풋의 data가 parent idx 의 data 보다 크다면
		{
			pheap->items[idx] = pheap->items[parent];
			idx = parent;
		}
		else break;
	}
	newNode.data = data;

	pheap->items[idx] = newNode;
	pheap->num++;
}

int GetHighPriorityChild(Heap*pheap, int idx)
{
	if (GetLchild(idx) > pheap->num)
		return 0;
	else if (GetLchild(idx) == pheap->num)
		return GetLchild(idx);
	else
	{
		int left = GetLchild(idx), right = GetRchild(idx);
		if (compareAB(pheap->items[left].data, pheap->items[right].data))
			return left;
		else return right;
	}
}


Penta_num Delete(Heap *pheap)
{
	Penta_num min = pheap->items[1].data;
	PNode last = pheap->items[pheap->num];
	int parent = 1, child;
	while (child = GetHighPriorityChild(pheap, parent))
	{
		if (!(compareAB(last.data, pheap->items[child].data)))
		{
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