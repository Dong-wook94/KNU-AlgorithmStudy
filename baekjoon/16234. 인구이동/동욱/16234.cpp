#include <stdio.h>
#include <vector>
#include <math.h>
using namespace std;

typedef struct Pos {
	int row;
	int col;
	Pos(int r, int c) { row = r; col = c; }
}Pos;

int N, L, R;
int map[51][51];
int prev_map[51][51];
int visited[51][51];
vector<Pos> Union;

int dir_row[4] = { 1,0,-1,0 };
int dir_col[4] = { 0,-1,0,1 };


void init_visit() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			visited[i][j] = 0;
		}
	}
}

void copyMap(int a[][51],int b[][51]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			a[i][j] = b[i][j];
		}
	}
}

bool isChanged() {
	bool changed = false;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (prev_map[i][j] != map[i][j])
				changed = true;
		}
	}
	return changed;
}

void dfs(Pos cur) {
	for (int d = 0; d < 4; d++) {
		int next_row = cur.row + dir_row[d];
		int next_col = cur.col + dir_col[d];
		if (next_row >= 0 && next_col >= 0 && next_row < N &&next_col < N) {
			if (visited[next_row][next_col] == 0) {
				int gap = abs(map[cur.row][cur.col] - map[next_row][next_col]);
				if (gap >= L && gap <= R) {
					Union.push_back(Pos(next_row, next_col));
					visited[next_row][next_col] = 1;
					dfs(Pos(next_row, next_col));
				}
			}
		}
	}
}

int countMovePopulation() {
	int count = 0;
	
	while(1) {
		copyMap(prev_map, map);
		init_visit();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (visited[i][j] == 0) {
					Union.push_back(Pos(i, j));
					visited[i][j] = 1;
					dfs(Pos(i, j));
					int sum = 0;
					for (int k = 0; k < Union.size(); k++) {
						sum += map[Union[k].row][Union[k].col];
					}
					int average = sum / Union.size();
					for (int k = 0; k < Union.size(); k++) {
						map[Union[k].row][Union[k].col] = average;
					}
					Union.clear();
				}
			}
		}
		if (!isChanged()) {
			return count;
		}
		else
			count++;

	}

}
int main() {
	scanf("%d %d %d", &N, &L, &R);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	printf("%d\n", countMovePopulation());
}