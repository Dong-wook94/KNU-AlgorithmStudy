#include    <iostream>
#include    <string>
#include    <vector>
using namespace std;

int N;
vector<vector<int>> Board;

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

int main() {
	int ans = solution({
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 4, 0, 0, 0},
		{0, 0, 0, 0, 0, 4, 4, 0, 0, 0},
		{0, 0, 0, 0, 3, 0, 4, 0, 0, 0},
		{0, 0, 0, 2, 3, 0, 0, 0, 5, 5},
		{1, 2, 2, 2, 3, 3, 0, 0, 0, 5},
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 5} });

	cout << ans << "\n";

	return 0;
}