#include	<iostream>
#include	<algorithm>
using namespace std;

#define MAX 50 + 1
#define INF 999999999
#define K_MAX 6

int board[MAX][MAX];						// array
int N, M, K;								// N, M, K
pair<pair<int, int>, int> K_list[K_MAX];	// <<r, c>, s> 
bool visited[K_MAX];
int ans = INF;

// get Row Miminum Sum
int getMinSize() {
	int tmp = INF;
	for (int i = 1; i <= N; i++) {
		int count = 0;
		for (int j = 1; j <= M; j++)
			count += board[i][j];
		tmp = min(tmp, count);
	}
	return tmp;
}

// if dir is 1,   
void circleTurn(int r, int c, int s, int dir) {
	// end state
	if (s < 1)
		return;
	if (dir == 1) {										// step
		int tmp = board[r - s][c - s];				// 0
		for (int i = r - s; i < r + s; i++)			// 1
			board[i][c - s] = board[i + 1][c - s];
		for (int j = c - s; j < c + s; j++)			// 2
			board[r + s][j] = board[r + s][j + 1];
		for (int i = r + s; i > r - s; i--)			// 3
			board[i][c + s] = board[i - 1][c + s];
		for (int j = c + s; j > c - s + 1; j--)		// 4
			board[r - s][j] = board[r - s][j - 1];
		board[r - s][c - s + 1] = tmp;				// 5
		circleTurn(r, c, s - 1, dir);
	}
	else {											// step
		int tmp = board[r - s][c - s];				// 0
		for (int j = c - s; j < c + s; j++)			// 1
			board[r - s][j] = board[r - s][j + 1];
		for (int i = r - s; i < r + s; i++)			// 2
			board[i][c + s] = board[i + 1][c + s];
		for (int j = c + s; j > c - s; j--)			// 3
			board[r + s][j] = board[r + s][j - 1];
		for (int i = r + s; i > r - s + 1; i--)		// 4
			board[i][c - s] = board[i - 1][c - s];
		board[r - s + 1][c - s] = tmp;				// 5
		circleTurn(r, c, s - 1, dir);
	}
	return;
}

void dfs(int k_count) {
	if (k_count == 0) {
		ans = min(ans, getMinSize());
		return;
	}
	for (int i = 0; i < K; i++) {
		if (!visited[i]) {
			circleTurn(K_list[i].first.first, K_list[i].first.second, K_list[i].second, 1);
			visited[i] = true;

			dfs(k_count - 1);

			visited[i] = false;
			circleTurn(K_list[i].first.first, K_list[i].first.second, K_list[i].second, 0);
		}
	}
}

int main() {
	// input
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			scanf("%d", &board[i][j]);
	for (int i = 0; i < K; i++)
		scanf("%d %d %d", &K_list[i].first.first, &K_list[i].first.second, &K_list[i].second);

	// solution
	dfs(K);

	// output
	cout << ans << "\n";

	return 0;
}