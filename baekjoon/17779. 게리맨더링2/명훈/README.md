# 17822 원판돌리기

## 문제해결 사진

![image](https://user-images.githubusercontent.com/42582516/83356710-c5654800-a3a2-11ea-8253-f8bfb4c7b93f.png)

## 문제 알고리즘

- 시뮬레이션

## 풀이방법

1. loop를 4번 돌리면서 x, y, d1, d2를 결정하여 구역을 결정한다.

2. 이후 결정한 구역에서 구역의 인구를 구해서 정렬하여 차이를 구한다.

- 핵심 코드

```c++
#include	<iostream>
#include	<vector>
#include	<algorithm>
#include	<limits.h>
using namespace std;

const int MAX = 20;
int N, res = INT_MAX;
int board[MAX][MAX];

// get max difference
int diff(int x, int y, int d1, int d2) {
	vector<int> population(5, 0);

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			//1번 선거구
			if (r < x + d1 && c <= y && !(r >= x && c >= y - (r - x))) {
				population[0] += board[r][c];
			}
			//2번 선거구
			else if (r <= x + d2 && c > y && !(r >= x && c <= y + (r - x))) {
				population[1] += board[r][c];
			}
			//3번 선거구
			else if (r >= x + d1 && c < y - d1 + d2 && !(r <= x + d1 + d2 && c >= (y - d1 + d2 - (x + d1 + d2 - r)))) {
				population[2] += board[r][c];
			}
			//4번 선거구
			else if (r > x + d2 && c >= y - d1 + d2 && !(r <= x + d1 + d2 && c <= (y - d1 + d2 + (x + d1 + d2 - r)))) {
				population[3] += board[r][c];
			}
			//5번 선거구
			else {
				population[4] += board[r][c];
			}
		}
	}

	sort(population.begin(), population.end());
	return (population[4] - population[0]);
}

int main() {
	// input
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &board[i][j]);

	// solution
	for (int x = 0; x < N; x++)
		for (int y = 1; y < N; y++)
			for (int d1 = 1; d1 <= y; d1++)
				for (int d2 = 1; d2 < N - y; d2++)
					res = min(res, diff(x, y, d1, d2));


	// output
	cout << res << "\n";

	return 0;
}

```

## 문제 후 느낀점

- 다른 사람 코드 참고하였음.