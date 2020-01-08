#include <stdio.h>
#include <vector>

using namespace std;

int N, M, T;
int circles[52][52];
int visited[52][52];

int dir_row[4] = { 1,0,-1,0 };
int dir_col[4] = { 0,-1,0,1 };
int check = 0;
void init_visit() {
	for (int i = 1; i <=N; i++) {
		for (int j = 1; j <= M; j++) {
			visited[i][j] = 0;
		}
	}
}

void dfs(int r,int c,int cmp) {
	for (int i = 0; i < 4; i++) {
		int next_row = r + dir_row[i];
		int next_col = c + dir_col[i];
		if (next_col == 0)
			next_col = M;
		else if (next_col == M+1)
			next_col = 1;
		if (circles[next_row][next_col] == cmp) {
			check = 1;
			circles[next_row][next_col] = 0;
			circles[r][c] = 0;
			dfs(next_row, next_col, cmp);
		}
	}
}
void erase() {
	check = 0;
	init_visit();
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if(circles[i][j]!=0)
				dfs(i, j,circles[i][j]);
		}
	}
	if (check == 0) {
		int sum = 0;
		int cnt = 0;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (circles[i][j] > 0) {
					sum += circles[i][j];
					cnt++;
				}
			}
		}
		float average = (float)sum / cnt;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (circles[i][j] > average) {
					circles[i][j]--;
				}
				else if (circles[i][j] < average&&circles[i][j]>0) {
					circles[i][j]++;
				}
			}
		}
	}
}

void rotate(int gap,int dir,int num_turn) {
	for (int i = gap; i <=N; i = i + gap) {//배수만큼
		if (dir == 1) {//반시계방향
			for (int t = 0; t < num_turn; t++) {
				for (int j = 1; j <= M; j++) {
					circles[i][j - 1] = circles[i][j];
				}
				circles[i][M] = circles[i][0];
				circles[i][0] = 0;
			}
			
		}
		else {//시계방향
			for (int t = 0; t < num_turn; t++) {
				circles[i][0] = circles[i][M];
				for (int j = M - 1; j >= 0; j--) {
					circles[i][j + 1] = circles[i][j];
				}
				circles[i][0] = 0;
			}
		}
	}
}

int main() {
	//freopen("input.txt", "r",stdin);
	scanf("%d %d %d", &N, &M, &T);
	for (int i = 1; i <=N; i++) {
		for (int j = 1; j <=M; j++) {
			scanf("%d", &circles[i][j]);
		}
	}
	int x, d, k;
	
	for (int t = 0; t < T; t++) {
		scanf("%d %d %d", &x, &d, &k);
		rotate(x, d, k);
		erase();
	}
	int sum = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			sum += circles[i][j];
			//printf("%d ", circles[i][j]);
		}
		//printf("\n");
	}
	printf("%d\n", sum);
}