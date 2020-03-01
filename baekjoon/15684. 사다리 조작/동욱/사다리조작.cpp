#include<stdio.h>
#include<stdlib.h>
bool ladder[31][11] = { false ,};
int N, M, H;
int correct_check() {
	int cur;
	for (int i = 1; i <= N; i++) {
		cur = i;
		for (int j = 1; j <= H; j++) {
			if (ladder[j][cur] == 1)
				cur++;
			else if (ladder[j][cur - 1] == 1)
				cur--;
		}
		if (cur != i)
			return 0;
	}
	return 1;
}
bool canPutLadder(int i, int j)
{
	return !ladder[i][j - 1] && !ladder[i][j] && !ladder[i][j + 1];
}
void dfs(int startRow, int endTime,int curTime) {
	if (curTime >= endTime) {
		if (correct_check()) {
			printf("%d\n", curTime);
			exit(0);
		}
		return;
	}
	for (int i = startRow; i <= H; i++) {
		for (int j = 1; j < N; j++) {
			if (canPutLadder(i, j)) {
				ladder[i][j] = true;
				dfs(i, endTime, curTime + 1);
				ladder[i][j] = false;
			}
		}
	}
}



int main() {
	scanf("%d %d %d", &N, &M, &H);
	for (int i = 0; i < M; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		ladder[a][b] = true;
	}
	for (int i = 0; i <= 3; i++) {
		dfs(1, 3, 0);
	}
	printf("-1\n");
}