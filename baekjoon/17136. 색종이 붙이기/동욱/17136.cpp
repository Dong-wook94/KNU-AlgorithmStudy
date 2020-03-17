#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <algorithm>

#define ATTACH 0
#define DETACH 1
using namespace std;

int map[10][10];
int one_cnt=0;
int paper_cnt[6];
int min_result = INT_MAX;

void attachPaper(int row, int col, int paper_size, int action) {
	for (int i = row; i < row + paper_size; i++) {
		for (int j = col; j < col + paper_size; j++) {
			map[i][j] = action;
		}
	}
}

bool canAttachPaper(int row,int col, int paper_size) {
	if (row + paper_size > 10 || col + paper_size > 10)
		return false;
	for (int i = row; i < row + paper_size; i++) {
		for (int j = col; j < col + paper_size; j++) {
			if (map[i][j] == 0)
				return false;
		}
	}
	return true;
}

void dfs(int index, int p_cnt) {
	if (index == 100) {//종료조건
		min_result = min(min_result, p_cnt);
		return;
	}
	int row = index / 10;
	int col = index % 10;

	if (min_result <= p_cnt)
		return;
	if (map[row][col] == 1) {
		for (int i = 5; i > 0; i--) {
			if (paper_cnt[i] > 0) {
				if (canAttachPaper(row, col, i)) {
					attachPaper(row, col, i, ATTACH);
					paper_cnt[i]--;
					dfs(index + 1, p_cnt + 1);
					attachPaper(row, col, i, DETACH);
					paper_cnt[i]++;
				}
			}
		}
	}
	else {
		dfs(index + 1, p_cnt);
	}
}

int main() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1)
				one_cnt++;
		}
	}
	for (int i = 1; i <= 5; i++)
		paper_cnt[i] = 5;
	dfs(0, 0);
	if (min_result == INT_MAX) {
		printf("-1");
	}
	else {
		printf("%d", min_result);
	}
}