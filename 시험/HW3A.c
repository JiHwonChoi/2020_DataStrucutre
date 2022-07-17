#include<stdio.h>
#define QMAX 100

char arr[10][11];

char visited[10][10][2];

int n, m, queue[QMAX][4];
int dr[4] = { 0,1,0,-1 };
int dc[4] = { 1,0,-1,0 };
int enque(int*, int, int, int, int);
int bound(int, int);

int main() {
	int i, j;
	int front = 0, rear = 0, nr, nc, lv, k, curr, curc, ans = -1;
	scanf("%d %d", &n, &m);
	for (i = 0; i < n; i++) scanf("%s", arr[i]);
	enque(&rear, 0, 0, 1, 0);
	visited[0][0][0] = 1;
	while (front != rear) {
		curr = queue[front][0];
		curc = queue[front][1];

		lv = queue[front][2];
		k = queue[front][3];
		front = (front + 1) % QMAX;
		
		if (curr == n - 1 && curc == m - 1 && (ans == -1 || ans > lv)) 
		{ 
			ans = lv; continue; 
		
		
		}
		
		for (i = 0; i < 4; i++) 
		{
			nr = curr + dr[i];
			nc = curc + dc[i];
			if (bound(nr, nc) && arr[nr][nc] != '1' && !visited[nr][nc][k]) {
				visited[nr][nc][k] = 1;
				enque(&rear, nr, nc, lv + 1, k);
			}
			if (k == 0 && bound(nr, nc) && arr[nr][nc] == '1' && !visited[nr][nc][1]) {
				visited[nr][nc][1] = 1;
				enque(&rear, nr, nc, lv + 1, 1);
			}
		}
	}
	printf("%d", ans);
}
int bound(int r, int c) {
	if (r >= 0 && r < n && c >= 0 && c < m) return 1;
	else return 0;
}
int enque(int* rear, int r, int c, int lv, int k) {
	queue[*rear][0] = r;
	queue[*rear][1] = c;
	queue[*rear][2] = lv;
	queue[*rear][3] = k;
	*rear = (*rear + 1) % QMAX;
}