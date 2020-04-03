#include <string>
#include <vector>
#include <iostream>

using namespace std;

int N;
vector<vector<int>> Board;

bool canFill(int row, int col) {
	for (int i = 0; i < row; i++) {
		if (Board[i][col] != 0)
			return false;
	}
	return true;
}

bool find(int row, int col, int h, int w) {
	int empty_cnt = 0;
	int block_num = -1;
	for (int r = row; r < row + h; r++) {
		for (int c = col; c < col + w; c++) {
			if (Board[r][c] == 0) {
				if (!canFill(r, c))
					return false;
				empty_cnt++;
				if (empty_cnt > 2)
					return false;
			}
			else {
				if (block_num != -1 && block_num != Board[r][c]) {//서로다른블록으로 엮인경우
					return false;
				}
				block_num = Board[r][c];//업데이트
			}
		}
	}
	for (int r = row; r < row + h; r++) {
		for (int c = col; c < col + w; c++) {
			Board[r][c] = 0;
		}
	}
	return true;
}

int solution(vector<vector<int>> board) {
	int answer = 0;
	Board = board;
	N = board.size();
	int cnt;

	do {
		cnt = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i <= N - 2 && j <= N - 3 && find(i, j, 2, 3)) {
					cnt++;
				}
				else if (i <= N - 3 && j <= N - 2 && find(i, j, 3, 2)) {
					cnt++;
				}
			}
		}
		answer += cnt;
	} while (cnt);

	return answer;
}

int main() {
	vector<vector<int>> board = { {0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,4,0,0,0},{0,0,0,0,0,4,4,0,0,0},{0,0,0,0,3,0,4,0,0,0},{0,0,0,2,3,0,0,0,5,5},{1,2,2,2,3,3,0,0,0,5},{1,1,1,0,0,0,0,0,0,5} };
	cout << solution(board) << endl;
}