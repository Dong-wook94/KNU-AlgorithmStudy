# [2019 카카오 공채] 블록게임

## 문제 알고리즘

- 전체 탐색

## 풀이방법

- 전체에서 N-1, N-1까지 도는데, 없앨 수 있는 애들을 없애기



* **동욱햄 코드** 참고 했음.

- 핵심 코드

~~~c++

bool isAnyBlock(int y, int x) {
	for (int i = 0; i < y; i++)
		if (Board[i][x])
			return true;
	return false;
}

bool isValidDelete(int y, int x, int h, int w) {
	if (y <= N - h && x <= N - w) {
		int cnt = 0, block_id = -1;
		for (int i = y; i < y + h; i++) {
			for (int j = x; j < x + w; j++) {
				if (Board[i][j] == 0) {
					if (isAnyBlock(i, j))
						return false;
					cnt++;
					if (cnt > 2)
						return false;
				}
				else {
					if (block_id != -1 && Board[i][j] != block_id)
						return false;
					block_id = Board[i][j];
				}
			}
		}
		for (int i = y; i < y + h; i++) {
			for (int j = x; j < x + w; j++) {
				Board[i][j] = 0;
			}
		}
		return true;
	}
	return false;
}

int solution(vector<vector<int>> board) {
	int answer = 0;
	N = board.size();
	Board = board;

	int cnt;
	do {
		cnt = 0;
		for (int i = 0; i < N - 1; i++) {
			for (int j = 0; j < N - 1; j++) {
				if (isValidDelete(i, j, 2, 3))
					cnt++;
				if (isValidDelete(i, j, 3, 2))
					cnt++;
			}
		}
		answer += cnt;
	} while (cnt);

	return answer;
}

~~~

## 문제 후 느낀점

- 열심히 하자.