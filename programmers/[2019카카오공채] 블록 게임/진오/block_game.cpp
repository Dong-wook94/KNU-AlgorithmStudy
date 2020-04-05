//미완.. .ㅠ

#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct loca {
	int row;
	int col;
};

int solution();
vector <vector <int>> board;
void shoot_all_row();
int right_down_sero(int row, int col);
int right_up_sero(int row, int col);
int right_down_garo(int row, int col);
int right_up_garo(int row, int col);
int left_down_sero(int row, int col);
int left_down_garo(int row, int col);
int left_up_sero(int row, int col);
int left_up_garo(int row, int col);

int main() {
	
	vector <int>temp;
	
	int n;

	for (int i = 0; i < 10; i++) {
		cin >> n;
		temp.push_back(n);
	
		board.push_back(temp);
		for (int j = 1; j < 10; j++) {
			cin >> n;
			board[i].push_back(n);
		}
		temp.clear();
	}
	solution();
	return 0;
}
int solution() {
	int answer = 0;
	vector <loca> block;
	loca temp;
	int flag = 0;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j] > 0) {
				temp.row = i;
				temp.col = j;
				block.push_back(temp);
			}
		}
	}
	shoot_all_row();
	for (int i = 0; i < block.size(); i++) {
		//a.erase(a.begin()+i); 
		flag = 0;
		if (left_down_garo(block[i].row, block[i].col) > 0) { //직사각형일경우
			flag = 1;
		}
		if (left_down_sero(block[i].row, block[i].col) > 0) {
			flag = 1;
		}
		if (left_up_garo(block[i].row, block[i].col) > 0) {
			flag = 1;
		}
		if (left_up_sero(block[i].row, block[i].col) > 0) {
			flag = 1;
		}
		if (right_down_garo(block[i].row, block[i].col) > 0) {
			flag = 1;
		}
		if (right_down_sero(block[i].row, block[i].col) > 0) {
			flag = 1;
		}
		if (right_up_garo(block[i].row, block[i].col) > 0) {
			flag = 1;
		}
		if (right_up_sero(block[i].row, block[i].col) > 0) {
			flag = 1;
		}
		if (flag == 1) {
			int j = 0;
			temp = block[i];
			while (1) {
				if (j >= block.size())break;
				if (board[temp.row][temp.col] == board[block[j].row][block[j].col]) {
					block.erase(block.begin() + j);
				}
				else
					j++;
			}
		}
	}
	return answer;
}
int left_down_garo(int row,int col) {
	int value = board[row][col];
	int i, j;
	int row_dest = row + 2;
	int col_dest = col - 3;
	if (row_dest < -1 || row_dest > board.size() || col_dest < -1 || col_dest > board.size()) {
		return -1;
	}
	for (i= row; i < row_dest; i++) 
		for (j= col; j > col_dest; j--) 
			if (board[i][j] != value && board[i][j] != -1) 
				break;	
	if (i == row_dest && j == col_dest) 
		return 1; // 직사각형이에요
	
	else 
		return -1;// 이거 삐꾼데요?
}
int left_down_sero(int row, int col) {
	int value = board[row][col];
	int i, j;
	int row_dest = row + 3;
	int col_dest = col - 2;
	if (row_dest < -1 || row_dest > board.size() || col_dest < -1 || col_dest > board.size()) {
		return -1;
	}
	for (i = row; i < row_dest; i++)
		for (j = col; j > col_dest; j--)
			if (board[i][j] != value && board[i][j] != -1)
				break;
	if (i == row_dest && j == col_dest)
		return 1; // 직사각형이에요

	else
		return -1;// 이거 삐꾼데요?
}
int left_up_garo(int row, int col) {
	int value = board[row][col];
	int i, j;
	int row_dest = row -2;
	int col_dest = col -3;
	if (row_dest < -1 || row_dest > board.size() || col_dest < -1 || col_dest > board.size()) {
		return -1;
	}
	for (i = row; i > row_dest; i--)
		for (j = col; j > col_dest; j--)
			if (board[i][j] != value && board[i][j] != -1)
				break;
	if (i == row_dest && j == col_dest)
		return 1; // 직사각형이에요

	else
		return -1;// 이거 삐꾼데요?
}
int left_up_sero(int row, int col) {
	int value = board[row][col];
	int i, j;
	int row_dest = row - 3;
	int col_dest = col - 2;
	if (row_dest < -1 || row_dest > board.size() || col_dest < -1 || col_dest > board.size()) {
		return -1;
	}
	for (i = row; i > row_dest; i--)
		for (j = col; j > col_dest; j--)
			if (board[i][j] != value && board[i][j] != -1)
				break;
	if (i == row_dest && j == col_dest)
		return 1; // 직사각형이에요

	else
		return -1;// 이거 삐꾼데요?
}
int right_up_garo(int row, int col) {
	int value = board[row][col];
	int i, j;
	int row_dest = row - 2;
	int col_dest = col + 3;
	if (row_dest < -1 || row_dest > board.size() || col_dest < -1 || col_dest > board.size()) {
		return -1;
	}
	for (i = row; i > row_dest; i--)
		for (j = col; j < col_dest; j++)
			if (board[i][j] != value && board[i][j] != -1)
				break;
	if (i == row_dest && j == col_dest)
		return 1; // 직사각형이에요

	else
		return -1;// 이거 삐꾼데요?
}
int right_up_sero(int row, int col) {
	int value = board[row][col];
	int i, j;
	int row_dest = row - 3;
	int col_dest = col + 2;
	if (row_dest < -1 || row_dest > board.size() || col_dest < -1 || col_dest > board.size()) {
		return -1;
	}
	for (i = row; i > row_dest; i--)
		for (j = col; j < col_dest; j++)
			if (board[i][j] != value && board[i][j] != -1)
				break;
	if (i == row_dest && j == col_dest)
		return 1; // 직사각형이에요

	else
		return -1;// 이거 삐꾼데요?
}

