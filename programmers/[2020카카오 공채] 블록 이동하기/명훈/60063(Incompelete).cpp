#include	<iostream>
#include	<vector>
#include	<string>
#include	<queue>
#include	<cmath>
using namespace std;

#define MAX 100

struct robot {
	int y1, x1;	// y, x position
	int y2, x2; // partner y, x postion
	bool ver;	// check vertical or horizontal
	int cnt;	// cnt
};

int small_pos_y[6] = { -1, 0, 0, -1, 0, 0 };	// 가로의 작은애(세로는 y,x 순서 바꾸면됨)
int small_pos_x[6] = { 0, 0, -1, 1, 1, 1 };
int other_dir_y[6] = { 1, 1, 0, 1, 1, 0 };		// 가로기준 다른애
int other_dir_x[6] = { 0, 0, 1, 0, 0, 1 };
int turn_check_y[6] = { 0, 1, 0, 0, 1, 0 };		// 가로에서 돌경우 고려 - 3, 6번째는 고려 x
int turn_check_x[6] = { 1, 1, 0, -1, -1, 0 };

bool visited[MAX][MAX][MAX][MAX];		// vistied - y1, x1, y2, x2
int N;

bool isSafeTurn(vector<vector<int>> board, int y, int x, bool isVer, int dir) {
	if ((dir + 1) % 3 != 0) {
		if (isVer)
			return !board[y + turn_check_y[dir]][x + turn_check_x[dir]];
		else
			return !board[y + turn_check_x[dir]][x + turn_check_y[dir]];
	}
	return true;
}


int bfs(vector<vector<int>> board, int y1, int x1, int y2, int x2) {
	queue<robot> q;
	robot t;
	t.y1 = y1;	t.y2 = y2;	t.x1 = x1;	t.x2 = x2;	t.ver = true;	t.cnt = 0;
	q.push(t);
	visited[0][0][0][1] = true;

	while (!q.empty()) {
		int curY1 = q.front().y1;	int curX1 = q.front().x1;
		int curY2 = q.front().y2;	int curX2 = q.front().x2;
		bool curVer = q.front().ver;	int curCnt = q.front().cnt;
		q.pop();

		// end state
		if (curY2 == N - 1 && curX2 == N - 1)
			return curCnt;

		// push state
		for (int i = 0; i < 6; i++) {
			int nextY1, nextX1, nextY2, nextX2;
			if (curVer) {
				nextY1 = curY1 + small_pos_y[i];
				nextX1 = curX1 + small_pos_x[i];
				nextY2 = nextY1 + other_dir_y[i];
				nextX2 = nextX1 + other_dir_x[i];
			}
			else {
				nextY1 = curY1 + small_pos_x[i];
				nextX1 = curX1 + small_pos_y[i];
				nextY2 = nextY1 + other_dir_x[i];
				nextX2 = nextX1 + other_dir_y[i];
			}
			bool isVertical;
			if (abs(nextX2 - nextX1))
				isVertical = true;
			else
				isVertical = false;

			if (0 <= nextY1 && nextY1 < N && 0 <= nextX1 && nextX1 < N)
				if (0 <= nextY2 && nextY2 < N && 0 <= nextX2 && nextX2 < N)
					if (!board[nextY1][nextX1] && !board[nextY2][nextX2] && !visited[nextY1][nextX1][nextY2][nextX2])
						if (isSafeTurn(board, nextY1, nextX1, curVer, i)) {
							t.y1 = nextY1;	t.x1 = nextX1;	t.y2 = nextY2;	t.x2 = nextX2;	t.ver = isVertical;	 t.cnt = curCnt + 1;
							q.push(t);
							visited[nextY1][nextX1][nextY2][nextX2] = true;
						}
		}
	}
	return -1;
}

int solution(vector<vector<int>> board) {
	int answer = 0;

	N = board.size();

	answer = bfs(board, 0, 0, 0, 1);

	return answer;
}

int main() {
	vector<vector<int>> board = { {0, 0, 0, 1, 1}, {0, 0, 0, 1, 0}, {0, 1, 0, 1, 1}, {1, 1, 0, 0, 1}, {0, 0, 0, 0, 0} };

	cout << solution(board) << "\n";
}
