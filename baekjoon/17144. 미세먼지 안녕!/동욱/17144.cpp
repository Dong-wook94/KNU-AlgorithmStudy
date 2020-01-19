#include <stdio.h>
#include <vector>

using namespace std;

typedef struct AirCleaner {
	int row;
	int col;
	AirCleaner(int rr, int cc) {
		row = rr;
		col = cc;
	}
}AirCleaner;

vector<AirCleaner> cleaner;
int Map[51][51];
int NextMap[51][51];
int R, C, T;
int dir_row[4] = { 0,-1,0,1 };
int dir_col[4] = { 1,0,-1,0 };
int circulate[2][4] = {
	{ 0,1,2,3 },//반시계방향
{0,3,2,1}//시계방향
};

void init_NextMap() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++)
			NextMap[i][j] = 0;
	}
	NextMap[cleaner[0].row][cleaner[0].col] = -1;
	NextMap[cleaner[1].row][cleaner[1].col] = -1;
}

void map_copy(int map[][51], int map2[][51]) { //map1 <-map2
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			map[i][j] = map2[i][j];
		}
	}
}

void SpreadDust() {//미세먼지 확산

	init_NextMap();
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (Map[i][j] > 0) {
				int cnt = 0;
				for (int d = 0; d < 4; d++) {
					int next_row = i + dir_row[d];
					int next_col = j + dir_col[d];
					if (next_row >= 0 && next_col >= 0 && next_row < R&&next_col < C&&Map[next_row][next_col] != -1) {
						NextMap[next_row][next_col] += (Map[i][j] / 5);
						cnt++;
					}
				}
				NextMap[i][j] = NextMap[i][j] + Map[i][j] - ((Map[i][j] / 5)*cnt);
			}
		}
	}
	map_copy(Map, NextMap);
}

void AirCleanerProcess(int num) {
	int col = cleaner[num].col + 1;
	int row = cleaner[num].row;

	NextMap[row][col] = 0;

	for (int i = 0; i < 4; i++) {
		while (1) {
			int next_row = row + dir_row[circulate[num][i]];
			int next_col = col + dir_col[circulate[num][i]];

			//방향바꾸는타이밍
			if (next_row <0 || next_col < 0 || next_row >= R||next_col >= C||Map[next_row][next_col] == -1) {
				break;
			}
			NextMap[next_row][next_col] = Map[row][col];
			row = next_row;
			col = next_col;
		}
	}
}

int main() {
	scanf("%d %d %d", &R, &C, &T);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			scanf("%d", &Map[i][j]);
			if (Map[i][j] == -1) {
				cleaner.push_back(AirCleaner(i, j));
			}
		}
	}
	for (int i = 0; i < T; i++) {//1동안하는일
		//확산
		SpreadDust();
		//공기청정기작동
		AirCleanerProcess(0);
		AirCleanerProcess(1);
		map_copy(Map, NextMap);
	}
	int cnt = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (Map[i][j] > 0) {
				cnt += Map[i][j];
			}
		}
	}
	printf("%d\n", cnt);
}