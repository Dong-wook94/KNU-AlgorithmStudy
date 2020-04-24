# 3190. 뱀

## 문제 알고리즘

- 시뮬레이션

## 풀이방법

- 문제에서 요구하는 대로 순서를 나눠서 풀면 쉬운 문제

  1. 다음 위치 지정

  2. 밖을 나가거나 자기 몸을 무는 경우 종료
  3. 다음 위치가 사과가 아니면 꼬리 제거
  4. 전진
  5. 방향 바꾸기

- 핵심 코드

```c++
#include	<iostream>
#include	<deque>
#include	<map>
using namespace std;

#define MAX 100 + 1

enum {BLANK, SNAKE, APPLE};
pair<int, int> dir[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };	// R, D, L, U
int N, K, L;
int board[MAX][MAX];
deque<pair<int, int>> snake;
map<int, char> comm;

int main() {
	// input
	cin >> N;
	cin >> K;
	for (int i = 0; i < K; i++) {
		int r, c;
		scanf("%d %d", &r, &c);
		board[r][c] = APPLE;
	}
	cin >> L;
	for (int i = 0; i < L; i++) {
		int t, d;
		scanf("%d %c", &t, &d);
		comm.insert({ t, d });
	}

	// solution
	board[1][1] = SNAKE;
	snake.push_back({ 1, 1 });

	int answer = 0, d = 0;
	while (true) {
		answer++;
		// y, x는 다음 위치
		
		int nextY = snake[0].first + dir[d].first;
		int nextX = snake[0].second + dir[d].second;

		// 밖을 나가거나, 자기 몸을 무는 경우. 종료
		if (nextY < 1 || nextY > N || nextX < 1 || nextX > N || board[nextY][nextX] == SNAKE) {
			break;
		}

		// 다음 위치가 사과가 아니면 꼬리 제거
		if (board[nextY][nextX] != APPLE) {
			pair<int, int> tail = snake[snake.size() - 1];
			snake.pop_back();
			board[tail.first][tail.second] = BLANK;
		}

		// 전진
		board[nextY][nextX] = SNAKE;
		snake.push_front({ nextY, nextX });

		// 방향 바꾸기
		if (comm.find(answer) != comm.end()) {	// 찾은 경우
			if (comm.find(answer)->second == 'L')
				d = (d + 3) % 4;
			else
				d = (d + 1) % 4;
		}
	}

	// output
	cout << answer << "\n";

	return 0;
}
```

## 문제 후 느낀점

- 쉬운 문제.