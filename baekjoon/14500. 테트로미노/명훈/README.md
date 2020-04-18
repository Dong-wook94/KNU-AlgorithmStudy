# 14500.테트로미노

> 삼성 SW 기출문제

## 문제 알고리즘

- dfs 문제
- 분류

## 풀이방법

* dfs를 통해서 `ㅜ` 모양을 제외하고는 다 만들 수 있다.

  * ![img](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/14500/1.png)
* 해당 문제는 dfs를 통해서 1~4번까지의 모양을 만들어서 최대합을 구하고 `ㅜ` 모양은 따로 확인해서 풀면 되는 문제이다.

- 핵심 코드

~~~c++
#include	<iostream>
#include	<vector>
using namespace std;

#define MAX 500

int N, M;
int board[MAX][MAX];
bool visited[MAX][MAX];
int answer = 0;

pair<int, int> dir[4] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

void dfs(int y, int x, int cnt, int sum) {
	if (cnt == 4) {
		if (answer < sum)
			answer = sum;
		return;
	}
	for (int i = 0; i < 4; i++) {
		int ny = y + dir[i].first;
		int nx = x + dir[i].second;
		if (ny >= 0 && ny < N && nx >= 0 && nx < M) {
			if (!visited[ny][nx]) {
				visited[ny][nx] = true;
				dfs(ny, nx, cnt + 1, sum + board[ny][nx]);
				visited[ny][nx] = false;
			}
		}
	}
}

int main() {
	// input
	cin >> N >> M;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &board[i][j]);

	// solution
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			visited[i][j] = true;
			dfs(i, j, 0, 0);
			visited[i][j] = false;
		}

	int sum = 0;
	for (int i = 0; i < N - 2; i++)		// ㅓ, ㅏ
		for (int j = 0; j < M - 1; j++) {
			sum = board[i][j + 1] + board[i + 1][j] + board[i + 1][j + 1] + board[i + 2][j + 1];
			if (sum > answer)
				answer = sum;
			sum = board[i][j] + board[i + 1][j] + board[i + 1][j + 1] + board[i + 2][j];
			if (sum > answer)
				answer = sum;
		}

	for (int i = 0; i < N - 1; i++)		// ㅜ, ㅗ
		for (int j = 0; j < M - 2; j++) {
			sum = board[i][j] + board[i][j + 1] + board[i + 1][j + 1] + board[i][j + 2];
			if (sum > answer)
				answer = sum;
			sum = board[i + 1][j] + board[i][j + 1] + board[i + 1][j + 1] + board[i + 1][j + 2];
			if (sum > answer)
				answer = sum;
		}


	// output
	cout << answer << "\n";

	return 0;
}
~~~

## 문제 후 느낀점

- 트릭을 사용한 dfs 문제