int right_down_garo(int row, int col) {
	int value = board[row][col];
	int i, j;
	int row_dest = row + 2;
	int col_dest = col + 3;
	if (row_dest < -1 || row_dest > board.size() || col_dest < -1 || col_dest > board.size()) {
		return -1;
	}
	for (i = row; i < row_dest; i++)
		for (j = col; j < col_dest; j++)
			if (board[i][j] != value && board[i][j] != -1)
				break;
	if (i == row_dest && j == col_dest)
		return 1; // 직사각형이에요

	else
		return -1;// 이거 삐꾼데요?
}
int right_down_sero(int row, int col) {
	int value = board[row][col];
	int i, j;
	int row_dest = row + 3;
	int col_dest = col + 2;
	if (row_dest < -1 || row_dest > board.size() || col_dest < -1 || col_dest > board.size()) {
		return -1;
	}
	for (i = row; i < row_dest; i++)
		for (j = col; j < col_dest; j++)
			if (board[i][j] != value && board[i][j] != -1)
				break;
	if (i == row_dest && j == col_dest)
		return 1; // 직사각형이에요

	else
		return -1;// 이거 삐꾼데요?
}
void shoot_all_row() {
	int i = 0;
	for (int j = 0; j < board[0].size(); j++) {
		while (1) {
			if (i + 1 >= board.size())break;
			if (board[i + 1][j] < 0 || board[i + 1][j]>0)break;
			
			i++;
		}
		board[i][j] = -1;
		i = 0;
	}
}

//8가지 케이스 검사 통과 
//내생각엔 각 지금 block 위치별로 다 검사해야할 거 같은데 통과
//2번까지 전지역을 대상으로 내려버리고 
//없어지면 2번내린거 싹다 삭제 첫번째 에서 발견되면 그때도 싹다 삭제하고 원점
