#include <stdio.h>

int N, L;
int Map[100][100];
int dir_row[2] = { 1, 0 };
int dir_col[2] = { 0, 1 };
int check_route(int start_row, int start_col, int dir);

int main() {
	int cnt_route = 0;
	scanf("%d %d", &N, &L);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &Map[i][j]);
		}
	}
	for (int i = 0; i < N; i++) {
		cnt_route += check_route(i, 0, 1);
	}
	for (int i = 0; i < N; i++) {
		cnt_route += check_route(0, i, 0);
	}
	printf("%d\n", cnt_route);
}
int check_route(int start_row, int start_col, int dir) {
	int next_row, next_col, height, cnt = 1;
	int slope = 0;
	height = Map[start_row][start_col];
	for (int i = 1; i < N; i++) {
		next_row = start_row + i * dir_row[dir];
		next_col = start_col + i * dir_col[dir];
		if (slope == -1) {//내리막
			if (height == Map[next_row][next_col]) {
				cnt++;
				if (cnt >= L) {
					slope = 0;
					cnt = 0;
				}
			}
			else
				return 0;

		}
		else {//평지인상황
			if (height == Map[next_row][next_col]) {
				cnt++;
			}
			else if (height == Map[next_row][next_col] + 1) {//한칸아래
				cnt = 1;
				height = height - 1;
				slope = -1; //현재상태 내리막으로
				if (cnt >= L) {
					cnt = 0;
					slope = 0;
				}
			}
			else if (height == Map[next_row][next_col] - 1) {//한칸위
				if (cnt >= L) {//평지개수가 L개이상일때 오르막세울수있다
					cnt = 1;
					height = height + 1;
				}
				else {
					return 0;
				}
			}
			else
				return 0;
		}

	}
	if (slope != 0)
		return 0;
	return 1;
}