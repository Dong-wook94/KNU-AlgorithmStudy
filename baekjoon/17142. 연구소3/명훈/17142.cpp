#include	<iostream>
#include	<vector>
#include	<queue>
#include	<string.h>
#include	<algorithm>
using namespace std;

#define MAX 50

struct Virus {
	int y;
	int x;
	int time;
};

pair<int, int> dir[4] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

int N, M;
int board[MAX][MAX], tboard[MAX][MAX];
int ans = 10000;
vector<Virus> virus;
queue<Virus> q;
bool visited[MAX][MAX];


bool isInRange(int y, int x) {
	if (y < 0 || y >= N || x < 0 || x >= N)
		return false;
	return true;
}

bool isFinished() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (tboard[i][j] == 0)
				return false;
	return true;
}

int getSpreadTime() {
	Virus cur, next;
	int max_time = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			tboard[i][j] = board[i][j];

	while (!q.empty()) {
		cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			next.y = cur.y + dir[i].first;
			next.x = cur.x + dir[i].second;

			// 범위 안, 벽이 아닌 경우
			if (isInRange(next.y, next.x) && !visited[next.y][next.x] && tboard[next.y][next.x] != 1) {
				tboard[next.y][next.x] = 2;
				visited[next.y][next.x] = true;
				next.time = cur.time + 1;
				if (max_time < next.time && board[next.y][next.x] == 0)
					max_time = next.time;
				q.push(next);
			}
		}
	}
	return max_time;
}


void solution() {
	vector<int> choice;
	int time = -1;
	for (int i = 0; i < virus.size() - M; i++)
		choice.push_back(0);
	for (int i = 0; i < M; i++)
		choice.push_back(1);

	do {
		for (int i = 0; i < N; i++)
			memset(visited[i], false, sizeof(bool) * N);
		for (int i = 0; i < choice.size(); i++) {
			if (choice[i] == 1) {
				visited[virus[i].y][virus[i].x] = true;
				q.push(virus[i]);
			}
		}
		time = getSpreadTime();
		if (time < ans && isFinished())
			ans = time;
		
	} while (next_permutation(choice.begin(), choice.end()));
}

int main() {
	// input
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &board[i][j]);
			if (board[i][j] == 2)
				virus.push_back({ i, j, 0 });
		}
	}

	// solution
	solution();

	// output
	if (ans == 10000)
		cout << "-1\n";
	else
		cout << ans << "\n";

	return 0;
}