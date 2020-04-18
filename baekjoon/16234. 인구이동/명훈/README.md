# 16234. 인구이동
> 삼성 sw 기출문제

## 문제 알고리즘

- bfs문제

## 풀이방법

1. bfs를 통해서 연합국을 모아준다.
2. 연합국을 update해주면서 횟수를 계산한다.

- 핵심 코드

~~~c++
#include	<iostream>
#include	<vector>
#include	<queue>
#include	<algorithm>
using namespace std;

#define MAX 50

pair<int, int> dir[4] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };	// (dy, dx)
int N, L, R;
int board[MAX][MAX];
bool visited[MAX][MAX];
int id_board[MAX][MAX];
vector<pair<int, int>> c_union;	// (size, count)
int c_id;
int answer = -1;

void bfs(int y, int x) {
	queue<pair<int, int>> q;
	int c_union_size = 0;
	int c_union_num = 0;

	visited[y][x] = true;
	q.push({ y, x });
	c_union_size += board[y][x];
	c_union_num++;

	while (!q.empty()) {
		int curY = q.front().first;
		int curX = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nextY = curY + dir[i].first;
			int nextX = curX + dir[i].second;
			int diff = abs(board[curY][curX] - board[nextY][nextX]);
			if (!visited[nextY][nextX]) {
				if (nextX >= 0 && nextX < N && nextY >= 0 && nextY < N) {
					if (diff >= L && diff <= R) {
						c_union_size += board[nextY][nextX];
						c_union_num++;
						q.push({ nextY, nextX });
						visited[nextY][nextX] = true;
						id_board[nextY][nextX] = c_id;
					}
				}
			}
		}
	}

	// no open boarder
	if (c_union_num == 1) {
		return;
	}
	id_board[y][x] = c_id++;
	c_union.push_back({c_union_size, c_union_num});
	
	return;
}

int main() {
	// input
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &board[i][j]);
	
	// solution
	bool end_state = true;
	while (end_state) {			// no moving state is end-state
		end_state = false;

		// initialize
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				visited[i][j] = false;
				id_board[i][j] = -1;
			}
		c_union.clear();
		c_id = 0;

		// open border line -> sharing population
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (!visited[i][j]) 
					bfs(i, j);
	
		// update population
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (id_board[i][j] >= 0) {
					end_state = true;	// moving state
					board[i][j] = c_union[id_board[i][j]].first / c_union[id_board[i][j]].second;
				}
			}
		}
		answer++;
	}

	// output
	cout << answer << "\n";

	return 0;
}
~~~

## 문제 후 느낀점

- bfs문제
- 점점 더 발전하자