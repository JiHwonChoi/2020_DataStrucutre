#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int N=0, val=0, pivot=0;
typedef enum {false, true} bool;
bool Select[30];

void swap(int *a, int *b)
{
    int tmp = 0;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort(int *arr, int N)
{
	for (int i=0; i< N; i++)
	{
		for ( int j=i+1; j < N; j++)
		{
			if(arr[i] < arr[j])
			{
				swap(arr+i, arr+j);
			}
		}
	}
}

void Print(int* arr)
{	
	int sum = 0, front = 0, rear = N-1;
	int *tmp = (int*)malloc(sizeof(int)*N);

    for (int i = 0; i < N; i++)
    {
        if (Select[i] == true)
        {
			sum += arr[i];
        }
		tmp[i] = arr[i];
    }
	if(sum == val)
	{
		for (int i = 0; i < N; i++)
		{
			if (Select[i] == true)
			{	
				arr[rear] = tmp[i];
				rear--;
			}
			else
			{
				arr[front] = tmp[i];
				front++;
			}
		}
		pivot=1;
	}
}
 
void DFS(int Idx, int Cnt, int* arr, int n)
{
	if (pivot == 1)
		return;

    if (Cnt == n)
    {
        Print(arr);
        return;
    }
 
    for (int i = Idx; i < N; i++)
    {
        if (Select[i] == true) continue;
        Select[i] = true;
        DFS(i, Cnt + 1, arr, n);
        Select[i] = false;
    }
}

bool checkMaxHeap(int *arr, int i)
{
	if (2*i + 2 > N)
		return true;

	bool left = (arr[i] >= arr[2*i +1]) && checkMaxHeap(arr, 2*i +1);

	bool right = (2*i + 2==N) || (arr[i] >= arr[2*i +2] && checkMaxHeap(arr, 2*i + 2));

	return left && right;
}

void preOrder(int *arr, int i)
{
	if (i>= N)
		return;

	printf("%d ", arr[i]);
	preOrder(arr, 2*i+1);
	preOrder(arr, 2*i+2);
}

int main()
{
    scanf("%d", &N);
 
    int *arr = (int*)malloc(sizeof(int)*N);
    int *heap = (int*)malloc(sizeof(int)*N);
    int h = log2(N);
    int p = N - pow(2, h) + 1;
    int m = pow(2, h);
    int num_left, num_right, right_idx=2, left_idx=1;
	int count = 0, height = 0;
    for(int i=0; i<N; i++)
        scanf("%d", &arr[i]);

	scanf("%d", &val);


    if(p >= m/2)
        num_left = pow(2, h) -1;
    else
        num_left = pow(2, h) - 1 - ((m/2) - p);
    num_right = N - num_left - 1;
    
    sort(arr, N);
	
	DFS(0, 0, arr, h+1);
	
	sort(arr + N - 1 - h, h+1);

	heap[0] = arr[N-1-h];
	for (int i=0; i<h; i++)
	{
		heap[left_idx] = arr[N - h + i];
		left_idx = left_idx *2 + 1;
	}

	while(count < num_right)
	{
		for(int i=0; i<pow(2,height); i++)
		{
			heap[right_idx + i] = arr[count++];
		}
		right_idx = right_idx * 2 + 1;
		height++;
	}

	count = 0;
	height = 0;
	left_idx = 1;
	right_idx = 2;

	while(count < N - num_right - h)
	{
		for(int i=1; i<pow(2, height); i++)
		{
			heap[left_idx + i] = arr[num_right+count];
			count++;
		}
		left_idx = left_idx * 2 + 1;
		height++;
	}

	if(checkMaxHeap(heap, 0))
    {
		preOrder(heap, 0);
		printf("\n");
        return 0;
    }

	pivot = 0;
	count = 0;
	height = 0;
	left_idx = 1;
	right_idx = 2;

    for (int i=0; i < N; i++)
    {
        Select[i] = 0;
        heap[i] = 0;
    }

    if(p != m)
    {
        sort(arr, N);
        
        DFS(0, 0, arr, h);
        
        sort(arr + N - h, h);

        heap[0] = arr[N-h];
        for (int i=0; i<h-1; i++)
        {
            heap[right_idx] = arr[N - h + i + 1];
            right_idx = right_idx *2 + 2;
        }
        
        while(count < num_left)
        {
            for(int i=0; i<pow(2,height); i++)
            {
                heap[left_idx + i] = arr[count++];
                if(count>= num_left)
                    break;
            }
            left_idx = left_idx * 2 + 1;
            height++;
        }

        count = 0;
        height = 0;
        left_idx = 1;
        right_idx = 2;

        while(count < N - num_left - h + 1)
        {
            for(int i=0; i<pow(2, height)-1; i++)
            {
                heap[right_idx + i] = arr[num_left+count];
                count++;
                if(count >= N - num_left - h + 1)
                    break;
            }
            right_idx = right_idx * 2 + 1;
            height++;
        }

        if(checkMaxHeap(heap, 0))
        {
            preOrder(heap, 0);
            printf("\n");
            return 0;
        }
    }
}
