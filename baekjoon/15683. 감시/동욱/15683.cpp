#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef struct Camera {
	int row;
	int col;
	int version;
	Camera(int r,int c,int v){
		row = r;
		col = c;
		version = v;
	}
}Camera;


int N, M;
int Map[8][8];
int min_cnt = 64;
vector<Camera> cam;
int dir_row[4] = { 1,0,-1,0 };
int dir_col[4] = { 0,1,0,-1 };

void MapCopy(int (*a)[8], int (*b)[8]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			a[i][j] = b[i][j];
		}
	}
}
void cam_1(Camera camera, int dir) {//1번방식
	int next_row = camera.row;
	int next_col = camera.col;
	next_row += dir_row[dir];
	next_col += dir_col[dir];
	for (; next_row >= 0 && next_col >= 0 && next_row < N&&next_col < M;) {


		switch (Map[next_row][next_col]) {
		case 0:
			Map[next_row][next_col] = -1;
			break;
		case 6://벽만나면 아예 함수 종료
			return;
		default:
			break;
		}
		next_row += dir_row[dir];
		next_col += dir_col[dir];
	}
}

void dfs(int num) {
	int cnt;
	int temp[8][8];
	if (num >= cam.size()) {
		cnt = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (Map[i][j] == 0)
					cnt++;
			}
		}
		min_cnt = min(min_cnt, cnt);
		return;
	}
	MapCopy(temp, Map);
	switch (cam[num].version) {
	case 1:
		for (int j = 0; j < 4; j++) {
			cam_1(cam[num], j);
			dfs(num + 1);
			MapCopy(Map, temp);
		}
		break;
	case 2:
		for (int j = 0; j < 2; j++) {
			cam_1(cam[num], j);
			cam_1(cam[num], (j + 2) % 4);
			dfs(num + 1);
			MapCopy(Map, temp);
		}
		break;
	case 3:
		for (int j = 0; j < 4; j++) {
			cam_1(cam[num], j);
			cam_1(cam[num], (j + 1) % 4);
			dfs(num + 1);
			MapCopy(Map, temp);
		}
		break;
	case 4:
		for (int j = 0; j < 4; j++) {
			cam_1(cam[num], j);
			cam_1(cam[num], (j + 1) % 4);
			cam_1(cam[num], (j + 2) % 4);
			dfs(num + 1);
			MapCopy(Map, temp);
		}
		break;
	case 5:
		for (int j = 0; j < 4; j++) {
			cam_1(cam[num], j);
		}
		dfs(num + 1);
		MapCopy(Map, temp);
		break;
	}
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &Map[i][j]);
			if (Map[i][j] >= 1 && Map[i][j] <= 5)
				cam.push_back(Camera(i, j, Map[i][j]));
		}
	}

	dfs(0);
	printf("%d\n", min_cnt);
}