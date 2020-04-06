#include <stdio.h>
#include <stdio.h>
int N, M;
typedef struct Robot {
	int r, c, d;
	Robot() {}
	Robot(int rr, int cc, int dd) { r = rr; c = cc; d = dd; }
}Robot;


int Map[51][51];
int dir_row[4] = {-1,0,1,0};
int dir_col[4] = {0,1,0,-1};

int cnt = 0;

bool isRange(int r, int c) {
	return r >= 0 && c >= 0 && r < N&&c < M;
}

void printMap(Robot robot) {
	printf("\ncnt : %d\n", cnt);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (i == robot.r&&j == robot.c)
				printf("R ");
			else
				printf("%d ", Map[i][j]);
		}
		printf("\n");
	}
}

void cleanMap(Robot robot) {
	//현재위치 청소
	if (Map[robot.r][robot.c] == 0) {
		cnt++;
		Map[robot.r][robot.c] = 2;
	}
	//printMap(robot);
	for (int i = 0; i < 4; i++) {
		int cur_dir = robot.d;
		int left_dir = (robot.d - 1) < 0 ? 3 : robot.d - 1;
		int next_row = robot.r + dir_row[left_dir];
		int next_col = robot.c + dir_col[left_dir];
		if (isRange(next_row, next_col) && Map[next_row][next_col] == 0) {
			cleanMap(Robot(next_row, next_col, left_dir));
			return;
		}
		robot.d = (robot.d + 3) % 4;
	}

	//한칸 후진 해야됨.
	int back_dir = (robot.d + 2) % 4;
	int next_row = robot.r + dir_row[back_dir];
	int next_col = robot.c + dir_col[back_dir];
	if (isRange(next_row, next_col) && Map[next_row][next_col] !=1) {
		
		cleanMap(Robot(next_row, next_col,robot.d));
		return;
	}
	//다안되는 경우 일로통과 그리고 리턴됨
	return;
}
int main() {
	Robot robot;
	scanf("%d %d", &N, &M);
	scanf("%d %d %d", &robot.r, &robot.c, &robot.d);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &Map[i][j]);
		}
	}
	cleanMap(robot);

	printf("%d\n", cnt);

}