#include	<iostream>
#include	<queue>
#include	<algorithm>
using namespace std;

// static
const int MAX = 300;
const pair<int, int> dir[4] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
// variable
int board[MAX][MAX], cpyboard[MAX][MAX];
int N, M;
int answer;					// year

bool visited[MAX][MAX];
queue<pair<int, int>> q;

// 범위내 체크
bool isInRange(int y, int x) {
	if (y < 0 || y > N || x < 0 || x > M)
		return false;
	return true;
}

// 빙산 업데이트
void updateGlacier() {
	// origin -> cpy
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cpyboard[i][j] = board[i][j];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j]) {
				int cnt = 0;
				for (int d = 0; d < 4; d++) {
					int nextY = i + dir[d].first;
					int nextX = j + dir[d].second;
					
					// 범위안이고 주변에 바다인 경우
					if (isInRange(nextY, nextX) && board[nextY][nextX] == 0) {
						cnt++;
					}
				}

				if (cpyboard[i][j] >= cnt)
					cpyboard[i][j] -= cnt;
				else
					cpyboard[i][j] = 0;
			}
		}
	}

	// cpy -> origin
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			board[i][j] = cpyboard[i][j];
}


// 빙하가 두개로 분리되어 있으면 종료
bool isSeperated() {
	bool isOne = false;		// 한개인지 체크
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			visited[i][j] = false;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			// 빙하가 아닌 경우
			if (board[i][j] && !visited[i][j]) {
				if (!isOne) {
					q.push({ i, j });
					visited[i][j] = true;
					isOne = true;

					while (!q.empty()) {
						int curY = q.front().first;
						int curX = q.front().second;
						q.pop();

						for (int d = 0; d < 4; d++) {
							int nextY = curY + dir[d].first;
							int nextX = curX + dir[d].second;

							if (isInRange(nextY, nextX) && board[nextY][nextX] && !visited[nextY][nextX]) {
								q.push({ nextY, nextX });
								visited[nextY][nextX] = true;
							}
						}
					}
				}
				else
					return true;	// 두번째 덩어리가 있는 경우	
			}
		}
	}
	return false;
}

// 빙하가 없으면  true
bool isNoGlacier() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			if (board[i][j])
				return false;
	return true;
}

int main() {
	// input
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &board[i][j]);
		}
	}

	// solution
	while (true) {
		answer++;

		updateGlacier();

		// check code
	/*	cout << answer << "\n";
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++)
				printf("%d ", board[i][j]);
			cout << "\n";
		}*/

		if (isSeperated()) {
			break;
		}
		if (isNoGlacier()) {
			answer = 0;
			break;
		}
	}

	// output
	cout << answer << "\n";
	return 0;
}