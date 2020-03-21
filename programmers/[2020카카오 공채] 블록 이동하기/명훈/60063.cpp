#include	<iostream>
#include	<vector>
#include	<string>
#include	<queue>
#include	<cmath>
using namespace std;

#define MAX 100

struct robot {
	int y, x;	// y, x position
	int dir;	// if dir is 1 horizontal. else vertical
	int cnt;	// cnt
	robot(int t_y, int t_x, bool t_dir, int t_count) {
		y = t_y;		x = t_x;		dir = t_dir;	cnt = t_count;
	}
};

pair<int, int> turnDir[4] = { {-1, 0}, {0, 0}, {-1, 1}, {0, 1} };	// horizontal <y, x>. vertical <x, y>
pair<int, int> safeTurn[4] = { {0, 1}, {1, 1}, {0, -1}, {1, -1} };	// horizontal <y, x>. vertical <x, y>
pair<int, int> goDir[4] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };
bool visited[MAX][MAX][2];
int N;

bool isSafeTurn(vector<vector<int>> board, int y, int x, int dir, int i) {
	if (dir)
		return (board[y + safeTurn[i].first][x + safeTurn[i].second] == 1) ? false : true;
	else
		return (board[y + safeTurn[i].second][x + safeTurn[i].first] == 1) ? false : true;
}

int bfs(vector<vector<int>> board, int y, int x) {
	queue<robot> q;			// queue
	robot t(0, 0, 1, 0);
	q.push(t);
	visited[0][0][1] = true;

	while (!q.empty()) {
		int curY = q.front().y;		int curX = q.front().x;
		int curDir = q.front().dir;	int curCnt = q.front().cnt;
		q.pop();

		// end state
		if (curDir) {	// 가로
			if (curY == N - 1 && (curX + 1) == N - 1)
				return curCnt;
		}
		else {			// 세로
			if ((curY + 1) == N - 1 && curX == N - 1)
				return curCnt;
		}

		// turn case (회전)
		for (int i = 0; i < 4; i++) {
			if (curDir == 1) {	// 가로 -> 세로
				int nextY = curY + turnDir[i].first;
				int nextX = curX + turnDir[i].second;
				int nextDir = (curDir == 0) ? 1 : 0;

				if (0 <= nextY && nextY < N - 1 && 0 <= nextX && nextX < N)
					if (!board[nextY][nextX] && !board[nextY + 1][nextX] && !visited[nextY][nextX][nextDir])
						if (isSafeTurn(board, nextY, nextX, curDir, i)) {
							robot tmp(nextY, nextX, nextDir, curCnt + 1);
							q.push(tmp);
							visited[nextY][nextX][nextDir] = true;
						}
			}
			else {				// 세로 -> 가로
				int nextY = curY + turnDir[i].second;
				int nextX = curX + turnDir[i].first;
				int nextDir = (curDir == 0) ? 1 : 0;

				if (0 <= nextY && nextY < N && 0 <= nextX && nextX < N - 1)
					if (!board[nextY][nextX] && !board[nextY][nextX + 1] && !visited[nextY][nextX][nextDir])
						if (isSafeTurn(board, nextY, nextX, curDir, i)) {
							robot tmp(nextY, nextX, nextDir, curCnt + 1);
							q.push(tmp);
							visited[nextY][nextX][nextDir] = true;
						}
			}
		}

		// go back case (앞뒤로 왔다갔다하는 경우)
		for (int i = 0; i < 4; i++) {
			if (curDir) {		// 가로 -> 가로
				int nextY = curY + goDir[i].first;
				int nextX = curX + goDir[i].second;

				if (0 <= nextY && nextY < N && 0 <= nextX && nextX < N - 1) {
					if (!board[nextY][nextX] && !board[nextY][nextX + 1] && !visited[nextY][nextX][curDir]) {
						robot tmp(nextY, nextX, curDir, curCnt + 1);
						q.push(tmp);
						visited[nextY][nextX][curDir] = true;
					}
				}
			}
			else {				// 세로 -> 세로
				int nextY = curY + goDir[i].first;
				int nextX = curX + goDir[i].second;

				if (0 <= nextY && nextY < N - 1 && 0 <= nextX && nextX < N) {
					if (!board[nextY][nextX] && !board[nextY + 1][nextX] && !visited[nextY][nextX][curDir]) {
						robot tmp(nextY, nextX, curDir, curCnt + 1);
						q.push(tmp);
						visited[nextY][nextX][curDir] = true;
					}
				}
			}
		}
	}
	return -1;	// error code
}

int solution(vector<vector<int>> board) {
	N = board.size();

	int answer = bfs(board, 0, 0);

	return answer;
}

int main() {
	vector<vector<int>> board = { {0, 0, 0, 1, 1}, {0, 0, 0, 1, 0}, {0, 1, 0, 1, 1}, {1, 1, 0, 0, 1}, {0, 0, 0, 0, 0} };

	cout << solution(board) << "\n";
}
