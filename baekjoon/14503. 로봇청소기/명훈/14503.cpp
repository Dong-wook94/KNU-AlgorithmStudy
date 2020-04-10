#include	<iostream>
#include	<vector>
#include	<algorithm>
using namespace std;

#define MAX 50

struct Robot {
	int r;
	int c;
	int d;
};

pair<int, int> dir[4] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };	// (y, x) = N, E, S, W
int N, M;
int board[MAX][MAX];
bool visited[MAX][MAX];

bool isInRange(int y, int x) {
	if (y < 0 || y >= N || x < 0 || x >= M)
		return false;
	return true;
}

void clean(Robot robot) {
	// 현재 위치 청소
	visited[robot.r][robot.c] = true;

	int next_dir;
	for (int i = 0; i < 4; i++) {
		// 다음 방향
		next_dir = robot.d - 1;
		if (next_dir == -1)
			next_dir = 3;

		int nextR = robot.r + dir[next_dir].first;
		int nextC = robot.c + dir[next_dir].second;
		// 벽이 아니고 방문하지 않은 경우. 이동
		if (isInRange(nextR, nextC) && board[nextR][nextC] != 1 && !visited[nextR][nextC]) {
			robot = { nextR, nextC, next_dir };
			clean(robot);
			return;
		}
		robot.d = next_dir;
	}

	// 후진
	int nextR = robot.r - dir[next_dir].first;
	int nextC = robot.c - dir[next_dir].second;
	if (isInRange(nextR, nextC) && board[nextR][nextC] != 1) {
		robot = {nextR, nextC, next_dir};
		clean(robot);
		return;
	}
	return;
}

int main() {
	// input
	Robot robot;
	cin >> N >> M;
	cin >> robot.r >> robot.c >> robot.d;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &board[i][j]);

	// solution
	clean(robot);

	int answer = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (visited[i][j])
				answer++;

	// output
	cout << answer << "\n";

	return 0;
}