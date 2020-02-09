#include <stdio.h>
#include <algorithm>

using namespace std;
int row_size, col_size;
int map[501][501];
int visited[501][501];
int dir_row[4] = { 1,0,-1,0 };
int dir_col[4] = { 0,1,0,-1 };
int sum = 0;
int max_sum = 0;

void dfs(int row, int col, int block_cnt, int sum) {
	if (block_cnt == 3) {
		max_sum = max(sum, max_sum);
		return;
	}
	visited[row][col] = 1;
	for (int d = 0; d < 4; d++) {
		int next_row = row + dir_row[d];
		int next_col = col + dir_col[d];

		if (next_row >= 0 && next_col >= 0 && next_row < row_size&&next_col < col_size) {
			if (visited[next_row][next_col] == 0) {
				dfs(next_row, next_col, block_cnt + 1, sum + map[next_row][next_col]);
			}
		}
	}
	visited[row][col] = 0;
}
void exception_shape() {
	for (int i = 0; i < row_size - 2; i++) {

		for (int j = 0; j < col_size - 1; j++) {
			sum = 0;
			sum += map[i][j];
			sum += map[i + 1][j];
			sum += map[i + 2][j];
			sum += map[i + 1][j + 1];
			max_sum = max(sum, max_sum);//た
			sum = 0;
			sum += map[i + 1][j];
			sum += map[i][j + 1];
			sum += map[i + 1][j + 1];
			sum += map[i + 2][j + 1];
			max_sum = max(sum, max_sum);//っ
		}
	}
	for (int i = 0; i < row_size - 1; i++) {

		for (int j = 0; j < col_size - 2; j++) {
			sum = 0;
			sum += map[i][j + 1];
			sum += map[i + 1][j];
			sum += map[i + 1][j + 1];
			sum += map[i + 1][j + 2];
			max_sum = max(sum, max_sum);//で
			sum = 0;
			sum += map[i][j];
			sum += map[i][j + 1];
			sum += map[i][j + 2];
			sum += map[i + 1][j + 1];
			max_sum = max(sum, max_sum);//ぬ
		}
	}
}
int main() {
	scanf("%d %d", &row_size, &col_size);
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < col_size; j++) {
			sum = 0;
			dfs(i, j, 0, map[i][j]);
		}
	}
	exception_shape();
	printf("%d\n", max_sum);
}