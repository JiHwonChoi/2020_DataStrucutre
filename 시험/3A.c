#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 10000
#define MAX_QUEUE 300

int dx[]={-1,0,0,1};
int dy[]={0,1,-1,0};

typedef enum{ false, true} bool; 
typedef struct Data{
    int break_wall;
    int cost;
    int x;
    int y;
}Data;

typedef struct{
    int front, rear;
    Data items[MAX_QUEUE];
} Queue;

// Check whether a queue is empty.
bool IsEmpty(Queue *pqueue){
    return pqueue->front == pqueue->rear;
}
// Check whether a queue is full.
bool IsFull(Queue *pqueue){
    return pqueue->front== (pqueue->rear + 1) % MAX_QUEUE;
}

// Read the item at the front.
Data Peek(Queue *pqueue){
    if(IsEmpty(pqueue))
        exit(1); //error: empty stack
    return pqueue->items[pqueue->front];
}
// Insert an item at the rear.
void Push(Queue *pqueue, Data item){
    if(IsFull(pqueue))
        exit(1);
    pqueue->items[pqueue->rear] = item;
    pqueue->rear = (pqueue->rear + 1) % MAX_QUEUE;
}
// Delete an item at the front.
void Pop(Queue *pqueue){
    if(IsEmpty(pqueue))
        exit(1);
    pqueue->front = (pqueue->front+1)%MAX_QUEUE;
}

// Make a queue empty.
void InitQueue(Queue *pqueue){
    pqueue->front = pqueue->rear = 0;
}

int BFS(char **map,int N,int M){
    int cost,x,y,next_x,next_y,break_wall,i,j,k;
    Data first_data,temp,next_data;
    bool visited[MAX_QUEUE][MAX_QUEUE][2];
    Queue *q = (Queue*)malloc(sizeof(Queue));


    for(i=0;i<MAX_QUEUE;i++)
        for(j=0;j<MAX_QUEUE;j++)
            for(k=0;k<2;k++)
                visited[i][j][k]=false;
    

    InitQueue(q);

    first_data.break_wall=0;
    first_data.cost=1;
    first_data.x=0;
    first_data.y=0;

    Push(q,first_data);
    
    while(!IsEmpty(q)){
        temp = Peek(q);
        break_wall = temp.break_wall;
        cost = temp.cost;
        x = temp.x;
        y = temp.y;
        Pop(q);

        if(x == N-1 && y == M-1)
            return cost;

        for(i=0;i<4;i++){
            next_x = x + dx[i];
            next_y = y + dy[i];
            if(!(next_x>=0 && next_x<N && next_y>=0 && next_y < M))
                continue;
            
            if(break_wall){
                if(!visited[next_x][next_y][1] && map[next_x][next_y]=='0'){
                    visited[next_x][next_y][1]=true;
                    next_data.break_wall=1;
                    next_data.cost = cost+1;
                    next_data.x = next_x;
                    next_data.y = next_y;
                    Push(q,next_data);
                }
            }else{
                if(!visited[next_x][next_y][0] && map[next_x][next_y]=='0'){
                    visited[next_x][next_y][0]=true;
                    next_data.break_wall=0;
                    next_data.cost = cost+1;
                    next_data.x = next_x;
                    next_data.y = next_y;
                    Push(q,next_data);
                }
                if(!visited[next_x][next_y][1] && map[next_x][next_y]=='1'){
                    visited[next_x][next_y][1]=true;
                    next_data.break_wall=1;
                    next_data.cost = cost+1;
                    next_data.x = next_x;
                    next_data.y = next_y;
                    Push(q,next_data);
                }
            }
        }
    }
    return INT_MAX;
}
int main(){
    int N,M,i,j,ret;
    char **map,temp;
    scanf("%d %d\n",&N,&M);
    
    map = (char**)malloc(N*sizeof(char*));
    for(i=0;i<N;i++)
	    map[i] = (char*)malloc(M*sizeof(char));

    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            scanf("%c",&map[i][j]);
        }
        scanf("%c",&temp);
    }

    ret = BFS(map,N,M);
    if(ret==INT_MAX)
        printf("-1\n");
    else
        printf("%d\n",ret);
}
