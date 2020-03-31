#include <string>
#include <vector>
#include <iostream>
using namespace std;

typedef struct Block {
	int row_pos;
	int col_pos;
	int row_size;
	int col_size;
	bool isErased;
	Block(int r, int c, int rs, int cs) {
		row_pos = r; col_pos = c; row_size = rs; col_size = cs;
		isErased = false;
	}
}Block;

vector<Block> blocks;

bool canFill(vector<vector<int>> board,int row, int col) {
	for (int i = 0; i < row; i++) {
		if (board[i][col] != 0)
			return false;
	}
	return true;
}

bool find(vector<vector<int>> board,int row, int col, int h, int w) {
	int empty_cnt = 0;
	int block_num = -1; //같은 번호 블록 확인하기 위함.
	for (int r = row; r < row + h; r++) {
		for (int c = col; c < col + w; c++) {
			if (board[r][c] == 0)
				empty_cnt++;
			else {
				if (block_num == -1) {
					block_num = board[r][c];
				}
				else if(block_num != board[r][c]) {//구역안에 서로다른 블록존재
					return false;
				}
			}
			if (empty_cnt > 2)
				return false;
		}
	}
	return true;
}

void searchAndRegisterBlockPos(vector<vector<int>> board,int n) {
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++) {
			if (i <= n - 2 && j <= n - 3&&find(board,i,j,2,3)) {
				blocks.push_back(Block(i, j, 2, 3));
			}
			else if (i <= n - 3 && j <= n - 2 && find(board,i, j, 3, 2)) {
				blocks.push_back(Block(i, j, 3, 2));
			}
		}
	}
}
int solution(vector<vector<int>> board) {
	int answer = 0;
	searchAndRegisterBlockPos(board, board.size());

	cout << blocks.size() << endl;
	return answer;
}

int main() {
	vector<vector<int>> board = { {0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,4,0,0,0},{0,0,0,0,0,4,4,0,0,0},{0,0,0,0,3,0,4,0,0,0},{0,0,0,2,3,0,0,0,5,5},{1,2,2,2,3,3,0,0,0,5},{1,1,1,0,0,0,0,0,0,5} };
	cout << solution(board) << endl;
}