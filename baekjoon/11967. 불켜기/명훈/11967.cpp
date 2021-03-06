#include	<iostream>
#include	<vector>
#include	<queue>
using namespace std;

const int MAX = 100 + 1;
const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, -1, 0, 1 };

int N, M, ans = 1;
bool flag = true;
bool visited[MAX][MAX];
bool light[MAX][MAX];
vector<pair<int, int>> graph[MAX][MAX];
queue<pair<int, int>> q;

// initialize visited array
void initVisited() {
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			visited[i][j] = false;
}

// check is in board
bool isInBoard(int x, int y) {
	if (x < 1 || x > N || y < 1 || y > N)
		return false;
	return true;
}

// turn on the light
void turnOnTheLight(int x, int y) {
	for (int i = 0; i < graph[x][y].size(); i++) {
		int nX = graph[x][y][i].first;
		int nY = graph[x][y][i].second;
		if (!light[nX][nY]) {
			light[nX][nY] = true;
			ans++;
			flag = true;
		}
	}
}

// bfs
void bfs() {
	initVisited();
	q.push({ 1, 1 });
	visited[1][1] = true;

	// loop
	while (!q.empty()) {
		int curX = q.front().first;
		int curY = q.front().second;
		q.pop();

		// turn on the light
		turnOnTheLight(curX, curY);

		for (int dir = 0; dir < 4; dir++) {
			int nextX = curX + dx[dir];
			int nextY = curY + dy[dir];

			if (isInBoard(nextX, nextY) && light[nextX][nextY] && !visited[nextX][nextY]) {
				visited[nextX][nextY] = true;
				q.push({ nextX, nextY });
			}
		}
	}
}

int main() {
	// input
	int x, y, a, b;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d %d", &x, &y, &a, &b);
		graph[x][y].push_back({ a, b });
	}

	// solution
	light[1][1] = true;
	while (flag) {
		flag = false;
		bfs();
	}

	// output
	cout << ans << "\n";

	return 0;
}